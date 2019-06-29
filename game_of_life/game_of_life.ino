#include "FastLED.h"

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN 3
#define LED_TYPE WS2811
#define COLOR_ORDER RBG
#define WIDTH 15
#define HEIGHT 20
#define NUM_LEDS WIDTH * HEIGHT
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 10
#define SECONDS 1

#define ALIVE 1
#define DEAD 0

int cells[WIDTH][HEIGHT];

void setup() {
  Serial.begin(9600);
  
  delay(3000); // 3 second delay for recovery
  
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  initGameOfLife();
}
  
void loop() {        
  gameOfLife();
}

void initGameOfLife() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      cells[x][y] = random(DEAD, ALIVE + 1);
    }  
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 255, 255);
  }

  FastLED.show();
}

void gameOfLife() {
  applyRules();
  draw();
}


void applyRules() {// TODO: optimize! We cycle through all of the led's twice (here + in draw())
  for (int i = 0; i < NUM_LEDS; i++) {
    int a, b;
    coordinate(i, &a, &b);

    int neighborCount = numerOfNeighborsAlive(a, b);
    
    if (neighborCount > 3 || neighborCount < 2) {
        cells[a][b] = DEAD;
    } /*else if (neighborCount == 2) {
        if (cells[a][b] == ALIVE) {
            cells[a][b] = ALIVE;
        } else {
            cells[a][b] = DEAD;
        }
    } */else {
        cells[a][b] = ALIVE;
    }
  }
}

void draw() {
      for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        int s = cells[x][y];
        int i = index(x, y);
  
        if (s == DEAD) {
          leds[i].nscale8( 64 );// = CRGB(0, 0, 0); 
        } else {
          leds[i].nscale8( 192 );// = CRGB(255, 255, 255); 
        }

        Serial.println(leds[i]);
      }  
    }
  FastLED.show();
  //delay(1000);
}

void coordinate(int i, int *x, int *y) {
    int _y = i / WIDTH;
    int _x = i - (WIDTH * _y);
    
    *x = _x;
    *y = _y;
}

int index(int x, int y) {
    if (x == 0 && y == 0 ) { return 0; }
    return y * WIDTH + x;
}

int numerOfNeighborsAlive(int x, int y) {
  int count = 0;
  
  for (int _y = -1; _y < 2; _y++) {
    if (!isSafeY(_y)) continue;
    
    for (int _x = -1; _x < 2; _x++) {
      if (!isSafeX(_x)) continue;

      int cx = x + _x;
      int cy = y + _y;

      if (cx == x && cy == y) continue;
      
      if (cells[cx][cx] == ALIVE) {
        count++;
      }
    }  
  }

  return count;
}

boolean isSafeX(int x) {
  return x < WIDTH;
}

boolean isSafeY(int y) {
  return y < HEIGHT;
}

void calibrateRGB() {
   leds[0] = CRGB(255,0,0); // red
   leds[1] = CRGB(0,255,0); // blue
   leds[2] = CRGB(0,255,0); // blue
   leds[3] = CRGB(0,0,255); // green
   leds[4] = CRGB(0,0,255); // green
   leds[5] = CRGB(0,0,255); // green
   
   FastLED.show();
   delay(1000);
}
