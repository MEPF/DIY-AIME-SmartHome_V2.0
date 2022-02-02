/****************************************************************************************************************/
/*                                              AIME - Smart Home DIY                                           */
/*                                                     RELEY                                                    */
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

#define relay_pin 0
unsigned int lastMsg = 0;

ESP8266WebServer webserver(80);
WiFiClient espClient;
PubSubClient client(espClient);

/****************************************************************************************************************/
/* EEPROM                                                                                                       */
/****************************************************************************************************************/

//EEPROM cleaning command
void clearEEPROM() 
{
  EEPROM.begin(64);delay(10);  // EEPROM size 64 bytes
  for (unsigned int i = 0; i < EEPROM.length(); i++) 
  {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

//startAdr: offset (bytes), maxLength: max length (bytes), writeValue: String to be written to EEPROM
void writeEEPROM(unsigned int startAdr, unsigned int maxLength, String writeValue) 
{
  EEPROM.begin(64);delay(10); // Max bytes of eeprom to use
  //Write to eeprom
  for (unsigned int i = 0; i < maxLength; i++)
    {
      EEPROM.write(startAdr + i, writeValue[i]);
    }
  EEPROM.commit();          
}

//startAdr: offset (bytes), endAdr: max length (bytes), buffer: String to be read from EEPROM
String readEEPROM(unsigned int startAdr, unsigned int maxLength) 
{
  EEPROM.begin(64);delay(10);String buffer;
  for (unsigned int i = startAdr; i < maxLength; i++)
    {
      buffer += char(EEPROM.read(i));
    }
  return buffer;
}


/****************************************************************************************************************/
/*  Connect / Reconnect MQTT                                                                                    */
/****************************************************************************************************************/

void connectMQTT() 
{
  if (client.connect(nodeTopic)) 
  {
    char attributes[255];
    sprintf(attributes, "{\"NoN\":\"%s\",\"NoL\":\"%s\",\"Typ\":\"%s\",\"Bat\":\"%s\",\"CTPub\":\"%d\",\"RSSI\":\"%d\",\"IP\":\"%s\",\"FW\":\"%s\",\"ParV\":{\"1\":\"%d\"}}", nodeName, nodeLocationName, nodeType, "None", cycleTimePub, WiFi.RSSI(), WiFi.localIP().toString().c_str(), nodeFW, readEEPROM(0, 1).toInt());
    
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

    String relayStatus = readEEPROM(0, 1).c_str();
    String action_msg = getValue(buff_p, ':', 0);

    if ((action_msg == "1") & (relayStatus != "1"))
    {
      Serial.print("Message arrived [");
      for (unsigned int i = 0; i < length; i++) 
      {
        Serial.print((char)payload[i]);
      }
      Serial.print("] ");
      Serial.println(" - Switch to CLOSE");
     
      writeEEPROM(0, 1, "1"); digitalWrite(relay_pin, HIGH); digitalWrite(LED_BUILTIN, HIGH);
    }
    else if ((action_msg == "0") & (relayStatus != "0"))
    {
      Serial.print("Message arrived [");
      for (unsigned int i = 0; i < length; i++) 
      {
        Serial.print((char)payload[i]);
      }
      Serial.print("] ");
      Serial.println(" - Switch to OPEN");
     
      writeEEPROM(0, 1, "0"); digitalWrite(relay_pin, LOW); digitalWrite(LED_BUILTIN, LOW);
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
void handleRoot() 
{
  if(webserver.arg("relay") == "Close") 
  {
    Serial.println("Relay - Close");
    writeEEPROM(0, 1, "1"); digitalWrite(relay_pin, HIGH); digitalWrite(LED_BUILTIN, HIGH);

    webserver.send(200, "text/html", htmlRelay(readEEPROM(0, 1).c_str(), nodeName));
  }
  else if(webserver.arg("relay") == "Open")
  {
    Serial.println("Relay - Open");
    writeEEPROM(0, 1, "0"); digitalWrite(relay_pin, LOW); digitalWrite(LED_BUILTIN, LOW);

    webserver.send(200, "text/html", htmlRelay(readEEPROM(0, 1).c_str(), nodeName));
  }
  else
  {
    webserver.send(200, "text/html", htmlRelay(readEEPROM(0, 1).c_str(), nodeName));
  }
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
/***************************************************************************************************************** Relay Status - Config */
  pinMode(LED_BUILTIN, OUTPUT); pinMode(relay_pin, OUTPUT); digitalWrite(relay_pin, LOW);
/***************************************************************************************************************** Relay Status - Change relay status on restart */
  int relayStatus = readEEPROM(0, 1).toInt();

  if ((relayStatus == 1) & oneWireRelay)
  {
    writeEEPROM(0, 1, "0"); digitalWrite(relay_pin, LOW); digitalWrite(LED_BUILTIN, LOW);
  }
    
  else if ((relayStatus == 0) & oneWireRelay)
  {
    writeEEPROM(0, 1, "1"); digitalWrite(relay_pin, HIGH); digitalWrite(LED_BUILTIN, HIGH);
  }
  
  else
  {
    if (relayStatus == 1)
    {
      digitalWrite(relay_pin, HIGH); digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
      digitalWrite(relay_pin, LOW); digitalWrite(LED_BUILTIN, LOW);
    }
  }
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
      Serial.println("Connection failed, rebooting in 60 sec!");
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
  if (mqttCheck && WifiMode == WIFI_STA) {
    if (millis() - lastMsg > (cycleTimePub * 1000))
    {
      connectMQTT();
    }
  }
/****************************************************************************************************************/
}

/****************************************************************************************************************/
/*https://github.com/doleron/esp8266-1-channel-relay-board-with-mqtt                                            */
/*byte close[] = {0xA0, 0x01, 0x01, 0xA2};                                                                      */
/*Serial.write(close, sizeof(close));                                                                           */
/*delay(2000);                                                                                                  */
/*                                                                                                              */
/*byte open[] = {0xA0, 0x01, 0x00, 0xA1};                                                                       */
/*Serial.write(open, sizeof(open));                                                                             */
/*delay(2000);                                                                                                  */
/****************************************************************************************************************/
