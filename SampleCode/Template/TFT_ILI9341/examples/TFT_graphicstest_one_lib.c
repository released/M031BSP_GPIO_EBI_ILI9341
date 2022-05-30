/*
 Adapted from the Adafruit graphicstest sketch.

 This sketch uses the GLCD font (font 1) only. Disable other fonts to make
 the sketch fit in an UNO!

 Make sure all the required fonts are loaded by editting the
 User_Setup.h file in the TFT_ILI9341 library folder.

 If using an UNO or Mega (ATmega328 or ATmega2560 processor) then for best
 performance use the F_AS_T option found in the User_Setup.h file in the
 TFT_ILI9341 library folder.

 The library uses the hardware SPI pins only:
   For UNO, Nano, Micro Pro ATmega328 based processors
      MOSI = pin 11, SCK = pin 13
   For Mega:
      MOSI = pin 51, SCK = pin 52

 The pins used for the TFT chip select (CS) and Data/command (DC) and Reset (RST)
 signal lines to the TFT must also be defined in the library User_Setup.h file.

 Sugested TFT connections for UNO and Atmega328 based boards
   sclk 13  // Don't change, this is the hardware SPI SCLK line
   mosi 11  // Don't change, this is the hardware SPI MOSI line
   cs   10  // Chip select for TFT display
   dc   9   // Data/command line
   rst  7   // Reset, you could connect this to the Arduino reset pin

 Suggested TFT connections for the MEGA and ATmega2560 based boards
   sclk 52  // Don't change, this is the hardware SPI SCLK line
   mosi 51  // Don't change, this is the hardware SPI MOSI line
   cs   47  // TFT chip select line
   dc   48  // TFT data/command line
   rst  44  // you could alternatively connect this to the Arduino reset

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######       TO SELECT THE FONTS AND PINS YOU USE, SEE ABOVE       ######
  #########################################################################
 */


// #include "SPI.h"
#include "TFT_ILI9341.h"

// Use hardware SPI
// TFT_ILI9341 tft = TFT_ILI9341();

// static unsigned long total = 0;
static unsigned long tn = 0;

static unsigned long testFillScreen(void);
static unsigned long testText(void); 
static unsigned long testLines(uint16_t color); 
static unsigned long testFastLines(uint16_t color1, uint16_t color2); 
static unsigned long testRects(uint16_t color);
static unsigned long testFilledRects(uint16_t color1, uint16_t color2);
static unsigned long testFilledCircles(uint8_t radius, uint16_t color); 
static unsigned long testCircles(uint8_t radius, uint16_t color); 
static unsigned long testTriangles(void);
static unsigned long testFilledTriangles(void);
static unsigned long testRoundRects(void); 
static unsigned long testFilledRoundRects(void);


void setup_TFT_graphicstest_one_lib(void) {
  // Serial.begin(115200);
  // while (!Serial);

  // Serial.printf("TFT_ILI9341 2.2\" SPI TFT Test!"); 
 
  // init();
  unsigned long x = 0;

  tn = micros();
  fillScreen(TFT_BLACK);

  printf("Benchmark                Time (microseconds)\r\n");

  printf("Screen fill              ");
  x = testFillScreen();printf("%dms\r\n" , x);//Serial.println(testFillScreen());
  //total+=testFillScreen();
  //delay(500);

  printf("Text                     ");
  x = testText();printf("%dms\r\n" , x);//  Serial.println(testText());
  //total+=testText();
  //delay(3000);

  printf("Lines                    ");
  x = testLines(TFT_CYAN);printf("%dms\r\n" , x);//  Serial.println(testLines(TFT_CYAN));
  //total+=testLines(TFT_CYAN);
  //delay(500);

  printf("Horiz/Vert Lines         ");
  x = testFastLines(TFT_RED, TFT_BLUE);printf("%dms\r\n" , x);//  Serial.println(testFastLines(TFT_RED, TFT_BLUE));
  //total+=testFastLines(TFT_RED, TFT_BLUE);
  //delay(500);

  printf("Rectangles (outline)     ");
  x = testRects(TFT_GREEN);printf("%dms\r\n" , x);//  Serial.println(testRects(TFT_GREEN));
  //total+=testRects(TFT_GREEN);
  //delay(500);

  printf("Rectangles (filled)      ");
  x = testFilledRects(TFT_YELLOW, TFT_MAGENTA);printf("%dms\r\n" , x);//  Serial.println(testFilledRects(TFT_YELLOW, TFT_MAGENTA));
  //total+=testFilledRects(TFT_YELLOW, TFT_MAGENTA);
  //delay(500);

  printf("Circles (filled)         ");
  x = testFilledCircles(10, TFT_MAGENTA);printf("%dms\r\n" , x);//  Serial.println(testFilledCircles(10, TFT_MAGENTA));
  //total+= testFilledCircles(10, TFT_MAGENTA);
  
  printf("Circles (outline)        ");
  x = testCircles(10, TFT_WHITE);printf("%dms\r\n" , x);//  Serial.println(testCircles(10, TFT_WHITE));
  //total+=testCircles(10, TFT_WHITE);
  //delay(500);

  printf("Triangles (outline)      ");
  x = testTriangles();printf("%dms\r\n" , x);//  Serial.println(testTriangles());
  //total+=testTriangles();
  //delay(500);

  printf("Triangles (filled)       ");
  x = testFilledTriangles();printf("%dms\r\n" , x);//  Serial.println(testFilledTriangles());
  //total += testFilledTriangles();
  //delay(500);

  printf("Rounded rects (outline)  ");
  x = testRoundRects();printf("%dms\r\n" , x);//  Serial.println(testRoundRects());
  //total+=testRoundRects();
  //delay(500);

  printf("Rounded rects (filled)   ");
  x = testFilledRoundRects();printf("%dms\r\n" , x);//  Serial.println(testFilledRoundRects());
  //total+=testFilledRoundRects();
  //delay(500);

  printf("Done! Total = ");printf("%dms\r\n" , millis()-tn); //Serial.println(total);

  //Serial.println(millis()-tn);
}

void loop_TFT_graphicstest_one_lib(void) {
  uint8_t rotation=0;  
  for( rotation=0; rotation<4; rotation++) {
    setRotation(rotation);
    testText();
    delay(2000);
  }
}


static unsigned long testFillScreen() {
  unsigned long start = micros();
  fillScreen(TFT_BLACK);
  fillScreen(TFT_RED);
  fillScreen(TFT_GREEN);
  fillScreen(TFT_BLUE);
  fillScreen(TFT_BLACK);
  return micros() - start;
}

static unsigned long testText() {
  char tmp[24];  
  unsigned long start = micros();  
  fillScreen(TFT_BLACK);

  setCursor2(0, 0);
  setTextColor1(TFT_WHITE);  //setTextSize(1);
  drawString("Hello World!",0,0,1);//println("Hello World!");
  setTextColor1(TFT_YELLOW); //setTextSize(2);
  sprintf(tmp,"%4.2f" , 1234.56);
  drawString(tmp, 10, 20, 2); //println(1234.56); 
  setTextColor1(TFT_RED);    //setTextSize(3);
  sprintf(tmp,"0x%6X" , 0xDEADBEEF);
  drawString(tmp, 1, 40, 2);//println(0xDEADBEEF, HEX);
  // println();
  setTextColor1(TFT_GREEN);
  // setTextSize(5);
  drawString("Groop",70,90,4);//println("Groop");
  // setTextSize(2);
  drawString("I implore thee,",140,50,2);//println("Groop");
  //setTextColor2(TFT_GREEN,TFT_BLACK);
  // setTextSize(1);
  drawString("my foonting turlingdromes.",30,130,1);//println("my foonting turlingdromes.");
  drawString("And hooptiously drangle me",30,140,1);//println("And hooptiously drangle me");
  drawString("with crinkly bindlewurdles,",30,150,1);//println("with crinkly bindlewurdles,");
  drawString("Or I will rend thee",30,170,1);//println("Or I will rend thee");
  drawString("in the gobberwarts",30,180,1);//println("in the gobberwarts");
  drawString("with my blurglecruncheon,",30,190,1);//println("with my blurglecruncheon,");
  drawString("see if I don't!",30,200,1);//println("see if I don't!");
  return micros() - start;
}

static unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = width(),
                h = height();

  fillScreen(TFT_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  fillScreen(TFT_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  fillScreen(TFT_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  fillScreen(TFT_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

static unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = width(), h = height();

  fillScreen(TFT_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

static unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = width()  / 2,
                cy = height() / 2;

  fillScreen(TFT_BLACK);
  n     = min(width(), height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

static unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(TFT_BLACK);
  n = min(width(), height());
  for(i=n-1; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

static unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = width(), h = height(), r2 = radius * 2;

  fillScreen(TFT_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

static unsigned long testCircles(uint8_t radius, uint16_t color) {
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

static unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = width()  / 2 - 1,
                      cy = height() / 2 - 1;

  fillScreen(TFT_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      color565(0, 0, i));
  }

  return micros() - start;
}

static unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = width()  / 2 - 1,
                   cy = height() / 2 - 1;

  fillScreen(TFT_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(0, i, i));
    t += micros() - start;
    drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(i, i, 0));
  }

  return t;
}

static unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(TFT_BLACK);
  w     = min(width(), height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    drawRoundRect(cx-i2, cy-i2, i, i, i/8, color565(i, 0, 0));
  }

  return micros() - start;
}

static unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(TFT_BLACK);
  start = micros();
  for(i=min(width(), height()); i>20; i-=6) {
    i2 = i / 2;
    fillRoundRect(cx-i2, cy-i2, i, i, i/8, color565(0, i, 0));
  }

  return micros() - start;
}

/***************************************************
  Original Adafruit text:

  This is an example sketch for the Adafruit 2.2" SPI display.
  This library works with the Adafruit 2.2" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/1480
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
 
