#include "Arduino.h"
#include "FastLED.h"
#define NUM_LEDS_PER_STRIP 20;
#define NUM_STRIPS 8;

int startButtonPin = 2;
int startbuttonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;

long debounce = 200;
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

void setup(){
  FastLED.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP);
}

void loop(){

}
