// Demo based on:
// UTFT_Demo_320x240 by Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
/*

 This sketch uses the GLCD and font 2 only. Disable other fonts to make
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

#define TFT_GREY 0x7BEF

// TFT_ILI9341 myGLCD = TFT_ILI9341();       // Invoke custom library

static unsigned long runTime = 0;
void setup_UTFT_demo_fast_2(void)
{
  // randomSeed(analogRead(A0));
  // pinMode(7, OUTPUT);
  // digitalWrite(7, LOW);
  // delay(10);
  // digitalWrite(7, HIGH);
// Setup the LCD
  // init();
  setRotation(3);
}

void loop_UTFT_demo_fast_2(void)
{
  // randomSeed(millis());
  //randomSeed(1234); // This ensure test is repeatable with exact same draws each loop
  int buf[318];
  int x, x2;
  int y, y2;
  int r;
  int i=9;
  int col = 0;
  int colour = 0;  
  byte j = 0;
  runTime = millis();
// Clear the screen and draw the frame
  fillScreen(TFT_BLACK);


  fillRect(0, 0, 319, 14,TFT_RED);

  fillRect(0, 226, 319, 14,TFT_GREY);

  setTextColor2(TFT_BLACK,TFT_RED);
  drawCentreString("* TFT_ILI9341 *", 160, 4, 1);
  setTextColor2(TFT_YELLOW,TFT_GREY);
  drawCentreString("Adapted by Bodmer", 160, 228,1);

  drawRect(0, 14, 319, 211, TFT_BLUE);

// Draw crosshairs
  drawLine(159, 15, 159, 224,TFT_BLUE);
  drawLine(1, 119, 318, 119,TFT_BLUE);
  for (i=9; i<310; i+=10)
    drawLine(i, 117, i, 121,TFT_BLUE);
  for (i=19; i<220; i+=10)
    drawLine(157, i, 161, i,TFT_BLUE);

// Draw sin-, cos- and tan-lines  
  setTextColor1(TFT_CYAN);
  drawString("Sin", 5, 15,2);
  for (i=1; i<318; i++)
  {
    drawPixel(i,119+(sin(((i*1.13)*3.14)/180)*95),TFT_CYAN);
  }
  setTextColor1(TFT_RED);
  drawString("Cos", 5, 30,2);
  for (i=1; i<318; i++)
  {
    drawPixel(i,119+(cos(((i*1.13)*3.14)/180)*95),TFT_RED);
  }
  setTextColor1(TFT_YELLOW);
  drawString("Tan", 5, 45,2);
  for (i=1; i<318; i++)
  {
    drawPixel(i,119+(tan(((i*1.13)*3.14)/180)),TFT_YELLOW);
  }

  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

  drawLine(159, 15, 159, 224,TFT_BLUE);
  drawLine(1, 119, 318, 119,TFT_BLUE);
// int col = 0;
// Draw a moving sinewave
  x=1;
  for (i=1; i<(317*20); i++) 
  {
    x++;
    if (x==318)
      x=1;
    if (i>318)
    {
      if ((x==159)||(buf[x-1]==119))
        col = TFT_BLUE;
      else
      drawPixel(x,buf[x-1],TFT_BLACK);
    }
    y=119+(sin(((i*1.1)*3.14)/180)*(90-(i / 100)));
    drawPixel(x,y,TFT_BLUE);
    buf[x-1]=y;
  }

  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

// Draw some filled rectangles
  for (i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        col = TFT_MAGENTA;
        break;
      case 2:
        col = TFT_RED;
        break;
      case 3:
        col = TFT_GREEN;
        break;
      case 4:
        col = TFT_BLUE;
        break;
      case 5:
        col = TFT_YELLOW;
        break;
    }
    fillRect(70+(i*20), 30+(i*20), 60, 60,col);
  }

  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

// Draw some filled, rounded rectangles
  for (i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        col = TFT_MAGENTA;
        break;
      case 2:
        col = TFT_RED;
        break;
      case 3:
        col = TFT_GREEN;
        break;
      case 4:
        col = TFT_BLUE;
        break;
      case 5:
        col = TFT_YELLOW;
        break;
    }
    fillRoundRect(190-(i*20), 30+(i*20), 60,60, 3,col);
  }
  
  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

// Draw some filled circles
  for (i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        col = TFT_MAGENTA;
        break;
      case 2:
        col = TFT_RED;
        break;
      case 3:
        col = TFT_GREEN;
        break;
      case 4:
        col = TFT_BLUE;
        break;
      case 5:
        col = TFT_YELLOW;
        break;
    }
    fillCircle(100+(i*20),60+(i*20), 30,col);
  }
  
  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

// Draw some lines in a pattern

  for (i=15; i<224; i+=5)
  {
    drawLine(1, i, (i*1.44)-10, 223,TFT_RED);
  }

  for (i=223; i>15; i-=5)
  {
    drawLine(317, i, (i*1.44)-11, 15,TFT_RED);
  }

  for (i=223; i>15; i-=5)
  {
    drawLine(1, i, 331-(i*1.44), 15,TFT_CYAN);
  }

  for (i=15; i<224; i+=5)
  {
    drawLine(317, i, 330-(i*1.44), 223,TFT_CYAN);
  }
  
  //delay(2000);


  fillRect(1,15,317,209,TFT_BLACK);

// Draw some random circles
  for (i=0; i<100; i++)
  {
    x=32+random(0,256);
    y=45+random(0,146);
    r=random(0,30);
    drawCircle(x, y, r,(uint16_t)random(0,0xFFFF));
  }

  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

// Draw some random rectangles
  for (i=0; i<100; i++)
  {
    x=2+random(0,316);
    y=16+random(0,207);
    x2=2+random(0,316);
    y2=16+random(0,207);
    if (x2<x) {
      r=x;x=x2;x2=r;
    }
    if (y2<y) {
      r=y;y=y2;y2=r;
    }
    drawRect(x, y, x2-x, y2-y,(uint16_t) random(0,0xFFFF));
  }

  //delay(2000);


  fillRect(1,15,317,209,TFT_BLACK);

// Draw some random rounded rectangles
  for (i=0; i<100; i++)
  {
    x=2+random(0,316);
    y=16+random(0,207);
    x2=2+random(0,316);
    y2=16+random(0,207);
    // We need to get the width and height and do some window checking
    if (x2<x) {
      r=x;x=x2;x2=r;
    }
    if (y2<y) {
      r=y;y=y2;y2=r;
    }
    // We need a minimum size of 6
    if((x2-x)<6) x2=x+6;
    if((y2-y)<6) y2=y+6;
    drawRoundRect(x, y, x2-x,y2-y, 3,(uint16_t) random(0,0xFFFF));
  }

  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

 //randomSeed(1234);
//  int colour = 0;
 for (i=0; i<100; i++)
  {
    x=2+random(0,316);
    y=16+random(0,209);
    x2=2+random(0,316);
    y2=16+random(0,209);
    colour= (uint16_t) random(0,0xFFFF);
    drawLine(x, y, x2, y2,colour);
  }

  //delay(2000);

  fillRect(1,15,317,209,TFT_BLACK);

  // This test has been modified as it takes more time to calculate the random numbers
  // than to draw the pixels (3 seconds to produce 30,000 randoms)!
  //for (int i=0; i<10000; i++)
  //{
  //  drawPixel(2+random(0,316), 16+random(0,209),(uint16_t) random(0,0xFFFF));
  //}

  // Draw 10,000 pixels to fill a 100x100 pixel box
  // use the coords as the colour to produce the banding
  i = 100;
  while (i--) {
    j = 100;
    while (j--) drawPixel(i+110,j+70,i+j);
    //while (j--) drawPixel(i+110,j+70,0xFFFF);
  }
  //delay(2000);

  fillScreen(TFT_BLUE);
  fillRoundRect(80, 70, 239-80,169-70, 3,TFT_RED);
  
  setTextColor2(TFT_WHITE,TFT_RED);
  drawCentreString("That's it!", 160, 93,2);
  drawCentreString("Restarting in a", 160, 119,2);
  drawCentreString("few seconds...", 160, 132,2);

  runTime = millis()-runTime;
  setTextColor2(TFT_GREEN,TFT_BLUE);
  drawCentreString("Runtime: (msecs)", 160, 210,2);
  drawNumber(runTime, 130, 225,2);
  delay (5000);
}


