// Mandlebrot

// This will run slowly due to the large number of calculations per pixel

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

#define ILI9341_GREY 0x7BEF

static unsigned long runTime = 0;

// float sx = 0, sy = 0;
// uint16_t x0 = 0, x1 = 0, y0 = 0, y1 = 0;

static unsigned int rainbow(int value);

void setup_TFT_Mandlebrot(void)
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

void loop_TFT_Mandlebrot(void)
{
  int px = 1;
  int py = 0;
  float x0 = 0.0f;
  float y0 = 0.0f;
  float xx = 0.0f;
  float yy = 0.0f;
  int iteration = 0;
  int max_iteration = 128;
  float xtemp = 0.0f;
  int color = 0;

  runTime = millis();

  fillScreen(ILI9341_BLACK);
  for (px = 1; px < 320; px++)
  {
    for (py = 0; py < 240; py++)
    {
      x0 = (map(px, 0, 320, -250000/2, -242500/2)) / 100000.0; //scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
      y0 = (map(py, 0, 240, -75000/4, -61000/4)) / 100000.0; //scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
      xx = 0.0;
      yy = 0.0;
      iteration = 0;
      max_iteration = 128;
      while ( ((xx * xx + yy * yy) < 4)  &&  (iteration < max_iteration) )
      {
        xtemp = xx * xx - yy * yy + x0;
        yy = 2 * xx * yy + y0;
        xx = xtemp;
        iteration++;
      }
      color = rainbow((3*iteration+64)%128);
      drawPixel(px, py, color);
    }
  }
  printf("runTime : %dms\r\n" , millis()-runTime);  //while(1);
  delay(5000);
}

static unsigned int rainbow(int value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to red = blue
  //int value = random (128);
  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}


