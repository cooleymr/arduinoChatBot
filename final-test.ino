#include <Wire.h>
#include <Adafruit_GFX.h>  // Hardware-specific library
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

char incomingByte;  // for incoming serial data

uint16_t x = 50, y = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("ID = 0x");
  Serial.println(identifier, HEX);
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);

  // Change background color to 0x1886
  tft.fillScreen(0x1886);

  // Rotate display by 90 degrees
  tft.setRotation(2);

  defaultFace(50 + 0, 50 + 60);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if (incomingByte == 'd') {
      defaultFace(x + 0, y + 60);
    } else if (incomingByte == 'l') {
      listeningFace(x + 20, y + 80);
    } else if (incomingByte == 't') {
      cuteFace(x = 40, y + 80);
    }

    delay(3000);
    incomingByte = '-1';
  }

  // // Draw the speaking face
  // speaking(x+0, y+60);

  // angryface(x+0, y+60);
}

void defaultFace(uint16_t x, uint16_t y) {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("^_^");
}

void listeningFace(uint16_t x, uint16_t y) {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(6);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("Listening");


  int rectWidth = 10;   // Width of each rectangle
  int rectHeight = 10;  // Height of each rectangle
  int numRects = 10;    // Number of rectangles in the wave
  int waveHeight = 10;  // Amplitude of the wave
  int waveSpeed = 800;  // Speed of the wave animation in ms

  int phaseShift = 0;
  for (int i = 0; i < numRects; i++) {
    int rectX = x + i * rectWidth;                                         // X position of the current rectangle
    int rectY = y + waveHeight * sin(2 * PI * i / numRects + phaseShift);  // Y position of the current rectangle
    tft.fillRect(rectX, rectY, rectWidth, rectHeight, 0xFFFF);             // Draw the rectangle
  }

  phaseShift++;
  if (phaseShift > 1000) {
    phaseShift = 0;
  }

  delay(waveSpeed);  // Wait for the wave to complete a cycle
}

void speakingFace(uint16_t x, uint16_t y) {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);

  int numTimes = 1;  // Number of times to repeat the face change
  for (int i = 0; i < numTimes; i++) {
    // Draw the initial face
    tft.print("^.^");
    delay(1000);

    // Draw the second face
    tft.fillRect(x, y, 16, 16, 0x1886);  // Clear the previous face
    tft.setCursor(x, y);
    tft.print("^o^");
  }
}

void angryFace(uint16_t x, uint16_t y) {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print(">_<");
}

void sadFace(uint16_t x, uint16_t y) {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("T_T");
}

void cuteFace(uint16_t x, uint16_t y) {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(4);
  tft.setTextColor(0xF1CF, 0x1886);  // Set text color to pink, background to white
  tft.setCursor(x, y);
  tft.print("(*^_^*)");
}
