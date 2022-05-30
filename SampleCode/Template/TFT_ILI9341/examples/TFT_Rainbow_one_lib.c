/*
 An example showing rainbow colours on a 2.2" TFT LCD screen
 and to show basic examples of font use.

 This sketch uses the GLCD, 2, 4, 6 fonts only. Disable other fonts
 to make the sketch fit in an UNO!

 Make sure all the required fonts are loaded by editting the
 User_Setup.h file in the TFT_ILI9341 library folder.

 If using an UNO or Mega (ATmega328 or ATmega2560 processor) then for best
 performance use the F_AS_T option found in the User_Setup.h file in the
 TFT_ILI9341 library folder.

 The library uses the hardware SPI pins only:
   For UNO, Nano, Micro Pro ATmega328 based processors
      MOSI = pin 11, SCK = pin 13
   For Mega:
      MOSI = pin 51, SCK = pin 52

 The pins used for the TFT chip select (CS) and Data/command (DC) and Reset (RST)
 signal lines to the TFT must also be defined in the library User_Setup.h file.

 Sugested TFT connections for UNO and Atmega328 based boards
   sclk 13  // Don't change, this is the hardware SPI SCLK line
   mosi 11  // Don't change, this is the hardware SPI MOSI line
   cs   10  // Chip select for TFT display
   dc   9   // Data/command line
   rst  7   // Reset, you could connect this to the Arduino reset pin

 Suggested TFT connections for the MEGA and ATmega2560 based boards
   sclk 52  // Don't change, this is the hardware SPI SCLK line
   mosi 51  // Don't change, this is the hardware SPI MOSI line
   cs   47  // TFT chip select line
   dc   48  // TFT data/command line
   rst  44  // you could alternatively connect this to the Arduino reset

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######       TO SELECT THE FONTS AND PINS YOU USE, SEE ABOVE       ######
  #########################################################################
 */

#include <TFT_ILI9341.h> // Hardware-specific library
// #include <SPI.h>

// TFT_ILI9341 tft = TFT_ILI9341();                   // Invoke custom library with default width and height

//TFT_ILI9341 tft = TFT_ILI9341(240, 320);       // Could invoke custom library declaring width and height

static unsigned long targetTime = 0;
static byte red = 31;
static byte green = 0;
static byte blue = 0;
static byte state = 0;
static unsigned int colour = 0; // Colour order is RGB 5+6+5 bits each

static void rainbow_fill(void);

void setup_TFT_Rainbow_one_lib(void) {
  // init();
  setRotation(2);
  fillScreen(TFT_BLACK);
  colour = red << 11;
  targetTime = millis() + 1000;
}

void loop_TFT_Rainbow_one_lib(void) {

    float pi = 0.0f;
    int precision = 0;
    int xpos = 0;
    int ypos = 0;
    int font = 0;
    char tmp[24]; 

  if (targetTime < millis()) {
    targetTime = millis() + 10000;

    rainbow_fill(); // Fill the screen with rainbow colours

    // The standard AdaFruit font still works as before
    setTextColor1(TFT_BLACK); // Background is not defined so it is transparent
    setCursor2(60, 5);

    // TODO : set font 0 is not allowed in MCU
    setTextFont(2);        // Select font 0 which is the Adafruit font
    println("Original Adafruit font!\r\n");

    // The new larger fonts do not need to use the .setCursor call, coords are embedded
    setTextColor1(TFT_BLACK); // Do not plot the background colour
    // Overlay the black text on top of the rainbow plot (the advantage of not drawing the backgorund colour!)
    drawCentreString("Font size 2", 120, 14, 2); // Draw text centre at position 120, 14 using font 2
    drawCentreString("Font size 4", 120, 30, 4); // Draw text centre at position 120, 30 using font 4
    drawCentreString("12.34", 120, 54, 6);       // Draw text centre at position 120, 54 using font 6

    drawCentreString("12.34 is in font size 6", 120, 92, 2); // Draw text centre at position 120, 92 using font 2
    // Note the x position is the top of the font!

    // draw a floating point number
    pi = 3.14159; // Value to print
    precision = 3;  // Number of digits after decimal point
    xpos = 90;      // x position
    ypos = 110;     // y position
    font = 2;       // font number 2
    xpos += drawFloat(pi, precision, xpos, ypos, font); // Draw rounded number and return new xpos delta for next print position
    drawString(" is pi", xpos, ypos, font);             // Continue printing from new x position

    setTextSize(1);           // We are using a size multiplier of 1

    setTextColor1(TFT_BLACK);  // Set text colour to black, no background (so transparent)
    setCursor3(36, 150, 4);    // Set cursor to x = 36, y = 150 and use font 4
    println("Transparent...\r\n");  // As we use println, the cursor moves to the next line

    setCursor2(30, 175);    // Set cursor to x = 30, y = 175
    setTextColor2(TFT_WHITE, TFT_BLACK);  // Set text colour to white and background to black
    println("White on black\r\n");

    setTextFont(4);        // Select font 4 without moving cursor
    setCursor2(50, 210);    // Set cursor to x = 50, y = 210 without changing the font
    setTextColor1(TFT_WHITE);
    
    // By using #TFT print we can use all the formatting features like printing HEX
    sprintf(tmp,"0x%6X\r\n" , 0x57005);
    println((unsigned char*)tmp);  //print(57005, HEX);    // Cursor does no move to next line
    sprintf(tmp,"0x%6X\r\n" , 0x48879);
    println((unsigned char*)tmp);  //println(48879, HEX);  // print and move cursor to next line

    setTextColor2(TFT_GREEN, TFT_BLACK); // This time we will use green text on a black background
    setTextFont(2); // Select font 2
    //Text will wrap to the next line if needed, by luck it breaks the lines at spaces!
    println(" Ode to a Small Lump of Green Putty I Found in My Armpit One Midsummer Morning \r\n");
  }
}

// Fill screen with a rainbow pattern
static void rainbow_fill(void)
{
  // The colours and state are not initialised so the start colour changes each time the funtion is called
  int i = 0;
  for (i = 319; i > 0; i--) {
    // Draw a vertical line 1 pixel wide in the selected colour
    drawFastHLine(0, i, width(), colour); // in this example width() returns the pixel width of the display
    // This is a "state machine" that ramps up/down the colour brightnesses in sequence
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
    colour = red << 11 | green << 5 | blue;
  }
}



