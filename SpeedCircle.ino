// Ben Posey, Eric Grasso, John Dott
// Credit to Adafruit for use of their Adafruit NeoPixel Library at https://github.com/adafruit/Adafruit_NeoPixel

#include <Adafruit_NeoPixel.h>
 
#define PIN 6
#define X A0
#define Y A1
#define UPPER 1000
#define LOWER 23
#define MIDU 600  //mid upper
#define MIDL 400  //mid lower

int target;
int correct = 0;
int score = 0;
int overall_score = 0;
int xPos,yPos;
int North[1] = {0};
int South[1] = {8};
int East[1] = {12};
int West[1] = {4};
int NorthEast[3] = {13,14,15};
int NorthWest[3] = {1,2,3};
int SouthWest[3] = {5,6,7};
int SouthEast[3] = {9,10,11};

uint32_t white;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Generate random seed from open analog port
  randomSeed(analogRead(5));
  pinMode(X,INPUT);  //x: 0 < 513 < 1023
  pinMode(Y,INPUT);  //y: 0 < 513 < 1023
  white = strip.Color(255,255,255);
  strip.begin();
  strip.setBrightness(60); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  strip.clear();
  strip.show();
  delay(1000);
  for (int i = 0; i < 5; i++) {
    // Pre-game white loading sequence
    theaterChaseLong(strip.Color(64, 64, 64), 50); // white
    // 16 "events" per level, speed increasing for 5 levels
    level(16, 1000-180*i);
    strip.clear();
    strip.show();
    delay(250);
    // Display score
    colorIterate(score);
    delay(500);
    strip.clear();
    strip.show();
  }
  // End game sequence
  if (overall_score >= 0) {
    theaterChaseRainbow(25);
  } else {
     colorWipe(strip.Color(127, 0, 0), 10); // Red
  }
  strip.clear();
  strip.show();
  delay(1000);
}

void level(int n, int wait) {
  long rng;
  uint16_t i, j;
  score = 0;
  for(i = 0; i < n; i++) {
    unsigned long start_t = 0;
    rng = random(8);
    correct = 0;
    // Light up surrounding LEDs based on rng
    lightDirection(rng, i);
    strip.show();
    start_t = millis();
    while (millis() - start_t < wait) {
      xPos = analogRead(X);
      yPos = analogRead(Y);
  
      if(xPos > MIDL && xPos < MIDU && yPos > MIDL && yPos < MIDU){
        // In middle, do nothing
      }
      else if(xPos >= UPPER){
        groupFill(white,West,1);
      }
      else if(yPos >= UPPER){
        groupFill(white,North,1);
      }
      else if(xPos <= LOWER){
        groupFill(white,East,1);
      }
      else if(yPos <= LOWER){
        groupFill(white,South,1);
      }
      else if(xPos >= 512 && yPos >= 512){
        groupFill(white,NorthWest,3);
      }
      else if(xPos >= 512 && yPos <512){
        groupFill(white,SouthWest,3);
      }
      else if(xPos < 512 && yPos >= 512){
        groupFill(white,NorthEast,3);
      }
      else if(xPos < 512 && yPos < 512){
        groupFill(white,SouthEast,3);
      }
      strip.show();
      
      if (correct == 1) {
        break;
      }
    }
    if (correct == 1) {
      // Display blue if correct
      theaterChase(strip.Color(0, 0, 127), 25); // Blue
      strip.clear();
      strip.show();
      score++;
      overall_score++;
    } else {
      // Display red if correct
      theaterChase(strip.Color(127, 0, 0), 25); // Red
      strip.clear();
      strip.show();
      overall_score--;
    }
    
    //delay(wait/2);
  }
}

void groupFill(uint32_t color, int group[], int len){
  if (len == 3) {
    strip.setPixelColor(group[1],color);
    strip.show();
    if (group[1] == target) {
      correct = 1;
    }
    delay(50);
    strip.setPixelColor(group[1],0,0,0);
  } else {
    strip.setPixelColor(group[0],color);
    strip.show();
    if (group[0] == target) {
      correct = 1;
    }
    delay(50);
    strip.setPixelColor(group[0],0,0,0);
  }
  
}

void lightDirection(long x, uint16_t i) {
  if(x == 0) {
    target = 0;
    strip.setPixelColor(15, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(0, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(1, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 1) {
    target = 2;
    strip.setPixelColor(1, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(2, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(3, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 2) {
    target = 4;
    strip.setPixelColor(3, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(4, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(5, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 3) {
    target = 6;
    strip.setPixelColor(5, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(6, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(7, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 4) {
    target = 8;
    strip.setPixelColor(7, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(8, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(9, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 5) {
    target = 10;
    strip.setPixelColor(9, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(10, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(11, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 6) {
    target = 12;
    strip.setPixelColor(11, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(12, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(13, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 7) {
    target = 14;
    strip.setPixelColor(13, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(14, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(15, Wheel(((i * 256 / strip.numPixels())) & 255));
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t j=1; j<127; j++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i,127-j,0,0);
      strip.show();
      delay(wait);
    }
    delay(wait);
  }
}

void theaterChaseLong(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 5 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<5; j++) {  //do 5 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void colorIterate(int n) {
  uint16_t i;
  for(i=0; i<n;i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.show();
    delay(100+8*i);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 4; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+4) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+4) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

