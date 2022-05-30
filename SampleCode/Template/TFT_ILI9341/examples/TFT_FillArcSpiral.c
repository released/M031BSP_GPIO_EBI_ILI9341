// This sketch tests a fillArc function that has been adapted to permit the drawing of spirals

// Sketch also includes (but does not use) a function to change the brightness of a colour

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

#define DEG2RAD 0.0174532925

static int segment = 0;
static unsigned int col = 0;
static int delta = -1;

static byte red = 31; // Red is the top 5 bits of a 16 bit colour value
static byte green = 0;// Green is the middle 6 bits
static byte blue = 0; // Blue is the bottom 5 bits
static byte state = 0;

static unsigned int rainbow(byte value);
static int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);

void setup_TFT_FillArcSpiral(void) {
  // begin();

  setRotation(3);

  fillScreen(TFT_BLACK);
}


void loop_TFT_FillArcSpiral(void) {
  fillArc(160, 120, segment*6, 1, 120-segment/4, 120-segment/4, 6, rainbow(col));

  segment+=delta;
  col+=1;
  if (col>191) col = 0;
  if (segment <0) delta = 1;
  if (segment >298) delta = -1; // ~5 turns in the spiral (300*6 degrees)
  //delay(5); // Slow drawing down
}

// #########################################################################
// Draw an arc with a defined thickness (modified to aid drawing spirals)
// #########################################################################

// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 3 degree segments to draw (120 => 360 degree arc)
// rx = x axis radius
// yx = y axis radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same an arc of a circle is drawn

static int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{
  int i = 0;
  float sx = 0.0f;
  float sy = 0.0f;
  uint16_t x0 = 0;
  uint16_t y0 = 0;
  uint16_t x1 = 0;
  uint16_t y1 = 0;

  float sx2 = 0.0f;
  float sy2 = 0.0f;
  int x2 = 0;
  int y2 = 0;
  int x3 = 0;
  int y3 = 0; 

  // Make the segment size 7 degrees to prevent gaps when drawing spirals
  byte seg = 7; // Angle a single segment subtends (made more than 6 deg. for spiral drawing)
  byte inc = 6; // Draw segments every 6 degrees

  // Draw colour blocks every inc degrees
  for (i = start_angle; i < start_angle + seg * seg_count; i += inc) {
    // Calculate pair of coordinates for segment start
    sx = cos((i - 90) * DEG2RAD);
    sy = sin((i - 90) * DEG2RAD);
    x0 = sx * (rx - w) + x;
    y0 = sy * (ry - w) + y;
    x1 = sx * rx + x;
    y1 = sy * ry + y;

    // Calculate pair of coordinates for segment end
    sx2 = cos((i + seg - 90) * DEG2RAD);
    sy2 = sin((i + seg - 90) * DEG2RAD);
    x2 = sx2 * (rx - w) + x;
    y2 = sy2 * (ry - w) + y;
    x3 = sx2 * rx + x;
    y3 = sy2 * ry + y;

    fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    fillTriangle(x1, y1, x2, y2, x3, y3, colour);
  }

  return 0;
}

// #########################################################################
// Return a 16 bit colour with brightness 0 - 100%
// #########################################################################
// unsigned int brightness(unsigned int colour, int brightness)
// {
//   byte red  = colour >> 11;
//   byte green = (colour & 0x7E0) >> 5;
//   byte blue   = colour & 0x1F;

//   blue = (blue * brightness)/100;
//   green = (green * brightness)/100;
//   red = (red * brightness)/100;

//   return (red << 11) + (green << 5) + blue;
// }

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
static unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

    switch (state) {
      case 0:
        green ++;
        if (green == 64) {
          green = 63;
          state = 1;
        }
        break;
      case 1:
        red--;
        if (red == 255) {
          red = 0;
          state = 2;
        }
        break;
      case 2:
        blue ++;
        if (blue == 32) {
          blue = 31;
          state = 3;
        }
        break;
      case 3:
        green --;
        if (green == 255) {
          green = 0;
          state = 4;
        }
        break;
      case 4:
        red ++;
        if (red == 32) {
          red = 31;
          state = 5;
        }
        break;
      case 5:
        blue --;
        if (blue == 255) {
          blue = 0;
          state = 0;
        }
        break;
    }
    return red << 11 | green << 5 | blue;
}

