#include <Adafruit_NeoPixel.h>
 
#define PIN 6

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
  pinMode(A0,INPUT);  //x: 0 < 513 < 1023
  pinMode(A1,INPUT);  //y: 0 < 513 < 1023
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(30); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  strip.clear();
  strip.show();
  delay(1000);
  for (int i = 0; i < 5; i++) {
    // Pre-game white loading sequence
    theaterChaseLong(strip.Color(127, 127, 127), 50); // white
    // 16 "events" per level, speed increasing for 5 levels
    level(16, 1000-190*i);
    strip.clear();
    strip.show();
    delay(250);
    // Display score
    colorIterate();
    delay(500);
    strip.clear();
    strip.show();
  }
  // End game sequence
  theaterChaseRainbow(33);
  strip.clear();
  strip.show();
  delay(1000);
}

void level(int n, int wait) {
  long rng;
  int correct = 1;
  uint16_t i, j;
  for(i = 0; i < n; i++) {
    rng = random(8);
    Serial.print("RNG: ");
    Serial.println(rng);
    // Light up surrounding LEDs based on rng
    lightDirection(rng, i);
    strip.show();
    delay(wait);
    //strip.clear();
    //strip.show();
    // Display blue if correct
    theaterChase(strip.Color(0, 0, 127), 25); // Blue
    strip.clear();
    strip.show();
    //delay(wait/2);
  }
}

void lightDirection(long x, uint16_t i) {
  if(x == 0) {
    strip.setPixelColor(15, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(0, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(1, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 1) {
    strip.setPixelColor(1, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(2, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(3, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 2) {
    strip.setPixelColor(3, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(4, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(5, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 3) {
    strip.setPixelColor(5, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(6, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(7, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 4) {
    strip.setPixelColor(7, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(8, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(9, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 5) {
    strip.setPixelColor(9, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(10, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(11, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 6) {
    strip.setPixelColor(11, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(12, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(13, Wheel(((i * 256 / strip.numPixels())) & 255));
  } else if(x == 7) {
    strip.setPixelColor(13, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(14, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.setPixelColor(15, Wheel(((i * 256 / strip.numPixels())) & 255));
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

void colorIterate() {
  uint16_t i;
  for(i=0; i<16;i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.show();
    delay(50+3*i);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
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

