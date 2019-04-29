#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
const char* ssid = "Redmi4";            
const char* password = "namaste99";
 
void setup () {
 
Serial.begin(115200);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);



 
}
 
void loop() {

  
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

HTTPClient http;  //Declare an object of class HTTPClient
 
initialdisp();

getTime();
getDate();
getTemp();
getHumidity();


delay(1000);


 
}  }



void initialdisp()
{
     display.clearDisplay();
    display.setCursor(0,0);
  display.print("Time:");
    display.setCursor(0,10);
  display.print("Date:");
  
  display.setCursor(0,20);
  display.print("Temperature:");
    display.setCursor(0,30);
  display.print("Humidity:");
  display.display();
 
}


void getTime()
{
  
HTTPClient http;  //Declare an object of class HTTPClient
http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=18OGDYOI5VV43ED8");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
String samay = http.getString();   //Get the request response payload

samay.trim();

Serial.println(samay);

  display.setCursor(30,0);
  display.print(samay);
  display.display();

 
}
 
http.end();   //Close connection
}



void getDate()
{
  
HTTPClient http;  //Declare an object of class HTTPClient
http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=N5PHULW23L6CBDNT");  //Specify request destination
int httpCode3 = http.GET();                                                                  //Send the request
 
if (httpCode3 > 0) { //Check the returning code
 
String date = http.getString();   //Get the request response payload

date.trim();

Serial.println(date);

  display.setCursor(30,10);
  display.print(date);
  display.print(" 2019");
  display.display();

 
}
 
http.end();   //Close connection
}



void getTemp()
{
  

HTTPClient http;  //Declare an object of class HTTPClient
http.begin("  http://api.thingspeak.com/apps/thinghttp/send_request?api_key=HS4YKJTJZ9UFNIM8");  //Specify request destination
int httpCode2 = http.GET();                                                                  //Send the request
 
if (httpCode2 > 0) { //Check the returning code
 
String temp = http.getString();   //Get the request response payload
Serial.println(temp);
temp.trim();


  display.setCursor(74,20);
  display.print(temp);
  display.display();

 
}
 
http.end();   //Close connection


}


void getHumidity()
{
  
HTTPClient http;  //Declare an object of class HTTPClient
http.begin("  http://api.thingspeak.com/apps/thinghttp/send_request?api_key=POW6KDE9LB35A1A6");  //Specify request destination
int httpCode1 = http.GET();                                                                  //Send the request
 
if (httpCode1 > 0) { //Check the returning code
 
String humidity = http.getString();   //Get the request response payload
Serial.println(humidity);
humidity.trim();

  display.setCursor(55,30);
  display.print(humidity);
  display.display();

 
}
 
http.end();   //Close connection
}
