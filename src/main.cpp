#include "Arduino.h"
#include "FastLED.h"
#define NUM_LEDS_PER_STRIP 20
#define NUM_SELECTOR_STRIPS 2
#define NUM_WHEEL_STRIPS 6
#define NUM_STRIPS 8
#define LED_TYPE WS2812
#define SELECTOR_WIDTH 3
#define SPACE_WIDTH 8

int startButton = 24;
int stopButton = 25;
int startbuttonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;

long debounce = 200;
CRGBArray<NUM_STRIPS * NUM_LEDS_PER_STRIP> leds;


void setup(){
  FastLED.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
}

int selectorRangeStart = 0;
int selectorRangeEnd = selectorRangeStart + SELECTOR_WIDTH -1;
int wheelRangeStart = (NUM_LEDS_PER_STRIP*NUM_SELECTOR_STRIPS);
int wheelRangeEnd = (NUM_STRIPS*NUM_LEDS_PER_STRIP);

void loop() {
  leds(selectorRangeStart,selectorRangeEnd).fill_solid(CRGB::Blue);
  leds(wheelRangeStart, wheelRangeEnd).fill_solid(CRGB::Red);
  FastLED.show();
}
