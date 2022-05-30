// Demo using arcFill to draw ellipses and a segmented elipse
#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

#define DEG2RAD 0.0174532925

static byte inc = 0;
static unsigned int col = 0;

static byte red = 31; // Red is the top 5 bits of a 16 bit colour value
static byte green = 0;// Green is the middle 6 bits
static byte blue = 0; // Blue is the bottom 5 bits
static byte state = 0;

static unsigned int rainbow(byte value);
static int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);  

void setup_TFT_ArcFill_2(void) {
  // begin();

  // if(g_InitOnce == 0)
  //     g_InitOnce = 1;
  // else
  //     return;

  setRotation(3);

  fillScreen(TFT_BLACK);

}


void loop_TFT_ArcFill_2(void) {

  unsigned long td = millis();
  // Continuous elliptical arc drawing
  fillArc(160, 120, inc*6, 1, 140, 100, 10, rainbow(col));

  // Continuous segmented (inc*2) elliptical arc drawing
  fillArc(160, 120, ((inc*2)%60)*6, 1, 120, 80, 30, rainbow(col));

  // Circle drawing using arc with arc width = radius
  fillArc(160, 120, inc*6, 1, 42, 42, 42, rainbow(col));

  inc++;
  col+=1;
  if (col>191) col = 0;
  if (inc > 59) inc = 0;
  //delay(10);

}


// #########################################################################
// Draw a circular or elliptical arc with a defined thickness
// #########################################################################

// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 6 degree segments to draw (60 => 360 degree arc)
// rx = x axis outer radius
// ry = y axis outer radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn

static int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{
    int i = start_angle;
    byte seg = 6; // Segments are 3 degrees wide = 120 segments for 360 degrees
    byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring
    float sx = 0.0f;
    float sy = 0.0f;
    float sx2 = 0.0f;
    float sy2 = 0.0f;
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;
    uint16_t x2 = sx * (rx - w) + x;
    uint16_t y2 = sy * (ry - w) + y;
    uint16_t x3 = sx * rx + x;
    uint16_t y3 = sy * ry + y;


    // Calculate first pair of coordinates for segment start
    sx = cos((start_angle - 90) * DEG2RAD);
    sy = sin((start_angle - 90) * DEG2RAD);
    x0 = sx * (rx - w) + x;
    y0 = sy * (ry - w) + y;
    x1 = sx * rx + x;
    y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (i = start_angle; i < start_angle + seg * seg_count; i += inc) {

    // Calculate pair of coordinates for segment end
    sx2 = cos((i + seg - 90) * DEG2RAD);
    sy2 = sin((i + seg - 90) * DEG2RAD);
    x2 = sx2 * (rx - w) + x;
    y2 = sy2 * (ry - w) + y;
    x3 = sx2 * rx + x;
    y3 = sy2 * ry + y;

    fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to sgement start for next segment
    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;

    delay(10);  // to see demo with slow motion
  }

  return 0;  
}

// #########################################################################
// Return the 16 bit colour with brightness 0-100%
// #########################################################################
// unsigned int brightness(unsigned int colour, int brightness)
// {
//   byte red   = colour >> 11;
//   byte green = (colour & 0x7E0) >> 5;
//   byte blue  = colour & 0x1F;

//   blue =  (blue * brightness)/100;
//   green = (green * brightness)/100;
//   red =   (red * brightness)/100;

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

