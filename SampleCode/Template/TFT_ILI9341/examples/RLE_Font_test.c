/*
 Display all the fonts.

 This sketch uses the GLCD (font 1) and fonts 2, 4, 6, 7, 8
 
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

// New background colour
#define TFT_BROWN 0x38E0

// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT (500)

#include <TFT_ILI9341.h> // Graphics and font library for ILI9341 driver chip
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();  // Invoke library, pins defined in User_Setup.h

static unsigned long targetTime = 0; // Used for testing draw times

void setup_RLE_Font_test(void) {
  // init();

  // if(g_InitOnce == 0)
  //     g_InitOnce = 1;
  // else
  //     return;
        
  setRotation(3);
}

void loop_RLE_Font_test(void) {
  int xpos = 0;

  targetTime = millis();

  // First we test them with a background colour set
  setTextSize(1);
  fillScreen(TFT_BLACK);
  setTextColor2(TFT_GREEN, TFT_BLACK);

  drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);
  drawString("789:;<=>?@ABCDEFGHIJKL", 0, 16, 2);
  drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 32, 2);
  drawString("abcdefghijklmnopqrstuvw", 0, 48, 2);
  // int xpos = 0;
  xpos += drawString("xyz{|}~", 0, 64, 2);
  drawChar4(127, xpos, 64, 2);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_GREEN, TFT_BLACK);

  drawString(" !\"#$%&'()*+,-.", 0, 0, 4);
  drawString("/0123456789:;", 0, 26, 4);
  drawString("<=>?@ABCDE", 0, 52, 4);
  drawString("FGHIJKLMNO", 0, 78, 4);
  drawString("PQRSTUVWX", 0, 104, 4);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  drawString("YZ[\\]^_`abc", 0, 0, 4);
  drawString("defghijklmno", 0, 26, 4);
  drawString("pqrstuvwxyz", 0, 52, 4);
  xpos = 0;
  xpos += drawString("{|}~", 0, 78, 4);
  drawChar4(127, xpos, 78, 4);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_BLUE, TFT_BLACK);

  drawString("012345", 0, 0, 6);
  drawString("6789", 0, 40, 6);
  drawString("apm-:.", 0, 80, 6);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_RED, TFT_BLACK);

  drawString("0123", 0, 0, 7);
  drawString("4567", 0, 60, 7);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  drawString("890:.", 0, 0, 7);
  drawString("", 0, 60, 7);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_YELLOW, TFT_BLACK);

  drawString("0123", 0, 0, 8);
  drawString("4567", 0, 72, 8);
  delay(WAIT);;

  fillScreen(TFT_BLACK);
  drawString("890:.", 0, 0, 8);
  drawString("", 0, 72, 8);
  delay(WAIT);;

  setTextSize(2);
  fillScreen(TFT_BLACK);
  setTextColor2(TFT_GREEN, TFT_BLACK);

  drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);
  drawString("789:;<=>?@ABCDEFGHIJKL", 0, 32, 2);
  drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 64, 2);
  drawString("abcdefghijklmnopqrstuvw", 0, 96, 2);
  xpos = 0;
  xpos += drawString("xyz{|}~", 0, 128, 2);
  drawChar4(127, xpos, 128, 2);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_GREEN, TFT_BLACK);

  drawString(" !\"#$%&'()*+,-.", 0, 0, 4);
  drawString("/0123456789:;", 0, 52, 4);
  drawString("<=>?@ABCDE", 0, 104, 4);
  drawString("FGHIJKLMNO", 0, 156, 4);
  drawString("PQRSTUVWX", 0, 208, 4);
  delay(WAIT);
  fillScreen(TFT_BLACK);
  drawString("YZ[\\]^_`abc", 0, 0, 4);
  drawString("defghijklmno", 0, 52, 4);
  drawString("pqrstuvwxyz", 0, 104, 4);
  xpos = 0;
  xpos += drawString("{|}~", 0, 156, 4);
  drawChar4(127, xpos, 156, 4);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_BLUE, TFT_BLACK);

  drawString("01234", 0, 0, 6);
  drawString("56789", 0, 80, 6);
  drawString("apm-:.", 0, 160, 6);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_RED, TFT_BLACK);

  drawString("0123", 0, 0, 7);
  drawString("4567", 0, 120, 7);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  drawString("890:.", 0, 0, 7);
  drawString("", 0, 120, 7);
  delay(WAIT);

  fillScreen(TFT_BLACK);
  setTextColor2(TFT_YELLOW, TFT_BLACK);

  drawString("0123", 0, 0, 8);
  drawString("4567", 0, 144, 8);
  delay(WAIT);;

  fillScreen(TFT_BLACK);
  drawString("890:.", 0, 0, 8);
  drawString("", 0, 144, 8);
  delay(WAIT);;

  setTextColor2(TFT_MAGENTA, TFT_BROWN);

  drawNumber(millis() - targetTime, 0, 180, 4);
  delay(4000);;

  // Now test them with transparent background
  targetTime = millis();

  setTextSize(1);
  fillScreen(TFT_BROWN);
  setTextColor1(TFT_GREEN);

  drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);
  drawString("789:;<=>?@ABCDEFGHIJKL", 0, 16, 2);
  drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 32, 2);
  drawString("abcdefghijklmnopqrstuvw", 0, 48, 2);
  xpos = 0;
  xpos += drawString("xyz{|}~", 0, 64, 2);
  drawChar4(127, xpos, 64, 2);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_GREEN);

  drawString(" !\"#$%&'()*+,-.", 0, 0, 4);
  drawString("/0123456789:;", 0, 26, 4);
  drawString("<=>?@ABCDE", 0, 52, 4);
  drawString("FGHIJKLMNO", 0, 78, 4);
  drawString("PQRSTUVWX", 0, 104, 4);

  delay(WAIT);
  fillScreen(TFT_BROWN);
  drawString("YZ[\\]^_`abc", 0, 0, 4);
  drawString("defghijklmno", 0, 26, 4);
  drawString("pqrstuvwxyz", 0, 52, 4);
  xpos = 0;
  xpos += drawString("{|}~", 0, 78, 4);
  drawChar4(127, xpos, 78, 4);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_BLUE);

  drawString("012345", 0, 0, 6);
  drawString("6789", 0, 40, 6);
  drawString("apm-:.", 0, 80, 6);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_RED);

  drawString("0123", 0, 0, 7);
  drawString("4567", 0, 60, 7);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  drawString("890:.", 0, 0, 7);
  drawString("", 0, 60, 7);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_YELLOW);

  drawString("0123", 0, 0, 8);
  drawString("4567", 0, 72, 8);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  drawString("890:.", 0, 0, 8);
  drawString("", 0, 72, 8);
  delay(WAIT);

  setTextSize(2);
  fillScreen(TFT_BROWN);
  setTextColor1(TFT_GREEN);

  drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);
  drawString("789:;<=>?@ABCDEFGHIJKL", 0, 32, 2);
  drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 64, 2);
  drawString("abcdefghijklmnopqrstuvw", 0, 96, 2);
  xpos = 0;
  xpos += drawString("xyz{|}~", 0, 128, 2);
  drawChar4(127, xpos, 128, 2);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_GREEN);

  drawString(" !\"#$%&'()*+,-.", 0, 0, 4);
  drawString("/0123456789:;", 0, 52, 4);
  drawString("<=>?@ABCDE", 0, 104, 4);
  drawString("FGHIJKLMNO", 0, 156, 4);
  drawString("PQRSTUVWX", 0, 208, 4);
  delay(WAIT);
  fillScreen(TFT_BROWN);
  drawString("YZ[\\]^_`abc", 0, 0, 4);
  drawString("defghijklmno", 0, 52, 4);
  drawString("pqrstuvwxyz", 0, 104, 4);
  xpos = 0;
  xpos += drawString("{|}~", 0, 156, 4);
  drawChar4(127, xpos, 156, 4);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_BLUE);

  drawString("01234", 0, 0, 6);
  drawString("56789", 0, 80, 6);
  drawString("apm-:.", 0, 160, 6);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_RED);

  drawString("0123", 0, 0, 7);
  drawString("4567", 0, 120, 7);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  drawString("890:.", 0, 0, 7);
  drawString("", 0, 120, 7);
  delay(WAIT);

  fillScreen(TFT_BROWN);
  setTextColor1(TFT_YELLOW);

  drawString("0123", 0, 0, 8);
  drawString("4567", 0, 144, 8);
  delay(WAIT);;

  fillScreen(TFT_BROWN);
  drawString("890:.", 0, 0, 8);
  drawString("", 0, 144, 8);
  delay(WAIT);;

  setTextColor1(TFT_MAGENTA);

  drawNumber(millis() - targetTime, 0, 180, 4);
  delay(1000);;
}

