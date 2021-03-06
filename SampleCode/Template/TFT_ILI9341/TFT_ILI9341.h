/***************************************************
  Arduino TFT graphics library targetted at the UNO
  and Mega boards.

  This library has been derived from the Adafruit_GFX
  library and the associated driver library. See text
  at the end of this file.

  This is a standalone library that contains the
  hardware driver, the graphics funtions and the
  proportional fonts.

  The larger fonts are Run Length Encoded to reduce
  their FLASH footprint.

 ****************************************************/

// Include header file that defines the fonts loaded and the pins to be used
#include <User_Setup.h>

// Include header file from the FastLED library for fast pin toggling using direct port access
// #include <TFT_FastPin.h>

// Stop fonts being loaded multiple times
#ifndef _TFT_ILI9341H_
#define _TFT_ILI9341H_

#include "gpio_EBI.h"

// Only load the fonts defined in User_Setup.h (to save space)
// Set flag so RLE rendering code is optionally compiled
// #ifdef LOAD_GLCD
//   #include <Fonts/glcdfont.c>
// #endif

// #ifdef LOAD_FONT2
//   #include <Fonts/Font16.h>
// #endif

// #ifdef LOAD_FONT4
//   #include <Fonts/Font32rle.h>
//   #define LOAD_RLE
// #endif

// #ifdef LOAD_FONT6
//   #include <Fonts/Font64rle.h>
//   #ifndef LOAD_RLE
//     #define LOAD_RLE
//   #endif
// #endif

// #ifdef LOAD_FONT7
//   #include <Fonts/Font7srle.h>
//   #ifndef LOAD_RLE
//     #define LOAD_RLE
//   #endif
// #endif

// #ifdef LOAD_FONT8
//   #include <Fonts/Font72rle.h>
//   #ifndef LOAD_RLE
//     #define LOAD_RLE
//   #endif
// #endif

// #include <Arduino.h>
// #include <Print.h>

// #include <avr/pgmspace.h>

// Swap any type
// template <typename T> static inline void
// swap(T& a, T& b) { T t = a; a = b; b = t; }
#ifndef swap
#define swap(a, b)     								{(a) ^= (b); (b) ^= (a); (a) ^= (b);}
#endif

#ifndef min
#define min(a,b) 									(((a) < (b)) ? (a) : (b))
#endif

typedef unsigned char boolean;
typedef unsigned char byte;
void delay(uint32_t t);
uint32_t millis(void);
unsigned long micros(void);
extern uint8_t g_InitOnce;
long map(long x, long in_min, long in_max, long out_min, long out_max);
uint32_t random(int min, int max );

//These define the ports and port bits used for the chip select (CS) and data/command (DC) lines
#define TFT_CS_L	CS_ACTIVE     //FastPin<TFT_CS>::lo()
#define TFT_DC_C 	CD_COMMAND    //FastPin<TFT_DC>::lo()
#define TFT_CS_H	CS_IDLE       //FastPin<TFT_CS>::hi()
#define TFT_DC_D 	CD_DATA       //FastPin<TFT_DC>::hi()

//These enumerate the text plotting alignment (reference datum point)
#define TL_DATUM 0 // Top left (default)
#define TC_DATUM 1 // Top centre
#define TR_DATUM 2 // Top right
#define ML_DATUM 3 // Middle left
#define CL_DATUM 3 // Centre left, same as above
#define MC_DATUM 4 // Middle centre
#define CC_DATUM 4 // Centre centre, same as above
#define MR_DATUM 5 // Middle right
#define CR_DATUM 5 // Centre right, same as above
#define BL_DATUM 6 // Bottom left
#define BC_DATUM 7 // Bottom centre
#define BR_DATUM 8 // Bottom right


// Change the width and height if required (defined in portrait mode)
// or use the constructor to over-ride defaults
#define ILI9341_TFTWIDTH  240
#define ILI9341_TFTHEIGHT 320

#define ILI9341_INIT_DELAY 0x80

// These are the ILI9341 control registers
#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13

#define ILI9341_RDMODE  0x0A
#define ILI9341_RDMADCTL  0x0B
#define ILI9341_RDPIXFMT  0x0C
#define ILI9341_RDIMGFMT  0x0A
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29

#define ILI9341_CASET   0x2A
#define ILI9341_PASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E

#define ILI9341_PTLAR   0x30
#define ILI9341_VSCRDEF 0x33
#define ILI9341_MADCTL  0x36
#define ILI9341_VSCRSADD 0x37
#define ILI9341_PIXFMT  0x3A

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6

#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5
#define ILI9341_VMCTR2  0xC7

#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

// New color definitions use for all my libraries
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFD20      /* 255, 165,   0 */
#define TFT_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define TFT_PINK        0xF81F

// Color definitions for backwards compatibility
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

typedef struct {
	const unsigned char *chartbl;
	const unsigned char *widthtbl;
	unsigned       char height;
	} fontinfo;

// This is a structure to conveniently hold infomation on the fonts
// Stores font character image address pointer, width table and height

// const fontinfo fontdata [] = {  //const PROGMEM fontinfo fontdata [] = {
//    { 0, 0, 0 },

//    { 0, 0, 8 },

//   #ifdef LOAD_FONT2
//    { (const unsigned char *)chrtbl_f16, widtbl_f16, chr_hgt_f16},
//   #else
//    { 0, 0, 0 },
//   #endif

//    { 0, 0, 0 },

//   #ifdef LOAD_FONT4
//    { (const unsigned char *)chrtbl_f32, widtbl_f32, chr_hgt_f32},
//   #else
//    { 0, 0, 0 },
//   #endif

//    { 0, 0, 0 },

//   #ifdef LOAD_FONT6
//    { (const unsigned char *)chrtbl_f64, widtbl_f64, chr_hgt_f64},
//   #else
//    { 0, 0, 0 },
//   #endif

//   #ifdef LOAD_FONT7
//    { (const unsigned char *)chrtbl_f7s, widtbl_f7s, chr_hgt_f7s},
//   #else
//    { 0, 0, 0 },
//   #endif

//   #ifdef LOAD_FONT8
//    { (const unsigned char *)chrtbl_f72, widtbl_f72, chr_hgt_f72}
//   #else
//    { 0, 0, 0 }
//   #endif
// };


// Class functions and variables
// class TFT_ILI9341 : public Print {

//  public:

  // TFT_ILI9341(int16_t _W = ILI9341_TFTWIDTH, int16_t _H = ILI9341_TFTHEIGHT);

  // void     init(void); begin(void); // Same - begin included for backwards compatibility
           void init(void);
           void begin(void);

           void drawPixel(uint16_t x, uint16_t y, uint16_t color);
           void fastPixel(uint16_t x, uint16_t y, uint16_t color);
           void fastSetup(void);

           void drawChar6(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t font);
           void setWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

           void pushColor1(uint16_t color);
           void pushColor2(uint16_t color, uint16_t len);

           void pushColors16(uint16_t *data, uint8_t len);
           void pushColors8(uint8_t  *data, uint16_t len);

           void fillScreen(uint16_t color);

           void writeEnd(void);
           void backupSPCR(void);
           void restoreSPCR(void);

           //spiWait17(void);
           //spiWait15(void);
           //spiWait14(void);

           void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
           void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
           void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

           void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
           void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
           void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
           void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);

           void setRotation(uint8_t r);
           void invertDisplay(boolean i);

           void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
           void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
           void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
           void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

           void drawEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color);
           void fillEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color);

           void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
           void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

           void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);

           void setCursor2(int16_t x, int16_t y);
           void setCursor3(int16_t x, int16_t y, uint8_t font);
           void setTextColor1(uint16_t color);
           void setTextColor2(uint16_t fgcolor, uint16_t bgcolor);
           void setTextSize(uint8_t size);
           void setTextFont(uint8_t font);
           void setTextWrap(boolean wrap);
           void setTextDatum(uint8_t datum);
           void setTextPadding(uint16_t x_width);

           void spiwrite(uint8_t c);
           void writecommand(uint8_t c);
           void writedata(uint8_t d);
           void commandList(const uint8_t *addr);

  uint8_t  getRotation(void);

  uint16_t fontsLoaded(void);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

  int  drawChar4(unsigned int uniCode, int x, int y, int font);
  int  drawNumber(long long_num,int poX, int poY, int font);
  int  drawFloat(float floatNumber,int decimal,int poX, int poY, int font);

  int  drawString(const char *string, int poX, int poY, int font);
  int  drawCentreString(const char *string, int dX, int poY, int font);
  int  drawRightString(const char *string, int dX, int poY, int font);

  int16_t  height(void);
  int16_t  width(void);
  int16_t  textWidth(const char *string, int font);
  int16_t  fontHeight(int font);

//    void  spiWrite16(uint16_t data, int16_t count);
//    void  spiWrite16s(uint16_t data);
//    void  spiWrite16R(uint16_t data, int16_t count);

//  virtual  size_t write(uint8_t);
  uint8_t write(uint8_t);
  void println(unsigned char* stream);

//  private:

    void  setAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

  // uint8_t  tabcolor;

  // boolean  hwSPI;

  // uint8_t  mySPCR, savedSPCR;

//  protected:

  // int16_t  cursor_x, cursor_y, win_xe, win_ye, padX;

  // uint16_t _width, _height; // Display w/h as modified by current rotation
  // uint16_t textcolor, textbgcolor, fontsloaded, addr_row, addr_col;

  // uint8_t  textfont,textsize, textdatum,rotation;

  // boolean  textwrap; // If set, 'wrap' text at right edge of display

// };

#endif

/***************************************************

  ORIGINAL LIBRARY HEADER

  This is our library for the Adafruit  ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution

  Updated with new functions by Bodmer 14/4/15
 ****************************************************/
