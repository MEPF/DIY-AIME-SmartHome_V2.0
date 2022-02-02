/****************************************************************************************************************/
/*                                              AIME - Smart Home DIY                                           */
/*                                                  PZEM-004T V3                                                */
/*                                                   02.02.2022                                                 */
/*                                               Power by M.Emanuel                                             */
/****************************************************************************************************************/

// https://innovatorsguru.com/pzem-004t-v3/

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include "html.h"
#include "config.h"

/****************************************************************************************************************/
/*  Globals                                                                                                     */
/****************************************************************************************************************/

SoftwareSerial pzemSWSerial(3,1);
PZEM004Tv30 pzem;

unsigned int lastMsg = 0;

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
    char attributes[255];
    sprintf(attributes, "{\"NoN\":\"%s\",\"NoL\":\"%s\",\"Typ\":\"%s\",\"Bat\":\"%s\",\"CTPub\":\"%d\",\"RSSI\":\"%d\",\"IP\":\"%s\",\"FW\":\"%s\",\"ParV\":{\"1\":\"%.2f\",\"2\":\"%.2f\",\"3\":\"%.2f\",\"4\":\"%.2f\",\"5\":\"%.2f\",\"6\":\"%.2f\"}}", nodeName, nodeLocationName, nodeType, "None", cycleTimePub, WiFi.RSSI(), WiFi.localIP().toString().c_str(), nodeFW, pzem.voltage(), pzem.current(), pzem.power(), pzem.energy(), pzem.frequency(), pzem.pf());
    
    lastMsg = millis();
    client.publish(nodeTopic, attributes);
    Serial.print("Publish to MQTT Server: "); Serial.println(attributes);

    char topic[50];
    sprintf(topic, "%s/command", nodeTopic);
    client.subscribe(topic);
  } 
  else 
  {
    Serial.print("Failed to connection with MQTT server, rc=");
    Serial.print(client.state());
    Serial.print(" it is tried again in "); Serial.print(cycleTimePub); Serial.println(" seconds");
      
    lastMsg = millis();
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

    if (action_msg == "RebootNode")
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
void handleRoot() 
{
  float pzem_voltage = pzem.voltage();
  float pzem_current = pzem.current();
  float pzem_power = pzem.power();
  float pzem_energy = pzem.energy();
  float pzem_frequency = pzem.frequency();
  float pzem_pf = pzem.pf();

  webserver.send(200, "text/html", htmlTH(pzem_voltage, pzem_current,pzem_power,pzem_energy,pzem_frequency, pzem_pf, nodeName));
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
/****************************************************************************************************************/
  pzem = PZEM004Tv30(pzemSWSerial);
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
      Serial.println("rebooting in 60 sec!");
      delay(60000);
      WiFi.disconnect();
      ESP.restart();
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
  /***************************************************************************************************************** MQTT - Config */
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
void loop()
{
  if (client.connected() && WifiMode == WIFI_STA)
  {
    client.loop();
  }
/****************************************************************************************************************/
  ArduinoOTA.handle();
/****************************************************************************************************************/
  webserver.handleClient();
/****************************************************************************************************************/
  if (mqttCheck && WifiMode == WIFI_STA) 
  {
    if (millis() - lastMsg > (cycleTimePub * 1000))
    {
      connectMQTT();
    }
  }
/****************************************************************************************************************/
}
