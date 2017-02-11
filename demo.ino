#include <Adafruit_NeoPixel.h>
#define PIN 6
#define X A0
#define Y A1

//int yPairs[2][8] = {{7,6,5,4,3,2,1,0},{8,9,10,11,12,13,14,15}};
int yPairs[2][8] = {{0,1,2,3,4,5,6,7},{15,14,13,12,11,10,9,8}};
int xPairs[2][8] = {{3,2,1,0,15,14,13,12},{4,5,6,7,8,9,10,11}};
int xPos,yPos;

int demoPairs[2][8] = {{0,2,4,6,8,10,12,14},{15,1,3,5,7,9,11,13}};
int a,b,c,d;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16,PIN,NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  strip.begin();
  colorFill(strip.Color(0,0,0)); //setting the pixels to black
  strip.setBrightness(30);
  strip.show();

  pinMode(X,INPUT);
  pinMode(Y,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.clear();
  xPos = analogRead(X);
  yPos = analogRead(Y);
  //xPos = xPos/128;
  //yPos = yPos/128;
  xPos = map(xPos, 0, 1023, 0, 7);
  yPos = map(yPos, 0, 1023, 0, 7);
  a = xPairs[0][xPos];  //first of two lights at given x position
  b = xPairs[1][xPos];  //pairing light at given x position
  c = yPairs[0][yPos];  //pair of ligts at given y position
  d = yPairs[1][yPos];
  if(a == c || a == d){
    strip.setPixelColor(a,strip.Color(0,255,0));
    for(int i=0; i<8; i++){
      if(demoPairs[0][i] == a){
        strip.setPixelColor(demoPairs[1][i],strip.Color(0,255,0));
        strip.show();
        delay(100);
        strip.setPixelColor(demoPairs[1][i],strip.Color(0,0,0));
        strip.setPixelColor(a,strip.Color(0,0,0));
        strip.show();
        break;
      }
      if(demoPairs[1][i] == a){
        strip.setPixelColor(demoPairs[0][i],strip.Color(0,255,0));
        strip.show();
        delay(100);
        strip.setPixelColor(demoPairs[0][i],strip.Color(0,0,0));
        strip.setPixelColor(a,strip.Color(0,0,0));
        strip.show();
        break;
      }
    }
       
  }
  else if(b==c || b==d){
    strip.setPixelColor(b,strip.Color(0,255,0));
    for(int i=0; i<8; i++){
      if(demoPairs[0][i] == b){
        strip.setPixelColor(demoPairs[1][i],strip.Color(0,255,0));
        strip.show();
        delay(100);
        strip.setPixelColor(demoPairs[1][i],strip.Color(0,0,0));
        strip.setPixelColor(b,strip.Color(0,0,0));
        strip.show();
        break;
      }
      if(demoPairs[1][i] == b){
        strip.setPixelColor(demoPairs[0][i],strip.Color(0,255,0));
        strip.show();
        delay(100);
        strip.setPixelColor(demoPairs[1][i],strip.Color(0,0,0));
        strip.setPixelColor(b,strip.Color(0,0,0));
        strip.show();
        break;
      }
    } 
  }
  
  
  
}

void colorFill(uint32_t color){
  for(int i=0; i<16; i++){
    strip.setPixelColor(i,color);
  }
}


