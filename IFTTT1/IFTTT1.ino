
#include <ESP8266WiFi.h>

#define ledPin D8
#define wakePin D0
#define ssid "srihari-Lenovo-ideapad-320-15ISK"
#define password "tYTaLp7J"

const char* host = "maker.ifttt.com";     //IFTTT channel address

void connectWifi() {
  Serial.print("Connecting to: SSID NAME"); 
  Serial.print(ssid); 
  WiFi.begin(ssid, password);  
  Serial.println(" ");
  Serial.print("Attempting to connect: ");

  int i = 0;
  while(WiFi.status() != WL_CONNECTED && i <=10) {
    delay(1000);
    Serial.print(i);
    Serial.print(", ");
    i++;
  }
  Serial.println(" ");


  if(WiFi.status() == WL_CONNECTED){
    Serial.print("Connected."); 
    Serial.println(" ");
    Serial.print("NodeMCU ip address: "); 
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed - check  credentials");
  }
}


void setup() {
  Serial.begin(115200);
  while(!Serial) { 
  }
  Serial.println(" ");    
  Serial.println("Button Triggered");
  Serial.println(" ");

  connectWifi();

  WiFiClient client;
       const int httpPort = 80;
       if (!client.connect(host, httpPort)) {
        Serial.println("Weak Network");
       return;
       }
   
       String url = "/trigger/event1/with/key/eTFX8TUSkuIdd_pcp3VPjvEEeUPCMikZ5Ffm2jKJJ53";   //our link to trigger the event with special key and event name 
  
     
       client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  // GET request 
       
  




  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);   
  delay(200);              
  digitalWrite(ledPin, LOW); 
   system_deep_sleep_set_option(2);
   system_deep_sleep_instant(5000*1000);
   digitalWrite(D0,LOW);
   
}

void loop(){

}
