
#include "EncoderStepCounter.h"
#include "ezButton.h"
#include <Wire.h>
#include <EEPROM.h>
#include <stdio.h>
 
#define ENCODER_PIN1 A4
#define ENCODER_PIN2 A2

ezButton button(4);          // auto pull-up library 
const int ledPin =  12;      // set button gnd side

unsigned char pos;

  boolean boo1;
  boolean boo2;
  boolean boo3;
  boolean boo4;

EncoderStepCounter encoder(ENCODER_PIN1, ENCODER_PIN2);

unsigned char lastpos = 0;

void transmitDataWire() {

  EEPROM.get(1, pos);                // recall encoder value
 
  uint32_t blu =   pos;
  
  Wire.write((uint8_t) blu);
  Wire.write((uint8_t)(blu >> 8));
  Wire.write((uint8_t)(blu >> 16));
  Wire.write((uint8_t)(blu >> 24));
    
}



void setup() {
  
  Wire.begin(0x52);                 // initialize slave
  Wire.onRequest(transmitDataWire); // register transmitDataWire as the handler

  encoder.begin();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);         // set button gnd side
  button.setDebounceTime(50);
  button.setCountMode(COUNT_FALLING);
  
}

void(* resetFunc) (void) = 0;

void loop() {
 
button.loop();

//----------------------------
 encoder.tick();
    unsigned char pos = encoder.getPosition();
      if (pos > 0) {
         if (pos != lastpos){
            delay(10);
              lastpos = pos;
                EEPROM.put(1, pos);   // store encoder value
              } 
            }  
//-----------------------------


/*    
//---------------------------------red------------------------------    
   if ( boo1 == true ){
    encoder.tick();
    unsigned char pos = encoder.getPosition();
      if (pos > 0) {
         if (pos != lastpos){
         
              colorWipe(strip.Color(((pos-1)*2), grn, blu), 5); 
              delay(10);
                   
              lastpos = pos;
              } 
            }  
          }
//---------------------------------green------------------------------    
   if ( boo2 == true ){
      encoder.tick();
      signed char pos = encoder.getPosition();
        if (pos > 0) {
         if (pos != lastpos){
          
              colorWipe(strip.Color(red, ((pos-1)*2), blu), 5); 
              Wire.write((uint8_t) pos);
              delay(10);
          
              lastpos = pos;
              } 
           }  
   
   
   }
 //---------------------------------blu------------------------------    
   if ( boo3 == true ){
   encoder.tick();
     signed char pos = encoder.getPosition();
  
      if (pos > 0) {
         if (pos != lastpos){
          
     
              colorWipe(strip.Color(red, grn, ((pos-1)*2)), 5); 
              delay(10);
          
              lastpos = pos;
              } 
           }  
        } 

//--------------------------rainbow------------------------------------ 
    if ( boo4 == true ){
    
    //  rainbow(10);
    //  rainbowCycle(10);        
    }
    */
//----------------encoder  button-------------------------
if(button.isPressed()){
  
    unsigned long count = button.getCount();

    switch (count) {
                    case 1:
                     
                        
                         
                   break;
                   case 2:
                     
                   break;
                   
                                                      
                   case 3:
                             resetFunc();
                           
                       
                       
                             button.resetCount();
                             
                   break; 
                  
                  
                 
 
                  }

    
                 }

if(button.isReleased()){
 
}

//------------------------------------------------------
           
  
  
}             // loop end

//------------------------------------------------------



/*


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { // do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  // turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      // turn every third pixel off
      }
    }
  }
}

// Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      // turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

*/
