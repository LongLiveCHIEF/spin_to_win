#include "Arduino.h"
#include "FastLED.h"
#define NUM_LEDS_PER_STRIP 20
#define NUM_STRIPS 8
#define LED_TYPE WS2812

int startButton = 24;
int stopButton = 25;
int startbuttonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;

long debounce = 200;
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

void fadeall() { for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) { leds[i].nscale8(250); } }

void id_strips(){
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j <= i; j++) {
      stripIdentifier[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
    }
  }

  FastLED.show();
}

void setup(){
  Serial.begin(9600);
  FastLED.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
  Serial.println("----Starting Spin to Win-----");
}

void loop(){
  static uint8_t hue = 0;
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
      leds[j] = CHSV(hue++, 255, 255);
    }
    FastLED.show();
    fadeall();
    delay(10);
  }

  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = (NUM_LEDS_PER_STRIP) -1; j >= 0; j--) {
      leds[j] = CHSV(hue++, 255, 255);
    }
    FastLED.show();
    fadeall();
    delay(10);
  }
}
