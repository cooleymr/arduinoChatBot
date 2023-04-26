#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char incomingByte; // for incoming serial data

void setup() {
  Serial.begin(9600);
  
  displayListening();
}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    displaySpeaking();
    incomingByte = '-1';
    delay(3000);

    // if(incomingByte == "t"){
    //   displayDefault();
    // }

    // // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingByte, DEC);
  }

  // displaySpeaking();
  // delay(3000);
  // displayListening();
  // delay(3000);
  // displayDefault();
  // delay(3000);

}

void displaySpeaking(){
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x64
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("~~~~~");
  // THIS LINE IS A TEST
  display.println(incomingByte);
  display.display();
}

void displayListening(){
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x64
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("^o^");
  display.display();
}

void displayDefault(){
  // Initialize the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Clear the display buffer
  display.clearDisplay();
  // Draw the "^_ ^" face
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.println("^_^");
  // Display the buffer contents on the screen
  display.display();
}
