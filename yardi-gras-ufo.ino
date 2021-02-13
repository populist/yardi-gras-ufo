#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS 273
#define LED_PIN  4
#define COLOR_ORDER BRG
#define CHIPSET     WS2811
#define BRIGHTNESS 77
CRGB leds[NUM_LEDS];

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
const bool    kMatrixVertical = false;

// Params for width and height
const uint8_t kMatrixWidth = 39;
const uint8_t kMatrixHeight = 7;

// Run once...
void setup() { 
    FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS);  
    FastLED.setBrightness(90);
    FastLED.clear(true);
    //FastLED.setMaxPowerInVoltsAndMilliamps(12, 1000);
}

// Run all the time....
void loop() {
     
    int colorred = 96;
    int colorgreen = 15;
    int colorblue = 151;
           
    for( uint8_t x = 0; x < kMatrixWidth-1; x++) {

        // This will create the star pattern
        for ( uint8_t x = 0; x < 1; x++) {
          int Pixel = random(NUM_LEDS);
          leds[Pixel] = CRGB(111, 111, 111);
        }

        // Now draw the UFO
        drawUFO( x -1, 3, colorred, colorgreen, colorblue);
        FastLED.show();

        // Warp speed away with a slight delay
        drawUFO( x -1 , 3, 0, 0, 0);
        delay(100);
    } 
}

// This function will draw a UFO
uint16_t drawUFO(int cockpitcol, int cockpitrow, int red, int green, int blue) {

  leds[ XY( cockpitcol+4, cockpitrow+3) ] = CRGB(red, green, blue);
  
  leds[ XY( cockpitcol+3, cockpitrow+2) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+4, cockpitrow+2) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+5, cockpitrow+2) ] = CRGB(red, green, blue);

  leds[ XY( cockpitcol+1, cockpitrow+1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+2, cockpitrow+1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+3, cockpitrow+1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+4, cockpitrow+1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+5, cockpitrow+1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+6, cockpitrow+1) ] = CRGB(red, green, blue);
  
  leds[ XY( cockpitcol, cockpitrow) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+1, cockpitrow) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+2, cockpitrow) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+3, cockpitrow) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+4, cockpitrow) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+5, cockpitrow) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+6, cockpitrow) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+7, cockpitrow) ] = CRGB(red, green, blue);

  leds[ XY( cockpitcol+1, cockpitrow-1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+2, cockpitrow-1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+3, cockpitrow-1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+4, cockpitrow-1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+5, cockpitrow-1) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+6, cockpitrow-1) ] = CRGB(red, green, blue);

  leds[ XY( cockpitcol+3, cockpitrow-2) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+4, cockpitrow-2) ] = CRGB(red, green, blue);
  leds[ XY( cockpitcol+5, cockpitrow-2) ] = CRGB(red, green, blue);
    
  leds[ XY( cockpitcol+4, cockpitrow-3) ] = CRGB(red, green, blue);
}

// This function will sanitize
uint16_t XY( uint8_t x, uint8_t y) {
  if (y > 7) {
    y = 7;
  }
  if (x < 0) {
    x = 0;
  }
  if (x > 39) {
    x = 39;
  }
  if (y < 0) {
    y = 0;
  }
  return XY_raw(x,y);
}

// This function will return the right 'led index number' for 
// a given set of X and Y coordinates on your matrix.  
uint16_t XY_raw( uint8_t x, uint8_t y) {
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    if (kMatrixVertical == false) {
      i = (y * kMatrixWidth) + x;
    } else {
      i = kMatrixHeight * (kMatrixWidth - (x+1))+y;
    }
  }

  if( kMatrixSerpentineLayout == true) {
    if (kMatrixVertical == false) {
      if( y & 0x01) {
        // Odd rows run backwards
        uint8_t reverseX = (kMatrixWidth - 1) - x;
        i = (y * kMatrixWidth) + reverseX;
      } else {
        // Even rows run forwards
        i = (y * kMatrixWidth) + x;
      }
    } else { // vertical positioning
      if ( x & 0x01) {
        i = kMatrixHeight * (kMatrixWidth - (x+1))+y;
      } else {
        i = kMatrixHeight * (kMatrixWidth - x) - (y+1);
      }
    }
  }
  
  return i;
}
