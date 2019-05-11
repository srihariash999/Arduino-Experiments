

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Bounce2.h>
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

int relay_pin = D2;
int button_pin = D6;
bool relayState = LOW;

// Instantiate a Bounce object :
Bounce debouncer = Bounce(); 


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    extButton();
    for(int i = 0; i<500; i++){
      extButton();
      delay(1);
    }
    Serial.print(".");
  }
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
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

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    digitalWrite(relay_pin, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.println("relay_pin -> LOW");
    relayState = LOW;
    EEPROM.write(0, relayState);    // Write state to EEPROM
    EEPROM.commit();
  } else if ((char)payload[0] == '1') {
    digitalWrite(relay_pin, HIGH);  // Turn the LED off by making the voltage HIGH
    Serial.println("relay_pin -> HIGH");
    relayState = HIGH;
    EEPROM.write(0, relayState);    // Write state to EEPROM
    EEPROM.commit();
  } else if ((char)payload[0] == '2') {
    relayState = !relayState;
    digitalWrite(relay_pin, relayState);  // Turn the LED off by making the voltage HIGH
    Serial.print("relay_pin -> switched to ");
    Serial.println(relayState); 
    EEPROM.write(0, relayState);    // Write state to EEPROM
    EEPROM.commit();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
   
      // ... and resubscribe
      if(digitalRead(D6 == 1))
      {
           client.publish(outTopic, "State is High");
      }

      if(digitalRead(D6 == 0))
      {
           client.publish(outTopic, "State is LOW");
      }
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      for(int i = 0; i<5000; i++){
        extButton();
        delay(1);
      }
    }
  }
}

void extButton() {
  debouncer.update();
   
   // Call code if Bounce fell (transition from HIGH to LOW) :
   if ( debouncer.fell() ) {
     Serial.println("Debouncer fell");
     // Toggle relay state :
     relayState = !relayState;
     digitalWrite(relay_pin,relayState);
     EEPROM.write(0, relayState);    // Write state to EEPROM
     if (relayState == 1){
      client.publish(outTopic, "The state is 1");
      Serial.println("Publishinng 1");
     }
     else if (relayState == 0){
      client.publish(outTopic, "0");
     }
   }
}

void setup() {
  EEPROM.begin(512);              // Begin eeprom to store on/off state
  pinMode(relay_pin, OUTPUT);     // Initialize the relay pin as an output
  pinMode(button_pin, INPUT);     // Initialize the relay pin as an output
  pinMode(13, OUTPUT);
  relayState = EEPROM.read(0);
  digitalWrite(relay_pin,relayState);
  
  debouncer.attach(button_pin);   // Use the bounce2 library to debounce the built in button
  debouncer.interval(50);         // Input must be low for 50 ms
  
  digitalWrite(13, LOW);          // Blink to indicate setup
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  
  Serial.begin(115200);
  setup_wifi();                   // Connect to wifi 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
    extButton();
  }
  extButton();
  client.loop();
 
}
