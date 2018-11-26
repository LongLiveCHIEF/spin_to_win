#include "Arduino.h"
#include "FastLED.h"
#define NUM_LEDS_PER_STRIP 20
#define NUM_SELECTOR_STRIPS 2
#define NUM_WHEEL_STRIPS 6
#define NUM_STRIPS 8
#define LED_TYPE WS2812
#define SELECTOR_WIDTH 3
#define SPACE_WIDTH 8

bool spinning = false;
int startButton = 7;
int stopButton = 6;
int startButtonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;

long debounce = 200;
CRGBArray<NUM_STRIPS * NUM_LEDS_PER_STRIP> leds;

void selector(){
  while(startButtonState == HIGH){
    for(int i = 0; i < (NUM_LEDS_PER_STRIP-SELECTOR_WIDTH); i++) {
      leds(i,i+SELECTOR_WIDTH-1).fill_solid(CRGB::Blue);
      leds(i+1,i+SELECTOR_WIDTH-1+1).fill_solid(CRGB::Blue);
      FastLED.show();
      FastLED.delay(10);
      leds(i,i+SELECTOR_WIDTH-1).fill_solid(CRGB::Black);
      leds(i+1,i+SELECTOR_WIDTH-1+1).fill_solid(CRGB::Black);
      FastLED.show();
      FastLED.delay(10);
    }

    for(int i =(NUM_LEDS_PER_STRIP-SELECTOR_WIDTH-1); i >= SELECTOR_WIDTH; i--){
      leds(i,i+SELECTOR_WIDTH-1).fill_solid(CRGB::Blue);
      leds(i-1,i+SELECTOR_WIDTH-1-1).fill_solid(CRGB::Blue);
      FastLED.show();
      FastLED.delay(10);
      leds(i,i+SELECTOR_WIDTH-1).fill_solid(CRGB::Black);
      leds(i-1,i+SELECTOR_WIDTH-1-1).fill_solid(CRGB::Black);
      FastLED.show();
      FastLED.delay(10);
    }
  }
}


void setup(){
  Serial.begin(115200);
  pinMode(startButton, INPUT);
  FastLED.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
  Serial.println("Begin Serial Output");
}

int selectorRangeStart = 0;
int selectorRangeEnd = selectorRangeStart + SELECTOR_WIDTH -1;
int wheelRangeStart = (NUM_LEDS_PER_STRIP*NUM_SELECTOR_STRIPS);
int wheelRangeEnd = (NUM_STRIPS*NUM_LEDS_PER_STRIP);
int bottomSelectorOffset = NUM_STRIPS-1;

void loop() {
  startButtonReading = digitalRead(startButton);
  if (startButtonReading == HIGH && startButtonPrevious == LOW && millis() - lastStartButtonPushTime > debounce){
    Serial.println("Start Button Pushed");
    if (startButtonState == HIGH) {
      startButtonState = LOW;
      spinning = false;
    } else {
      startButtonState = HIGH;
      spinning = true;
    }

    lastStartButtonPushTime = millis();
  }
  startButtonPrevious = startButtonReading;
  selector();
}
