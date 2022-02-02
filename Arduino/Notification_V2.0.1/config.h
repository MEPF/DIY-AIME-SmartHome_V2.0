//****************************************************************************************************************/
//****************************************************************************************************************/
//******************** IMPORTANT SETTINGS - YOU MUST CHANGE CONFIGURE TO FIT YOUR HARDWARE ***********************/
//****************************************************************************************************************/
//****************************************************************************************************************/

//Hostname (useful for finding device for static lease)
const char* nodeName    = "Front Door";
const char* nodeLocationName = "Hall";

bool modeBattery = true; 
bool wifiDebug = false;

//****************************************************************************************************************/
#define WifiMode   WIFI_STA   // STA
//#define WifiMode   WIFI_AP  // AP

// Enter your WiFi configuration below
const char* ssid      = "NameWiFi";  // Your router's SSID here
const char* password  = "PassWiFi";  // Your router's password here

// the media access control (ethernet hardware) address for the shield:
byte bssid[6] = {0xC4, 0x6E, 0x1F, 0x87, 0xCC, 0xCE};

byte wifichannel = 10;
//****************************************************************************************************************/
// parameters below are for your static IP address, if used network configuration. gateway and subnet are optional

bool dhcp = false;

//the IP address for the shield:
IPAddress staticIP(192, 168, 0, 210);
// the router's gateway address:
IPAddress gateway(192, 168, 0, 1);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
// the default dns: (8.8.8.8) & (8.8.4.4)
IPAddress dns1(8, 8, 8, 8);
IPAddress dns2(8, 8, 4, 4);

//****************************************************************************************************************/
/// MQTT Server

bool mqttCheck = true;

const char* nodeTopic = "front_door";

//the IP address for the mqtt server:
byte mqtt_server[] = {192, 168, 0, 250};
//the port for the mqtt server:
int mqtt_port = 1883;

unsigned int cycleTimePub = 10;

//************************************************ END CONFIG ****************************************************/
//****************************************************************************************************************/
const char* nodeType    = "Notification";
const char* nodeFW      = "V2.0.1";
//****************************************************************************************************************/
