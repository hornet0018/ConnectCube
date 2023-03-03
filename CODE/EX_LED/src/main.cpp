#include "Arduino.h"
#include <FastLED.h>

// LED設定
#define NUM_LEDS 100
#define CLOCK_PIN 4
#define DATA_PIN 5
#define BRIGHTNESS 50
CRGB leds[NUM_LEDS];
uint8_t hue = 0;

void setup()
{
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  for (int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = CHSV(hue + (i * 10), 255, 255);
  }
  // You can change the pattern speed here
  EVERY_N_MILLISECONDS(10)
  {
    hue = hue + 10;
  }
  FastLED.show();
  delay(100);
}