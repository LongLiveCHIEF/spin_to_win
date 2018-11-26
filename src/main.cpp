#include "Arduino.h"
#include "FastLED.h"
#define NUM_LEDS_PER_STRIP 20
#define NUM_SELECTOR_STRIPS 2
#define NUM_WHEEL_STRIPS 6
#define NUM_STRIPS 8
#define LED_TYPE WS2812

int spaceWidth = 8;
int startButton = 24;
int stopButton = 25;
int startbuttonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;

long debounce = 200;
CRGBArray<NUM_STRIPS * NUM_LEDS_PER_STRIP> leds;


void setup(){
  Serial.begin(9600);
  LEDS.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
  LEDS.clearData();
  Serial.println("----Starting Spin to Win-----");
}

void loop() {
  leds(0,(NUM_LEDS_PER_STRIP*NUM_SELECTOR_STRIPS)-1).fill_solid(CRGB::Blue);
  leds(20, 160).fill_solid(CRGB::Red);
  LEDS.show();
}
