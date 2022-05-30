/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "project_config.h"

// #include "GUI.h"
// #include "lcd.h"

#include "gpio_EBI.h"
#include "TFT_ILI9341.h"
#include "example.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
volatile uint32_t BitFlag = 0;
volatile uint32_t counter_tick = 0;

enum
{
	ADC0_CH0 = 0 ,
	ADC0_CH1 , 
	
	ADC0_CH2 , 
	ADC0_CH3 , 
	ADC0_CH4 , 
	ADC0_CH5 , 
	ADC0_CH6 , 
	ADC0_CH7 , 
	ADC0_CH8 , 
	ADC0_CH9 , 
	ADC0_CH10 , 
	ADC0_CH11 , 
	ADC0_CH12 ,
	ADC0_CH13 , 
	ADC0_CH14 , 
	ADC0_CH15 , 
	
	ADC_CH_DEFAULT 	
}ADC_CH_TypeDef;

/*_____ M A C R O S ________________________________________________________*/
#define ENABLE_ADC_IRQ

/*_____ F U N C T I O N S __________________________________________________*/

void loop_empty(void);
void setup_empty(void);

#define __noinit__ __attribute__((zero_init))
__noinit__ unsigned char keycode_demo_index __attribute__((at( 0x20003FFC)));

typedef void (_ptr_)(void);

typedef struct
{
	unsigned char keycode;  
	unsigned char message[32];

    _ptr_ *setup;   // void (*setup) (void);
    _ptr_ *loop;    // void (*loop) (void);

} table_t;

table_t *g_fun;

const table_t tbl_function[] = 
{
    {'1'    ,"RLE_Font_test\r\n"                , setup_RLE_Font_test               ,  loop_RLE_Font_test } , 
    {'2'    ,"TFT_ArcFill\r\n"                  , setup_TFT_ArcFill                 ,  loop_TFT_ArcFill } , 
    {'3'    ,"TFT_ArcFill_2\r\n"                , setup_TFT_ArcFill_2               ,  loop_TFT_ArcFill_2 } , 
    {'4'    ,"TFT_Char_times\r\n"               , setup_TFT_Char_times              ,  loop_TFT_Char_times } , 
    {'5'    ,"TFT_Clock\r\n"                    , setup_TFT_Clock                   ,  loop_TFT_Clock } , 
    {'6'    ,"TFT_Clock_Digital\r\n"            , setup_TFT_Clock_Digital           ,  loop_TFT_Clock_Digital } , 
    {'7'    ,"TFT_Clock_Digital2\r\n"           , setup_TFT_Clock_Digital2          ,  loop_TFT_Clock_Digital2 } , 
    {'8'    ,"TFT_Ellipse\r\n"                  , setup_TFT_Ellipse                 ,  loop_TFT_Ellipse } , 
    {'9'    ,"TFT_FillArcSpiral\r\n"            , setup_TFT_FillArcSpiral           ,  loop_TFT_FillArcSpiral } , 
    {'0'    ,"TFT_Flash_Bitmap\r\n"             , setup_TFT_Flash_Bitmap            ,  loop_TFT_Flash_Bitmap } , 

    {'a'    ,"TFT_Float_Test\r\n"               , setup_TFT_Float_Test              ,  loop_TFT_Float_Test } , 
    {'A'    ,"TFT_Float_Test\r\n"               , setup_TFT_Float_Test              ,  loop_TFT_Float_Test } , 

    {'b'    ,"TFT_graphicstest_one_lib\r\n"     , setup_TFT_graphicstest_one_lib    ,  loop_TFT_graphicstest_one_lib } , 
    {'B'    ,"TFT_graphicstest_one_lib\r\n"     , setup_TFT_graphicstest_one_lib    ,  loop_TFT_graphicstest_one_lib } , 

    {'c'    ,"TFT_graphicstest_PDQ\r\n"         , setup_TFT_graphicstest_PDQ        ,  loop_TFT_graphicstest_PDQ } , 
    {'C'    ,"TFT_graphicstest_PDQ\r\n"         , setup_TFT_graphicstest_PDQ        ,  loop_TFT_graphicstest_PDQ } , 

    {'d'    ,"TFT_Mandlebrot\r\n"               , setup_TFT_Mandlebrot              ,  loop_TFT_Mandlebrot } , 
    {'D'    ,"TFT_Mandlebrot\r\n"               , setup_TFT_Mandlebrot              ,  loop_TFT_Mandlebrot } , 

    {'e'    ,"TFT_Matrix_2\r\n"                 , setup_TFT_Matrix_2                ,  loop_TFT_Matrix_2 } , 
    {'E'    ,"TFT_Matrix_2\r\n"                 , setup_TFT_Matrix_2                ,  loop_TFT_Matrix_2 } , 

    {'f'    ,"TFT_Meter_linear_4\r\n"           , setup_TFT_Meter_linear_4          ,  loop_TFT_Meter_linear_4 } , 
    {'F'    ,"TFT_Meter_linear_4\r\n"           , setup_TFT_Meter_linear_4          ,  loop_TFT_Meter_linear_4 } , 

    {'g'    ,"TFT_Meters\r\n"                   , setup_TFT_Meters                  ,  loop_TFT_Meters } , 
    {'G'    ,"TFT_Meters\r\n"                   , setup_TFT_Meters                  ,  loop_TFT_Meters } , 

    {'h'    ,"TFT_Pie_Chart\r\n"                , setup_TFT_Pie_Chart               ,  loop_TFT_Pie_Chart } , 
    {'H'    ,"TFT_Pie_Chart\r\n"                , setup_TFT_Pie_Chart               ,  loop_TFT_Pie_Chart } , 

    {'i'    ,"TFT_Pong_v2\r\n"                  , setup_TFT_Pong_v2                 ,  loop_TFT_Pong_v2 } , 
    {'I'    ,"TFT_Pong_v2\r\n"                  , setup_TFT_Pong_v2                 ,  loop_TFT_Pong_v2 } , 

    {'j'    ,"TFT_Print_Test\r\n"               , setup_TFT_Print_Test              ,  loop_TFT_Print_Test } , 
    {'J'    ,"TFT_Print_Test\r\n"               , setup_TFT_Print_Test              ,  loop_TFT_Print_Test } , 

    {'k'    ,"TFT_Rainbow_one_lib\r\n"          , setup_TFT_Rainbow_one_lib         ,  loop_TFT_Rainbow_one_lib } , 
    {'K'    ,"TFT_Rainbow_one_lib\r\n"          , setup_TFT_Rainbow_one_lib         ,  loop_TFT_Rainbow_one_lib } , 

    {'l'    ,"TFT_TFT_Spiro_2\r\n"              , setup_TFT_Spiro_2                 ,  loop_TFT_Spiro_2 } , 
    {'L'    ,"TFT_TFT_Spiro_2\r\n"              , setup_TFT_Spiro_2                 ,  loop_TFT_Spiro_2 } , 

    {'m'    ,"TFT_Starfield\r\n"                , setup_TFT_Starfield               ,  loop_TFT_Starfield } , 
    {'M'    ,"TFT_Starfield\r\n"                , setup_TFT_Starfield               ,  loop_TFT_Starfield } , 

    {'n'    ,"TFT_String_Align\r\n"             , setup_TFT_String_Align            ,  loop_TFT_String_Align } , 
    {'N'    ,"TFT_String_Align\r\n"             , setup_TFT_String_Align            ,  loop_TFT_String_Align } , 

    {'o'    ,"TFT_Terminal\r\n"                 , setup_TFT_Terminal                ,  loop_TFT_Terminal } , 
    {'O'    ,"TFT_Terminal\r\n"                 , setup_TFT_Terminal                ,  loop_TFT_Terminal } , 

    {'p'    ,"UTFT_demo_fast_2\r\n"             , setup_UTFT_demo_fast_2            ,  loop_UTFT_demo_fast_2 } , 
    {'P'    ,"UTFT_demo_fast_2\r\n"             , setup_UTFT_demo_fast_2            ,  loop_UTFT_demo_fast_2 } , 

    {0xFF   ,"exceed max range\r\n"             , setup_empty                       ,  loop_empty } , 
};

const unsigned int color_idx[] =
{
    ILI9341_BLACK,  
    ILI9341_NAVY,
    ILI9341_DARKGREEN,
    ILI9341_DARKCYAN,
    ILI9341_MAROON,
    ILI9341_PURPLE,
    ILI9341_OLIVE,
    ILI9341_LIGHTGREY,
    ILI9341_DARKGREY,
    ILI9341_BLUE,
    ILI9341_GREEN,
    ILI9341_CYAN,
    ILI9341_RED,
    ILI9341_MAGENTA,
    ILI9341_YELLOW,
    ILI9341_WHITE,
    ILI9341_ORANGE,
    ILI9341_GREENYELLOW,
    ILI9341_PINK,
};

uint16_t idx_change(void)
{   
    static uint8_t counter = 0;    
    uint16_t idx = 0;

    idx = color_idx[counter];
    printf("counter:%2d,idx=0x%4X,size=%2d\r\n" , counter , idx , SIZEOF(color_idx));

    counter = (counter >= (SIZEOF(color_idx)-1) ) ? (0) : ( counter + 1) ;

    return idx ;
}

void pattern_change(void)
{
    uint16_t res = 0;
    if (is_flag_set(flag_swap_color))
    {
        set_flag(flag_swap_color , DISABLE);
        
        res = idx_change();
        fillScreen(res);
    }
}

void loop_empty(void)
{
    // printf("no exist loop\r\n");
    pattern_change();
}

void setup_empty(void)
{
    printf("no exist setup\r\n");
}

void tick_counter(void)
{
	counter_tick++;
}

uint32_t get_tick(void)
{
	return (counter_tick);
}

void set_tick(uint32_t t)
{
	counter_tick = t;
}

void compare_buffer(uint8_t *src, uint8_t *des, int nBytes)
{
    uint16_t i = 0;	
	
    for (i = 0; i < nBytes; i++)
    {
        if (src[i] != des[i])
        {
            printf("error idx : %4d : 0x%2X , 0x%2X\r\n", i , src[i],des[i]);
			set_flag(flag_error , ENABLE);
        }
    }

	if (!is_flag_set(flag_error))
	{
    	printf("%s finish \r\n" , __FUNCTION__);	
		set_flag(flag_error , DISABLE);
	}

}

void reset_buffer(void *dest, unsigned int val, unsigned int size)
{
    uint8_t *pu8Dest;
//    unsigned int i;
    
    pu8Dest = (uint8_t *)dest;

	#if 1
	while (size-- > 0)
		*pu8Dest++ = val;
	#else
	memset(pu8Dest, val, size * (sizeof(pu8Dest[0]) ));
	#endif
	
}

void copy_buffer(void *dest, void *src, unsigned int size)
{
    uint8_t *pu8Src, *pu8Dest;
    unsigned int i;
    
    pu8Dest = (uint8_t *)dest;
    pu8Src  = (uint8_t *)src;


	#if 0
	  while (size--)
	    *pu8Dest++ = *pu8Src++;
	#else
    for (i = 0; i < size; i++)
        pu8Dest[i] = pu8Src[i];
	#endif
}

void dump_buffer(uint8_t *pucBuff, int nBytes)
{
    uint16_t i = 0;
    
    printf("dump_buffer : %2d\r\n" , nBytes);    
    for (i = 0 ; i < nBytes ; i++)
    {
        printf("0x%2X," , pucBuff[i]);
        if ((i+1)%8 ==0)
        {
            printf("\r\n");
        }            
    }
    printf("\r\n\r\n");
}

void dump_buffer_hex(uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0)
    {
        printf("0x%04X  ", nIdx);
        for (i = 0; i < 16; i++)
            printf("%02X ", pucBuff[nIdx + i]);
        printf("  ");
        for (i = 0; i < 16; i++)
        {
            if ((pucBuff[nIdx + i] >= 0x20) && (pucBuff[nIdx + i] < 127))
                printf("%c", pucBuff[nIdx + i]);
            else
                printf(".");
            nBytes--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
}

void delay_ms(uint32_t ms)
{
	TIMER_Delay(TIMER0, 1000*ms);
}


void setup(void)
{
    uint8_t i = 0 ;

    // search table index
    do
    {
        if (tbl_function[i].keycode == keycode_demo_index)
        {
            printf("get index : %c(%2d)\r\n" , keycode_demo_index ,i);
            printf("%s" , tbl_function[i].message);
            break;
        }

        if (tbl_function[i].keycode == 0xFF)
        {
            printf("no index ,insert dummy function(%2d)\r\n",i); 
            // g_fun->setup = (_ptr_ *)setup_empty;
            // g_fun->loop = (_ptr_ *)loop_empty;                   
            break;
        }
        i++;

    } while (1);

    // setRotation(3);
    g_fun = (table_t*) &tbl_function[i];       
    g_fun->setup();
   
}

void loop(void)
{
    g_fun->loop();
     
}

// use ADC for random seed 
void ADC_IRQHandler(void)
{	
//	printf("aADCxConvertedData : %d\r\n" , aADCxConvertedData);
	set_flag(flag_ADC_Data_Ready , ENABLE);	
    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT); /* Clear the A/D interrupt flag */
}

unsigned int ADC_ReadChannel(uint8_t ch)
{
    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);    
    #if defined (ENABLE_ADC_IRQ)
    set_flag(flag_ADC_Data_Ready ,DISABLE);
    ADC_ENABLE_INT(ADC, ADC_ADF_INT);
    #endif

	ADC_START_CONV(ADC);		

    #if defined (ENABLE_ADC_IRQ)
    while(!is_flag_set(flag_ADC_Data_Ready));	
    ADC_DISABLE_INT(ADC, ADC_ADF_INT);
    #else
    __WFI();
    while (ADC_GET_INT_FLAG(ADC, ADC_ADF_INT)==0);
    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);    

    while(ADC_IS_DATA_VALID(ADC, ch) == 0);         
    #endif

	return (ADC_GET_CONVERSION_DATA(ADC, ch));
}

void ADC_InitChannel(uint8_t ch)
{
    uint32_t ADCextendSampling = 0;

	set_flag(flag_ADC_Data_Ready , DISABLE);

    /* Enable ADC converter */
    ADC_POWER_ON(ADC);

    /*Wait for ADC internal power ready*/
    CLK_SysTickDelay(10000);

    /* Set input mode as single-end, and Single mode*/
    ADC_Open(ADC, ADC_ADCR_DIFFEN_SINGLE_END, ADC_ADCR_ADMD_SINGLE,(uint32_t) 0x1 << ch);
    
    /* To sample band-gap precisely, the ADC capacitor must be charged at least 3 us for charging the ADC capacitor ( Cin )*/
    /* Sampling time = extended sampling time + 1 */
    /* 1/24000000 * (Sampling time) = 3 us */
	/*
	    printf("+----------------------------------------------------------------------+\n");
	    printf("|   ADC clock source -> PCLK1  = 48 MHz                                |\n");
	    printf("|   ADC clock divider          = 2                                     |\n");
	    printf("|   ADC clock                  = 48 MHz / 2 = 24 MHz                   |\n");
	    printf("|   ADC extended sampling time = 71                                    |\n");
	    printf("|   ADC conversion time = 17 + ADC extended sampling time = 88         |\n");
	    printf("|   ADC conversion rate = 24 MHz / 88 = 272.7 ksps                     |\n");
	    printf("+----------------------------------------------------------------------+\n");
	*/

    /* Set extend sampling time based on external resistor value.*/
    ADC_SetExtendSampleTime(ADC,(uint32_t) NULL, ADCextendSampling);

    /* Select ADC input channel */
    ADC_SET_INPUT_CHANNEL(ADC, 0x1 << ch);

	ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);
    #if defined (ENABLE_ADC_IRQ)
	ADC_ENABLE_INT(ADC, ADC_ADF_INT);
	NVIC_EnableIRQ(ADC_IRQn);
    #endif

    /* Start ADC conversion */
    ADC_START_CONV(ADC);

    #if !defined (ENABLE_ADC_IRQ)
    __WFI();
    while(ADC_IS_DATA_VALID(ADC, ch) == 0);
    #endif

    #if defined (ENABLE_ADC_IRQ)
	while(!is_flag_set(flag_ADC_Data_Ready));
    #endif

	#if 0	// debug
	printf("%s : 0x%4X\r\n" , __FUNCTION__ , ADC_GET_CONVERSION_DATA(ADC, ch));
	#endif
}

uint32_t random(int min, int max)
{
    uint32_t res= 0;    
    uint32_t length_of_range = 0;
    uint16_t adc_vaule = 0;

    length_of_range = max - min + 1;

    adc_vaule = ADC_ReadChannel(ADC0_CH15); 
    srand(adc_vaule);
    res = (uint32_t)(rand() % length_of_range + min);

    #if 0   // debug
    printf("adc :0x%4X,rand :%5d(min :%5d,max :%5d)\r\n" ,adc_vaule , res , min , max);
    #endif

    return res;
}


void GPIO_Init (void)
{
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB14MFP_Msk)) | (SYS_GPB_MFPH_PB14MFP_GPIO);
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB15MFP_Msk)) | (SYS_GPB_MFPH_PB15MFP_GPIO);

    GPIO_SetMode(PB, BIT14, GPIO_MODE_OUTPUT);
    GPIO_SetMode(PB, BIT15, GPIO_MODE_OUTPUT);	

}

// void TMR3_IRQHandler(void)
// {
//     if(TIMER_GetIntFlag(TIMER3) == 1)
//     {
//         TIMER_ClearIntFlag(TIMER3);
// 		ustick_counter();	
//     }
// }

// void TIMER3_Init(void)
// {
//     TIMER_Open(TIMER3, TIMER_PERIODIC_MODE, 1);
//     TIMER_EnableInt(TIMER3);
//     NVIC_EnableIRQ(TMR3_IRQn);	
//     TIMER_Start(TIMER3);
// }

void TMR1_IRQHandler(void)
{
//	static uint32_t LOG = 0;

	
    if(TIMER_GetIntFlag(TIMER1) == 1)
    {
        TIMER_ClearIntFlag(TIMER1);
		tick_counter();

		if ((get_tick() % 1000) == 0)
		{
//        	printf("%s : %4d\r\n",__FUNCTION__,LOG++);

			PB14 ^= 1;
		}

		if ((get_tick() % 50) == 0)
		{
            set_flag(flag_swap_color , ENABLE);
		}	
    }
}


void TIMER1_Init(void)
{
    TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 1000);
    TIMER_EnableInt(TIMER1);
    NVIC_EnableIRQ(TMR1_IRQn);	
    TIMER_Start(TIMER1);
}

void UARTx_Process(void)
{
	uint8_t res = 0;
	res = UART_READ(UART0);

	// if (res == 'x' || res == 'X')
	// {
	// 	NVIC_SystemReset();
	// }

	if (res > 0x7F)
	{
		printf("invalid command\r\n");
	}
	else
	{
        #if 1
        g_InitOnce = 0;
        fillScreen(TFT_BLACK);
        printf("\r\n\r\nreceive uart digit:%c (0x%2X)\r\n" ,res , res);
        keycode_demo_index = res;
        while(!UART_IS_TX_EMPTY(UART0));
        NVIC_SystemReset();
        #else
		switch(res)
		{
            case '1':
                break;
			case 'X':
			case 'x':
			case 'Z':
			case 'z':
				NVIC_SystemReset();		
				break;
		}
        #endif
	}
}

void UART02_IRQHandler(void)
{
    if(UART_GET_INT_FLAG(UART0, UART_INTSTS_RDAINT_Msk | UART_INTSTS_RXTOINT_Msk))     /* UART receive data available flag */
    {
        while(UART_GET_RX_EMPTY(UART0) == 0)
        {
			UARTx_Process();
        }
    }

    if(UART0->FIFOSTS & (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk | UART_FIFOSTS_RXOVIF_Msk))
    {
        UART_ClearIntFlag(UART0, (UART_INTSTS_RLSINT_Msk| UART_INTSTS_BUFERRINT_Msk));
    }	
}

void UART0_Init(void)
{
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
    UART_EnableInt(UART0, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk);
    NVIC_EnableIRQ(UART02_IRQn);
	
	#if (_debug_log_UART_ == 1)	//debug
	printf("\r\nCLK_GetCPUFreq : %8d\r\n",CLK_GetCPUFreq());
	printf("CLK_GetHXTFreq : %8d\r\n",CLK_GetHXTFreq());
	printf("CLK_GetLXTFreq : %8d\r\n",CLK_GetLXTFreq());	
	printf("CLK_GetPCLK0Freq : %8d\r\n",CLK_GetPCLK0Freq());
	printf("CLK_GetPCLK1Freq : %8d\r\n",CLK_GetPCLK1Freq());	
	#endif	

}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

//    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

//    CLK_EnableXtalRC(CLK_PWRCTL_LIRCEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);	

//    CLK_EnableXtalRC(CLK_PWRCTL_LXTEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);	

    /* Select HCLK clock source as HIRC and HCLK source divider as 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    CLK_EnableModuleClock(UART0_MODULE);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    CLK_EnableModuleClock(TMR0_MODULE);
  	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, 0);

    CLK_EnableModuleClock(TMR1_MODULE);
  	CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HIRC, 0);

    // CLK_EnableModuleClock(TMR3_MODULE);
  	// CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_HIRC, 0);

    // CLK_EnableModuleClock(EBI_MODULE);

    CLK_EnableModuleClock(ADC_MODULE);	
    CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL2_ADCSEL_PCLK1, CLK_CLKDIV0_ADC(2));	

    /* Set PB multi-function pins for UART0 RXD=PB.12 and TXD=PB.13 */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk)) |
                    (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    SYS->GPB_MFPH = (SYS->GPB_MFPH &~(SYS_GPB_MFPH_PB15MFP_Msk  )) \
                    | (SYS_GPB_MFPH_PB15MFP_ADC_CH15 ) ;

    /* Set PB.0 ~ PB.3 to input mode */
    GPIO_SetMode(PB, BIT15, GPIO_MODE_INPUT);

    /* Disable the PB0 ~ PB3 digital input path to avoid the leakage current. */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT0);

   /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Lock protected registers */
    SYS_LockReg();
}

/*
 * This is a template project for M031 series MCU. Users could based on this project to create their
 * own application without worry about the IAR/Keil project settings.
 *
 * This template application uses external crystal as HCLK source and configures UART0 to print out
 * "Hello World", users may need to do extra system configuration based on their system design.
 */

int main()
{
    SYS_Init();

    GPIO_Init();
    UART0_Init();
    TIMER1_Init();
    // TIMER3_Init();

	ADC_InitChannel(ADC0_CH15);    

    /* Configure DC/RESET/LED pins */
    EBI_FuncPinInit();

    /* Init LCD Module */
    ILI9341_Initial();

    begin();

    setup();

    /* Got no where to go, just loop forever */
    while(1)
    {    
        loop();        

    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
