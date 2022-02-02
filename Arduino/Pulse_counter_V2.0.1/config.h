//****************************************************************************************************************/
//****************************************************************************************************************/
//******************** IMPORTANT SETTINGS - YOU MUST CHANGE CONFIGURE TO FIT YOUR HARDWARE ***********************/
//****************************************************************************************************************/
//****************************************************************************************************************/

//Hostname (useful for finding device for static lease)
const char* nodeName = "Relay Test";
const char* nodeLocationName = "Living";

bool oneWireRelay = false; 
bool wifiDebug = true;

//****************************************************************************************************************/
#define WifiMode   WIFI_STA   // STA
//#define WifiMode   WIFI_AP  // AP

// Enter your WiFi configuration below
const char* ssid      = "NameWiFi";  // Your router's SSID here
const char* password  = "PassWiFi";  // Your router's password here

// the media access control (ethernet hardware) address for the shield:
byte bssid[6] = {0x00, 0x26, 0x5E, 0x11, 0x41, 0x31};

byte wifichannel = 1;
//****************************************************************************************************************/
// parameters below are for your static IP address, if used network configuration. gateway and subnet are optional

bool dhcp = true;

//the IP address for the shield:
IPAddress staticIP(10, 42, 0, 5); 
// the router's gateway address:
IPAddress gateway(10, 42, 0, 1);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
// the default dns: (8.8.8.8) & (1.1.1.1)
IPAddress dns1(10, 42, 0, 1);
IPAddress dns2(1, 1, 1, 1);

//****************************************************************************************************************/
/// MQTT Server

bool mqttCheck = true;

const char* nodeTopic = "esp_test";

//the IP address for the mqtt server:
byte mqtt_server[] = {192, 168, 0, 250};
//the port for the mqtt server:
int mqtt_port = 1883;

unsigned int cycleTimePub = 30;

// *********************************************** END CONFIG ****************************************************/
//****************************************************************************************************************/
const char* nodeType    = "Pulse_Counter";
const char* nodeFW      = "V2.0.1";
//****************************************************************************************************************/
