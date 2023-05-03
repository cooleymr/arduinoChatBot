#include <Wire.h>
#include <Adafruit_GFX.h>  // Hardware-specific library
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

char incomingByte;  // for incoming serial data

uint16_t x = 50, y = 50;

bool talking = false;
bool open = false;
String face = "";

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
  tft.setRotation(0);

  defaultFace();
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

// ANGRY FACE
void angryFace() {
  tft.fillScreen(0x1886);
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);
  tft.setCursor(x, y);
  tft.print(">_<");
}
void angryFaceOpen() {
  tft.fillScreen(0x1886);
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);
  tft.setCursor(x, y);
  tft.print(">o<");
}

// SAD FACE
void sadFace() {
  tft.fillScreen(0x1886);
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);
  tft.setCursor(x, y);
  tft.print("T_T");
}
void sadFaceOpen() {
  tft.fillScreen(0x1886);
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);
  tft.setCursor(x, y);
  tft.print("ToT");
}

void cuteFace() {
  tft.fillScreen(0x1886);
  tft.setTextSize(8);
  tft.setCursor(x, y);
  tft.print("*^_^*");

  // tft.fillRect(x, y, 16, 16, 0x1886);  // Clear the previous face
  //   tft.setCursor(x, y);
  //   tft.print("*^o^*")
}
void cuteFaceOpen() {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  // tft.setTextColor(0xF1CF, 0x1886);  // Set text color to pink, background to white
  tft.setCursor(x, y);
  tft.print("*^o^*");

  // tft.fillRect(x, y, 16, 16, 0x1886);  // Clear the previous face
  //   tft.setCursor(x, y);
  //   tft.print("*^o^*")
}

void defaultFace() {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("^_^");
}

void supriseFace() {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("o_O");

  // tft.fillRect(x, y, 16, 16, 0x1886);  // Clear the previous face
  //   tft.setCursor(x, y);
  //   tft.print("O_o^");
}
void supriseFaceOpen() {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("ovO");

  // tft.fillRect(x, y, 16, 16, 0x1886);  // Clear the previous face
  //   tft.setCursor(x, y);
  //   tft.print("O_o^");
}

void fearFace() {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("@_@");
}
void fearFaceOpen() {
  tft.fillScreen(0x1886);  // Clear the screen
  tft.setTextSize(8);
  tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
  tft.setCursor(x, y);
  tft.print("@o@");
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if (incomingByte == 'z') {
      talking = true;
    } else if (incomingByte == 'x') {
      talking = false;
    }

    if (incomingByte == 'p') {  //Happy
      face = "Happy";
      // cuteFace();
    } else if (incomingByte == 'g') {  //Angry
      face = "Angry";
    } else if (incomingByte == 'r') {  //Suprise
      face = "Suprise";
    } else if (incomingByte == 'd') {  //Sad
      face = "Sad";
    } else if (incomingByte == 'a') {  //Fearful
      face = "Fear";
    }
  }

  if (talking == true) {
    if(face == "Happy"){
      if (open == true) {
          cuteFaceOpen();
          open = false;
        } else if (open == false) {
          cuteFace();
          open = true;
        }
    }
    else if(face == "Sad"){
      if (open == true) {
          sadFaceOpen();
          open = false;
        } else if (open == false) {
          sadFace();
          open = true;
        }
    }
    else if(face == "Angry"){
      if (open == true) {
          angryFaceOpen();
          open = false;
        } else if (open == false) {
          angryFace();
          open = true;
        }
    }
    else if(face == "Suprise"){
      if (open == true) {
          supriseFaceOpen();
          open = false;
        } else if (open == false) {
          supriseFace();
          open = true;
        }
    }
    else if(face == "Fear"){
      if (open == true) {
          fearFaceOpen();
          open = false;
        } else if (open == false) {
          fearFace();
          open = true;
        }
    }
    delay(300);
  } else if (talking == false) {
    if (face != "default") {
      defaultFace();
      face = "default";
    }
  }

  incomingByte = '-1';
}

// testFaces();

// Rotates between all of the screens
void testFaces() {
  cuteFace();
  delay(2000);
  angryFace();
  delay(2000);
  supriseFace();
  delay(2000);
  sadFace();
  delay(2000);
  fearFace();
  delay(2000);
  defaultFace();
}

// void listeningFace(uint16_t x, uint16_t y) {
//   tft.fillScreen(0x1886);  // Clear the screen
//   tft.setTextSize(6);
//   tft.setTextColor(0xFFFF, 0x1886);  // Set text color to white, background to transparent
//   tft.setCursor(x, y);
//   tft.print("Listening");


//   int rectWidth = 10;   // Width of each rectangle
//   int rectHeight = 10;  // Height of each rectangle
//   int numRects = 10;    // Number of rectangles in the wave
//   int waveHeight = 10;  // Amplitude of the wave
//   int waveSpeed = 800;  // Speed of the wave animation in ms

//   int phaseShift = 0;
//   for (int i = 0; i < numRects; i++) {
//     int rectX = x + i * rectWidth;                                         // X position of the current rectangle
//     int rectY = y + waveHeight * sin(2 * PI * i / numRects + phaseShift);  // Y position of the current rectangle
//     tft.fillRect(rectX, rectY, rectWidth, rectHeight, 0xFFFF);             // Draw the rectangle
//   }

//   phaseShift++;
//   if (phaseShift > 1000) {
//     phaseShift = 0;
//   }

//   delay(waveSpeed);  // Wait for the wave to complete a cycle
// }
