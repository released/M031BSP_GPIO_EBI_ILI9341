
#include <stdio.h>
#include "gpio_EBI.h"


const uint8_t tlb_Power_Control_A_CBh[] =
{
    0xCB ,
    0x39 ,
    0x2C ,
    0x00 ,
    0x34 , 
    0x02 
};

const uint8_t tlb_Power_Control_B_CFh[] =
{
    0xCF ,
    0x00 ,
    0xC1 ,      // DATASHEET : 0x81
    0x30
};


const uint8_t tlb_Driver_Timing_Control_A_E8h[] =
{
    0xE8 ,
    0x85 ,      // DATASHEET : 0x84
    0x00 ,      // DATASHEET : 0x11
    0x78        // DATASHEET : 0x7A
};

const uint8_t tlb_Driver_Timing_Control_B_EAh[] =
{
    0xEA ,
    0x00 ,      // DATASHEET : 0x66
    0x00
};

const uint8_t tlb_Power_On_Sequence_Control_EDh[] =
{
    0xED ,
    0x64 ,      // DATASHEET : 0x55
    0x03 ,      // DATASHEET : 0x01
    0x12 ,      // DATASHEET : 0x23
    0x81        // DATASHEET : 0x01
};

const uint8_t tlb_Pump_ratio_control_F7h[] =
{
    0xF7 ,
    0x20        // DATASHEET : 0x10
};

const uint8_t tlb_Power_Control_1_C0h[] =
{
    0xC0 ,
    0x23        // DATASHEET : 0x21
};

const uint8_t tlb_Power_Control_2_C1h[] =
{
    0xC1 ,
    0x10
};

const uint8_t tlb_VCOM_Control_1_C5h[] =
{
    0xC5 ,
    0x3E ,      // DATASHEET : 0x31
    0x28        // DATASHEET : 0x3C
};

const uint8_t tlb_VCOM_Control_2_C7h[] =
{
    0xC7 ,
    0x86        // DATASHEET : 0xC0
};

const uint8_t tlb_Memory_Access_Control_36h[] =
{
    0x36 ,
    0x48        // DATASHEET : 0x00
};

const uint8_t tlb_COLMOD_Pixel_Format_Set_3Ah[] =
{
    0x3A ,
    0x55        // DATASHEET : 0x66
};

const uint8_t tlb_Frame_Rate_Control_In_Normal_Mode_Full_Colors_B1h[] =
{
    0xB1 ,
    0x00 ,
    0x18        // DATASHEET : 0x1B  
};

const uint8_t tlb_Display_Function_Control_B6h[] =
{
    0xB6 ,
    0x08 ,      // DATASHEET : 0x0A
    0x82 , 
    0x27   
};

const uint8_t tlb_Enable_3G_F2h[] =
{
    0xF2 ,
    0x00        // DATASHEET : 0x02
};

const uint8_t tlb_Gamma_Set_26h[] =
{
    0x26 ,
    0x01
};

const uint8_t tlb_Positive_Gamma_Correction_E0h[] =
{
    0xE0 ,
    0x0F ,
    0x31 ,
    0x2B ,
    0x0C ,
    0x0E ,
    0x08 ,
    0x4E ,
    0xF1 ,
    0x37 ,
    0x07 ,
    0x10 ,
    0x03 ,
    0x0E ,
    0x09 ,
    0x00 
};

const uint8_t tlb_Negative_Gamma_Correction_E1h[] =
{
    0xE1 ,
    0x00 ,
    0x0E ,
    0x14 ,
    0x03 ,
    0x11 ,
    0x07 ,
    0x31 ,
    0xC1 ,
    0x48 ,
    0x08 ,
    0x0F ,
    0x0C ,
    0x31 ,
    0x36 ,
    0x0F
};



void delayMicroseconds(uint16_t t)
{
    CLK_SysTickDelay(t);
}

void LCD_Data_SetInput(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA7MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA4MFP_GPIO | SYS_GPA_MFPL_PA5MFP_GPIO | SYS_GPA_MFPL_PA6MFP_GPIO | SYS_GPA_MFPL_PA7MFP_GPIO);    
    GPIO_SetMode(PA, BIT4|BIT5|BIT6|BIT7, GPIO_MODE_INPUT);

    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC2MFP_GPIO | SYS_GPC_MFPL_PC3MFP_GPIO | SYS_GPC_MFPL_PC4MFP_GPIO | SYS_GPC_MFPL_PC5MFP_GPIO);    
    GPIO_SetMode(PC, BIT2|BIT3|BIT4|BIT5, GPIO_MODE_INPUT);
}
void LCD_Data_SetOutput(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA7MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA4MFP_GPIO | SYS_GPA_MFPL_PA5MFP_GPIO | SYS_GPA_MFPL_PA6MFP_GPIO | SYS_GPA_MFPL_PA7MFP_GPIO);    
    GPIO_SetMode(PA, BIT4|BIT5|BIT6|BIT7, GPIO_MODE_OUTPUT);

    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC2MFP_GPIO | SYS_GPC_MFPL_PC3MFP_GPIO | SYS_GPC_MFPL_PC4MFP_GPIO | SYS_GPC_MFPL_PC5MFP_GPIO);    
    GPIO_SetMode(PC, BIT2|BIT3|BIT4|BIT5, GPIO_MODE_OUTPUT);
}

/*
                                        CS      WR      RD      D/CX(RS)
    Write command code.                 L       rising  H       L
    Read internal status.               L       H       rising  H 
    Write parameter or display data.    L       rising  H       H
    Reads parameter or display data.    L       H       rising  H


    WRITE cycle (RESET always HIGH)
    CS LOW , 
        D/CX(RS) LOW (if send addr)
                                                        D/CX(RS) set high after WR high
        WR set LOW 
                            WR set high when addr ready
        RD high
        DATA bus : addr

        D/CX(RS) high (if send data)
        WR set LOW
                            WR set high when data ready        
        RD high
        DATA bus : data


    READ cycle (RESET always HIGH)
    CS LOW , 
        D/CX(RS) LOW (if send addr)
                                                        D/CX(RS) set high after WR high
        WR set LOW 
                            WR set high when addr ready
        RD high
        DATA bus : addr

        D/CX(RS) high (if READ data)
        WR high    

        // FIRST DATA INVALID
        RD set LOW 
                            RD set high when data ready   
        DATA bus : data   

        // second DATA is VALID 
        RD set LOW 
                            RD set high when data ready   
        DATA bus : data               

*/

uint8_t read8(void)
{
    uint8_t temp = 0;
   
    RD_ACTIVE;
    __NOP();// delayMicroseconds(10);

    temp |= LCD_D0  << 0;
    temp |= LCD_D1  << 1;
    temp |= LCD_D2  << 2;
    temp |= LCD_D3  << 3;
    temp |= LCD_D4  << 4;
    temp |= LCD_D5  << 5;
    temp |= LCD_D6  << 6;
    temp |= LCD_D7  << 7;
    __NOP();// delayMicroseconds(10);

    RD_IDLE;
    __NOP();// delayMicroseconds(10);

    return temp;
}

void write8(uint8_t c) 
{ 

    WR_ACTIVE;
    LCD_D0 = (c&BIT0)?HIGH:LOW;
    LCD_D1 = (c&BIT1)?HIGH:LOW;
    LCD_D2 = (c&BIT2)?HIGH:LOW;
    LCD_D3 = (c&BIT3)?HIGH:LOW;
    LCD_D4 = (c&BIT4)?HIGH:LOW;
    LCD_D5 = (c&BIT5)?HIGH:LOW;
    LCD_D6 = (c&BIT6)?HIGH:LOW;
    LCD_D7 = (c&BIT7)?HIGH:LOW;
    __NOP();// delayMicroseconds(10);

    WR_IDLE;
    __NOP();// delayMicroseconds(10);    

}

void writeCommand8(uint8_t c)
{
     
	CS_ACTIVE_CD_COMMAND;
	write8(c&0xFF);
    CD_DATA;

}

// void writeCommand16(uint16_t c)
// {
// 	CS_ACTIVE_CD_COMMAND;
// 	write8(c>>8);
// 	write8(c&0xFF);
//     CD_DATA;
// }

// void writeData16(uint16_t c)
// {
// 	write8(c>>8);
// 	write8(c&0xFF);
// }


void LCD_WR_REG(uint8_t cmd)   //void LCD_WR_REG(uint16_t cmd)
{
    writeCommand8(cmd);
}

uint16_t LCD_RD_REG(uint16_t r)
{
    uint16_t id; 
    uint8_t x;

    writeCommand8(r);
    setReadDir();  // Set up LCD data port(s) for READ operations
    delayMicroseconds(10);

    // first data is invalid
    x = read8();
    id = x;
    id <<= 8;
    
    // second data is valid   
    id = 0; 
    x = read8();
    id |= x;
    CS_IDLE;
    setWriteDir();  // Restore LCD data port(s) to WRITE configuration

    return id;    
}

void LCD_WR_DATA(uint8_t dat)  //void LCD_WR_DATA(uint16_t dat)
{  
	write8(dat&0xFF);

}

uint8_t LCD_RD_DATA(void)  //uint16_t LCD_RD_DATA(void)
{
    uint8_t id;    
    uint8_t x;

    // first data is invalid
    x = read8();
    id = x; 
    // id <<= 8;
    
    // second data is valid   
    id = 0; 
    x = read8();
    id |= x;
    CS_IDLE;
    setWriteDir();  // Restore LCD data port(s) to WRITE configuration

    return id;       
}

void LcdWriteDataMultipleREG(uint8_t * pData, int NumItems) 
{
	CS_ACTIVE_CD_COMMAND;	
    while (NumItems--) 
    {
        write8(*pData++);
    }
    CD_DATA;    

}

void LcdWriteDataMultipleData(uint8_t * pData, int NumItems)
{  
    while (NumItems--) 
    {
        write8(*pData++);
    }
}

void LcdReadDataMultiple(uint8_t * pData, int NumItems) 
{
    // uint8_t id;
    uint8_t x;

    // first data is invalid
    x = read8();
    // id = x; 
    // id <<= 8;
    UNUSED(x);
    
    // second data is valid   
    // id = 0; 
    while (NumItems--) 
    {
        *pData++ = read8();
    }

    CS_IDLE;
    setWriteDir();  // Restore LCD data port(s) to WRITE configuration    

}

#if 0
void LCD_SetCursor(uint16_t x_s, uint16_t y_s)
{ 
    uint16_t x_e = x_s+1;
    uint16_t y_e = y_s+1;
        
    /* X range */
    LCD_WR_REG(0x2A);
    LCD_WR_DATA(x_s>>8);
    LCD_WR_DATA(x_s);
    LCD_WR_DATA(x_e>>8);
    LCD_WR_DATA(x_e);

    /* Y range */
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(y_s>>8);
    LCD_WR_DATA(y_s);
    LCD_WR_DATA(y_e>>8);
    LCD_WR_DATA(y_e);
        
    /* Memory write */
    LCD_WR_REG(0x2C);
    
}
#endif

/*-----------------------------------------------*/
// Initial LIL9341 LCD driver chip 
// 
/*-----------------------------------------------*/
void tbl_Initial(uint8_t REG , uint8_t* Item)
{
    uint8_t len = COUNTOF(Item) - 1;
    uint8_t i = 0;

    writeCommand8(REG);

    for ( i = 0 ; i < len ; i++)
    {
        write8(Item[i]);
    }
    
    CS_IDLE;

}


void ILI9341_Initial(void)
{
    uint16_t Reg = 0;
    
    /* Hardware reset */
    SET_RST;
    CLK_SysTickDelay(5000);     // Delay 5ms
    
    CLR_RST;
    CLK_SysTickDelay(20000);    // Delay 20ms
    
    SET_RST;
    CLK_SysTickDelay(40000);    // Delay 40ms

    tbl_Initial(tlb_Power_Control_A_CBh[0],(uint8_t*)&tlb_Power_Control_A_CBh[1] );
    tbl_Initial(tlb_Power_Control_B_CFh[0],(uint8_t*)&tlb_Power_Control_B_CFh[1] );
    tbl_Initial(tlb_Driver_Timing_Control_A_E8h[0],(uint8_t*)&tlb_Driver_Timing_Control_A_E8h[1] );
    tbl_Initial(tlb_Driver_Timing_Control_B_EAh[0],(uint8_t*)&tlb_Driver_Timing_Control_B_EAh[1] );
    tbl_Initial(tlb_Power_On_Sequence_Control_EDh[0],(uint8_t*)&tlb_Power_On_Sequence_Control_EDh[1] );
    tbl_Initial(tlb_Pump_ratio_control_F7h[0],(uint8_t*)&tlb_Pump_ratio_control_F7h[1] );
    tbl_Initial(tlb_Power_Control_1_C0h[0],(uint8_t*)&tlb_Power_Control_1_C0h[1] );
    tbl_Initial(tlb_Power_Control_2_C1h[0],(uint8_t*)&tlb_Power_Control_2_C1h[1] );
    tbl_Initial(tlb_VCOM_Control_1_C5h[0],(uint8_t*)&tlb_VCOM_Control_1_C5h[1] );
    tbl_Initial(tlb_VCOM_Control_2_C7h[0],(uint8_t*)&tlb_VCOM_Control_2_C7h[1] );
    tbl_Initial(tlb_Memory_Access_Control_36h[0],(uint8_t*)&tlb_Memory_Access_Control_36h[1] );
    tbl_Initial(tlb_COLMOD_Pixel_Format_Set_3Ah[0],(uint8_t*)&tlb_COLMOD_Pixel_Format_Set_3Ah[1] );
    tbl_Initial(tlb_Frame_Rate_Control_In_Normal_Mode_Full_Colors_B1h[0],(uint8_t*)&tlb_Frame_Rate_Control_In_Normal_Mode_Full_Colors_B1h[1] );
    tbl_Initial(tlb_Display_Function_Control_B6h[0],(uint8_t*)&tlb_Display_Function_Control_B6h[1] );
    tbl_Initial(tlb_Enable_3G_F2h[0],(uint8_t*)&tlb_Enable_3G_F2h[1] );
    tbl_Initial(tlb_Gamma_Set_26h[0],(uint8_t*)&tlb_Gamma_Set_26h[1] );
    tbl_Initial(tlb_Positive_Gamma_Correction_E0h[0],(uint8_t*)&tlb_Positive_Gamma_Correction_E0h[1] );
    tbl_Initial(tlb_Negative_Gamma_Correction_E1h[0],(uint8_t*)&tlb_Negative_Gamma_Correction_E1h[1] );

    LCD_WR_REG(0x11);
    CLK_SysTickDelay(200000);   // Delay 200ms
    
    LCD_WR_REG(0x29);           //Display on

    LCD_WR_REG(0x0A);
    Reg = LCD_RD_DATA();
    printf("0Ah = %02x.\n", Reg);
    
    LCD_WR_REG(0x0B);
    Reg = LCD_RD_DATA();
    printf("0Bh = %02x.\n", Reg);
    
    LCD_WR_REG(0x0C);
    Reg = LCD_RD_DATA();
    printf("0Ch = %02x.\n", Reg);

    printf("Initial ILI9341 LCD Module done.\n\n");

}

void EBI_FuncPinInit(void)
{

    LCD_Data_SetOutput();

    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB4MFP_Msk | SYS_GPB_MFPL_PB5MFP_Msk | SYS_GPB_MFPL_PB6MFP_Msk | SYS_GPB_MFPL_PB7MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_GPIO | SYS_GPB_MFPL_PB4MFP_GPIO | SYS_GPB_MFPL_PB5MFP_GPIO | SYS_GPB_MFPL_PB6MFP_GPIO | SYS_GPB_MFPL_PB7MFP_GPIO);    
    GPIO_SetMode(PB, BIT0|BIT4|BIT5|BIT6|BIT7, GPIO_MODE_OUTPUT);

    CD_DATA;
}



