#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// RGB LED Pins (PWM)
const int pinR = 3;
const int pinG = 5;
const int pinB = 6;

// Potentiometers
const int potR = A0;
const int potG = A1;
const int potB = A2;
const int potBrightness = A3; // Brightness control

// Buttons
const int btnRed = 7;
const int btnGreen = 8;
const int btnWhite = 9;
const int btnFade = 10;

// States
bool fadeMode = false;
int fadeHue = 0;
unsigned long lastFadeTime = 0;

int rVal = 0, gVal = 0, bVal = 0;
int brightness = 255;

void setup() {
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

  pinMode(btnRed, INPUT);
  pinMode(btnGreen, INPUT);
  pinMode(btnWhite, INPUT);
  pinMode(btnFade, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // Load last color from EEPROM
  rVal = EEPROM.read(0);
  gVal = EEPROM.read(1);
  bVal = EEPROM.read(2);

  brightness = 255;
  applyColor(rVal, gVal, bVal, brightness);
}

void loop() {
  // Read brightness level
  brightness = map(analogRead(potBrightness), 0, 1023, 0, 255);

  // Toggle Fade Mode
  if (digitalRead(btnFade) == HIGH) {
    fadeMode = !fadeMode;
    delay(300);  // debounce
  }

  if (fadeMode) {
    if (millis() - lastFadeTime >= 30) {
      float rf, gf, bf;
      hsvToRGB(fadeHue / 255.0, rf, gf, bf);
      rVal = (int)(rf * 255);
      gVal = (int)(gf * 255);
      bVal = (int)(bf * 255);
      fadeHue = (fadeHue + 1) % 256;
      lastFadeTime = millis();
    }
  } else {
    rVal = map(analogRead(potR), 0, 1023, 0, 255);
    gVal = map(analogRead(potG), 0, 1023, 0, 255);
    bVal = map(analogRead(potB), 0, 1023, 0, 255);
  }

  // Preset Buttons
  if (digitalRead(btnRed) == HIGH) {
    rVal = 255; gVal = 0; bVal = 0;
    saveColor(rVal, gVal, bVal);
    fadeMode = false;
    delay(300);
  }
  if (digitalRead(btnGreen) == HIGH) {
    rVal = 0; gVal = 255; bVal = 0;
    saveColor(rVal, gVal, bVal);
    fadeMode = false;
    delay(300);
  }
  if (digitalRead(btnWhite) == HIGH) {
    rVal = 255; gVal = 255; bVal = 255;
    saveColor(rVal, gVal, bVal);
    fadeMode = false;
    delay(300);
  }

  applyColor(rVal, gVal, bVal, brightness);
  showOLED(rVal, gVal, bVal, brightness, fadeMode);
}

// ===== Helper Functions =====

void applyColor(int r, int g, int b, int brightness) {
  int rOut = (r * brightness) / 255;
  int gOut = (g * brightness) / 255;
  int bOut = (b * brightness) / 255;

  analogWrite(pinR, 255 - rOut);  // Invert for common anode
  analogWrite(pinG, 255 - gOut);
  analogWrite(pinB, 255 - bOut);
}

void saveColor(int r, int g, int b) {
  EEPROM.update(0, r);
  EEPROM.update(1, g);
  EEPROM.update(2, b);
}

void hsvToRGB(float h, float &r, float &g, float &b) {
  int i = int(h * 6);
  float f = h * 6 - i;
  float q = 1 - f;
  float t = f;

  switch (i % 6) {
    case 0: r = 1; g = t; b = 0; break;
    case 1: r = q; g = 1; b = 0; break;
    case 2: r = 0; g = 1; b = t; break;
    case 3: r = 0; g = q; b = 1; break;
    case 4: r = t; g = 0; b = 1; break;
    case 5: r = 1; g = 0; b = q; break;
  }
}

void showOLED(int r, int g, int b, int brightness, bool fade) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("R: "); display.print(r);
  display.print(" G: "); display.print(g);
  display.print(" B: "); display.println(b);

  char hexColor[8];
  sprintf(hexColor, "#%02X%02X%02X", r, g, b);
  display.print("HEX: "); display.println(hexColor);

  display.print("Bright: "); display.println(brightness);
  display.print("Mode: "); display.println(fade ? "Auto-Fade" : "Manual");

  // Simulated Color Preview Bar
  bool darkColor = (r + g + b) < 120;
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 50; y < 63; y++) {
      display.drawPixel(x, y, darkColor ? SSD1306_WHITE : SSD1306_BLACK);
    }
  }

  display.display();
}
