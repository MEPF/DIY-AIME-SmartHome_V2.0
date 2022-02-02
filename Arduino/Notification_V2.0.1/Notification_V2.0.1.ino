/****************************************************************************************************************/
/*                                              AIME - Smart Home DIY                                           */
/*                                                  Notification                                                */
/*                                                   02.02.2022                                                 */
/*                                               Power by M.Emanuel                                             */
/****************************************************************************************************************/

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include "html.h"
#include "config.h"

/****************************************************************************************************************/
/*  Globals                                                                                                     */
/****************************************************************************************************************/

#define input_pin 2
unsigned int lastMsg = 0;
bool input_trigger  = false;
bool readyDeepSleep = false;

ADC_MODE(ADC_VCC);

ESP8266WebServer webserver(80);
WiFiClient espClient;
PubSubClient client(espClient);


/****************************************************************************************************************/
/*  Connect / Reconnect MQTT                                                                                    */
/****************************************************************************************************************/

void connectMQTT()
{
  if (client.connect(nodeTopic)) 
  {
    const char* batteryStatus;
    if (modeBattery)
    {
      int batvcc = ESP.getVcc();
      if (batvcc <= 2800)
      { 
        batteryStatus = "Low"; 
      }
      else
      {
        batteryStatus = "Good";
      }
    }
    else
    {
      batteryStatus = "None";
    }

    char attributes[255];
    if (modeBattery)
    {
      sprintf(attributes, "{\"NoN\":\"%s\",\"NoL\":\"%s\",\"Typ\":\"%s\",\"Bat\":\"%s\",\"CTPub\":\"%d\",\"RSSI\":\"%d\",\"IP\":\"%s\",\"FW\":\"%s\",\"ParV\":{\"1\":\"%d\"}}", nodeName, nodeLocationName, nodeType, batteryStatus, cycleTimePub, WiFi.RSSI(), WiFi.localIP().toString().c_str(), nodeFW, 1);
      lastMsg = millis();    
    }
    else if (digitalRead(input_pin) == LOW)
    {
      sprintf(attributes, "{\"NoN\":\"%s\",\"NoL\":\"%s\",\"Typ\":\"%s\",\"Bat\":\"%s\",\"CTPub\":\"%d\",\"RSSI\":\"%d\",\"IP\":\"%s\",\"FW\":\"%s\",\"ParV\":{\"1\":\"%d\"}}", nodeName, nodeLocationName, nodeType, batteryStatus, cycleTimePub, WiFi.RSSI(), WiFi.localIP().toString().c_str(), nodeFW, 1);
      lastMsg = millis();
    }
    else
    {
      sprintf(attributes, "{\"NoN\":\"%s\",\"NoL\":\"%s\",\"Typ\":\"%s\",\"Bat\":\"%s\",\"CTPub\":\"%d\",\"RSSI\":\"%d\",\"IP\":\"%s\",\"FW\":\"%s\",\"ParV\":{\"1\":\"%d\"}}", nodeName, nodeLocationName, nodeType, batteryStatus, cycleTimePub, WiFi.RSSI(), WiFi.localIP().toString().c_str(), nodeFW, 0);
      lastMsg = millis();
    }
    
    client.publish(nodeTopic, attributes);
    Serial.print("Publish to MQTT Server: "); Serial.println(attributes);

    if (client.endPublish() & modeBattery)
    {
      readyDeepSleep = true;
      lastMsg = millis();  
    }

    char topic[50];
    sprintf(topic, "%s/command", nodeTopic);
    client.subscribe(topic);
  } 
  else 
  {
    if (modeBattery)
    {
      Serial.print("Failed to connection with MQTT server, rc=");
      Serial.print(client.state());
      Serial.println(" go to deep sleep mode!");
      
      ESP.deepSleep(0);
    }

    else
    {
      Serial.print("Failed to connection with MQTT server, rc=");
      Serial.print(client.state());
      Serial.print(" it is tried again in "); Serial.print(cycleTimePub); Serial.println(" seconds");
      
      lastMsg = millis();
    }
  }
}


/****************************************************************************************************************/
/*  Call back MQTT                                                                                              */
/****************************************************************************************************************/

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) 
  {
    if (data.charAt(i) == separator || i == maxIndex) 
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
  
void callback(char* topic, byte* payload, unsigned int length) 
{
  String strTopic = String((char*)topic);
  char cTopic[50];
  sprintf(cTopic, "%s/command", nodeTopic);
  String cstrTopic = cTopic;
      
  if(strTopic == cstrTopic)
  {
    char buff_p[length];
    buff_p[length] = '\0';
    for (unsigned int i = 0; i < length; i++)
    {
      buff_p[i] = (char)payload[i];
    }
  
    String action_msg = getValue(buff_p, ':', 0);

    if (action_msg == "StopDeepSleep")
    {
      readyDeepSleep = false;
      Serial.println("DeepSleep mode is disabled");
    }
    else if (action_msg == "RebootNode")
    {
      Serial.println("Reboot..");
      ESP.restart();
    }
    else
    {
      Serial.print("Message arrived [");
      for (unsigned int i = 0; i < length; i++) 
      {
        Serial.print((char)payload[i]);
      }
      Serial.println("]");
    }
  }
}


/****************************************************************************************************************/
/* Pages HTML                                                                                                   */
/****************************************************************************************************************/
void handleRoot() {
  if (digitalRead(input_pin) == LOW) 
  {
    input_trigger = true;
  }
  else 
  {
    input_trigger = false;
  }
  webserver.send(200, "text/html", htmlNotification(input_trigger, nodeName));
}
/****************************************************************************************************************/
void handleNotFound() 
{
  webserver.send(404, "text/html", html404);
}


/****************************************************************************************************************/
/* Main - Setup                                                                                                 */
/****************************************************************************************************************/
void setup() 
{
  Serial.begin(115200);
  while (!Serial) 
  {
    delay(1);
  }
  Serial.println('\n');
  Serial.println("Node start setup...");
  Serial.println('\n');
/***************************************************************************************************************** Pin GPIO 2 Status */
  pinMode(input_pin, INPUT_PULLUP);
/***************************************************************************************************************** Start wifi */
  WiFi.mode(WifiMode);
  WiFi.hostname(nodeName);

  if (WifiMode == WIFI_STA)
  {
    if (dhcp)
    {
      WiFi.begin(ssid, password);
    }
    else
    {
      WiFi.config(staticIP, gateway, subnet, dns1, dns2);
      WiFi.begin(ssid, password, wifichannel, bssid, true);
    }
    
    while (WiFi.waitForConnectResult() != WL_CONNECTED) 
    {
      Serial.print("Connection failed, ");
  
      if (modeBattery)
      {
        Serial.println("go to deep sleep mode!");
        ESP.deepSleep(0);
      }
      else
      {
        Serial.println("rebooting in 60 sec!");
        delay(60000);
        WiFi.disconnect();
        ESP.restart();
      }
    }
    
    if (wifiDebug)
    {
      Serial.println();
      Serial.print("Access point MAC address: ");
      Serial.println(WiFi.BSSIDstr());
      Serial.print("Device IP gateway: ");
      Serial.println(WiFi.gatewayIP());
      Serial.print("Device IP netmask : ");
      Serial.println(WiFi.subnetMask());
      Serial.print("Device IP DNS : ");
      Serial.println(WiFi.dnsIP());
      
      Serial.println();
      WiFi.printDiag(Serial);
      Serial.println();
  
      Serial.print("Device IP address: ");
      Serial.println(WiFi.localIP());
      Serial.print("Device MAC address: ");
      Serial.println(WiFi.macAddress());
      Serial.print("Signal: ");
      Serial.print(WiFi.RSSI());
      Serial.println(" dBm");
      Serial.println();
    }
  }
  else
  {
    WiFi.softAP(ssid, password);
  }
/***************************************************************************************************************** Wifi firmware upgrade */
  ArduinoOTA.setHostname(nodeName);
  ArduinoOTA.begin();
  /*************************************************************************************************************** HTML Server */
  webserver.on("/", handleRoot);
  webserver.onNotFound(handleNotFound);
  
  webserver.begin();
 /****************************************************************************************************************/
  Serial.println("Boot completed - device is ready");
  Serial.println('\n');
  /*************************************************************************************************************** MQTT - Config */
  if (mqttCheck && WifiMode == WIFI_STA)
  {
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    delay(50);
    connectMQTT();
  }
}


/****************************************************************************************************************/
/* MAIN - Loop                                                                                                  */
/****************************************************************************************************************/
void loop() {
  if (client.connected() && WifiMode == WIFI_STA)
  {
    client.loop();
  }
/****************************************************************************************************************/
  if (readyDeepSleep && WifiMode == WIFI_STA)
  {
    if (millis() - lastMsg > 1000)
    {
      Serial.println("Battery mode is set, I'm going into deep sleep mode!");
      
      ESP.deepSleep(0);
    }
  }
  
/****************************************************************************************************************/
  ArduinoOTA.handle();
/****************************************************************************************************************/
  webserver.handleClient();
/****************************************************************************************************************/
  if (mqttCheck && !readyDeepSleep && WifiMode == WIFI_STA)
  {
    if (millis() - lastMsg > (cycleTimePub * 1000))
    {
      connectMQTT();
    }
  }
/****************************************************************************************************************/
}
