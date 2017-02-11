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
  randomSeed(analogRead(5));
  pinMode(A0,INPUT);  //x: 0 < 513 < 1023
  pinMode(A1,INPUT);  //y: 0 < 513 < 1023
  //pinMode(3,INPUT);   //switch
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(10); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //Serial.println(analogRead(A0));
  strip.clear();
  strip.show();
  delay(1000);
  strip.setPixelColor(0,255,0,0);
  strip.show();
  delay(200);
  levelOne(64);
}

void levelOne(int n) {
  long rng;
  uint16_t i, j;
  for(i = 0; i < n; i++) {
    rng = random(16);
    Serial.print("RNG: ");
    Serial.println(rng);
    strip.setPixelColor(rng, Wheel(((i * 256 / strip.numPixels())) & 255));
    strip.show();
    delay(500);
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

