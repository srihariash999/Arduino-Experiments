// Arduino program to send sms



----> Connections : 






#include <SoftwareSerial.h> // SoftwareSerial is used to allow serial communication on other digital pins of arduino.
SoftwareSerial SIM900A(9,10);  //SoftwareSerial myobject(rxPin,txPin);
int count=0; 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial);
Serial.println("Arduino with SIM900A is ready");
// start communication with the SIM900A in 9600
SIM900A.begin(9600); 
Serial.println("SIM900A started at 9600");
delay(1000);
Serial.println("Setup Complete! SIM900A is Ready!");
}

void loop() {
  // put your main code here, to run repeatedly:

while(count<3){
 Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("Good morning, how are you doing?");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent");
  count+=1;
}
Serial.println("Done");
while(1);
}
