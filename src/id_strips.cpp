#include "Arduino.h"
#include "FastLED.h"
#define NUM_LEDS_PER_STRIP 20
#define NUM_STRIPS 8
#define LED_TYPE WS2812

int startButtonPin = 2;
int startbuttonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;

long debounce = 200;
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

void setup(){
  FastLED.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
}

void loop(){
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j <= i; j++) {
      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
    }
  }

  FastLED.show();
}
