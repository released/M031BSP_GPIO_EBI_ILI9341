/*
  Ellipse drawing example

  This sketch does not use any fonts.
*/

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

void setup_TFT_Ellipse(void) {
  // init();

  setRotation(3);

}

void loop_TFT_Ellipse(void) {
  int i = 0;
  int rx = 0;
  int ry = 0;
  int x = 0;
  int y = 0;

  fillScreen(TFT_BLACK);

  // Draw some random circles
  for (i = 0; i < 40; i++)
  {
    rx = random(0,60);
    ry = random(0,60);
    x = rx + random(0 , (320 - rx - rx));
    y = ry + random(0 , (240 - ry - ry));
    fillEllipse(x, y, rx, ry, (uint16_t) random(0,0xFFFF));
  }

  delay(500);
  fillScreen(TFT_BLACK);

  for (i = 0; i < 40; i++)
  {
    rx =random(0,60);
    ry = random(0,60);
    x = rx + random(0,320 - rx - rx);
    y = ry + random(0,240 - ry - ry);
    drawEllipse(x, y, rx, ry, (uint16_t) random(0,0xFFFF));
  }

  delay(500);
}



