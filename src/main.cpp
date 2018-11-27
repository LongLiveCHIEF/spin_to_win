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
#define SELECTOR_COLOR CRGB::Green
#define BRIGHTNESS 160

// matrix control indeces
const int selectorControlBegin = 0;
const int selectorControlEnd = (NUM_LEDS_PER_STRIP-1);
const int wheelControlBegin = NUM_LEDS_PER_STRIP;
const int wheelControlEnd = ((NUM_LEDS_PER_STRIP*2)-1);

// wheel controls
bool spinning = false;
int startButtonReading;
long lastStartButtonPushTime = 0;
int stopButtonReading;
long lastStopButtonPushTime = 0;
int selectorBegin = 0;
int selectorEnd = SELECTOR_WIDTH;
bool selectorForward = true;
long debounce = 100;

int bottomSelectorStripBegin = (NUM_STRIPS*NUM_LEDS_PER_STRIP)-NUM_LEDS_PER_STRIP;
int bottomSelectorStripEnd = ((NUM_STRIPS*NUM_LEDS_PER_STRIP)-1);

CRGBArray<NUM_STRIPS * NUM_LEDS_PER_STRIP> leds;

void moveSelector(){
  if (selectorEnd == (NUM_LEDS_PER_STRIP-1) && selectorForward){
    selectorForward = false;
  }

  if (selectorBegin == selectorControlBegin && !selectorForward){
    selectorForward = true;
  }

  if(selectorForward){
    leds[selectorBegin] = CRGB::Black;
    leds[selectorEnd+1] = SELECTOR_COLOR;
    leds(bottomSelectorStripBegin, bottomSelectorStripEnd) = leds(selectorControlBegin, selectorControlEnd);
    selectorBegin++;
    selectorEnd++;
    FastLED.show();
  } else {
    leds[selectorEnd] = CRGB::Black;
    leds[selectorBegin-1] = SELECTOR_COLOR;
    leds(bottomSelectorStripBegin, bottomSelectorStripEnd) = leds(selectorControlBegin, selectorControlEnd);
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
    default:
      return CRGB::Red;
  }
}

int currentSpaceLength = 0;
CRGB currentColor = randomWheelColor();
// for each LED in 2nd row, get current color and move that color one spot to the left
// spot 0 introduces new colors and gets a random color from the selectable palette whenever
// currentSpaceLength == SPACE_WIDTH (if not yet full, it increments currentSpaceLength as it colors it)
void moveWheel(){
  for(int i = wheelControlEnd; i >= wheelControlBegin; i--){
    if(i == wheelControlBegin){
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

  // loop through the remaining wheel strips and mirror the wheel control strips display
  for(int i = 3; i < NUM_STRIPS; i++){
    leds(((i*NUM_LEDS_PER_STRIP)-NUM_LEDS_PER_STRIP),((i*NUM_LEDS_PER_STRIP))-1) = leds(wheelControlBegin, wheelControlEnd);
  }
}


void setup(){
  Serial.begin(9600);
  Serial.println("Begin Serial Output");

  // setup random generator for color wheel
  randomSeed(analogRead(0));

  pinMode(START_BUTTON, INPUT);
  pinMode(STOP_BUTTON, INPUT);

  FastLED.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);

  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

void loop() {
  if(!spinning){
    startButtonReading = digitalRead(START_BUTTON);
    if (startButtonReading == HIGH && millis() - lastStartButtonPushTime > debounce){
      Serial.println("Start Button Pushed");
      lastStartButtonPushTime = millis();
      spinning = true;
      moveSelector();
      moveWheel();
    }
  } else {
    stopButtonReading = digitalRead(STOP_BUTTON);
    if (stopButtonReading == HIGH && millis() - lastStopButtonPushTime > debounce){
      Serial.println("Stop Button Pushed");
      lastStopButtonPushTime = millis();
      spinning = false;
    } else {
      moveSelector();
      moveWheel();
    }
    FastLED.delay(15);
  }
}
