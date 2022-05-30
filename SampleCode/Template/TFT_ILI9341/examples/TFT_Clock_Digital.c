/*
 An example digital clock using a TFT LCD screen to show the time.
 Demonstrates use of the font printing routines. (Time updates but date does not.)
 
 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo. 
 
 This sketch uses the GLCD and fonts 2, 4, 6, 7

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
 
 Based on clock sketch by Gilchrist 6/2/2014 1.0

A few colour codes:
 
code	color
0x0000	Black
0xFFFF	White
0xBDF7	Light Gray
0x7BEF	Dark Gray
0xF800	Red
0xFFE0	Yellow
0xFBE0	Orange
0x79E0	Brown
0x7E0	Green
0x7FF	Cyan
0x1F	Blue
0xF81F	Pink

 */

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

#define TFT_GREY 0x5AEB

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

static uint32_t targetTime = 0;                    // for next 1 second timeout

static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x
static uint8_t hh = 0, mm = 0, ss = 0;  // Get H, M, S from compile time

static byte omm = 99;
static boolean initial = 1;
static byte xcolon = 0;
static unsigned int colour = 0;

void setup_TFT_Clock_Digital(void) {
  // init();

  // if(g_InitOnce == 0)
  //     g_InitOnce = 1;
  // else
  //     return;

  setRotation(3);
  fillScreen(TFT_BLACK);

  setTextSize(1);
  setTextColor2(TFT_YELLOW, TFT_BLACK);

  targetTime = millis() + 1000; 

  hh = conv2d(__TIME__);
  mm = conv2d(__TIME__+3);
  ss = conv2d(__TIME__+6);
}

void loop_TFT_Clock_Digital(void) {
  byte xpos = 50;
  byte ypos = 0;
  char buffer[20];

  if (targetTime < millis()) {
    targetTime = millis()+1000;
    ss++;              // Advance second
    if (ss==60) {
      ss=0;
      omm = mm;
      mm++;            // Advance minute
      if(mm>59) {
        mm=0;
        hh++;          // Advance hour
        if (hh>23) {
          hh=0;
        }
      }
    }

    if (ss==0 || initial) {
      initial = 0;
      setTextColor2(TFT_GREEN, TFT_BLACK);
      setCursor2(50, 52);
      // print(__DATE__); // This uses the standard ADAFruit small font

      setTextColor2(TFT_BLUE, TFT_BLACK);
      drawCentreString("It is windy",160,48,2); // Next size up font 2

      setTextColor2(0xF81F, TFT_BLACK); // Pink
      drawCentreString("12.34",120,91,6); // Large font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 . : a p m
    }

    // Update digital time
    xpos = 50;
    ypos = 0;
    if (omm != mm) { // Only redraw every minute to minimise flicker
      // Uncomment ONE of the next 2 lines, using the ghost image demonstrates text overlay as time is drawn over it
      setTextColor2(0x39C4, TFT_BLACK);  // Leave a 7 segment ghost image, comment out next line!
      //setTextColor(TFT_BLACK, TFT_BLACK); // Set font colour to back to wipe image
      // Font 7 is to show a pseudo 7 segment display.
      // Font 7 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .
      drawString("88:88",xpos,ypos,7); // Overwrite the text to clear it
      setTextColor1(0xFBE0); // Orange
      omm = mm;

      if (hh<10) xpos+= drawChar4('0',xpos,ypos,7);
      xpos+= drawNumber(hh,xpos,ypos,7);
      xcolon=xpos;
      xpos+= drawChar4(':',xpos,ypos,7);
      if (mm<10) xpos+= drawChar4('0',xpos,ypos,7);
      drawNumber(mm,xpos,ypos,7);
    }

    if (ss%2) { // Flash the colon
      setTextColor2(0x39C4, TFT_BLACK);
      xpos+= drawChar4(':',xcolon,ypos,7);
      setTextColor2(0xFBE0, TFT_BLACK);
    }
    else {
      drawChar4(':',xcolon,ypos,7);
      colour = (uint16_t) random(0 ,0xFFFF);
      // Erase the text with a rectangle
      fillRect (0, 64, 240, 20, TFT_BLACK);
      setTextColor1(colour);
      drawRightString("Colour:",120,64,4); // Right justified string drawing to x position 120
      #if 1
      memset(buffer,0x00 , 20);
      sprintf(buffer,"%4X", colour);      
      #else
      // String scolour = String(colour,HEX);
      // scolour.toUpperCase();
      // buffer[20];
      // scolour.toCharArray(buffer,20);
      #endif

      drawString(buffer,128,64,4);
    }
  }
}

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}



