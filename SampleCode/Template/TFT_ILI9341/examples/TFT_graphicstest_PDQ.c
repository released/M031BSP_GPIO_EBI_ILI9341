/*
 Adapted from the Adafruit and Xark's PDQ graphicstest sketch.

 This sketch uses the GLCD font only. Disable other fonts to make
 the sketch fit in an UNO!

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


// #include "SPI.h"
#include "TFT_ILI9341.h"

// These are used to get information about static SRAM and flash memory sizes
// extern "C" char __data_start[];		// start of SRAM data
// extern "C" char _end[];			// end of SRAM data (used to check amount of SRAM this program's variables use)
// extern "C" char __data_load_end[];	// end of FLASH (used to check amount of Flash this program's code and data uses)

static const unsigned long __data_start = 0x20000000;
static const unsigned long _end = 0x20000000 + 0x4000;
static const unsigned long __data_load_end = 0x20000;

static void printnice(int32_t v);
static uint32_t micros_start(void);
static uint32_t testHaD(void);
static uint32_t testFillScreen(void);
static uint32_t testText(void);
static uint32_t testPixels(void);
static uint32_t testLines(uint16_t color);
static uint32_t testFastLines(uint16_t color1, uint16_t color2);
static uint32_t testRects(uint16_t color);
static uint32_t testFilledRects(uint16_t color1, uint16_t color2);
static uint32_t testFilledCircles(uint8_t radius, uint16_t color);
static uint32_t testCircles(uint8_t radius, uint16_t color);
static uint32_t testTriangles(void);
static uint32_t testFilledTriangles(void);
static uint32_t testRoundRects(void);
static uint32_t testFilledRoundRects(void);


// Use hardware SPI
// TFT_ILI9341 tft = TFT_ILI9341();

// unsigned long total = 0;
// unsigned long tn = 0;

void setup_TFT_graphicstest_PDQ(void) {
//   Serial.begin(115200);
//   while (!Serial);
  println("Bodmer's 2.2\" SPI TFT Test!"); 
 
//   init();
}

void loop_TFT_graphicstest_PDQ(void)
{
  	char tmp[24];  	
	uint16_t c = 4;
	int8_t d = 1;
	int32_t i = 0;
	uint32_t usedFilledRoundRects = 0;
	uint32_t usecRoundRects = 0;
	uint32_t usecFilledTrangles = 0;
	uint32_t usecTriangles = 0;
	uint32_t usecCircles = 0;
	uint32_t usecFilledCircles = 0;
	uint32_t usecFilledRects = 0;
	uint32_t usecRects = 0;
	uint32_t usecFastLines = 0;
	uint32_t usecLines = 0;
	uint32_t usecPixels = 0;
	uint32_t usecText = 0;
	uint32_t usecFillScreen = 0;
	uint32_t usecHaD = 0;


  	printf(__DATE__ " " __TIME__ " - Flash=0x");
	printf("%X", __data_load_end);
	printf(" RAM=0x");
	printf("%X\r\n", _end - __data_start);

	printf("Benchmark                Time (microseconds)\r\n");

	usecHaD = testHaD();
	printf("HaD pushColor            ");
	printf("%dms\r\n" , usecHaD);//Serial.println(usecHaD);
	delay(100);

	usecFillScreen = testFillScreen();
	printf("Screen fill              ");
	printf("%dms\r\n" , usecFillScreen);//Serial.println(usecFillScreen);
	delay(100);

	usecText = testText();
	printf("Text                     ");
	printf("%dms\r\n" , usecText);//Serial.println(usecText);
	delay(100);

	usecPixels = testPixels();
	printf("Pixels                   ");
	printf("%dms\r\n" , usecPixels);//Serial.println(usecPixels);
	delay(100);

	usecLines = testLines(TFT_BLUE);
	printf("Lines                    ");
	printf("%dms\r\n" , usecLines);//Serial.println(usecLines);
	delay(100);

	usecFastLines = testFastLines(TFT_RED, TFT_BLUE);
	printf("Horiz/Vert Lines         ");
	printf("%dms\r\n" , usecFastLines);//Serial.println(usecFastLines);
	delay(100);

	usecRects = testRects(TFT_GREEN);
	printf("Rectangles (outline)     ");
	printf("%dms\r\n" , usecRects);//Serial.println(usecRects);
	delay(100);

	usecFilledRects = testFilledRects(TFT_YELLOW, TFT_MAGENTA);
	printf("Rectangles (filled)      ");
	printf("%dms\r\n" , usecFilledRects);//Serial.println(usecFilledRects);
	delay(100);

	usecFilledCircles = testFilledCircles(10, TFT_MAGENTA);
	printf("Circles (filled)         ");
	printf("%dms\r\n" , usecFilledCircles);//Serial.println(usecFilledCircles);
	delay(100);

	usecCircles = testCircles(10, TFT_WHITE);
	printf("Circles (outline)        ");
	printf("%dms\r\n" , usecCircles);//Serial.println(usecCircles);
	delay(100);

	usecTriangles = testTriangles();
	printf("Triangles (outline)      ");
	printf("%dms\r\n" , usecTriangles);//Serial.println(usecTriangles);
	delay(100);

	usecFilledTrangles = testFilledTriangles();
	printf("Triangles (filled)       ");
	printf("%dms\r\n" , usecFilledTrangles);//Serial.println(usecFilledTrangles);
	delay(100);

	usecRoundRects = testRoundRects();
	printf("Rounded rects (outline)  ");
	printf("%dms\r\n" , usecRoundRects);//Serial.println(usecRoundRects);
	delay(100);

	usedFilledRoundRects = testFilledRoundRects();
	printf("Rounded rects (filled)   ");
	printf("%dms\r\n" , usedFilledRoundRects);//Serial.println(usedFilledRoundRects);
	delay(100);

	printf("Done!\r\n");//printf("Done!"));

	// uint16_t c = 4;
	// int8_t d = 1;
	for (i = 0; i < height(); i++)
	{
		drawFastHLine(0, i, width(), c);
		c += d;
		if (c <= 4 || c >= 11)
			d = -d;
	}
	
	setCursor2(0, 0);
	setTextColor1(TFT_MAGENTA);
	setTextSize(2);

 	println("     TFT_ILI9341    ");

	setCursor2(0, 40);
	setTextSize(1);
	setTextColor1(TFT_WHITE);
	println(" GPIO LCD Benchmark (nuvoTon M031@48MHz)");

	setCursor2(0, 50);
	setTextSize(1);
	println("");
	setTextColor1(color565(0x80, 0x80, 0x80));
	println("  Memory Used:  Flash=0x");
		sprintf(tmp,"0x%X" , __data_load_end);//print((uint16_t)__data_load_end, HEX);
        println((unsigned char*)tmp);
	println(" RAM=0x");
        sprintf(tmp,"0x%X" , _end - __data_start );//println((uint16_t)_end - (uint16_t)__data_start, HEX);
		println((unsigned char*)tmp);
	println("");
	println("");

	setCursor2(0, 60);
	setTextColor1(TFT_GREEN);
	println(" Benchmark         microseconds");
	println("");
	setTextColor1(TFT_YELLOW);

	setCursor2(0, 80);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("HaD pushColor      ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecHaD);

	setCursor2(0, 90);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Screen fill        ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecFillScreen);

	setCursor2(0, 100);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Text               ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecText);

	setCursor2(0, 110);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Pixels             ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecPixels);

	setCursor2(0, 120);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Lines              ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecLines);

	setCursor2(0, 130);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Horiz/Vert Lines   ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecFastLines);

	setCursor2(0, 140);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Rectangles         ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecRects);

	setCursor2(0, 150);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Rectangles-filled  ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecFilledRects);

	setCursor2(0, 160);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Circles            ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecCircles);

	setCursor2(0, 170);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Circles-filled     ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecFilledCircles);

	setCursor2(0, 180);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Triangles          ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecTriangles);

	setCursor2(0, 190);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Triangles-filled   ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecFilledTrangles);

	setCursor2(0, 200);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Rounded rects      ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usecRoundRects);

	setCursor2(0, 210);
	setTextColor1(TFT_CYAN); setTextSize(1);
	println("Rounded rects-fill ");
	setTextColor1(TFT_YELLOW); setTextSize(1);
	printnice(usedFilledRoundRects);

	setCursor2(0, 220);
	setTextSize(1);
	println("");
	setTextColor1(TFT_GREEN); setTextSize(2);
	println("Benchmark Completed!");

	delay(5000);
}

void printnice(int32_t v)
{
	#if 1
	char	str[32] = { 0 };
	sprintf(str, "%lu", v);	
	println((unsigned char*)str);
	#else
	char	str[32] = { 0 };
	char *p;
	sprintf(str, "%lu", v);
	for (*p = (char)(str+strlen(str))-3; p > str; p -= 3)
	{
		memmove(p+1, p, strlen(p)+1);
		*p = ',';
		
	}
	while (strlen(str) < 10)
	{
		memmove(str+1, str, strlen(str)+1);
		*str = ' ';
	}
	println((unsigned char*)str);
	#endif
}

// static inline uint32_t micros_start() __attribute__ ((always_inline));
static uint32_t micros_start()
{
	uint8_t oms = millis();
	while ((uint8_t)millis() == oms)
		;
	return micros();
}

uint32_t testHaD()
{

	uint32_t t = 0 ;
	uint32_t start =0;
	
	int i = 0;

	uint16_t cnt = 0;
	uint16_t color = 0;
	uint16_t curcolor = 0;

	uint8_t *cmp;	

	// pseudo-code for cheesy RLE
	// start with color1
	// while more input data remaining
	// 	count =  0nnnnnnn = 1 byte or 1nnnnnnn nnnnnnnn 2 bytes (0 - 32767)
	// 	repeat color count times
	// 	toggle color1/color2
	const uint8_t HaD_240x320[] =
	{
		0xb9, 0x50, 0x0e, 0x80, 0x93, 0x0e, 0x41, 0x11, 0x80, 0x8d, 0x11, 0x42, 0x12, 0x80, 0x89, 0x12, 
		0x45, 0x12, 0x80, 0x85, 0x12, 0x48, 0x12, 0x80, 0x83, 0x12, 0x4a, 0x13, 0x7f, 0x13, 0x4c, 0x13, 
		0x7d, 0x13, 0x4e, 0x13, 0x7b, 0x13, 0x50, 0x13, 0x79, 0x13, 0x52, 0x13, 0x77, 0x13, 0x54, 0x13, 
		0x75, 0x13, 0x57, 0x11, 0x75, 0x11, 0x5a, 0x11, 0x73, 0x11, 0x5c, 0x11, 0x71, 0x11, 0x5e, 0x10, 
		0x71, 0x10, 0x60, 0x10, 0x6f, 0x10, 0x61, 0x10, 0x6f, 0x10, 0x60, 0x11, 0x6f, 0x11, 0x5e, 0x13, 
		0x6d, 0x13, 0x5c, 0x14, 0x6d, 0x14, 0x5a, 0x15, 0x6d, 0x15, 0x58, 0x17, 0x6b, 0x17, 0x37, 0x01, 
		0x1f, 0x17, 0x6b, 0x17, 0x1f, 0x01, 0x17, 0x02, 0x1d, 0x18, 0x6b, 0x18, 0x1d, 0x02, 0x17, 0x03, 
		0x1b, 0x19, 0x6b, 0x19, 0x1b, 0x03, 0x17, 0x05, 0x18, 0x1a, 0x6b, 0x1a, 0x18, 0x05, 0x17, 0x06, 
		0x16, 0x1b, 0x6b, 0x1b, 0x16, 0x06, 0x17, 0x07, 0x14, 0x1c, 0x6b, 0x1c, 0x14, 0x07, 0x17, 0x08, 
		0x12, 0x1d, 0x6b, 0x1d, 0x12, 0x08, 0x17, 0x09, 0x10, 0x1e, 0x6b, 0x1e, 0x10, 0x09, 0x17, 0x0a, 
		0x0e, 0x1f, 0x6b, 0x1f, 0x0e, 0x0a, 0x17, 0x0b, 0x0c, 0x20, 0x6b, 0x20, 0x0c, 0x0b, 0x17, 0x0c, 
		0x0b, 0x21, 0x69, 0x21, 0x0b, 0x0c, 0x18, 0x0d, 0x08, 0x23, 0x67, 0x23, 0x08, 0x0d, 0x19, 0x0e, 
		0x06, 0x26, 0x63, 0x26, 0x06, 0x0e, 0x19, 0x0f, 0x04, 0x28, 0x61, 0x28, 0x04, 0x0f, 0x19, 0x10, 
		0x02, 0x2a, 0x5f, 0x2a, 0x02, 0x10, 0x1a, 0x3c, 0x5d, 0x3c, 0x1b, 0x3d, 0x5b, 0x3d, 0x1c, 0x3d, 
		0x59, 0x3d, 0x1d, 0x3e, 0x57, 0x3e, 0x1e, 0x3e, 0x55, 0x3e, 0x1f, 0x40, 0x51, 0x40, 0x20, 0x40, 
		0x4f, 0x40, 0x22, 0x40, 0x22, 0x09, 0x22, 0x40, 0x24, 0x40, 0x1a, 0x17, 0x1a, 0x40, 0x26, 0x40, 
		0x16, 0x1d, 0x16, 0x40, 0x28, 0x40, 0x12, 0x23, 0x12, 0x40, 0x2a, 0x40, 0x0f, 0x27, 0x0f, 0x40, 
		0x2c, 0x41, 0x0b, 0x2b, 0x0b, 0x41, 0x2f, 0x3f, 0x09, 0x2f, 0x09, 0x3f, 0x32, 0x3d, 0x08, 0x33, 
		0x08, 0x3d, 0x35, 0x3a, 0x08, 0x35, 0x08, 0x3a, 0x3a, 0x36, 0x07, 0x39, 0x07, 0x36, 0x41, 0x09, 
		0x05, 0x23, 0x07, 0x3b, 0x07, 0x23, 0x05, 0x09, 0x54, 0x21, 0x07, 0x3d, 0x07, 0x21, 0x64, 0x1f, 
		0x06, 0x41, 0x06, 0x1f, 0x66, 0x1d, 0x06, 0x43, 0x06, 0x1d, 0x68, 0x1b, 0x06, 0x45, 0x06, 0x1b, 
		0x6b, 0x18, 0x06, 0x47, 0x06, 0x18, 0x6e, 0x16, 0x06, 0x49, 0x06, 0x16, 0x70, 0x14, 0x06, 0x4b, 
		0x06, 0x14, 0x72, 0x13, 0x06, 0x4b, 0x06, 0x13, 0x74, 0x11, 0x06, 0x4d, 0x06, 0x11, 0x76, 0x0f, 
		0x06, 0x4f, 0x06, 0x0f, 0x78, 0x0e, 0x05, 0x51, 0x05, 0x0e, 0x7a, 0x0c, 0x06, 0x51, 0x06, 0x0c, 
		0x7d, 0x09, 0x06, 0x53, 0x06, 0x09, 0x80, 0x80, 0x08, 0x05, 0x55, 0x05, 0x08, 0x80, 0x82, 0x06, 
		0x05, 0x57, 0x05, 0x06, 0x80, 0x84, 0x05, 0x05, 0x57, 0x05, 0x05, 0x80, 0x86, 0x03, 0x05, 0x59, 
		0x05, 0x03, 0x80, 0x88, 0x02, 0x05, 0x59, 0x05, 0x02, 0x80, 0x8f, 0x5b, 0x80, 0x95, 0x5b, 0x80, 
		0x94, 0x5d, 0x80, 0x93, 0x5d, 0x80, 0x92, 0x5e, 0x80, 0x92, 0x5f, 0x80, 0x91, 0x5f, 0x80, 0x90, 
		0x61, 0x80, 0x8f, 0x61, 0x80, 0x8f, 0x61, 0x80, 0x8e, 0x63, 0x80, 0x8d, 0x63, 0x80, 0x8d, 0x63, 
		0x80, 0x8d, 0x63, 0x80, 0x8c, 0x19, 0x07, 0x25, 0x07, 0x19, 0x80, 0x8b, 0x16, 0x0d, 0x1f, 0x0d, 
		0x16, 0x80, 0x8b, 0x14, 0x11, 0x1b, 0x11, 0x14, 0x80, 0x8b, 0x13, 0x13, 0x19, 0x13, 0x13, 0x80, 
		0x8b, 0x12, 0x15, 0x17, 0x15, 0x12, 0x80, 0x8a, 0x12, 0x17, 0x15, 0x17, 0x12, 0x80, 0x89, 0x11, 
		0x19, 0x13, 0x19, 0x11, 0x80, 0x89, 0x11, 0x19, 0x13, 0x19, 0x11, 0x80, 0x89, 0x10, 0x1b, 0x11, 
		0x1b, 0x10, 0x80, 0x89, 0x0f, 0x1c, 0x11, 0x1c, 0x0f, 0x80, 0x89, 0x0f, 0x1c, 0x11, 0x1c, 0x0f, 
		0x80, 0x89, 0x0f, 0x1c, 0x11, 0x1c, 0x0f, 0x80, 0x89, 0x0e, 0x1d, 0x11, 0x1d, 0x0e, 0x80, 0x89, 
		0x0e, 0x1c, 0x13, 0x1c, 0x0e, 0x80, 0x89, 0x0e, 0x1b, 0x15, 0x1b, 0x0e, 0x80, 0x89, 0x0e, 0x1b, 
		0x15, 0x1b, 0x0e, 0x80, 0x89, 0x0e, 0x1a, 0x17, 0x1a, 0x0e, 0x80, 0x89, 0x0e, 0x18, 0x1b, 0x18, 
		0x0e, 0x80, 0x89, 0x0e, 0x16, 0x1f, 0x16, 0x0e, 0x80, 0x89, 0x0e, 0x14, 0x23, 0x14, 0x0e, 0x80, 
		0x89, 0x0f, 0x11, 0x27, 0x11, 0x0f, 0x80, 0x89, 0x0f, 0x0e, 0x2d, 0x0e, 0x0f, 0x80, 0x89, 0x0f, 
		0x0c, 0x31, 0x0c, 0x0f, 0x80, 0x89, 0x0f, 0x0b, 0x33, 0x0b, 0x0f, 0x80, 0x8a, 0x0f, 0x09, 0x35, 
		0x09, 0x0f, 0x80, 0x8b, 0x10, 0x08, 0x35, 0x08, 0x10, 0x80, 0x8b, 0x10, 0x07, 0x37, 0x07, 0x10, 
		0x80, 0x8b, 0x11, 0x06, 0x37, 0x06, 0x11, 0x80, 0x8b, 0x12, 0x05, 0x37, 0x05, 0x12, 0x80, 0x8c, 
		0x13, 0x03, 0x1b, 0x01, 0x1b, 0x03, 0x13, 0x80, 0x8d, 0x30, 0x03, 0x30, 0x80, 0x8d, 0x30, 0x04, 
		0x2f, 0x80, 0x8d, 0x2f, 0x05, 0x2f, 0x80, 0x8e, 0x2e, 0x06, 0x2d, 0x80, 0x8f, 0x2d, 0x07, 0x2d, 
		0x80, 0x8f, 0x2d, 0x07, 0x2d, 0x80, 0x90, 0x2c, 0x08, 0x2b, 0x80, 0x91, 0x2b, 0x09, 0x2b, 0x80, 
		0x8c, 0x01, 0x05, 0x2a, 0x09, 0x2a, 0x05, 0x01, 0x80, 0x85, 0x03, 0x05, 0x2a, 0x09, 0x2a, 0x05, 
		0x03, 0x80, 0x82, 0x04, 0x05, 0x2a, 0x09, 0x2a, 0x04, 0x05, 0x80, 0x80, 0x06, 0x05, 0x29, 0x04, 
		0x02, 0x03, 0x29, 0x05, 0x06, 0x7e, 0x07, 0x05, 0x29, 0x03, 0x03, 0x03, 0x29, 0x05, 0x07, 0x7c, 
		0x09, 0x05, 0x28, 0x02, 0x05, 0x02, 0x28, 0x05, 0x09, 0x7a, 0x0a, 0x05, 0x28, 0x02, 0x05, 0x02, 
		0x28, 0x05, 0x0a, 0x78, 0x0c, 0x05, 0x27, 0x02, 0x05, 0x02, 0x27, 0x05, 0x0c, 0x76, 0x0d, 0x06, 
		0x26, 0x01, 0x07, 0x01, 0x26, 0x06, 0x0d, 0x73, 0x10, 0x05, 0x55, 0x05, 0x10, 0x70, 0x12, 0x05, 
		0x53, 0x05, 0x12, 0x6e, 0x13, 0x06, 0x51, 0x06, 0x13, 0x6c, 0x15, 0x05, 0x51, 0x05, 0x15, 0x6a, 
		0x16, 0x06, 0x4f, 0x06, 0x16, 0x68, 0x18, 0x06, 0x4d, 0x06, 0x18, 0x66, 0x1a, 0x06, 0x4b, 0x06, 
		0x1a, 0x64, 0x1c, 0x06, 0x49, 0x06, 0x1c, 0x55, 0x07, 0x05, 0x1e, 0x06, 0x49, 0x06, 0x1e, 0x05, 
		0x07, 0x42, 0x30, 0x06, 0x47, 0x06, 0x30, 0x3a, 0x34, 0x06, 0x45, 0x06, 0x34, 0x35, 0x37, 0x06, 
		0x43, 0x06, 0x37, 0x32, 0x39, 0x07, 0x3f, 0x07, 0x39, 0x2f, 0x3c, 0x07, 0x3d, 0x07, 0x3c, 0x2c, 
		0x3e, 0x07, 0x3b, 0x07, 0x3e, 0x2a, 0x40, 0x06, 0x3b, 0x06, 0x40, 0x28, 0x40, 0x06, 0x3c, 0x07, 
		0x40, 0x26, 0x3f, 0x08, 0x3d, 0x08, 0x3f, 0x24, 0x3f, 0x09, 0x3d, 0x09, 0x3f, 0x22, 0x3f, 0x0a, 
		0x14, 0x01, 0x13, 0x02, 0x13, 0x0a, 0x3f, 0x20, 0x3f, 0x0b, 0x14, 0x01, 0x13, 0x02, 0x13, 0x0b, 
		0x3f, 0x1f, 0x3e, 0x0c, 0x14, 0x01, 0x13, 0x02, 0x13, 0x0c, 0x3e, 0x1e, 0x3e, 0x0d, 0x13, 0x02, 
		0x13, 0x02, 0x13, 0x0d, 0x3e, 0x1d, 0x3d, 0x0e, 0x13, 0x02, 0x13, 0x02, 0x13, 0x0e, 0x3d, 0x1c, 
		0x3c, 0x11, 0x11, 0x04, 0x11, 0x04, 0x11, 0x11, 0x3c, 0x1b, 0x10, 0x01, 0x2a, 0x12, 0x11, 0x04, 
		0x11, 0x04, 0x11, 0x12, 0x2a, 0x01, 0x10, 0x1a, 0x0f, 0x04, 0x28, 0x14, 0x0f, 0x06, 0x0f, 0x06, 
		0x0f, 0x14, 0x28, 0x04, 0x0f, 0x19, 0x0e, 0x06, 0x26, 0x16, 0x0d, 0x08, 0x0d, 0x08, 0x0d, 0x16, 
		0x26, 0x06, 0x0e, 0x19, 0x0d, 0x07, 0x25, 0x18, 0x0b, 0x0a, 0x0b, 0x0a, 0x0b, 0x18, 0x25, 0x07, 
		0x0d, 0x19, 0x0c, 0x09, 0x23, 0x1c, 0x06, 0x0f, 0x05, 0x10, 0x05, 0x1c, 0x23, 0x09, 0x0c, 0x18, 
		0x0c, 0x0b, 0x21, 0x69, 0x21, 0x0b, 0x0c, 0x17, 0x0b, 0x0d, 0x1f, 0x6b, 0x1f, 0x0d, 0x0b, 0x17, 
		0x0a, 0x0f, 0x1e, 0x6b, 0x1e, 0x0f, 0x0a, 0x17, 0x09, 0x11, 0x1d, 0x6b, 0x1d, 0x11, 0x09, 0x17, 
		0x07, 0x14, 0x1c, 0x6b, 0x1c, 0x14, 0x07, 0x17, 0x06, 0x16, 0x1b, 0x6b, 0x1b, 0x16, 0x06, 0x17, 
		0x05, 0x18, 0x1a, 0x6b, 0x1a, 0x18, 0x05, 0x17, 0x04, 0x1a, 0x19, 0x6b, 0x19, 0x1a, 0x04, 0x17, 
		0x03, 0x1b, 0x19, 0x6b, 0x19, 0x1b, 0x03, 0x17, 0x02, 0x1d, 0x18, 0x6b, 0x18, 0x1d, 0x02, 0x37, 
		0x17, 0x6b, 0x17, 0x58, 0x16, 0x6b, 0x16, 0x5a, 0x14, 0x6d, 0x14, 0x5c, 0x13, 0x6d, 0x13, 0x5e, 
		0x12, 0x6d, 0x12, 0x60, 0x10, 0x6f, 0x10, 0x61, 0x10, 0x6f, 0x10, 0x60, 0x11, 0x6f, 0x11, 0x5e, 
		0x11, 0x71, 0x11, 0x5c, 0x12, 0x71, 0x12, 0x5a, 0x12, 0x73, 0x12, 0x58, 0x12, 0x75, 0x12, 0x56, 
		0x13, 0x75, 0x13, 0x54, 0x13, 0x77, 0x13, 0x51, 0x14, 0x79, 0x14, 0x4e, 0x14, 0x7b, 0x14, 0x4c, 
		0x14, 0x7d, 0x14, 0x4a, 0x14, 0x7f, 0x14, 0x48, 0x13, 0x80, 0x83, 0x13, 0x46, 0x13, 0x80, 0x85, 
		0x13, 0x44, 0x12, 0x80, 0x89, 0x12, 0x42, 0x11, 0x80, 0x8d, 0x11, 0x40, 0x0f, 0x80, 0x93, 0x0f, 
		0x45, 0x04, 0x80, 0x9d, 0x04, 0xb9, 0x56, 
	};

	
	fillScreen(TFT_BLACK);

	start = micros_start();
	
	for (i = 0; i < 0x10; i++)
	{
		setWindow(0, 0, 240-1, 320-1);

		cnt = 0;
		color = color565((i << 4) | i, (i << 4) | i, (i << 4) | i);
		curcolor = 0;

		 cmp = (uint8_t*) &HaD_240x320[0];

		while (cmp < &HaD_240x320[sizeof(HaD_240x320)])
		{
			cnt = *(__IO uint8_t *)(cmp++);
			if (cnt & 0x80) cnt = ((cnt & 0x7f) << 8) | *(__IO uint8_t *)(cmp++);
			pushColor2(curcolor, cnt);	// PDQ_GFX has count
			curcolor ^= color;
		}
	}

	t = micros() - start;

	setTextColor1(TFT_YELLOW);
	setTextSize(2);
	setCursor2(8, 285);
	println("http://hackaday.io/");
	setCursor2(96, 302);
	println("Xark");

	delay(3 * 1000L);
	
	return t;
}

uint32_t testFillScreen()
{
	uint32_t start = micros_start();
    // Shortened this tedious test!
		fillScreen(TFT_WHITE);
		fillScreen(TFT_RED);
		fillScreen(TFT_GREEN);
		fillScreen(TFT_BLUE);
		fillScreen(TFT_BLACK);

	return (micros() - start)/5;
}

uint32_t testText()
{
  	char tmp[24];  	
	uint32_t start = micros_start();
	uint32_t t = 0;
	fillScreen(TFT_BLACK);

	setCursor2(0, 0);
	setTextColor2(TFT_WHITE,TFT_BLACK);	setTextSize(1);
	println("Hello World!");
	setTextSize(2);
	setTextColor1(color565(0xff, 0x00, 0x00));
	println("RED ");
	setTextColor1(color565(0x00, 0xff, 0x00));
	println("GREEN ");
	setTextColor1(color565(0x00, 0x00, 0xff));
	println("BLUE");
	setTextColor1(TFT_YELLOW); setTextSize(2);
	sprintf(tmp,"%4.2f" , 1234.56);
	println((unsigned char*)tmp);	
	setTextColor1(TFT_RED);		setTextSize(3);
	sprintf(tmp,"0x%6X" , 0xDEADBEEF);
	println((unsigned char*)tmp);
	// println();
	setTextColor1(TFT_GREEN);
	setTextSize(5);
	println("Groop");
	setTextSize(2);
	println("I implore thee,");
  	setTextColor1(TFT_GREEN);
	setTextSize(1);
	println("my foonting turlingdromes.");
	println("And hooptiously drangle me");
	println("with crinkly bindlewurdles,");
	println("Or I will rend thee");
	println("in the gobberwarts");
	println("with my blurglecruncheon,");
	println("see if I don't!");
	println("");
	println("");
	setTextColor1(TFT_MAGENTA);
	setTextSize(6);
	println("Woot!");
	t = micros() - start;
	delay(1000);
	return t;
}

uint32_t testPixels()
{
	int32_t	w = width();
	int32_t	h = height();
	uint16_t y = 0;
	uint16_t x = 0; 

	uint32_t start = micros_start();

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			drawPixel(x, y, color565(x<<3, y<<3, x*y));
		}
	}
	
	return micros() - start;
}


uint32_t testLines(uint16_t color)
{
	uint32_t start, t;
	int32_t	x1, y1, x2, y2;
	int32_t	w = width();
	int32_t	h = height();

	fillScreen(TFT_BLACK);

	x1 = y1 = 0;
	y2 = h - 1;

	start = micros_start();

	for (x2 = 0; x2 < w; x2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}

	x2 = w - 1;

	for (y2 = 0; y2 < h; y2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}

	t = micros() - start; // fillScreen doesn't count against timing

	fillScreen(TFT_BLACK);

	x1 = w - 1;
	y1 = 0;
	y2 = h - 1;

	start = micros_start();

	for (x2 = 0; x2 < w; x2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}

	x2 = 0;
	for (y2 = 0; y2 < h; y2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}

	t += micros() - start;

	fillScreen(TFT_BLACK);

	x1 = 0;
	y1 = h - 1;
	y2 = 0;

	start = micros_start();

	for (x2 = 0; x2 < w; x2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}
	x2 = w - 1;
	for (y2 = 0; y2 < h; y2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}
	t += micros() - start;

	fillScreen(TFT_BLACK);

	x1 = w - 1;
	y1 = h - 1;
	y2 = 0;

	start = micros_start();

	for (x2 = 0; x2 < w; x2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}

	x2 = 0;
	for (y2 = 0; y2 < h; y2 += 6)
	{
		drawLine(x1, y1, x2, y2, color);
	}

	t += micros() - start;

	return t;
}

uint32_t testFastLines(uint16_t color1, uint16_t color2)
{
	uint32_t start;
	int32_t x, y;
	int32_t w = width();
	int32_t h = height();

	fillScreen(TFT_BLACK);

	start = micros_start();

	for (y = 0; y < h; y += 5)
		drawFastHLine(0, y, w, color1);
	for (x = 0; x < w; x += 5)
		drawFastVLine(x, 0, h, color2);

	return micros() - start;
}

uint32_t testRects(uint16_t color)
{
	uint32_t start;
	int32_t n, i, i2;
	int32_t cx = width() / 2;
	int32_t cy = height() / 2;

	fillScreen(TFT_BLACK);
	n = min(width(), height());
	start = micros_start();
	for (i = 2; i < n; i += 6)
	{
		i2 = i / 2;
		drawRect(cx-i2, cy-i2, i, i, color);
	}

	return micros() - start;
}

uint32_t testFilledRects(uint16_t color1, uint16_t color2)
{
	uint32_t start, t = 0;
	int32_t n, i, i2;
	int32_t cx = width() / 2 - 1;
	int32_t cy = height() / 2 - 1;

	fillScreen(TFT_BLACK);
	n = min(width(), height());
	for (i = n; i > 0; i -= 6)
	{
		i2 = i / 2;

		start = micros_start();

		fillRect(cx-i2, cy-i2, i, i, color1);

		t += micros() - start;

		// Outlines are not included in timing results
		drawRect(cx-i2, cy-i2, i, i, color2);
	}

	return t;
}

uint32_t testFilledCircles(uint8_t radius, uint16_t color)
{
	uint32_t start;
	int32_t x, y, w = width(), h = height(), r2 = radius * 2;

	fillScreen(TFT_BLACK);

	start = micros_start();

	for (x = radius; x < w; x += r2)
	{
		for (y = radius; y < h; y += r2)
		{
			fillCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

uint32_t testCircles(uint8_t radius, uint16_t color)
{
	uint32_t start;
	int32_t x, y, r2 = radius * 2;
	int32_t w = width() + radius;
	int32_t h = height() + radius;

	// Screen is not cleared for this one -- this is
	// intentional and does not affect the reported time.
	start = micros_start();

	for (x = 0; x < w; x += r2)
	{
		for (y = 0; y < h; y += r2)
		{
			drawCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

uint32_t testTriangles()
{
	uint32_t start;
	int32_t n, i;
	int32_t cx = width()/ 2 - 1;
	int32_t cy = height() / 2 - 1;

	fillScreen(TFT_BLACK);
	n = min(cx, cy);

	start = micros_start();

	for (i = 0; i < n; i += 5)
	{
		drawTriangle(
			cx		, cy - i, // peak
			cx - i, cy + i, // bottom left
			cx + i, cy + i, // bottom right
			color565(0, 0, i));
	}

	return micros() - start;
}

uint32_t testFilledTriangles()
{
	uint32_t start, t = 0;
	int32_t i;
	int32_t cx = width() / 2 - 1;
	int32_t cy = height() / 2 - 1;

	fillScreen(TFT_BLACK);

	start = micros_start();

	for (i = min(cx,cy); i > 10; i -= 5) {
		start = micros_start();
		fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			color565(0, i, i));
		t += micros() - start;
		drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			color565(i, i, 0));
	}

	return t;
}

uint32_t testRoundRects()
 {
	uint32_t start;
	int32_t w, i, i2;
	int32_t cx = width() / 2 - 1;
	int32_t cy = height() / 2 - 1;

	fillScreen(TFT_BLACK);
	
	w = min(width(), height());
	
	start = micros_start();

	for (i = 0; i < w; i += 6)
	{
		i2 = i / 2;
		drawRoundRect(cx-i2, cy-i2, i, i, i/8, color565(i, 0, 0));
	}

	return micros() - start;
}

uint32_t testFilledRoundRects()
{
	uint32_t start;
	int32_t i, i2;
	int32_t cx = width() / 2 - 1;
	int32_t cy = height() / 2 - 1;

	fillScreen(TFT_BLACK);

	start = micros_start();

	for (i = min(width(), height()); i > 20; i -= 6)
	{
		i2 = i / 2;
		fillRoundRect(cx-i2, cy-i2, i, i, i/8, color565(0, i, 0));
	}

	return micros() - start;
}

/***************************************************
  Original sketch text:

  This is an example sketch for the Adafruit 2.2" SPI display.
  This library works with the Adafruit 2.2" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/1480
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
 
