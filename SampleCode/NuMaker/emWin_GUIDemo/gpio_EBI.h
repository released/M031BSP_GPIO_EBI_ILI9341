
#include <stdio.h>
#include <math.h>
#include "NuMicro.h"


#ifndef HIGH
#define HIGH              					(1)
#endif

#ifndef LOW
#define LOW              					(0)
#endif

#ifndef COUNTOF
#define COUNTOF(a)                          (sizeof((a))/sizeof((a)[0]))
#endif


/*
	PANEL pin define : 240 x 320 , 2.4" inch
	
	PAENL/M032EVB
        [LEFT]						[RIGHT]
        X		/PB2				X		/PB1
        X		/PB3				LCD_RST	/PB0
        LCD_D2	/PC4				LCD_CS	/PB4
        LCD_D3	/PC5				LCD_RS	/PB5
        LCD_D4	/PC3				LCD_WR	/PB6
        LCD_D5	/PC2				LCD_RD	/PB7
        LCD_D6	/PA7	
        LCD_D7	/PA6				X		/VIN
                                    GND		/VSS
        LCD_D0	/PA5				X		/VSS
        LCD_D1	/PA4				5V		/5VCC
        SD_SS	/PA3				3V3		/3VCC
        SD_DI	/PA0				X		/nRESET
        SD_DO	/PA1						/VDD
        SD_SCL	/PA2						/NC
        X		/VSS
        X		/VREF
                /PC0
                /PC1


*/

#define LCD_D0                              (PA5)
#define LCD_D1                              (PA4)
#define LCD_D2                              (PC4)
#define LCD_D3                              (PC5)
#define LCD_D4                              (PC3)
#define LCD_D5                              (PC2)
#define LCD_D6                              (PA7)
#define LCD_D7                              (PA6)

#define LCD_RST	                            (PB0)
#define LCD_CS	                            (PB4)
#define LCD_RS	                            (PB5)
#define LCD_WR	                            (PB6)
#define LCD_RD	                            (PB7)


#define CD_COMMAND                          (LCD_RS = LOW)
#define CD_DATA                             (LCD_RS = HIGH)

#define RD_ACTIVE                           (LCD_RD = LOW) 
#define RD_IDLE                             (LCD_RD = HIGH)
#define WR_ACTIVE                           (LCD_WR = LOW) 
#define WR_IDLE                             (LCD_WR = HIGH)
#define CS_ACTIVE                           (LCD_CS = LOW)
#define CS_IDLE                             (LCD_CS = HIGH)
#define CS_ACTIVE_CD_COMMAND	            { CS_ACTIVE; CD_COMMAND; }
#define WR_STROBE                           { WR_ACTIVE; WR_IDLE; }


/* LCD Module "RESET" */
#define SET_RST                             (LCD_RST = 1)
#define CLR_RST                             (LCD_RST = 0)


#define setReadDir()                        (LCD_Data_SetInput())
#define setWriteDir()                       (LCD_Data_SetOutput())

void LCD_Data_SetInput(void);
void LCD_Data_SetOutput(void);

void delayMicroseconds(uint16_t t);

void LCD_Data_SetInput(void);
void LCD_Data_SetOutput(void);

uint8_t read8(void);
void write8(uint8_t c);

void writeCommand8(uint8_t c);

// void writeCommand16(uint16_t c);
// void writeData16(uint16_t c);

void LCD_WR_REG(uint8_t cmd);
uint16_t LCD_RD_REG(uint16_t r);

void LCD_WR_DATA(uint8_t dat);
uint8_t LCD_RD_DATA(void);

void LcdWriteDataMultipleREG(uint8_t * pData, int NumItems);
void LcdWriteDataMultipleData(uint8_t * pData, int NumItems);

void LcdReadDataMultiple(uint8_t * pData, int NumItems);

// void LCD_SetCursor(uint16_t x_s, uint16_t y_s);

void tbl_Initial(uint8_t REG , uint8_t* Item);
void ILI9341_Initial(void);

void EBI_FuncPinInit(void);

