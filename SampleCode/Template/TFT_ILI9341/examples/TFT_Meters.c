/*
 Example animated analogue meters using a ILI9341 TFT LCD screen

 Needs Font 2 (also Font 4 if using large scale label)

 Comment out lines 153 and 197 to reduce needle flicker and
 to remove need for Font 4 (which uses ~5k of FLASH!)

 */

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();       // Invoke custom library

#define TFT_GREY 0x5AEB

static float ltx = 0;    // Saved x coord of bottom of needle
static uint16_t osx = 120, osy = 120; // Saved x & y coords
static uint32_t updateTime = 0;       // time for next update

static int old_analog =  -999; // Value last displayed
// int old_digital = -999; // Value last displayed

static int value[6] = {0, 0, 0, 0, 0, 0};
static int old_value[6] = { -1, -1, -1, -1, -1, -1};
static int d = 0;

static void analogMeter(void);
static void plotNeedle(int value, byte ms_delay);
static void plotLinear(char *label, int x, int y);
static void plotPointer(void);

void setup_TFT_Meters(void) {
  byte d = 0;

  // init();
  setRotation(0);
  // Serial.begin(57600); // For debug
  fillScreen(TFT_BLACK);

  analogMeter(); // Draw analogue meter

  // Draw 6 linear meters
  d = 40;
  plotLinear("A0", 0, 160);
  plotLinear("A1", 1 * d, 160);
  plotLinear("A2", 2 * d, 160);
  plotLinear("A3", 3 * d, 160);
  plotLinear("A4", 4 * d, 160);
  plotLinear("A5", 5 * d, 160);

  updateTime = millis(); // Next update time
}


void loop_TFT_Meters(void) {
  if (updateTime <= millis()) {
    updateTime = millis() + 35;
 
    d += 4; if (d >= 360) d = 0;

    //value[0] = map(analogRead(A0), 0, 1023, 0, 100); // Test with value form Analogue 0
    //value[1] = map(analogRead(A1), 0, 1023, 0, 100); // Test with value form Analogue 1
    //value[2] = map(analogRead(A2), 0, 1023, 0, 100); // Test with value form Analogue 2
    //value[3] = map(analogRead(A3), 0, 1023, 0, 100); // Test with value form Analogue 3
    //value[4] = map(analogRead(A4), 0, 1023, 0, 100); // Test with value form Analogue 4
    //value[5] = map(analogRead(A5), 0, 1023, 0, 100); // Test with value form Analogue 5

    // Create a Sine wave for testing
    value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
    value[1] = 50 + 50 * sin((d + 60) * 0.0174532925);
    value[2] = 50 + 50 * sin((d + 120) * 0.0174532925);
    value[3] = 50 + 50 * sin((d + 180) * 0.0174532925);
    value[4] = 50 + 50 * sin((d + 240) * 0.0174532925);
    value[5] = 50 + 50 * sin((d + 300) * 0.0174532925);
    
    //unsigned long t = millis(); 
    plotPointer(); // It takes aout 3.5ms to plot each gauge for a 1 pixel move, 21ms for 6 gauges
     
    plotNeedle(value[0], 0); // It takes between 2 and 12ms to replot the needle with zero delay
    //Serial.println(millis()-t); // Print time taken for meter update
  }
}


// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
static void analogMeter(void)
{
  int i = 0;
  int tl = 0;

  // Coodinates of tick to draw
  float sx = 0.0f;
  float sy = 0.0f;
  uint16_t x0 = 0;
  uint16_t y0 = 0;
  uint16_t x1 = 0;
  uint16_t y1 = 0;

  // Coordinates of next tick for zone fill
  float sx2 = 0.0f;
  float sy2 = 0.0f;
  int x2 = 0;
  int y2 = 0;
  int x3 = 0;
  int y3 = 0;


  // Meter outline
  fillRect(0, 0, 239, 126, TFT_GREY);
  fillRect(5, 3, 230, 119, TFT_WHITE);

  setTextColor1(TFT_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (i = -50; i < 51; i += 5) {
    // Long scale tick length
    tl = 15;

    // Coodinates of tick to draw
    sx = cos((i - 90) * 0.0174532925);
    sy = sin((i - 90) * 0.0174532925);
    x0 = sx * (100 + tl) + 120;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + 120;
    y1 = sy * 100 + 140;

    // Coordinates of next tick for zone fill
    sx2 = cos((i + 5 - 90) * 0.0174532925);
    sy2 = sin((i + 5 - 90) * 0.0174532925);
    x2 = sx2 * (100 + tl) + 120;
    y2 = sy2 * (100 + tl) + 140;
    x3 = sx2 * 100 + 120;
    y3 = sy2 * 100 + 140;

    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
    //  fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    //}

    // Green zone limits
    if (i >= 0 && i < 25) {
      fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
      fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
      fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (100 + tl) + 120;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + 120;
    y1 = sy * 100 + 140;

    // Draw tick
    drawLine(x0, y0, x1, y1, TFT_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (100 + tl + 10) + 120;
      y0 = sy * (100 + tl + 10) + 140;
      switch (i / 25) {
        case -2: drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: drawCentreString("25", x0, y0 - 9, 2); break;
        case 0: drawCentreString("50", x0, y0 - 6, 2); break;
        case 1: drawCentreString("75", x0, y0 - 9, 2); break;
        case 2: drawCentreString("100", x0, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 100 + 120;
    y0 = sy * 100 + 140;
    // Draw scale arc, don't draw the last part
    if (i < 50) drawLine(x0, y0, x1, y1, TFT_BLACK);
  }

  drawString("%RH", 5 + 230 - 40, 119 - 20, 2); // Units at bottom right
  drawCentreString("%RH", 120, 70, 4); // Comment out to avoid font 4
  drawRect(5, 3, 230, 119, TFT_BLACK); // Draw bezel line

  plotNeedle(0, 0); // Put meter needle at 0
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
static void plotNeedle(int value, byte ms_delay)
{
  char buf[8];
  float sdeg = 0.0f;
  float sx = 0.0f;
  float sy = 0.0f;
  float tx = 0.0f;

  setTextColor2(TFT_BLACK, TFT_WHITE);
  // char buf[8]; 
  sprintf(buf,"%4d" , value); //dtostrf(value, 4, 0, buf);
  drawRightString(buf, 40, 119 - 20, 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle util new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately id delay is 0

    sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    sx = cos(sdeg * 0.0174532925);
    sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_WHITE);
    drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_WHITE);
    drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    setTextColor1(TFT_BLACK);
    drawCentreString("%RH", 120, 70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = sx * 98 + 120;
    osy = sy * 98 + 140;

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_RED);
    drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_MAGENTA);
    drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}

// #########################################################################
//  Draw a linear meter on the screen
// #########################################################################
static void plotLinear(char *label, int x, int y)
{
  int w = 36;
  int i = 0;
  drawRect(x, y, w, 155, TFT_GREY);
  fillRect(x+2, y + 19, w-3, 155 - 38, TFT_WHITE);
  setTextColor2(TFT_CYAN, TFT_BLACK);
  drawCentreString(label, x + w / 2, y + 2, 2);

  for (i = 0; i < 110; i += 10)
  {
    drawFastHLine(x + 20, y + 27 + i, 6, TFT_BLACK);
  }

  for (i = 0; i < 110; i += 50)
  {
    drawFastHLine(x + 20, y + 27 + i, 9, TFT_BLACK);
  }
  
  fillTriangle(x+3, y + 127, x+3+16, y+127, x + 3, y + 127 - 5, TFT_RED);
  fillTriangle(x+3, y + 127, x+3+16, y+127, x + 3, y + 127 + 5, TFT_RED);
  
  drawCentreString("---", x + w / 2, y + 155 - 18, 2);
}

// #########################################################################
//  Adjust 6 linear meter pointer positions
// #########################################################################
static void plotPointer(void)
{
  int dy = 187;
  byte pw = 16;
  int i = 0;
  char buf[8];
  int dx = 0;

  setTextColor2(TFT_GREEN, TFT_BLACK);

  // Move the 6 pointers one pixel towards new value
  for (i = 0; i < 6; i++)
  {
    // char buf[8]; 
    sprintf(buf,"%4d" , value);// dtostrf(value[i], 4, 0, buf);
    drawRightString(buf, i * 40 + 36 - 5, 187 - 27 + 155 - 18, 2);

    dx = 3 + 40 * i;
    if (value[i] < 0) value[i] = 0; // Limit value to emulate needle end stops
    if (value[i] > 100) value[i] = 100;

    while (!(value[i] == old_value[i])) {
      dy = 187 + 100 - old_value[i];
      if (old_value[i] > value[i])
      {
        drawLine(dx, dy - 5, dx + pw, dy, TFT_WHITE);
        old_value[i]--;
        drawLine(dx, dy + 6, dx + pw, dy + 1, TFT_RED);
      }
      else
      {
        drawLine(dx, dy + 5, dx + pw, dy, TFT_WHITE);
        old_value[i]++;
        drawLine(dx, dy - 6, dx + pw, dy - 1, TFT_RED);
      }
    }
  }
}

