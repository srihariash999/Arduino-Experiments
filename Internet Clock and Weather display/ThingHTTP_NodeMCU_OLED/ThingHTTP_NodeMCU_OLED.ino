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
 
const char* ssid = "srihari-Lenovo-ideapad-320-15ISK";            
const char* password = "tYTaLp7J";




const unsigned char introscreen [] PROGMEM = {
  // 'Into, 128x64px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1c, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1c, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x03, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1c, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x03, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1c, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x03, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1c, 0x00, 0x03, 0xe0, 0x00, 0x07, 0xfe, 0x03, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1c, 0x00, 0x03, 0xc0, 0x00, 0x1f, 0xff, 0x03, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1e, 0x00, 0x03, 0xc7, 0xf0, 0x3f, 0xff, 0x03, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1e, 0x00, 0x07, 0x8f, 0xf8, 0x3e, 0x0f, 0x83, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1e, 0x07, 0x87, 0x9f, 0xfc, 0x3c, 0x07, 0x83, 0xf8, 0xe0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 
  0x0f, 0x0f, 0x87, 0x9e, 0x3c, 0x38, 0x07, 0x9f, 0xf8, 0xe0, 0x00, 0x0f, 0x83, 0xfe, 0x00, 0x00, 
  0x0f, 0x1f, 0xcf, 0x1e, 0x3c, 0x00, 0x03, 0xdf, 0xf8, 0xe0, 0x00, 0x7f, 0xe3, 0xfe, 0x00, 0x00, 
  0x0f, 0x3f, 0xcf, 0x1f, 0xfc, 0x00, 0x03, 0xdf, 0xc0, 0xe7, 0xc0, 0xff, 0xe3, 0xff, 0x00, 0x00, 
  0x07, 0x7f, 0xee, 0x1f, 0xfc, 0x7f, 0xff, 0xc3, 0x80, 0xff, 0xf0, 0xff, 0xf3, 0xcf, 0x00, 0x00, 
  0x07, 0xfd, 0xfe, 0x3f, 0xf8, 0xff, 0xff, 0xe3, 0x80, 0xff, 0xf8, 0xe0, 0xf3, 0xcf, 0x00, 0x00, 
  0x07, 0xf9, 0xfe, 0x3f, 0xf8, 0xff, 0xff, 0xe3, 0x80, 0xff, 0xfc, 0xe0, 0xf7, 0x87, 0x00, 0x00, 
  0x07, 0xf0, 0xfc, 0x3e, 0x00, 0xf0, 0x03, 0xe3, 0x80, 0xfc, 0x3c, 0xff, 0xf7, 0x80, 0x00, 0x00, 
  0x03, 0xe0, 0xfc, 0x3f, 0xe0, 0xf8, 0x01, 0xe3, 0x80, 0xf8, 0x3c, 0xff, 0xe7, 0x80, 0x00, 0x00, 
  0x03, 0xe0, 0x78, 0x1f, 0xfe, 0xfe, 0x7f, 0xe3, 0x80, 0xf0, 0x1c, 0xff, 0xe7, 0x00, 0x00, 0x00, 
  0x01, 0xe0, 0x38, 0x0f, 0xfe, 0x7f, 0xff, 0xf3, 0xfc, 0xf0, 0x1c, 0xf8, 0x07, 0x00, 0x00, 0x00, 
  0x01, 0xc0, 0x00, 0x00, 0x7e, 0x1f, 0xff, 0xf3, 0xfc, 0xf0, 0x1c, 0x7e, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0xf1, 0xfc, 0xf0, 0x1c, 0x7f, 0xe7, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0xf0, 0x1c, 0x3f, 0xe7, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe7, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc1, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xfc, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xfe, 0x03, 0x80, 0x1f, 0xe0, 0x03, 0xe0, 0x07, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xff, 0x03, 0x80, 0x3f, 0xf0, 0x0f, 0xfc, 0x07, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0x8f, 0x07, 0x80, 0x7f, 0xf8, 0x3f, 0xfc, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0x07, 0x07, 0x80, 0x78, 0xf8, 0x3f, 0xfc, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x07, 0x07, 0x80, 0x70, 0x78, 0x7c, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x00, 0x07, 0x00, 0x70, 0x38, 0x78, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x00, 0x07, 0x00, 0x70, 0x38, 0x78, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x00, 0x07, 0x00, 0x70, 0x38, 0x70, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x00, 0x07, 0x80, 0x70, 0x38, 0x70, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0x3f, 0x87, 0xf8, 0x70, 0x38, 0x78, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0xff, 0x87, 0xf8, 0x70, 0x78, 0x7f, 0xff, 0x07, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xff, 0x83, 0xf8, 0x7f, 0xf8, 0x7f, 0xff, 0x07, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xf0, 0x01, 0xf8, 0x7f, 0xf0, 0x3f, 0xff, 0x07, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




const unsigned char credits [] PROGMEM = {
  // 'Credits, 128x64px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x38, 0xd1, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x51, 0x00, 0x01, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x51, 0x00, 0x01, 0x18, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x53, 0x00, 0x01, 0x30, 0x80, 0x7c, 0x3e, 0x08, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x5f, 0x00, 0x01, 0x70, 0x80, 0x44, 0x40, 0x1f, 0x3c, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x08, 0xc1, 0x00, 0x01, 0x3c, 0xfe, 0x84, 0xc0, 0x11, 0x26, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0x81, 0x00, 0x01, 0x24, 0x82, 0xfc, 0x80, 0x31, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0x20, 0x01, 0x3c, 0x82, 0x80, 0x80, 0x31, 0x06, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0x20, 0x00, 0x18, 0xc2, 0xc0, 0xc0, 0x1b, 0x0c, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0x20, 0x00, 0x00, 0x7e, 0x7c, 0x7c, 0x0e, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x0c, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x3c, 0x30, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x32, 0x3e, 0x44, 0x1e, 0x06, 0x07, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x11, 0x22, 0xfc, 0x10, 0x0f, 0x0c, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x11, 0x22, 0x80, 0x10, 0x09, 0x8c, 0x19, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x0d, 0x22, 0xfe, 0x10, 0x08, 0x8b, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x3c, 0x00, 0x1f, 0x08, 0x8d, 0x11, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x87, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x81, 0x88, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x82, 0x08, 0x21, 0x0e, 0x00, 0x08, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x84, 0x0e, 0x21, 0x10, 0x07, 0x88, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x07, 0x8b, 0xaf, 0x10, 0x08, 0x88, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x04, 0x58, 0xa0, 0x10, 0x08, 0x88, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x04, 0x50, 0xb2, 0x10, 0x08, 0x88, 0x8f, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x04, 0x5f, 0x9e, 0x1f, 0x0f, 0x8f, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x10, 0x0f, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x40, 0xf1, 0x00, 0xe1, 0x38, 0x3c, 0x11, 0x18, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x41, 0x81, 0x01, 0x33, 0x08, 0x36, 0x11, 0x00, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x43, 0x01, 0x02, 0x12, 0x00, 0x22, 0x13, 0x00, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x42, 0xe1, 0xe3, 0xe2, 0x00, 0x22, 0x1f, 0x03, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x42, 0x31, 0x93, 0x03, 0x00, 0x22, 0x01, 0x00, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x42, 0x11, 0x12, 0x01, 0x88, 0x3e, 0x01, 0x00, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x43, 0x11, 0x91, 0xf0, 0xf8, 0x00, 0x01, 0x0f, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x41, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


 
void setup () {
 
Serial.begin(115200);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.clearDisplay(); // Make sure the display is cleared
  
  // Draw the bitmap:
  // drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(0, 0, introscreen, 128, 64, WHITE);

  // Update the display
  display.display();


   delay(3000);
    
  display.clearDisplay(); // Make sure the display is cleared
  // Draw the bitmap:
  // drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(0, 0, credits, 128, 64, WHITE);

  // Update the display
  display.display();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  delay(3000);



 
}
 
void loop() {

  
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

HTTPClient http;  //Declare an object of class HTTPClient
 
initialdisp();

getTime();
getDate();
getTemp();
getHumidity();
getForecast();





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
  display.setCursor(0,40);
  display.print("Weather:");
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
http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=HS4YKJTJZ9UFNIM8");  //Specify request destination
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
http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=POW6KDE9LB35A1A6");  //Specify request destination
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



void getForecast()
{
  
HTTPClient http;  //Declare an object of class HTTPClient
http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=FS0673O3WWVW69LL");  //Specify request destination
int httpCode4 = http.GET();                                                                  //Send the request
 
if (httpCode4 > 0) { //Check the returning code
 
String forecast = http.getString();   //Get the request response payload

forecast.trim();
Serial.println(forecast);
  display.setCursor(47,40);
  display.print(forecast);
  display.display();

 
}
 
http.end();   //Close connection
}
