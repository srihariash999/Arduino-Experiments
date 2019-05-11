#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>


const char* ssid = "Redmi4";
const char* password = "namaste99";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const char* outTopic = "poopy";
const char* inTopic = "peepee";


void setup_wifi() {
  // Connect to WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}




void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  
  if ((char)payload[0] == '0') {
    
    Serial.println("relay_pin -> LOW");
  } 

    if ((char)payload[0] == '1') {
    
    Serial.println("relay_pin -> HIGH");
  } 
  
  }

char p = '9';
void setup() {

   pinMode(D2,OUTPUT);
  digitalWrite(D2, LOW);          // Blink to indicate setup
  delay(500);
  digitalWrite(D2, HIGH);
  delay(500);
  
  Serial.begin(115200);
  setup_wifi();                   // Connect to wifi 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
  
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    
      Serial.println("msg sent");
      client.subscribe(inTopic);
    } 
    
  
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      }

        delay(3000);
    }
  }
