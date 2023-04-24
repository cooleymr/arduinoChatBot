#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

String receivedString = "";
boolean received = false;

void setup() {
  Serial.begin(9600);

  // initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  // check for incoming serial data
  while (Serial.available() > 0) {
    receivedString = Serial.readString();
    received = true;
  }

  if (received) {
    // display the received text on the OLED display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(receivedString);
    display.display();

    received = false;
  }
}
