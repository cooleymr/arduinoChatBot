#include <ArduinoHttpClient.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <EasyVR.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define OLED_RESET -1
#define OLED_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

EasyVR easyvr(0, 1);

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* api_key = "YOUR_API_KEY";

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Say Nishad...");
  display.display();

  easyvr.setPinOutput(EasyVR::IO1, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  int16_t res = easyvr.recognize();
  if (res >= 0) {
    switch (res) {
      case 0:
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Listening...");
        display.display();
        delay(1000);
        while (easyvr.isRecording()) {
          delay(100);
        }

        if (easyvr.hasFinished()) {
          int reco = easyvr.getWord();
          if (reco >= 0) {
            Serial.print("You said: ");
            Serial.println(reco);
            String prompt = "You said: " + String(reco);
            prompt.replace(" ", "%20");

            if (WiFi.status() == WL_CONNECTED) {
              HTTPClient http;
              http.begin("https://api.openai.com/v1/engines/davinci-codex/completions");
              http.addHeader("Content-Type", "application/json");
              http.addHeader("Authorization", "Bearer " + String(api_key));
              int httpCode = http.POST("{\"prompt\": \"" + prompt + "\"}");
              String response = http.getString();
              Serial.println(httpCode);
              Serial.println(response);
              http.end();

              if (httpCode == 200) {
                display.clearDisplay();
                display.setCursor(0, 0);
                display.println("GPT says:");
                display.display();

                String text = "";
                int start_pos = response.indexOf("text\":") + 7;
                int end_pos = response.indexOf("\",", start_pos);
                if (start_pos != -1 && end_pos != -1) {
                  text = response.substring(start_pos, end_pos);
                }

                if (text != "") {
                  Serial.println("GPT says: " + text);
                  display.setCursor(0, 10);
                  display.println(text);
                  display.display();
                  delay(2000);
                  display.clearDisplay();
                  display.setCursor(0, 0);
                  display.println("Say Nishad...");
                  display.display();
                }
              }
            }
          }
        }
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
     
