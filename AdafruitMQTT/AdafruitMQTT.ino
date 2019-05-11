
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"



#define WLAN_SSID       "Redmi4"
#define WLAN_PASS       "namaste99"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "srihariash"
#define AIO_KEY         "c640fbb3668c44ddbfd945347aa40170"


#define LED LED_BUILTIN

/************ Global State ******************/


WiFiClient client;



Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);






/****************************** Feeds ***************************************/





Adafruit_MQTT_Subscribe livingroomlight = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/livingroomlight");
Adafruit_MQTT_Subscribe bedroomlight = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/bedroomlight");












/*************************** Sketch Code ************************************/




void MQTT_connect();

void setup() {

  pinMode(D4,OUTPUT);
   pinMode(D5,OUTPUT);
   pinMode(LED,OUTPUT);

  Serial.begin(115200);
  delay(10);


  Serial.println(); Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());


  mqtt.subscribe(&bedroomlight);
  mqtt.subscribe(&livingroomlight);

}


void loop() {

  MQTT_connect();



  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(5000))) {


    if (subscription == &bedroomlight) {
      Serial.print(F("Bed room light: "));
      Serial.println((char *)bedroomlight.lastread);
      
      if (strcmp((char *)bedroomlight.lastread, "On") == 0) {
        digitalWrite(LED, LOW);
        digitalWrite(D4,LOW); 
      }
      if (strcmp((char *)bedroomlight.lastread, "Off") == 0) {
        digitalWrite(LED, HIGH); 
        digitalWrite(D4,HIGH);
      }
    }


    if (subscription == &livingroomlight) {
      Serial.print(F("Living room light: "));
      Serial.println((char *)livingroomlight.lastread);
      
      if (strcmp((char *)livingroomlight.lastread, "ON") == 0) {

        digitalWrite(D5,LOW); 
      }
      if (strcmp((char *)livingroomlight.lastread, "OFF") == 0) {
      
        digitalWrite(D5,HIGH);
      }
    }
    

  
  
  }

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

}


void MQTT_connect() {
  int8_t ret;


  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
