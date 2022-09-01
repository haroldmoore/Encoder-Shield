
/*
 * ****** Nano master controller for lamp display module ******
 * ************************************************************
 * 
 * asking the red, green, and blue attiny3226 encoders for their positions,
 * at addresses 0x54(red), 0x53(green), and 0x52(blue) on the I2C bus.
 * This master code works with the three attiny3226 microcontroller
 * boards mounted with the encoder board:
 * 'mega_slave_red.ino','mega_slave_green.ino','mega_slave_blue.ino'.
 * 
 * 8/21/2022  Harold Moore
 * 
 */

#include <Wire.h>
#include <stdio.h>
#include "Adafruit_NeoPixel.h"        // Adafruit works better with the I2C bus: 'Wire.h' library.
//#include <tinyNeoPixel.h>           // if using attiny3226 
#define PIN 4                         // pin A4 on the Nano to control the led strip.

//Adafruit_NeoPixel strip(49, PIN, NEO_GRB + NEO_KHZ800);                  // if using straight WS2812B with Nano.
//tinyNeoPixel strip = tinyNeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800); // if using SK6812 with attiny3226.
//tinyNeoPixel strip = tinyNeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);        // if using straight WS2812B with attiny3226.
Adafruit_NeoPixel strip(49, PIN, NEO_RGBW + NEO_KHZ800);                   // if using special SK6812 with Nano.

int8_t len = 0;                       // initialiaze len to 0.

void setup() {
  
  Wire.begin();                       // initialize I2C bus.
  Serial.begin(9600);                 // initialize serial port on Nano.
  
  strip.begin();                      // start Adafruit_NeoPixel.
  strip.show();                       // Initialize all pixels to 'off'.

}

void loop() {

      sendDataWire();                 // tell encoders to send their position values.
      len = 0;                        // since the data was sent, the position is 0 again.
     
}

void sendDataWire() {
  uint32_t red;
  uint32_t grn;
  uint32_t blu;
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
  //    Serial.print("grn: ");
  //    Serial.println(grn);                      // print the value from the Green Slave encoder.
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
      colorWipe(strip.Color(((red-1)*2), ((grn-1)*2),((blu-1)*2) ), 5);    // send control colors.
      
      
  //    Serial.print("blu: ");
   //   Serial.println(blu);                       // print the value from the Blue Slave encoder.
      delay(14);
    }
  } else {
//    MySerial.println("blu timed out!");
  }

//----------------
  
}




//#############################################################
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
//#############################################################
