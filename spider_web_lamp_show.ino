#include <FastLED.h>
#define LED_PIN     9
#define BUTTON_PIN  7
#define NUM_LEDS    13
CRGB leds[NUM_LEDS];

int val = 0;
int state = 1;
int exitShow = 0;

int r = 0;
int g = 0;
int b = 0;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  switch (state) {
    case 1:
    lightShow1(); // Soft Rainbow Transition
    break;
    case 2:
    lightShow2(); // Rainbow chaser
    break;
    case 3:
    lightShow3(); // Off
    break;
  }
}

void buttonState() {
  val = digitalRead(BUTTON_PIN);

  while (digitalRead(BUTTON_PIN)) { // Change state only when button depressed.
    delay(1);
  }

  if (val) {
    state++;
    if (state > 3) {
      state = 1;
    }
  }
}

/*
 * Soft Rainbow Transition
 */

void lightShow1() {

  setColor(255, 0, 0);    // red
  if (exitShow == 1) {
    exitShow = 0;
    return;
  }

  setColor(0, 255, 0);    // green
  if (exitShow == 1) {
    exitShow = 0;
    return;
  }

  setColor(0, 0, 255);    // blue
  if (exitShow == 1) {
    exitShow = 0;
    return;
  }

  setColor(255, 255, 0);  // yellow
  if (exitShow == 1) {
    exitShow = 0;
    return;
  }

  setColor(80, 0, 80);    // purple
  if (exitShow == 1) {
    exitShow = 0;
    return;
  }

  setColor(0, 255, 255); // aqua
  if (exitShow == 1) {
    exitShow = 0;
    return;
  }

}

// lightShow1 private functions

void setColor(int red, int green, int blue) {
  while ( r != red || g != green || b != blue ) {
    if ( r < red ) r += 1;
    if ( r > red ) r -= 1;

    if ( g < green ) g += 1;
    if ( g > green ) g -= 1;

    if ( b < blue ) b += 1;
    if ( b > blue ) b -= 1;

    buttonState();
    if (state == 2) {
      exitShow = 1;
      dark();
      return;
    }
    _setColor();
    delay(10);
  }
}

void _setColor() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB (r, g, b);
    }
    FastLED.show();
}

/*
 * Rainbow chaser
 */

void lightShow2() {

  buttonState();
  if (state == 3) {
    exitShow = 1;
    dark();
    return;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB (255, 0, 0);
    FastLED.show();
    delay(40);
  }

  buttonState();
  if (state == 3) {
    exitShow = 1;
    dark();
    return;
  }

  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB (0, 255, 0);
    FastLED.show();
    delay(40);
  }

  buttonState();
  if (state == 3) {
    exitShow = 1;
    dark();
    return;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB (0, 0, 255);
    FastLED.show();
    delay(40);
  }

  buttonState();
  if (state == 3) {
    exitShow = 1;
    dark();
    return;
  }

  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB (255, 255, 0);
    FastLED.show();
    delay(40);
  }

  buttonState();
  if (state == 3) {
    exitShow = 1;
    dark();
    return;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB (80, 0, 80);
    FastLED.show();
    delay(40);
  }

  buttonState();
  if (state == 3) {
    exitShow = 1;
    dark();
    return;
  }

  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB (0, 255, 255);
    FastLED.show();
    delay(40);
  }


}

/*
 * Off
 */

void lightShow3() {
  dark();
  buttonState();
  delay(10);
}

void dark() { // Turns off all LEDs.
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB (0, 0, 0);
    FastLED.show();
  }
}
