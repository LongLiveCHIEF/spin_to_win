#include "Arduino.h"
#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 20
#define NUM_SELECTOR_STRIPS 2
#define NUM_WHEEL_STRIPS 6
#define NUM_STRIPS 8
#define LED_TYPE WS2812
#define SELECTOR_WIDTH 3
#define SPACE_WIDTH 8
#define START_BUTTON 22
#define STOP_BUTTON 23
#define SELECTOR_COLOR CRGB::Gold
#define BRIGHTNESS 160

int spinning = HIGH;
int startButtonState = HIGH;
int startButtonReading;
int startButtonPrevious = LOW;
long lastStartButtonPushTime = 0;
int selectorBegin = 0;
int selectorEnd = SELECTOR_WIDTH-1;
bool selectorForward = true;

long debounce = 100;
int bottomSelectorStripBegin = (NUM_STRIPS*NUM_LEDS_PER_STRIP)-NUM_LEDS_PER_STRIP;
int bottomSelectorStripEnd = (NUM_STRIPS*NUM_LEDS_PER_STRIP);

CRGBArray<NUM_STRIPS * NUM_LEDS_PER_STRIP> leds;

void moveSelector(){
  if (selectorEnd == (NUM_LEDS_PER_STRIP-1) && selectorForward){
    selectorForward = false;
  }

  if (selectorBegin == 0 && !selectorForward){
    selectorForward = true;
  }

  if(selectorForward){
    leds[selectorBegin] = CRGB::Black;
    leds[selectorEnd+1] = SELECTOR_COLOR;
    leds(bottomSelectorStripBegin, bottomSelectorStripEnd) = leds(0, (NUM_LEDS_PER_STRIP-1));
    selectorBegin++;
    selectorEnd++;
    FastLED.show();
  } else {
    leds[selectorEnd] = CRGB::Black;
    leds[selectorBegin-1] = SELECTOR_COLOR;
    leds(bottomSelectorStripBegin, bottomSelectorStripEnd) = leds(0, (NUM_LEDS_PER_STRIP-1));
    selectorBegin--;
    selectorEnd--;
    FastLED.show();
  }
}

CRGB randomWheelColor(){
  switch(random(3)){
    case 0:
      return CRGB::Red;
    case 1:
      return CRGB::Orange;
    case 2:
      return CRGB::Blue;
  }
}

CRGB currentColor = CRGB::Black;
int currentSpaceLength = 0;
int stripOffset = (NUM_LEDS_PER_STRIP-1);
// for each LED in 2nd row, get current color and move that color one spot to the left
// spot 0 introduces new colors and gets a random color from the selectable palette whenever
// currentSpaceLength == SPACE_WIDTH (if not yet full, it increments currentSpaceLength as it colors it)
void moveWheel(){
  for(int i = stripOffset+NUM_LEDS_PER_STRIP; i >= stripOffset; i--){
    if(i == stripOffset){
      if(currentSpaceLength == SPACE_WIDTH) {
        currentColor = randomWheelColor();
        leds[i] = currentColor;
        currentSpaceLength = 1;
      } else {
        leds[i] = currentColor;
        currentSpaceLength++;
      }
    } else {
      leds[i] = leds[(i-1)];
    }
  }
}


void setup(){
  Serial.begin(9600);
  Serial.println("Begin Serial Output");

  // setup random generator for color wheel
  randomSeed(analogRead(0));

  pinMode(START_BUTTON, INPUT);

  FastLED.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);

  leds(selectorBegin, selectorEnd).fill_solid(SELECTOR_COLOR);

  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  startButtonReading = digitalRead(START_BUTTON);
  if (startButtonReading == HIGH && startButtonPrevious == LOW && millis() - lastStartButtonPushTime > debounce){
    Serial.println("Start Button Pushed");
    lastStartButtonPushTime = millis();
    moveSelector();
  } else {
    moveSelector();
  }
  startButtonPrevious = startButtonReading;

  delay(50);
}
