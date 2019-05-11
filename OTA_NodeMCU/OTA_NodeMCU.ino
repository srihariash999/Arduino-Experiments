#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "srihari-Lenovo-ideapad-320-15ISK"
#define STAPSK  "tYTaLp7J"
#endif

#define ledPin D8
#define wakePin D0

const char* ssid = "srihari-Lenovo-ideapad-320-15ISK";
const char* password = "tYTaLp7J" ;
const char* host = "maker.ifttt.com";     //IFTTT channel address

void setup() {
  Serial.begin(115200);
  pinMode(D2,OUTPUT);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


pinMode(ledPin,OUTPUT); 


  
}



void trigbut()
{



  WiFiClient client;
       const int httpPort = 80;
       if (!client.connect(host, httpPort)) {
        Serial.println("Weak Network");
       return;
       }
   
       String url = "/trigger/event1/with/key/eTFX8TUSkuIdd_pcp3VPjvEEeUPCMikZ5Ffm2jKJJ53";   //our link to trigger the event with special key and event name 
  
     
       client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  // GET request 
       
  

  digitalWrite(ledPin, HIGH);   
  delay(2000);              
  digitalWrite(ledPin, LOW);   
  delay(2000);
  
}

void loop() {



  ArduinoOTA.handle();
  if(digitalRead(D0) == LOW)
  {
    trigbut();
  }
  digitalWrite(D8,HIGH);
  delay(100);
  digitalWrite(D8,LOW);
  delay(100);

}
