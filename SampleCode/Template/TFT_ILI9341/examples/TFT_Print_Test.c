/*  
 Test the print() viz embedded write() function

 This sketch used font 2, 4, 7
 
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


#include <TFT_ILI9341.h> // Graphics and font library for ILI9341 driver chip
// #include <SPI.h>

#define TFT_GREY 0x5AEB // New colour

// TFT_ILI9341 tft = TFT_ILI9341();  // Invoke library


void setup_TFT_Print_Test(void) {
  // init();
  setRotation(2);
}

void loop_TFT_Print_Test(void) {
  char tmp[24];  
  // float fnumber = 0.0f;
  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  fillScreen(TFT_GREY);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'println'
  //  or stay on the line is there is room for the text with print)
  setCursor3(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  setTextColor2(TFT_WHITE,TFT_BLACK);  setTextSize(1);
  // We can now plot text on screen using the "print" class
  println("Hello World!\r\n");
  
  // Set the font colour to be yellow with no background, set to font 7
  setTextColor1(TFT_YELLOW); setTextFont(7);
	sprintf(tmp,"%4.2f\r\n" , 1234.56);
	println((unsigned char*)tmp);  //println(1234.56);
  
  // Set the font colour to be red with black background, set to font 4
  setTextColor2(TFT_RED,TFT_BLACK);    setTextFont(4);

	sprintf(tmp,"0x%6X\r\n" , 0x37359285);
	println((unsigned char*)tmp);  //  println(3735928559, HEX); // Should print DEADBEEF

  // Set the font colour to be green with black background, set to font 4
  setTextColor2(TFT_GREEN,TFT_BLACK);
  setTextFont(4);
  println("Groop\r\n");
  println("I implore thee,\r\n");

  // Change to font 2
  setTextFont(2);
  println("my foonting turlingdromes.\r\n");
  println("And hooptiously drangle me\r\n");
  println("with crinkly bindlewurdles,\r\n");
  // This next line is deliberately made too long for the display width to test
  // automatic text wrapping onto the next line
  println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!\r\n");
  
  // // Test some print formatting functions
  // fnumber = 123.45f;
  //  // Set the font colour to be blue with no background, set to font 4
  // setTextColor1(TFT_BLUE);    setTextFont(4);
  // println("Float = "); 
	// sprintf(tmp,"%4.2f\r\n" , fnumber);
	// println((unsigned char*)tmp); //println(fnumber);           // Print floating point number

  // println("Binary = "); 
	// sprintf(tmp,"%b\r\n" , fnumber);
	// println((unsigned char*)tmp); //  println((int)fnumber, BIN); // Print as integer value in binary

  // println("Hexadecimal = "); 
  // sprintf(tmp,"0x%lX\r\n" , fnumber);
	// println((unsigned char*)tmp); //println((int)fnumber, HEX); // Print as integer number in Hexadecimal
 
  delay(10000);
}



