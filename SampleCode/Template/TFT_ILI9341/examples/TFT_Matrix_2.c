// A fun MATRIX-like screen demo of scrolling
// Screen will flicker initially until fully drawn
// then scroll smoothly

// Needs GLCD font enabled in User_Setup.h

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

#define TEXT_HEIGHT 8 // Height of text to be printed and scrolled
#define BOT_FIXED_AREA 0  // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define TOP_FIXED_AREA 0 // Number of lines in top fixed area (lines counted from top of screen)

static uint16_t yStart = TOP_FIXED_AREA;
// uint16_t yArea = 320 - TOP_FIXED_AREA - BOT_FIXED_AREA;
static uint16_t yDraw = 320 - BOT_FIXED_AREA - TEXT_HEIGHT;
static byte     pos[42];
static uint16_t xPos = 0;

static void setupScrollArea(uint16_t TFA, uint16_t BFA);
static int scroll_slow(int lines, int wait);
static void scrollAddress(uint16_t VSP);

void setup_TFT_Matrix_2(void) {
  // Serial.begin(115200);
  // randomSeed(analogRead(A0));
  // init();
  setRotation(0);
  fillScreen(ILI9341_BLACK);
  setupScrollArea(TOP_FIXED_AREA, BOT_FIXED_AREA);
}

void loop_TFT_Matrix_2(void) {
  int j = 0;
  int i = 0; 

  // First fill the screen with randomt streaks of characters
  for (j = 0; j < 600; j += TEXT_HEIGHT) {
    for (i = 0; i < 40; i++) {
      if (pos[i] > 20) pos[i] -= 3; // Rapid fade initially brightness values
      if (pos[i] > 0) pos[i] -= 1; // Slow fade later
      if ((random(0,20) == 1) && (j<400)) pos[i] = 63; // ~1 in 20 probability of a new character
        setTextColor2(ILI9341_GREEN, ILI9341_BLACK); // Set the character brightness
      if (pos[i] == 63) setTextColor2(ILI9341_GREEN, ILI9341_BLACK); // Draw white character
      {
        xPos += drawChar4(random(32, 128), xPos, yDraw, 1); // Draw the character
      }
      
    }
    yDraw = scroll_slow(TEXT_HEIGHT, 14); // Scroll, 14ms per pixel line
    xPos = 0;
  }

  //setRotation(2);
  //setTextColor(63 << 5, ILI9341_BLACK);
  //drawCentreString("MATRIX",120,60,4);
  //setRotation(0);

  // Now scroll smoothly forever
  // while (1) yDraw = scroll_slow(320,8); // Scroll 320 lines, 8ms per line

}

static void setupScrollArea(uint16_t TFA, uint16_t BFA) {
  writecommand(ILI9341_VSCRDEF); // Vertical scroll definition
  writedata(TFA >> 8);
  writedata(TFA);
  writedata((320 - TFA - BFA) >> 8);
  writedata(320 - TFA - BFA);
  writedata(BFA >> 8);
  writedata(BFA);
}

static int scroll_slow(int lines, int wait) {
  int i = 0;  
  int yTemp = yStart;
  for (i = 0; i < lines; i++) {
    yStart++;
    if (yStart == 320 - BOT_FIXED_AREA) yStart = TOP_FIXED_AREA;
    scrollAddress(yStart);
    delay(wait);
  }
  return  yTemp;
}

static void scrollAddress(uint16_t VSP) {
  writecommand(ILI9341_VSCRSADD); // Vertical scrolling start address
  writedata(VSP >> 8);
  writedata(VSP);
}



