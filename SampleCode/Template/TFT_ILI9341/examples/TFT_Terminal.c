
/*************************************************************
  This sketch implements a simple serial receive terminal
  program for monitoring serial debug messages from another
  board.
  
  Connect GND to target board GND
  Connect RX line to TX line of target board
  Make sure the target and terminal have the same baud rate
  and serial stettings!

  The sketch works with the ILI9341 TFT 240x320 display and
  the called up libraries.
  
  The sketch uses the hardware scrolling feature of the
  display. Modification of this sketch may lead to problems
  unless the ILI9341 data sheet has been understood!

  Updated by Bodmer 21/7/16 for TFT_ILI9341 library:
  https://github.com/Bodmer/TFT_ILI9341
  
  BSD license applies, all text above must be included in any
  redistribution
 *************************************************************/

// In most cases characters don't get lost at 9600 baud but
// it is a good idea to increase the serial Rx buffer from 64
// to 512 or 1024 bytes especially if higher baud rates are
// used (this sketch does not need much RAM).
// The method described here works well:
// http://www.hobbytronics.co.uk/arduino-serial-buffer-size
//

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

// The scrolling area must be a integral multiple of tTEXT_HEIGHT
#define tTEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define tBOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define tTOP_FIXED_AREA 16 // Number of lines in top fixed area (lines counted from top of screen)
#define YMAX 320 // Bottom of screen area

// The initial y coordinate of the top of the scrolling area
static uint16_t yStart = tTOP_FIXED_AREA;
// yArea must be a integral multiple of tTEXT_HEIGHT
// static uint16_t yArea = YMAX-tTOP_FIXED_AREA-tBOT_FIXED_AREA;
// The initial y coordinate of the top of the bottom text line
static uint16_t yDraw = YMAX - tBOT_FIXED_AREA - tTEXT_HEIGHT;

// Keep track of the drawing x coordinate
static uint16_t xPos = 0;

// For the byte we read from the serial port
static byte data = 0;

// A few test variables used during debugging
// static boolean change_colour = 1;
// static boolean selected = 1;

// We have to blank the top line each time the display is scrolled, but this takes up to 13 milliseconds
// for a full width line, meanwhile the serial buffer may be filling... and overflowing
// We can speed up scrolling of short text lines by just blanking the character we drew
static int blank[19]; // We keep all the strings pixel lengths to optimise the speed of the top line blanking

static int scroll_line(void);
static void setupScrollArea(uint16_t tfa, uint16_t bfa);
static void scrollAddress(uint16_t vsp);


void setup_TFT_Terminal(void) {
  byte i = 0;

  // Setup the TFT display
  // init();
  setRotation(0); // Must be setRotation(0) for this sketch to work correctly
  fillScreen(TFT_BLACK);
  
  // Setup baud rate and draw top banner
  // Serial.begin(9600);
  
  setTextColor2(TFT_WHITE, TFT_BLUE);
  fillRect(0,0,240,16, TFT_BLUE);
  drawCentreString(" Serial Terminal - 9600 baud ",120,0,2);

  // Change colour for scrolling zone text
  setTextColor2(TFT_WHITE, TFT_BLACK);

  // Setup scroll area
  setupScrollArea(tTOP_FIXED_AREA, tBOT_FIXED_AREA);

  // Zero the array
  for (i = 0; i<18; i++) blank[i]=0;
}


void loop_TFT_Terminal(void) {
  //  These lines change the text colour when the serial buffer is emptied
  //  These are test lines to see if we may be losing characters
  //  Also uncomment the change_colour line below to try them
  //
  //  if (change_colour){
  //  change_colour = 0;
  //  if (selected == 1) {setTextColor(TFT_CYAN, TFT_BLACK); selected = 0;}
  //  else {setTextColor(TFT_MAGENTA, TFT_BLACK); selected = 1;}
  //}

  while (1/*Serial.available()*/) {
    data = UART_READ(UART0);//Serial.read();
    // If it is a CR or we are near end of line then scroll one line
    if (data == '\r' || xPos>231) {
      xPos = 0;
      yDraw = scroll_line(); // It can take 13ms to scroll and blank 16 pixel lines
    }
    if (data > 31 && data < 128) {
      xPos += drawChar4(data,xPos,yDraw,2);
      blank[(18+(yStart-tTOP_FIXED_AREA)/tTEXT_HEIGHT)%19]=xPos; // Keep a record of line lengths
    }
    //change_colour = 1; // Line to indicate buffer is being emptied
  }
}

// ##############################################################################################
// Call this function to scroll the display one text line
// ##############################################################################################
static int scroll_line(void) {
  int yTemp = yStart; // Store the old yStart, this is where we draw the next line
  // Use the record of line lengths to optimise the rectangle size we need to erase the top line
  fillRect(0,yStart,blank[(yStart-tTOP_FIXED_AREA)/tTEXT_HEIGHT],tTEXT_HEIGHT, TFT_BLACK);

  // Change the top of the scroll area
  yStart+=tTEXT_HEIGHT;
  // The value must wrap around as the screen memory is a circular buffer
  if (yStart >= YMAX - tBOT_FIXED_AREA) yStart = tTOP_FIXED_AREA + (yStart - YMAX + tBOT_FIXED_AREA);
  // Now we can scroll the display
  scrollAddress(yStart);
  return  yTemp;
}

// ##############################################################################################
// Setup a portion of the screen for vertical scrolling
// ##############################################################################################
// We are using a hardware feature of the display, so we can only scroll in portrait orientation
static void setupScrollArea(uint16_t tfa, uint16_t bfa) {
  writecommand(ILI9341_VSCRDEF); // Vertical scroll definition
  writedata(tfa >> 8);           // Top Fixed Area line count
  writedata(tfa);
  writedata((YMAX-tfa-bfa)>>8);  // Vertical Scrolling Area line count
  writedata(YMAX-tfa-bfa);
  writedata(bfa >> 8);           // Bottom Fixed Area line count
  writedata(bfa);
}

// ##############################################################################################
// Setup the vertical scrolling start address pointer
// ##############################################################################################
static void scrollAddress(uint16_t vsp) {
  writecommand(ILI9341_VSCRSADD); // Vertical scrolling pointer
  writedata(vsp>>8);
  writedata(vsp);
}

