/*
 * This is a sketch for using the DS1307 RTC module *WITHOUT* using the RTC library.
 * 
 * I wrote this as an experiment and in no way I think, is more optimised. It's more of a "Because, when you can, why not" type of (fling) thing.
 * I commented almost every line of the code for ease. If that's annoying, Sorry !!!
 * 
 * Suggestions, improvements and edits are welcome.
 * 
 * 
 * 
 * 
 * Connections:      DS1307 pins : SDA ---> A4 (Arduino UNo)
 *                                 SCL ---> A5 (Arduino Uno)
 *                                 VCC ---> 5V (Arduino Uno)
 *                                 GND ---> GND (Arduino Uno)
 *                                 
 *               LCD(16x2) pins :  VSS ---> GND              
 *                                 VCC ---> VCC
 *                                 VEE ---> 6
 *                                 RS  ---> 12
 *                                 RW  ---> GND
 *                                 E   ---> 11
 *                                 DB4 ---> 5
 *                                 DB5 ---> 4
 *                                 DB6 ---> 3
 *                                 DB7 ---> 2
 *                                LED+ ---> VCC 
 *                                LED- ---> GND
 *                                 
 *                   
 * 
 * 
 * 
 * 
 * BY - Srihari Ayapilla
 * Dated - 24-02-2019
 * email: 16bec021@smvdu.ac.in
 * 
 * 
 * PS: See the appendix to see what I think different 'symbols' i used to comment mean. ;)
 * PPS: Drop an email if you find this code useful or interesting. That'd be nice.
 * 
 * 
 * 
 * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-------------------------  MAY THE FORCE BE WITH YOU !!!!!! ----------------------XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 * 
 */



#include <Wire.h>
#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 



int RTCAddress = 0x68;                           // RTC module(slave) address. I found this using the i2c scanner sketch(see in my codes and designs);
#define seconds_reg 0x00                         // hex address for seconds register(internal) --> I looked up these register values in datasheet.
#define minutes_reg 0x01                         // hex address for minutes register(internal)
#define hours_reg 0x02                          // hex address for hours register(internal)
#define day_reg 0x03
#define date_reg 0x04
#define month_reg 0x05
#define year_reg 0x06


int minv,secv,hourv,datev,monthv,yearv,daybufv,flag = 0,t24,buf =0;                                       // Variables declared for use in code.
int* flagpoint= &flag;
int* t24point = &t24;
String dayv;




// Function prototypes declarations follow.
int dectobcd(int x);
int bcdtodec(int x);
int hour_dec(int x);
void set_hours_format(int x,String y);
void set_hours(int x);                               
void set_minutes(int x);                            
void set_seconds(int x);  
void rtc_time_call();
void rtc_date_call();
String day_dec(int x);

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  Start of setup function.$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ 




void setup() { 
                                                        
  Wire.begin();                                                      // Initiate the Wire library
  Serial.begin(9600);                                               // Initializing the Serial monitor.
  pinMode(6,OUTPUT);
  analogWrite(6,90);
  lcd.begin(16,2);
  delay(100);                          



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                           //XXXXXXXXXXXXXXXXXXXXXXXXXX-- "" IMPORTANT - Read the notes below ""   -- XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

                           

//NOTE: Uncomment the following lines only if you want to set the time.
//NOTE2: Also, use only once, i.e., uncomment--> change the time to correct value --> upload --> comment again to keep the set time. --> upload again.


 // ---------- Selecting the hour format you want (read comments) --------------------
         
//   Set ALL the registers at the start up for better results.

//     set_hours_format(24,"XX");                          // change the "xx" to either "12" or "24"And "YY" to "AM" or "PM" or "XX"(for 24) Only those, nothing else. please.
//     set_hours(17);                               // change the "xx" to the current time. (12/24 hour format as you selected above)
//     set_minutes(37);                             // change the "xx" to the current value.
//     set_seconds(10);                             // really? Seconds too? Okay though.
//
//     set_date(24);                               // change the "xx" to the current date. 
//     set_month(02);                             // change the "xx" to the current month.
//     set_year(2019);                             // change the "xxxx" to the current year.
//     set_day(1);                                 // change the "x" to current day. (1-7). ( 1 = monday && 7 = sunday)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


}                               


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$        End of setup.       $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$




// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  The INFINITE Loop follows $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



void loop() {
  
     rtc_time_call();                                // Calling the main function which retrieves the time.

     rtc_date_call();                                // Calling the fucntion which retrieves the date.

    Serial.print("Time :-  ");                       // Printing the time to Serial Monitor.

    Serial.print(hourv);
    Serial.print(":");
    Serial.print(minv);
    Serial.print(":");
    Serial.print(secv);  
    if(t24 ==1)
    {
          if(flag ==0)
      
        {
          Serial.print(" AM");
        }
          if(flag ==1)
      
        {
          Serial.print(" PM");
        }
    }
    
    Serial.print("       ");
    
    Serial.print("Date :-  ");                       // Printing the time to Serial Monitor.
    Serial.print(datev);
    Serial.print("-");
    Serial.print(monthv);
    Serial.print("-");
    Serial.print(yearv);
    Serial.print(" -- ");  
    Serial.print(dayv);
    Serial.println("nday");

  lcd.setCursor(0, 0);
      lcd.print("\Time:");
      lcd.print(hourv,DEC);
      lcd.print(":");
      lcd.print(minv,DEC);
      lcd.print(":");
      lcd.print(secv,DEC);
          if(t24 ==1)
    {
          if(flag ==0)
      
        {
          lcd.print(" AM");
        }
          if(flag ==1)
      
        {
          lcd.print(" PM");
        }
    }
lcd.setCursor(0,1);

      lcd.print("Date: ");
      lcd.print(datev, DEC);
      lcd.print("-");
      lcd.print(monthv, DEC);
      lcd.print("-");
      lcd.print(yearv, DEC);
      lcd.print(" ");
      lcd.print(dayv);
    delay(989);
  
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$S$$$$$$$$$$$$$$$$$$  The INFINITE Loop ends $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void rtc_time_call()
{
     //Following is asking the particular registers for data

//For seconds value.
  
  Wire.beginTransmission(RTCAddress);                                  // Begin transmission to the RTC module.
  Wire.write(seconds_reg);                                              // Ask for the data from seconds reg.
  Wire.endTransmission();                                               // End tx. And proceed to recieve the asked byte.
  
  
  Wire.requestFrom(RTCAddress,1);                                      // Request the transmitted byte from the seconds register.
  
  if(Wire.available()<=1) {                                             //If Rtc is sending data... 
    secv = bcdtodec(Wire.read());                               // Reads the data from the seconds register & Converting the recieved BCD value to decimal to print in future.
                                                                        
  }

  //For minutes value.
  
  
  Wire.beginTransmission(RTCAddress);                                  // Begin transmission to the RTC module.
  Wire.write(minutes_reg);                                              // Ask for the data from minutes reg.
  Wire.endTransmission();                                               // End tx. And proceed to recieve the asked byte.
  
  
  Wire.requestFrom(RTCAddress,1);                                      // Request the transmitted byte from the minutes register.
  
  if(Wire.available()<=1) {                                             //If Rtc is sending data... 
    minv = bcdtodec(Wire.read());                                     // Reads the data from the minutess register & Converting the recieved BCD value to decimal to print in future.                                               
  }

  
  //For hours value.
  
 Wire.beginTransmission(RTCAddress);                                  // Begin transmission to the RTC module.
  Wire.write(hours_reg);                                               // Ask for the data from minutes reg.
  Wire.endTransmission();                                               // End tx. And proceed to recieve the asked byte.
  
  
  Wire.requestFrom(RTCAddress,1);                                      // Request the transmitted byte from the minutes register.
  
  if(Wire.available()<=1) {                                             //If Rtc is sending data... 
    hourv = hour_dec(Wire.read());                                        // Reads the data from the minutess register  & Converting the recieved BCD value to decimal to print in future.                                                
}
  
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void rtc_date_call()
{
     //Following is asking the particular registers for data

//For date value.
  
  Wire.beginTransmission(RTCAddress);                                  // Begin transmission to the RTC module.
  Wire.write(date_reg);                                              // Ask for the data from seconds reg.
  Wire.endTransmission();                                               // End tx. And proceed to recieve the asked byte.
  
  
  Wire.requestFrom(RTCAddress,1);                                      // Request the transmitted byte from the seconds register.
  
  if(Wire.available()<=1) {                                             //If Rtc is sending data... 
    datev = bcdtodec(Wire.read());                               // Reads the data from the seconds register & Converting the recieved BCD value to decimal to print in future.
                                                                        
  }

  //For month value.
  
  
  Wire.beginTransmission(RTCAddress);                                  // Begin transmission to the RTC module.
  Wire.write(month_reg);                                              // Ask for the data from minutes reg.
  Wire.endTransmission();                                               // End tx. And proceed to recieve the asked byte.
  
  
  Wire.requestFrom(RTCAddress,1);                                      // Request the transmitted byte from the minutes register.
  
  if(Wire.available()<=1) {                                             //If Rtc is sending data... 
    monthv = bcdtodec(Wire.read());                                     // Reads the data from the minutess register & Converting the recieved BCD value to decimal to print in future.                                               
  }

  
  //For year value.
  
  
  Wire.beginTransmission(RTCAddress);                                  // Begin transmission to the RTC module.
  Wire.write(year_reg);                                               // Ask for the data from minutes reg.
  Wire.endTransmission();                                               // End tx. And proceed to recieve the asked byte.
  
  
  Wire.requestFrom(RTCAddress,1);                                      // Request the transmitted byte from the minutes register.
  
  if(Wire.available()<=1) {                                             //If Rtc is sending data... 
    yearv = bcdtodec(Wire.read());                                        // Reads the data from the minutess register  & Converting the recieved BCD value to decimal to print in future.                                                
  }

  //For day value.
  
  
  Wire.beginTransmission(RTCAddress);                                  // Begin transmission to the RTC module.
  Wire.write(day_reg);                                               // Ask for the data from minutes reg.
  Wire.endTransmission();                                               // End tx. And proceed to recieve the asked byte.
  
  
  Wire.requestFrom(RTCAddress,1);                                      // Request the transmitted byte from the minutes register.
  
  if(Wire.available()<=1) {                                             //If Rtc is sending data... 
   daybufv = bcdtodec(Wire.read());                                        // Reads the data from the minutess register  & Converting the recieved BCD value to decimal to print in future.
   dayv = day_dec(daybufv);                                                
  }
  
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int bcdtodec(int x)
{
  return((x / 16 * 10) + (x% 16));

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int dectobcd(int x)
{
  return((x/10*16) + (x%10));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int hour_dec(int x)
{
   int p = x;
   x &= B01000000;
   x = x >> 6;


   if(x ==1)                     // The format is 12 hours format. We use flag to tell it is AM or PM.
   { *t24point = 1;
    int n = p;
    p &= B00100000;
    p = p >> 5;

     if(p ==1)
     {
      *flagpoint = 1;
      n &= B00011111;
      return(bcdtodec(n));
     }
    
     else if(p ==0)
     {
      *flagpoint = 0;
      n &= B00011111;
      return(bcdtodec(n));
     }
}
  else if(x ==0)                     // The format is 24 hours format. We directly decode the hour value.
   { 
      *t24point = 0;
       p &= B00111111;
      return(bcdtodec(p));    
   }
  

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


String day_dec(int x)
{
    switch(x)
    {
      case 1:
            return("Mo");
            break;  
      case 2:
            return("Tu");
            break;
      case 3:
            return("We");
            break; 
      case 4:
            return("Th");
            break;                       
      case 5:
            return("Fr");
            break;    
      case 6:
            return("Sa");
            break;    
      case 7:
            return("Su");
            break;

      default:
            return("Su");      
     }
    
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



void set_hours_format(int x, String y)
{
      if(x == 12 && y == "AM")
      {
          *flagpoint = 1;
          Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
          Wire.write(hours_reg);                                                 
          Wire.write(B01000000);  
          buf = B01000000;                                            
          Wire.endTransmission();                                               // Don't forget to end the transmission.
                         
      }

     else if(x == 12 && y == "PM")
      {
          *flagpoint = 1;
          Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
          Wire.write(hours_reg);                                                 
          Wire.write(B01100000);  
          buf = B01100000;                                                          
          Wire.endTransmission();                                               // Don't forget to end the transmission.
                         
      }
         else if(x == 24 && y == "XX")
      {
          *flagpoint =0;
          Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
          Wire.write(hours_reg);                                                 
          Wire.write(B00000001);                                              
          Wire.endTransmission();                                               // Don't forget to end the transmission.
                         
      }



       

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



void set_hours(int x)
{
     
       int hr = dectobcd(x);
               if(flag ==1)
        {
            hr = hr |buf;
        }
          Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
          Wire.write(hours_reg);                                                 
          Wire.write(hr);                                              
          Wire.endTransmission();                                               // Don't forget to end the transmission.


    
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void set_minutes(int x)
{   if(x >= 0 && x <= 59) 
 { int minu = dectobcd(x);

  Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
  Wire.write(minutes_reg);                                             
  Wire.write(minu);                                               
  Wire.endTransmission();                                               // Don't forget to end the transmission.
 }                       
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void set_seconds(int x)
{   
  if(x >= 0 && x <= 59)
  {
  int sec = dectobcd(x);

    Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
  Wire.write(seconds_reg);                                             
  Wire.write(sec);                                               
  Wire.endTransmission();                                               // Don't forget to end the transmission.
  }  
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void set_date(int x)
{
      if(x >= 1 && x <= 30)
      {
        int date = dectobcd(x);
          Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
          Wire.write(date_reg);                                                 
          Wire.write(date);                                              
          Wire.endTransmission();                                               // Don't forget to end the transmission.
                         
      }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void set_month(int x)
{   if(x >= 1 && x <= 12) 
 { int month = dectobcd(x);

  Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
  Wire.write(month_reg);                                             
  Wire.write(month);                                               
  Wire.endTransmission();                                               // Don't forget to end the transmission.
 }                       
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void set_year(int x)
{   
  if(x >= 2019 && x <= 2100)
  {
    x %= 100;
  int year = dectobcd(x);
    Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
  Wire.write(year_reg);                                             
  Wire.write(year);                                               
  Wire.endTransmission();                                               // Don't forget to end the transmission.
  }  
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void set_day(int x)
{   
  if(x >= 1 && x <= 7)
  {
  int day = dectobcd(x);
    Wire.beginTransmission(RTCAddress);                                  // Staring the I2C comm.
  Wire.write(day_reg);                                             
  Wire.write(day);                                               
  Wire.endTransmission();                                               // Don't forget to end the transmission.
  }  
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------






// -X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X



/*
 *   Appendix:
 * 
 * 
 * 
 *   Hello again, I am so happy you are reading this. 
 * 
 * 
 * 
 *   "XXXXXXXXXXXXXXXXXXXXXXX---------------XXXXXXXXXXXXXXXXXXXXXXX"   : Enclosed between these are the comments I personally really want you to read.
 *
 *   "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"   : These symbols seperates main blocks of code, like setup and loop. 
 *
 *   "-------------------------------------------------------------"   : These seperate the smaller function definitions.
 *
 *
 *   "-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X "   : These mark the end of all functional code.
 *
 *
 */
