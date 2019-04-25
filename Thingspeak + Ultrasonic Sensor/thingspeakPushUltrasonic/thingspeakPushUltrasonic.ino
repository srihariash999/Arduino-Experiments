#include <ThingSpeak.h>
#include <ESP8266WiFi.h>


/*
////////////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/////////////////////////////////////


 --> Change the SSID, Password with your WiFi credentials.
 --> Change the API key with your 'Write API' from thingspeak channel.


Connections :

Trig -------> D2
Echo -------> D3

VCC -----> 3v3 
GND -----> GND 



*NOTE*: If The above connections doesn't work, try this :-


Trig -------> D2
Echo -------> D3
Connect VCC -----> 5v of arduino.
connect GND -----> GND of arduino.
Connect GND of Arduino ---> GND of NodeMCU

Plug in both arduino and nodemcu.



*NOTE*: If The both of the above connections doesn't work, try this :-


Trig -------> D2
Echo -------> D3
Connect VCC -----> 5v of arduino.
connect GND -----> GND of arduino.
Connect Vin of NodeMCU to 3v3 of Arduino
Connect GND of Arduino ---> GND of NodeMCU

Plug in arduino  only.




////////////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/////////////////////////////////////
*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////

String apiKey = "*******"; //API key from ThingSpeak channel
const char* ssid = "Your Wifi name"; //SSID of your wifi
const char* password = "Your Wifi pswd"; //password of your wifi
int duration = 5;
////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* server = "api.thingspeak.com";

const int trigPin = D2;
const int echoPin = D3;

float dur;
int distance;




WiFiClient client; //Start clinet

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

dur = pulseIn(echoPin, HIGH);

distance= dur*0.034/2;



  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(distance);
    postStr += "\r\n\r\n";

    //Uplad the postSting with temperature and Humidity information every
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("% send to Thingspeak");
  }
  client.stop();

  Serial.println("Waiting…");
  // thingspeak needs minimum 15 sec delay between updates
    // thingspeak needs minimum 15 sec delay between updates
  delay(duration*1000);
}
