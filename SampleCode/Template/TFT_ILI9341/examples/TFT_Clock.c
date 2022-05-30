/*
 An example analogue clock using a TFT LCD screen to show the time
 use of some of the drawing commands with the modified Adafruit_TFT_AS library.
 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo. 
 
 This sketch uses font 4 only.

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
 
 Based on a sketch by Gilchrist 6/2/2014 1.0
 */

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

#define TFT_GREY 0x5AEB

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=120, osy=120, omx=120, omy=120, ohx=120, ohy=120;  // Saved H, M, S x & y coords
uint16_t x0=0, x1=0, y0=0, y1=0;
uint32_t targetTime_TFT_Clock = 0;                    // for next 1 second timeout

static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x
uint8_t hh_TFT_Clock = 0, mm_TFT_Clock = 0, ss_TFT_Clock = 0;  // Get H, M, S from compile time

boolean initial_TFT_Clock = 1;

void setup_TFT_Clock(void) {
  int i = 0;

  // if(g_InitOnce == 0)
  //     g_InitOnce = 1;
  // else
  //     return;

  // init();
  setRotation(3);
  
  //fillScreen(TFT_BLACK);
  //fillScreen(TFT_RED);
  //fillScreen(TFT_GREEN);
  //fillScreen(TFT_BLUE);
  //fillScreen(TFT_BLACK);
  fillScreen(TFT_GREY);
  
  setTextColor2(TFT_WHITE, TFT_GREY);  // Adding a background colour erases previous text automatically
  
  // Draw clock face
  fillCircle(120, 120, 118, TFT_GREEN);
  fillCircle(120, 120, 110, TFT_BLACK);

  // Draw 12 lines
  for(i = 0; i<360; i+= 30) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*114+120;
    y0 = sy*114+120;
    x1 = sx*100+120;
    y1 = sy*100+120;

    drawLine(x0, y0, x1, y1, TFT_GREEN);
  }

  // Draw 60 dots
  for(i = 0; i<360; i+= 6) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*102+120;
    y0 = sy*102+120;
    // Draw minute markers
    drawPixel(x0, y0, TFT_WHITE);
    
    // Draw main quadrant dots
    if(i==0 || i==180) fillCircle(x0, y0, 2, TFT_WHITE);
    if(i==90 || i==270) fillCircle(x0, y0, 2, TFT_WHITE);
  }

  fillCircle(120, 121, 3, TFT_WHITE);

  // Draw text at position 120,260 using fonts 4
  // Only font numbers 2,4,6,7 are valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : . - a p m
  // Font 7 is a 7 segment font and only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : .
  drawCentreString("Time flies",120,260,4);

  targetTime_TFT_Clock = millis() + 1000; 

  hh_TFT_Clock = conv2d(__TIME__);
  mm_TFT_Clock = conv2d(__TIME__+3);
  ss_TFT_Clock = conv2d(__TIME__+6);

}

void loop_TFT_Clock(void) {

    if (targetTime_TFT_Clock < millis()) {
      targetTime_TFT_Clock = millis()+1000;
      ss_TFT_Clock++;              // Advance second
      if (ss_TFT_Clock==60) {
        ss_TFT_Clock=0;
        mm_TFT_Clock++;            // Advance minute
        if(mm_TFT_Clock>59) {
          mm_TFT_Clock = 0;
          hh_TFT_Clock++;          // Advance hour
          if (hh_TFT_Clock>23) {
            hh_TFT_Clock=0;
          }
        }
      }

      // Pre-compute hand degrees, x & y coords for a fast screen update
      sdeg = ss_TFT_Clock*6;                  // 0-59 -> 0-354
      mdeg = mm_TFT_Clock*6+sdeg*0.01666667;  // 0-59 -> 0-360 - includes seconds
      hdeg = hh_TFT_Clock*30+mdeg*0.0833333;  // 0-11 -> 0-360 - includes minutes and seconds
      hx = cos((hdeg-90)*0.0174532925);    
      hy = sin((hdeg-90)*0.0174532925);
      mx = cos((mdeg-90)*0.0174532925);    
      my = sin((mdeg-90)*0.0174532925);
      sx = cos((sdeg-90)*0.0174532925);    
      sy = sin((sdeg-90)*0.0174532925);

      if (ss_TFT_Clock==0 || initial_TFT_Clock) {
        initial_TFT_Clock = 0;
        // Erase hour and minute hand positions every minute
        drawLine(ohx, ohy, 120, 121, TFT_BLACK);
        ohx = hx*62+121;    
        ohy = hy*62+121;
        drawLine(omx, omy, 120, 121, TFT_BLACK);
        omx = mx*84+120;    
        omy = my*84+121;
      }

        // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
        drawLine(osx, osy, 120, 121, TFT_BLACK);
        osx = sx*90+121;    
        osy = sy*90+121;
        drawLine(osx, osy, 120, 121, TFT_RED);
        drawLine(ohx, ohy, 120, 121, TFT_WHITE);
        drawLine(omx, omy, 120, 121, TFT_WHITE);
        drawLine(osx, osy, 120, 121, TFT_RED);

      fillCircle(120, 121, 3, TFT_RED);
    }
}

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

