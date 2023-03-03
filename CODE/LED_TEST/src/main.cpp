#include "Arduino.h"
#include <FastLED.h>

// LED設定
#define NUM_LEDS 1
#define DATA_PIN 13
// Define the array of leds
CRGB leds[NUM_LEDS];

void setup()
{
  // LED setup
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // GRB ordering is assumed
  FastLED.setBrightness(50);
}

void loop()
{
  // ゲーミング点灯
  for (int i = 0; i <= 255; i++)
  {
    leds[0] = CHSV(i, 255, 255);
    FastLED.show();
    delay(5);
  }
}