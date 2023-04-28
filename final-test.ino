#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

void setup() {
  tft.begin();
  uint16_t ID = tft.readID();
  // use ID as needed
}

void loop() {
  tft.fillScreen(0x1886);
  tft.drawPixel(150, 50, 0xFFFF); // draw a white pixel at coordinates (50, 50)
  uint16_t color = tft.readPixel(150, 50); // read the color of the pixel at coordinates (50, 50)
  tft.drawLine(50,50,100,100,0xFFFF);
  // do something with the color value if desired
  while (true) {}
}
