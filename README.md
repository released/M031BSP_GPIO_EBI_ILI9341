# M031BSP_GPIO_EBI_ILI9341
 M031BSP_GPIO_EBI_ILI9341

update @ 2022/05/30

1. use GPIO to emulate i80 mode , to driver ILI9341 2.4" TFT panel

2. below is 2.4" TFT panel pin define

![image](https://github.com/released/M031BSP_GPIO_EBI_ILI9341/blob/main/pin_name_define_I.jpg)	

3. two project : to demo GUI display 

\NuMaker\emWin_GUIDemo : use emWin library  , porting from below link , 

https://www.nuvoton.com/resource-download.jsp?tp_GUID=SW1820200914190828


\Template : use adafruit library sample code  , porting from below link

https://github.com/Bodmer/TFT_ILI9341

https://github.com/adafruit/Adafruit-GFX-Library

https://github.com/adafruit/Adafruit_ILI9341


4. also attached demo video (adafruit library) , by terminal key , from digit 1~0 , a (or A) to p (or P)

when pressed non-exist key , will display color pattern instead

