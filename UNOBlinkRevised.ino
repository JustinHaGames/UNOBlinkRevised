//Color changing variables
Timer colorTimer;

byte colorChange;

Color currentColor;

byte colorValue;

byte colorFreq = 250;

//Face changing variables
Timer faceTimer;

byte faceChange;

byte wFace;

byte faceFreq = 250;

//moved variables
bool moved;

//connection variables
bool set;
byte buttonCount;

//debugging
#include "Serial.h"
ServicePortSerial Serial;

void setup() {
  Serial.begin();

  colorTimer.set(colorFreq * 10);
  faceTimer.set(faceFreq * 10);
}

void loop() {
  //if it's alone, it has moved
  if (isAlone()) {
    moved = true;
  }

  //Color changing code
  if (colorTimer.isExpired()) {
    if (!set) {
      colorChange += 1;
      colorTimer.set(colorFreq * 10);
    }
  }

  switch (colorChange) {
    case 0: currentColor = BLUE; colorValue = 0; break;
    case 1: currentColor = RED; colorValue = 1; break;
    case 2: currentColor = YELLOW; colorValue = 2; break;
    case 3: currentColor = GREEN; colorValue = 3; break;
    case 4: colorChange = 0; break;
  }

  //Face changing code
  if (faceTimer.isExpired()) {
    if (!set) {
      faceChange += 1;
      faceTimer.set(faceFreq * 10);
    }
  }

  switch (faceChange) {
    case 0: wFace = 0; break;
    case 1: wFace = 1; break;
    case 2: wFace = 2; break;
    case 3: wFace = 3; break;
    case 4: wFace = 4; break;
    case 5: wFace = 5; break;
    case 6: faceChange = 0; break;
  }

  //Go through the faces and assign the correct colors and and white pixel
  for (int i = 0; i < 6; i++) {
    if (i != wFace) {
      setFaceColor(i, currentColor);
    } else if (i == wFace) {
      setFaceColor(i, WHITE);
    }
  }

  //Set the piece when clicked
  if (moved) {
    if (buttonPressed()) {
      buttonCount += 1;
      if (buttonCount == 1) {
        set = true;
      } else if (buttonCount >= 2) {
        set = false;
        buttonCount = 0;
      }
    }
  }

}
