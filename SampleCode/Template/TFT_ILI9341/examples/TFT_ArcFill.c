// This sketch tests a function to draw elliptical (or circular) arcs
// of a defined width

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

#define DEG2RAD 0.0174532925

static unsigned long td = 0;
static unsigned int colour = 0x7FFF;

static int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);

void setup_TFT_ArcFill(void) {
  // Serial.begin(115200);

  // delay(4000);
    
  // begin();

  // if(g_InitOnce == 0)
  //     g_InitOnce = 1;
  // else
  //     return;

  setRotation(3);

  fillScreen(ILI9341_BLACK);
}


void loop_TFT_ArcFill(void) {

  int w  = 12;
  int rx = 160;
  int ry = 100;
  int n = 0;

  td = millis();
 
  for (n = 0; n < 5; n++) {
    fillArc(160, 100, 300, 20, rx-n*w, ry-n*w, w, colour);
  }

  printf("time:%4dms(idx:0x%4X)\r\n" , millis()-td , colour);//Serial.println(millis()-td);

  delay(100);
  fillScreen(ILI9341_BLACK);
  colour = (colour == 0xFFFF) ? (0) : (colour+1) ;  
  // while(1);
}

// #########################################################################
// Draw a circular or elliptical arc with a defined thickness
// #########################################################################

// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 3 degree segments to draw (120 => 360 degree arc)
// rx = x axis radius
// ry = y axis radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn

static int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{

  byte seg = 6; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring
  int i = start_angle;
  float sx;
  float sy;
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
    sx = cos((i + seg - 90) * DEG2RAD);
    sy = sin((i + seg - 90) * DEG2RAD);
    x2 = sx * (rx - w) + x;
    y2 = sy * (ry - w) + y;
    x3 = sx * rx + x;
    y3 = sy * ry + y;

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


