#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library
#include <TouchScreen.h>
// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

SWTFT tft;

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define DEBUG true

/*********************************************************************************************************************************************************************************************
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                                     TFT Module necessary decelarations end here                                                                          */

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*********************************************************************************************************************************************************************************************/



/**********************  WiFi SSID Name and Password **************************/

String Host_name = "Name";
String password = "Password";



/********************** Functions to be performed when touched Button on the screen ****************************/

void RESET();
void Buttons();

String Gold_ABAD();   // live gold rate of Gujarat
String TEMP_ABAD();  // live Temperature in Ahmedabad
String Views();     // My video's views ( DIY Heart Beat Sensor))
String Time();      // live Time in India


void setup(void) {
  Serial.begin(115200);
  Serial1.begin(115200);
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  Buttons();  // Caliing the buttons.
}

void loop(void) {

  TSPoint p = ts.getPoint();   //
  pinMode(XP, OUTPUT);         //   For getting the coodinates 
  pinMode(XM, OUTPUT);         //   when we touch on the screen.
  pinMode(YP, OUTPUT);         //
  pinMode(YM, OUTPUT);         //

  
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)    // if touched
  {  
    int X = map(p.y, 912, 110, tft.height(), 0);   
    int Y = map(p.x, 90, 913, tft.width(), 0);   
  
    if (DEBUG)
    {
      Serial.print("X = "); Serial.print(X);
      Serial.print("\tY = "); Serial.print(Y);
      Serial.print("\tPressure = "); Serial.println(p.z);
    }

    if (X < 320 && X > 226 && Y < 129 && Y > 82)   //--------------------------------------------------------RESET button 
    {
      if (DEBUG)
        Serial.println("RESET");
        RESET();
    }
    
    if (X < 202 && X > 100 && Y < 129 && Y > 82)   //------------------------------------------------------  Gold button
    {
      tft.fillRect(0, 0, 320, 120, BLACK);
    
      if (DEBUG)
      Serial.println("Gold");
      
      tft.setCursor(0, 0);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
  
      if (DEBUG)
      tft.println( "Fetching data");
     
      tft.setCursor(0, 0);
      tft.println( Gold_ABAD());
    }

    
    if (X < 82 && X > 11 && Y < 129 && Y > 82)  //------------------------------------------------------ Temperature Button
    {
      tft.fillRect(0, 0, 320, 120, BLACK);
     
      if (DEBUG)
      Serial.println("TEMP");
      
      tft.setCursor(0, 0);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.println( "Fetching data");
      tft.setCursor(0, 0);
      tft.println( TEMP_ABAD());
      tft.setCursor(40, 0);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.println( "deg C");
    }


    if (X < 320 && X > 226 && Y < 175 && Y > 140)  //------------------------------------------------------ Views Button
    {

      tft.fillRect(0, 0, 320, 120, BLACK);
      
      if (DEBUG)
      Serial.println("Views");
    
      tft.setCursor(0, 0);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.println( "Fetching data");
      tft.setCursor(0, 0);
      tft.println( Views());

    }


    if (X < 202 && X > 100 && Y < 175 && Y > 140)//------------------------------------------------------ Time
    {

     tft.fillRect(0, 0, 320, 120, BLACK);
      
      if (DEBUG)
      Serial.println("Time");
    
      tft.setCursor(0, 0);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.println( "Fetching data");
      tft.setCursor(0, 0);
      tft.println( Time());
    
    }
    
  }
}



void RESET()
{
  //Disconnecting previous networks
  tft.fillScreen(BLACK);
  tft.fillScreen(BLACK);
  tft.setCursor(40, 120);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Resetting");
  sendData("AT+RST\r\n", 2000, DEBUG);
  sendData("AT+CWQAP\r\n", 5000, DEBUG); // Disconnect WiFi if connected.

  //Selecting Mode for WiFi
  tft.fillScreen(BLACK);
  tft.fillScreen(BLACK);
  tft.setCursor(70, 120);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Mode=3");
  sendData("AT+CWMODE=3\r\n", 1000, DEBUG); // configure as  both access point and station mode.

  

  //Searching for the wifi Connecrions.
  tft.fillScreen(BLACK);
  tft.fillScreen(BLACK);
  tft.setCursor(70, 80);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Searching");
  tft.setCursor(50, 120);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("WiFi Networks");
  char inv = '"';
  delay(3000);
  
  sendData("AT+CWQAP\r\n", 4000, DEBUG); // again quit the connection if any.
  
  
  String conn = "AT+CWJAP";
  conn += "=";
  conn += inv;
  conn += Host_name;  // Host name
  conn += inv;
  conn += ",";
  conn += inv;
  conn += password; // Password
  conn += inv;
  conn += "\r\n\r\n";
  sendData(conn, 7000, DEBUG); // Join the connection.( AT+CWJAP = "Host_name","password" )

  
  
  tft.fillScreen(BLACK);
  tft.fillScreen(BLACK);
  tft.setCursor(70, 120);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Connected");
  
  
  Buttons();  // again calling buttons.

}


void Buttons()
{
  tft.fillScreen(BLACK);
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(10, 140);
  tft.fillRect(0, 120, 80, 50, YELLOW);
  tft.println("RESET");

  tft.setCursor(100, 140);
  tft.fillRect(90, 120, 80, 50, YELLOW);
  tft.println("Gold");

  tft.setCursor(190, 140);
  tft.fillRect(180, 120, 80, 50, YELLOW);
  tft.println("TEMP");

  tft.setCursor(10, 200);
  tft.fillRect(0, 180, 80, 50, YELLOW);
  tft.println("Views");

  tft.setCursor(100, 200);
  tft.fillRect(90, 180, 80, 50, YELLOW);
  tft.println("Time");
  
}

String Views()
{
  char inv = '"';
  String add = "AT+CIPSTART";
  add += "=";
  add += inv;
  add += "TCP";
  add += inv;
  add += ",";
  add += inv;
  add += "api.thingspeak.com";  // Host_server_name
  add += inv;
  add += ",";
  add += "80";
  add += "\r\n";
  sendData(add, 3000, 0);  // Establishing a TCP Connection. ( AT+CIPSTART = "TCP","Host_server_name",80 )

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, 2000, 0); //Number of characters to send. ( "AT+CIPSEND=90" )


  String hostt = "GET /apps/thinghttp/send_request?api_key=X414S48DGHDD45GN";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String views = sendData(hostt, 2000, 0);  // GET request ( GET /apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXXX 
                                            //               Host: Host_server_name ) 
  
  
/********************** Steps To filter the received data. ****************************/
 
  int i = 0;        
  if (DEBUG)
    Serial.println(views);

  while (views.charAt(i) != ':') // Character before required data starts.
    i++;
    
  i++;
  views = views.substring(i);
  
  int j = 0;
  while (views.charAt(j) != 'C') // Character after required data ends.
    j++;
    
  views = views.substring(0, j);
  
  if (DEBUG)
    Serial.println(views);
    
  tft.fillRect(0, 0, 320, 120, BLACK);

  return (views);
}



String TEMP_ABAD()
{

  char inv = '"';
  String add = "AT+CIPSTART";
  add += "=";
  add += inv;
  add += "TCP";   // type of connection
  add += inv;
  add += ",";
  add += inv;
  add += "api.thingspeak.com";  // host server
  add += inv;
  add += ",";
  add += "80";   // port 
  add += "\r\n";
  sendData(add, 3000, 0);

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";   // carriage return and new line
  sendData(rest, 1000, 0);


  String hostt = "GET /apps/thinghttp/send_request?api_key=QOSIIMQ9NBH5YQQN";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  ;
  String Temp = sendData(hostt, 2000, 0);
  int i = 0;
  Serial.println(Temp);

  while (Temp.charAt(i) != ':')
    i++;
  i++;
  Temp = Temp.substring(i);
  Temp = Temp.substring(0, 2);
  if (DEBUG)
    Serial.print(Temp);
  tft.fillRect(0, 0, 320, 120, BLACK);
  return (Temp);
}


String Gold_ABAD()
{
  //sendData("AT+RST\r\n", 4000, DEBUG);
  char inv = '"';
  String add = "AT+CIPSTART";
  add += "=";
  add += inv;
  add += "TCP";
  add += inv;
  add += ",";
  add += inv;
  add += "api.thingspeak.com";
  add += inv;
  add += ",";
  add += "80";
  add += "\r\n";
  sendData(add, 2000, 0);

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, 2000, 0);

  String hostt = "GET /apps/thinghttp/send_request?api_key=J5T95BKCO22HA58I";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Gold = sendData(hostt, 1500, 0);

  int i = 0;
  Serial.println(Gold);

  while (Gold.charAt(i) != '>')
    i++;
  i++;
  Gold = Gold.substring(i);
 
  Serial.println(Gold);
  int j = 0;
  while (Gold.charAt(j) != '<')
    j++;
  Gold = Gold.substring(0, j);
  Serial.println(Gold);
  if (DEBUG)
    Serial.println(Gold);
  tft.fillRect(0, 0, 320, 120, BLACK);
  return (Gold);
}

String Time()
{

 char inv = '"';
  String add = "AT+CIPSTART";
  add += "=";
  add += inv;
  add += "TCP";
  add += inv;
  add += ",";
  add += inv;
  add += "api.thingspeak.com";  // Host_server_name
  add += inv;
  add += ",";
  add += "80";
  add += "\r\n";
  sendData(add, 3000, 0);  // Establishing a TCP Connection. ( AT+CIPSTART = "TCP","Host_server_name",80 )

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, 2000, 0); //Number of characters to send. ( "AT+CIPSEND=90" )


  String hostt = "GET /apps/thinghttp/send_request?api_key=J0EIT0XF42Y00RBJ";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Time = sendData(hostt, 2000, 1);  // GET request ( GET /apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXXX 
                                            //               Host: Host_server_name ) 
  
  
/********************** Steps To filter the received data. ****************************/
 
  int i = 0;        
  if (DEBUG)
    Serial.println(Time);

  while (Time.charAt(i) != ':') // Character before required data starts.
    i++;
    
  i++;
  Time = Time.substring(i);
  
  int j = 0;
  while (Time.charAt(j) != 'C') // Character after required data ends.
    j++;
    
  Time = Time.substring(0, j);
  
  if (DEBUG)
    Serial.println(Time);
    
  tft.fillRect(0, 0, 320, 120, BLACK);

  return (Time);

  
}



String sendData(String command, const int Goldout, boolean debug)
{
  String response = "";

  Serial1.print(command); // send the read character to the Serial1

  long int Gold = millis();

  while ( (Gold + Goldout) > millis())
  {
    while (Serial1.available())
    {

      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}


