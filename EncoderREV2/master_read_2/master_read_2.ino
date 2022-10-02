
/*
 * ****** Nano master controller for lamp display module ******
 * ************************************************************
 * 
 * asking the red, green, blue, and white attiny3226 encoders for their positions,
 * at addresses 0x54(red), 0x53(green), 0x52(blue), and 0x51(white) on the I2C bus.
 * This master code works with four attiny3226 microcontroller boards, mounted
 * with the encoder boards:
 * 'mega_slave_red.ino','mega_slave_green.ino','mega_slave_blue.ino',
 * and with 'mega_slave_wht.ino'-->(SK6812 leds).
 * 8/21/2022  Harold Moore
 * 
 */

#include <Wire.h>
#include <stdio.h>
#include "SK6812.h"                     // if using sk6812 for red, green, blue, AND white control.
//#include "Adafruit_NeoPixel.h"        // Adafruit works better with the I2C bus: 'Wire.h' library.
//#include <tinyNeoPixel.h>             // if using attiny3226 
//#define PIN 4                         // pin A4 on the Nano to control the led strip, (neopixel).
SK6812 LED(4);                          // with 'SK6812.h'. 

//Adafruit_NeoPixel strip(49, PIN, NEO_GRB + NEO_KHZ800);                  // if using WS2812B with Nano.
//tinyNeoPixel strip = tinyNeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800); // if using SK6812 with attiny3226.
//tinyNeoPixel strip = tinyNeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);        // if using WS2812B with attiny3226.
//Adafruit_NeoPixel strip(49, PIN, NEO_RGBW + NEO_KHZ800);                 // if using SK6812 with Nano.

int8_t len = 0;                       // initialiaze len to 0.

void setup() {
  
  LED.set_output(4);                  // set digital signal pin 
  Wire.begin();                       // initialize I2C bus.
  Serial.begin(9600);                 // initialize serial port on Nano.

}

void loop() {

      sendDataWire();                 // tell encoders to send their position values.
      len = 0;                        // since the data was sent, the position is 0 again.
     
}

void sendDataWire() {
  uint32_t red;
  uint32_t grn;
  uint32_t blu;
  uint32_t wht;
  if (4 == Wire.requestFrom(0x53, 4, 0x01)) {     // request data from the Red Slave encoder.
    while (Wire.available()) {
      red  = (uint32_t)Wire.read();               // read out 32-bit wide data.
      red |= (uint32_t)Wire.read() <<  8;
      red |= (uint32_t)Wire.read() << 16;
      red |= (uint32_t)Wire.read() << 24;   
  //    Serial.print("red: ");
  //    Serial.println(red);                      // print the value from Red Slave encoder.

      delay(14);
    }
  } else {
//    MySerial.println("red timed out!");
  }
//----------------

  if (4 == Wire.requestFrom(0x54, 4, 0x01)) {     // request data from the Green Slave encoder.
    while (Wire.available()) {
      grn  = (uint32_t)Wire.read();               // read out 32-bit wide data.
      grn |= (uint32_t)Wire.read() <<  8;
      grn |= (uint32_t)Wire.read() << 16;
      grn |= (uint32_t)Wire.read() << 24;
   //   Serial.print("grn: ");
   //   Serial.println(grn);                      // print the value from the Green Slave encoder.
      delay(14);
    }
  } else {
//    MySerial.println("grn timed out!");
  }

//----------------
 if (4 == Wire.requestFrom(0x52, 4, 0x01)) {      // request data from the Blu Slave encoder.
    while (Wire.available()) {
      blu  = (uint32_t)Wire.read();               // read out 32-bit wide data.
      blu |= (uint32_t)Wire.read() <<  8;
      blu |= (uint32_t)Wire.read() << 16;
      blu |= (uint32_t)Wire.read() << 24;
      
      // math needed to set color control from 256 values to 127,
      // 256 still comes out, also 0 an 1 are special cases that need to be taken care of.
      // this way the operators ain't twisting color knobs all day!
    //  colorWipe(strip.Color(((red-1)*2), ((grn-1)*2),((blu-1)*2) ), 5);    // send control colors.
    
    //    for (uint16_t i = 0; i < 48; i++) { 
         
    //        LED.set_rgbw(i, {((red-1)*2), ((grn-1)*2), ((blu-1)*2), wht});
    //        LED.sync();
    //    }
      
  //    Serial.print("blu: ");
  //    Serial.println(blu);                       // print the value from the Blue Slave encoder.
      delay(14);
    }
  } else {
//    MySerial.println("blu timed out!");
  }

//----------------
if (4 == Wire.requestFrom(0x51, 4, 0x01)) {     // request data from the wht Slave encoder.
    while (Wire.available()) {
      wht  = (uint32_t)Wire.read();               // read out 32-bit wide data.
      wht |= (uint32_t)Wire.read() <<  8;
      wht |= (uint32_t)Wire.read() << 16;
      wht |= (uint32_t)Wire.read() << 24;  
       
      for (uint16_t i = 0; i < 48; i++) { 
         
            LED.set_rgbw(i, {((red-1)*2), ((grn-1)*2), ((blu-1)*2), (wht-1)*2});
            LED.sync();
        }


      
   //   Serial.print("wht: ");
   //   Serial.println(wht);                      // print the value from Red Slave encoder.

      delay(14);
    }
  } else {
//    MySerial.println("wht timed out!");
  }
//-----------------
  
}

void clear(){
 for (uint16_t i = 0; i < 48; i++) { 
   LED.set_rgbw(i, {0, 0, 0, 0});
   LED.sync();
 }
}
