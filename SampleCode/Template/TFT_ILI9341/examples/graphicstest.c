/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


// #include "SPI.h"
// #include "Adafruit_GFX.h"
// #include "Adafruit_ILI9341.h"
#include <TFT_ILI9341.h>

// For the Adafruit shield, these are the default.
// #define TFT_DC 9
// #define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);



unsigned long testFillScreen() {
  unsigned long start = micros();

  fillScreen(ILI9341_BLACK);
  
  fillScreen(ILI9341_RED);
  
  fillScreen(ILI9341_GREEN);
  
  fillScreen(ILI9341_BLUE);
  
  fillScreen(ILI9341_BLACK);
  
  return micros() - start;
}

// unsigned long testText() {
//   fillScreen(ILI9341_BLACK);
//   unsigned long start = micros();
//   setCursor(0, 0);
//   setTextColor(ILI9341_WHITE);  setTextSize(1);
//   println("Hello World!");
//   setTextColor(ILI9341_YELLOW); setTextSize(2);
//   println(1234.56);
//   setTextColor(ILI9341_RED);    setTextSize(3);
//   println(0xDEADBEEF, HEX);
//   println();
//   setTextColor(ILI9341_GREEN);
//   setTextSize(5);
//   println("Groop");
//   setTextSize(2);
//   println("I implore thee,");
//   setTextSize(1);
//   println("my foonting turlingdromes.");
//   println("And hooptiously drangle me");
//   println("with crinkly bindlewurdles,");
//   println("Or I will rend thee");
//   println("in the gobberwarts");
//   println("with my blurglecruncheon,");
//   println("see if I don't!");
//   return micros() - start;
// }

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = width(),
                h = height();

  fillScreen(ILI9341_BLACK);
  
  
  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  
  fillScreen(ILI9341_BLACK);
  

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  
  fillScreen(ILI9341_BLACK);
  

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  
  fillScreen(ILI9341_BLACK);
  

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);

  
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = width(), h = height();

  fillScreen(ILI9341_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = width()  / 2,
                cy = height() / 2;

  fillScreen(ILI9341_BLACK);
  n     = min(width(), height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  n = min(width(), height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    drawRect(cx-i2, cy-i2, i, i, color2);
    
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = width(), h = height(), r2 = radius * 2;

  fillScreen(ILI9341_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = width()  + radius,
                h = height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = width()  / 2 - 1,
                      cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      color565(i, i, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = width()  / 2 - 1,
                   cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(0, i*10, i*10));
    t += micros() - start;
    drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(i*10, i*10, 0));
    
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  w     = min(width(), height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    drawRoundRect(cx-i2, cy-i2, i, i, i/8, color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(width(), height()); i>20; i-=6) {
    i2 = i / 2;
    fillRoundRect(cx-i2, cy-i2, i, i, i/8, color565(0, i, 0));
    
  }

  return micros() - start;
}



void setup_graphicstest(void) {

  uint32_t x = 0;
  // Serial.begin(9600);
  // x = "ILI9341 Test!"); 
 
  // begin();

  // read diagnostics (optional but can help debug problems)
  x = LCD_RD_REG(ILI9341_RDMODE);
  printf("Display Power Mode: 0x");   printf("%2X\r\n" , x);
  x = LCD_RD_REG(ILI9341_RDMADCTL);
  printf("MADCTL Mode: 0x");   printf("%2X\r\n" , x);
  x = LCD_RD_REG(ILI9341_RDPIXFMT);
  printf("Pixel Format: 0x");   printf("%2X\r\n" , x);
  x = LCD_RD_REG(ILI9341_RDIMGFMT);
  printf("Image Format: 0x");   printf("%2X\r\n" , x);
  x = LCD_RD_REG(ILI9341_RDSELFDIAG);
  printf("Self Diagnostic: 0x");   printf("%2X\r\n" , x); 
  
  printf("Benchmark                Time (microseconds)\r\n");
  delay(10);
  printf("Screen fill              ");
  x = testFillScreen();   printf("%dms\r\n" , x); 
  delay(500);

  // printf("Text                     ");
  // x = testText();   printf("%dms\r\n" , x); 
  // delay(3000);

  printf("Lines                    ");
  x = testLines(ILI9341_CYAN);   printf("%dms\r\n" , x); 
  delay(500);

  printf("Horiz/Vert Lines         ");
  x = testFastLines(ILI9341_RED, ILI9341_BLUE);   printf("%dms\r\n" , x); 
  delay(500);

  printf("Rectangles (outline)     ");
  x = testRects(ILI9341_GREEN);   printf("%dms\r\n" , x); 
  delay(500);

  printf("Rectangles (filled)      ");
  x = testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA);   printf("%dms\r\n" , x); 
  delay(500);

  printf("Circles (filled)         ");
  x = testFilledCircles(10, ILI9341_MAGENTA);   printf("%dms\r\n" , x); 

  printf("Circles (outline)        ");
  x = testCircles(10, ILI9341_WHITE);   printf("%dms\r\n" , x); 
  delay(500);

  printf("Triangles (outline)      ");
  x = testTriangles();   printf("%dms\r\n" , x); 
  delay(500);

  printf("Triangles (filled)       ");
  x = testFilledTriangles();   printf("%dms\r\n" , x); 
  delay(500);

  printf("Rounded rects (outline)  ");
  x = testRoundRects();   printf("%dms\r\n" , x); 
  delay(500);

  printf("Rounded rects (filled)   ");
  x = testFilledRoundRects();   printf("%dms\r\n" , x); 
  delay(500);

  printf("Done!\r\n");

}


void loop_graphicstest(void) {
  uint8_t rotation=0;

  for(rotation=0; rotation<4; rotation++) {
    setRotation(rotation);
    // testText();
    delay(1000);
  }
}

