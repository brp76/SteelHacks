#include <Adafruit_NeoPixel.h>
#define PIN 6
#define X A0
#define Y A1
#define UPPER 1000
#define LOWER 23
#define MIDU 600  //mid upper
#define MIDL 400  //mid lower

int xPos,yPos;
int North[1] = {0};
int South[1] = {8};
int East[1] = {12};
int West[1] = {4};
int NorthEast[3] = {13,14,15};
int NorthWest[3] = {1,2,3};
int SouthWest[3] = {5,6,7};
int SouthEast[3] = {9,10,11};

uint32_t red;
uint32_t black;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16,PIN,NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  strip.begin();
  colorFill(strip.Color(0,0,0)); //setting the pixels to black
  strip.setBrightness(30);
  strip.show();
  red = strip.Color(255,0,0);
  black = strip.Color(0,0,0);
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.clear();
  xPos = analogRead(X);
  yPos = analogRead(Y);

  if(xPos > MIDL && xPos < MIDU && yPos > MIDL && yPos < MIDU){
    
  }
  else if(xPos >= UPPER){
    groupFill(red,West,1);
  }
  else if(yPos >= UPPER){
    groupFill(red,North,1);
  }
  else if(xPos <= LOWER){
    groupFill(red,East,1);
  }
  else if(yPos <= LOWER){
    groupFill(red,South,1);
  }
  else if(xPos >= 512 && yPos >= 512){
    groupFill(red,NorthWest,3);
  }
  else if(xPos >= 512 && yPos <512){
    groupFill(red,SouthWest,3);
  }
  else if(xPos < 512 && yPos >= 512){
    groupFill(red,NorthEast,3);
  }
  else if(xPos < 512 && yPos < 512){
    groupFill(red,SouthEast,3);
  }
  strip.show();
  delay(100); 
}

void colorFill(uint32_t color){
  for(int i=0; i<16; i++){
    strip.setPixelColor(i,color);
  }
}

void groupFill(uint32_t color, int group[], int len){
  for(int i=0; i<len; i++){
    strip.setPixelColor(group[i],color);
  }
}

