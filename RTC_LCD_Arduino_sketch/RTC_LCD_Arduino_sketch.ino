/*
  DS1307 RTC (Real-Time-Clock) Example

  Uno       A4 (SDA), A5 (SCL)
  Mega      20 (SDA), 21 (SCL)
  Leonardo   2 (SDA),  3 (SCL)
 */

#include <Wire.h>
#include <DS1307.h>
#include <LiquidCrystal.h> 

int Contrast=75;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

DS1307 rtc;


void setup()
{

   pinMode(6,OUTPUT);
    analogWrite(6,90);
     lcd.begin(16, 2);
     Serial.begin(9600);
     
  //init Serial port
  Serial.begin(9600);
  while(!Serial); //wait for serial port to connect - needed for Leonardo only

  //init RTC
  Serial.println("Init RTC...");

  //only set the date+time one time
  // rtc.set(0, 29, 12, 24, 2, 2019); //08:00:00 24.12.2014 //sec, min, hour, day, month, year

  //stop/pause RTC
  // rtc.stop();

  //start RTC
  rtc.start();
}


void loop()
{
  uint8_t sec, minu, hour, day, month;
  uint16_t year;

  //get time from RTC
  rtc.get(&sec, &minu, &hour, &day, &month, &year);

lcd.setCursor(0, 0);
      lcd.print("\Time:");
      lcd.print(hour,DEC);
      lcd.print(":");
      lcd.print(minu,DEC);
      lcd.print(":");
      lcd.print(sec,DEC);
lcd.setCursor(0,1);

      lcd.print("Date: ");
      lcd.print(day, DEC);
      lcd.print("-");
      lcd.print(month, DEC);
      lcd.print("-");
      lcd.print(year, DEC);

  //serial output
  Serial.print("\nTime: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(minu, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);

  Serial.print("\nDate: ");
  Serial.print(day, DEC);
  Serial.print(".");
  Serial.print(month, DEC);
  Serial.print(".");
  Serial.print(year, DEC);

  //wait a second
  delay(1000);
}
