#include "Arduino.h"
#include "FastLED.h"
#define LEDS_PER_STRIP 20;

int startButtonPin = 2;
int startbuttonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;

long debounce = 200;
CRGB leds[NUM_LEDS_PER_STRIP]:

void setup(){

}

void loop(){

}