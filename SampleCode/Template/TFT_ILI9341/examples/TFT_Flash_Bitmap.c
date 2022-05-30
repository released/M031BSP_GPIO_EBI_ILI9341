// Icons are stored in tabs ^ e.g. Alert.h etc above this line
// more than one icon can be in a header file

/*
 This sketch demonstrates loading images from arrays stored in program (FLASH) memory.

 Works with TFT_ILI9341 library here:
 https://github.com/Bodmer/TFT_ILI9341

 This sketch does not use/need any fonts at all...

 Arrays containing FLASH images can be created with UTFT library tool:
 (libraries\UTFT\Tools\ImageConverter565.exe)
 Convert to .c format then copy into a new tab

 The number and size of icons is limited by available FLASH memory. The icon array will
 use width x height x 2 bytes of FLASH, i.e. 32 x 32 icon uses ~2048 bytes

 Performance is good enough for most applications:
 A 32 x 32 icon can be drawn by a humble UNO in ~3.6 milliseconds, i.e. ~280 icons per second!
 A 320 x 240 screen can be completely filled with icons in about 270ms

 Code derived from ILI9341_due example
*/

#include <TFT_ILI9341.h> // Hardware-specific library

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

// Include the header files that contain the icons
#include "alert.h"
#include "Close.h"
#include "Info.h"

static long count = 0; // Loop count

void drawIcon(const unsigned short* icon, int16_t x, int16_t y, int8_t width, int8_t height);

void setup_TFT_Flash_Bitmap(void)
{
  // Serial.begin(115200);
  // begin();
  setRotation(3);	// landscape

  fillScreen(TFT_BLACK);

  // Draw the icons
  drawIcon(info, 100, 100, infoWidth, infoHeight);
  drawIcon(alert, 140, 100, alertWidth, alertHeight);
  drawIcon(close, 180, 100, closeWidth, closeHeight);

  // Pause here to admire the icons!
  delay(4000);
  fillScreen(TFT_BLACK);
}

void loop_TFT_Flash_Bitmap(void)
{

  // Loop filling and clearing screen to show draw speed
  drawIcon(info, random(0,width() - infoWidth), random(0,height() - infoHeight), infoWidth, infoHeight);
  delay(250);
  fillScreen(TFT_BLACK);

  drawIcon(alert, random(0,width() - alertWidth), random(0,height() - alertHeight), alertWidth, alertHeight);
  delay(250);
  fillScreen(TFT_BLACK);
   
  drawIcon(close, random(0,width() - closeWidth), random(0,height() - closeHeight), closeWidth, closeHeight);
  delay(250);
  fillScreen(TFT_BLACK);

  // Clear screen after 100 x 3 = 300 icons drawn
  if (100 == count++) {
    count = 1;
    setRotation(2 * ((uint8_t)random(0,2))); // Rotate randomly to clear display left>right or right>left to reduce monotony!
    fillScreen(TFT_BLACK);
    setRotation(3);
    // Serial.println(millis());
  }
}


//====================================================================================
// This is the function to draw the icon stored as an array in program memory (FLASH)
//====================================================================================

// To speed up rendering we use a 64 pixel buffer
#define BUFF_SIZE 64

// Draw array "icon" of defined width and height at coordinate x,y
// Maximum icon size is 255x255 pixels to avoid integer overflow

void drawIcon(const unsigned short* icon, int16_t x, int16_t y, int8_t width, int8_t height) {

  uint16_t  pix_buffer[BUFF_SIZE];   // Pixel buffer (16 bits per pixel)
  uint16_t nb = 0;
  int i = 0;
  int j = 0;
  uint16_t np = 0;

  // Set up a window the right size to stream pixels into
  setWindow(x, y, x + width - 1, y + height - 1);

  // Work out the number whole buffers to send
  nb = ((uint16_t)height * width) / BUFF_SIZE;

  // Fill and send "nb" buffers to TFT
  for (i = 0; i < nb; i++) {
    for (j = 0; j < BUFF_SIZE; j++) {
      pix_buffer[j] = *(__IO uint16_t *)(&icon[i * BUFF_SIZE + j]);
    }
    pushColors16(pix_buffer, BUFF_SIZE);
  }

  // Work out number of pixels not yet sent
  np = ((uint16_t)height * width) % BUFF_SIZE;

  // Send any partial buffer left over
  if (np) {
    for (i = 0; i < np; i++) pix_buffer[i] = *(__IO uint16_t *)(&icon[nb * BUFF_SIZE + i]);
    pushColors16(pix_buffer, np);
  }
}

