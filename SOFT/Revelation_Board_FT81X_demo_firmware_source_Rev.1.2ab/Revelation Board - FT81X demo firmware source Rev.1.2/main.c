/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
****************************************************************************/

/* Includes */

#define FT_81X_ENABLE

#include <stddef.h>
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_i2c.h"
#include "stm32f0xx_syscfg.h"
#include "FT_Platform.h"
#include "SampleApp.h"
#include "FM_M25P80.h"

/* Private typedef */
typedef enum {
	NONE = 0,
	NTP70 = 1,
	RTP70 = 2,
	CTP70 = 3,
	NTP50 = 4,
	RTP50 = 5,
	CTP50 = 6,
} tftConfiguration_t;

typedef struct{
volatile uint32_t ms;
unsigned char reset;
unsigned char enable;
} stopwatch_t;

 /* Private define  */
#define BUTTON_FILTER_VALUE_MS 5



/* Private variables */
ft_int16_t FT_DispWidth = 800;
ft_int16_t FT_DispHeight = 480;
ft_int16_t FT_DispHCycle = 1056;
ft_int16_t FT_DispHOffset = 46;
ft_int16_t FT_DispHSync0 = 0;
ft_int16_t FT_DispHSync1 = 10;
ft_int16_t FT_DispVCycle = 525;
ft_int16_t FT_DispVOffset = 23;
ft_int16_t FT_DispVSync0 = 0;
ft_int16_t FT_DispVSync1 = 10;
ft_uint8_t FT_DispPCLK = 2;
ft_char8_t FT_DispSwizzle = 0;
ft_char8_t FT_DispPCLKPol = 1;

Ft_Gpu_Hal_Context_t host,*phost;

/* Global variables */
uint32_t ending_address;
volatile unsigned char buttonPressDetectFlag, buttonPressFlag;
volatile tftConfiguration_t tftConfig;
static volatile unsigned char buttonFilter;
stopwatch_t stopwatch = {0};
__IO uint8_t SMbusAlertOccurred;

//time of 8 demos for diffrent displays
const ft_uint32_t DemoTime_NTP70[8]={500,700,0,0,0,1500,2000,1000};
const ft_uint32_t DemoTime_RTP70[8]={500,700,3000,0,3000,1500,2000,1000};//3000,0,3000,1500,2000,1000};
const ft_uint32_t DemoTime_CTP70[8]={500,700,3000,4000,3000,1500,2000,1000};//3000,4000,3000,1500,2000,1000};
const ft_uint32_t DemoTime_NTP50[8]={500,700,0,0,0,1500,2000,1000};
const ft_uint32_t DemoTime_RTP50[8]={500,700,3000,0,3000,1500,2000,1000};
const ft_uint32_t DemoTime_CTP50[8]={500,700,3000,4000,3000,1500,2000,1000};

ft_uint32_t *DemoTime;//time of 8 demos
ft_char8_t StringArray[20];
ft_uint32_t ThisDemoEnd;
u8 CurrentDemo;
u8 tft_state;
u8 *pointer;
u8 FirstTimeThisDemo;
u8 DoTheCalibration;
ft_int16_t bitmap_i;
SAMAPP_Bitmap_header_t *p_bmhdr;

ft_uint8_t CurrTag2 = 0;
ft_uint8_t CurrTag3 = 0;

//Global variables for keyboard
ft_int16_t TextFont,ButtonW,ButtonH,yBtnDst,yOffset,xOffset;
#define SAMAPP_COPRO_WIDGET_KEYS_INTERACTIVE_TEXTSIZE (512)
ft_char8_t DispText[SAMAPP_COPRO_WIDGET_KEYS_INTERACTIVE_TEXTSIZE],CurrChar;
ft_uint8_t CurrTag,PrevTag,Pendown;
ft_int32_t CurrTextIdx;


ft_int32_t  poly_x0, poly_y0, poly_x1, poly_y1;
ft_int32_t  poly_x[8], poly_y[8];
ft_uint8_t poly_n,j;
ft_int16_t sx[5], sy[5];
ft_int32_t i=0,a=0;
ft_int32_t test=0;
ft_int16_t cx = 0, cy = 0;
ft_uint8_t angles[5];
ft_uint8_t n=0;

//Global variables for bitmap
ft_int16_t BMoffsetx,BMoffsety;
ft_int16_t scale;

/* Private functions */
//Switch initialization
void SwitchInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
	// Configure EXTI line
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// Enable and set EXTI Line1 Interrupt to the lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
}

//Systick initialization
void msTimerInit(void)
{
	RCC_HSICmd(ENABLE);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_Config(8000000/1000);//Set up a systick interrupt every millisecond
}

//Street map drawing on screen
ft_void_t Draw_streets()
{
	Ft_App_WrCoCmd_Buffer(phost, BEGIN(LINES));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(-160*2,-20*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(320*2,4160*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(800*2,-20*2   ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(1280*2,4160*2 ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(1920*2,-20*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(2400*2,4160*2 ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(2560*2,-20*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(3040*2,4160*2 ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(3200*2,-20*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(3680*2,4160*2 ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(2880*2,-20*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(3360*2,4160*2 ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(-20*2,0	   ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(5440*2,-480*2 ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(-20*2,960*2   ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(5440*2,480*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(-20*2,1920*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(5440*2,1440*2 ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(-20*2,2880*2  ));
	Ft_App_WrCoCmd_Buffer(phost, VERTEX2F(5440*2,2400*2 ));
	Ft_App_WrCoCmd_Buffer(phost, END());
}

//Keyboard demo
ft_void_t Keyboard()
{
       /*************************************************************************/
       /* Below code demonstrates the usage of keys function. keys function     */
       /* draws buttons with characters given as input parameters. Keys support */
       /* Flat and 3D effects, draw at (x,y) coordinates or center of the display*/
       /* , inbuilt or custom fonts can be used for key display                 */
       /*************************************************************************/
       {
       	   if(FirstTimeThisDemo ==1)
       	   {
               TextFont = 31;
               ButtonW = 50;
               ButtonH = 50;
               yBtnDst = 15;
               CurrChar = '|';
               CurrTag = 0;
               PrevTag = 0;
               Pendown = 1;
               CurrTextIdx = 0;
               if((tftConfig==CTP70 || tftConfig==CTP50))
               {
            	   Ft_Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);//set mode to compatability,
               }
               FirstTimeThisDemo=0;
    	   }

       {

       /* Check the user input and then add the characters into array */
       CurrTag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
       Pendown = ((Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_DIRECT_XY)>>31) & 0x01);
   	   CurrChar = CurrTag;
   	   if(CurrTag==249)
   	   {
   		   CurrTag=0;
   	   }

       if(0 == CurrTag)
       {
              CurrChar = '|';
       }

       /* check whether pendown has happened */
       if(( 1 == Pendown) && (0 != PrevTag))
       {
              CurrTextIdx++;
              /* clear all the charaters after 24 are pressed */
              if(CurrTextIdx > 24)
              {
                     CurrTextIdx = 0;
              }
       }

       Ft_Gpu_CoCmd_Dlstart(phost);
       Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
       Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
       /* Draw text entered by user */
       /* make sure the array is a string */
       DispText[CurrTextIdx] = CurrChar;
       DispText[CurrTextIdx + 1] = '\0';

       Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
       Ft_Gpu_CoCmd_Text(phost,FT_DispWidth/2, 40, TextFont, OPT_CENTER, DispText);//text info
       Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));

       yOffset = 120 + 10;
       /* Construct a simple keyboard - note that the tags associated with the keys are the character values given in the arguments */
       Ft_Gpu_CoCmd_FgColor(phost,0x404080);
       Ft_Gpu_CoCmd_GradColor(phost,0x00ff00);
       Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, (OPT_CENTER | CurrTag), "qwertyuiop");
       Ft_Gpu_CoCmd_GradColor(phost,0x00ffff);
       yOffset += ButtonH + yBtnDst;
       Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, (OPT_CENTER | CurrTag), "asdfghjkl");
       Ft_Gpu_CoCmd_GradColor(phost,0xffff00);
       yOffset += ButtonH + yBtnDst;
       Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, (OPT_CENTER | CurrTag), "zxcvbnm");//hilight button z
       yOffset += ButtonH + yBtnDst;
       Ft_App_WrCoCmd_Buffer(phost,TAG(' '));
       if(' ' == CurrTag)
       {
              Ft_Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER | OPT_FLAT, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
       }
       else
       {
              Ft_Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
       }
       yOffset = 120 + 10;
       Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "789");
       yOffset += ButtonH + yBtnDst;
       Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "456");
       yOffset += ButtonH + yBtnDst;
       Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "123");
       yOffset += ButtonH + yBtnDst;
       Ft_App_WrCoCmd_Buffer(phost,COLOR_A(255));
       Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "0.");//hilight button 0

       Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
       StringArray[0] = '\0';
       strcat(StringArray,"Next demo in ");
       Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
       strcat(StringArray,"s");
       Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);
       if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
       {
    	   Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
    	   Ft_App_WrCoCmd_Buffer(phost,TAG(249));
    	   Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
    	   CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
       }
       Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
       Ft_Gpu_CoCmd_Swap(phost);

       /* Download the commands into fifo */
       Ft_App_Flush_Co_Buffer(phost);

       /* Wait till coprocessor completes the operation */
       Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
       PrevTag = CurrTag;
       }
       }
}

//Bitmap animation demo
ft_void_t	Bitmap()
{
	if(FirstTimeThisDemo == 1)
	{
		//decompress the .binh contents using CMD_INFLATE
		Ft_Gpu_Hal_WrCmd32(phost,CMD_INFLATE);
		//specify starting address in graphics RAM
		Ft_Gpu_Hal_WrCmd32(phost,0L);
		//write the .binh contents to the FT800 FIFO command buffer, filesize=3888
		Ft_Gpu_Hal_WrCmdBuf(phost,&SAMAPP_Bitmap_RawData2[0],3888);
		p_bmhdr = (SAMAPP_Bitmap_header_t *)&SAMAPP_Bitmap_RawData_Header2[0];

		while(Ft_Gpu_Hal_Rd16(phost,REG_CMD_WRITE)!=Ft_Gpu_Hal_Rd16(phost,REG_CMD_READ));//Wait till the compression was done
		uint16_t x=Ft_Gpu_Hal_Rd16(phost,REG_CMD_WRITE);
		ending_address=0;
		Ft_Gpu_CoCmd_GetPtr(phost,0);
		//get ending adress in RAM_G
		ending_address=Ft_Gpu_Hal_Rd32(phost,(RAM_CMD+x+4));

		bitmap_i=0;
		FirstTimeThisDemo=0;
	}
		Ft_Gpu_CoCmd_Dlstart(phost);
		Ft_Gpu_CoCmd_Stop(phost);
		Ft_App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(255,255,255));
		Ft_App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
		Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
		//start drawing bitmaps
		Ft_App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
		//specify the starting address of the bitmap in graphics RAM
		Ft_App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(0L));
		Ft_App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(p_bmhdr->Format, p_bmhdr->Stride, p_bmhdr->Height));

		BMoffsetx = 150;
			BMoffsety = 180;
			scale = 250;

		if(bitmap_i*12>scale)
		{
			Ft_App_WrCoCmd_Buffer(phost,BITMAP_TRANSFORM_A(scale));//bitmap width scaling
		}
		else
		{
			Ft_App_WrCoCmd_Buffer(phost,BITMAP_TRANSFORM_A((bitmap_i*12)));//bitmap width scaling
		}
		Ft_App_WrCoCmd_Buffer(phost,BITMAP_TRANSFORM_E(scale));//bitmap height scaling
		Ft_App_WrCoCmd_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, BORDER, 0, 0));
		if(bitmap_i*8>255)
		{
			Ft_App_WrCoCmd_Buffer(phost,COLOR_A(255));//bitmap transparency
		}
		else
		{
			Ft_App_WrCoCmd_Buffer(phost,COLOR_A(bitmap_i*8));//bitmap transparency
		}
		Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(BMoffsetx, BMoffsety, 0, 0));
		Ft_App_WrCoCmd_Buffer(phost,END());
		//Restore transform matrix and transparency to default settings
		Ft_App_WrCoCmd_Buffer(phost,BITMAP_TRANSFORM_A(256));
		Ft_App_WrCoCmd_Buffer(phost,BITMAP_TRANSFORM_E(256));
		Ft_App_WrCoCmd_Buffer(phost,COLOR_A(255));
		Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
		StringArray[0] = '\0';
		strcat(StringArray,"Next demo in ");
		Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
		strcat(StringArray,"s");
		Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);

		if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
		{
			Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
			Ft_App_WrCoCmd_Buffer(phost,TAG(249));
			Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
			CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		}

		Ft_App_WrCoCmd_Buffer(phost, DISPLAY() );

		Ft_Gpu_CoCmd_Swap(phost);
		/* Download the commands into fifo */
		Ft_App_Flush_Co_Buffer(phost);
		/* Wait till coprocessor completes the operation */
		Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
		bitmap_i++;
}


//Sketch function demo
ft_void_t Sketch()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of sketch function. Sketch function */
	/* draws line for pen movement. Skecth supports L1 and L8 output formats */
	/* Sketch draws till stop command is executed.                           */
	/*************************************************************************/

	ft_int16_t BorderSz = 40;
	ft_int16_t BorderSz2 = 16;
    ft_uint32_t MemZeroSz;

    MemZeroSz = 1L*(FT_DispWidth - 2*BorderSz2)*(FT_DispHeight - BorderSz - BorderSz2);
	if(FirstTimeThisDemo == 1)
	{
		//Clear memory
		Ft_Gpu_CoCmd_MemZero(phost, (RAM_G+ending_address),MemZeroSz);
		FirstTimeThisDemo=0;
	}

	/* Sketch L8 format */
	/* Send command sketch */
	if(tftConfig==RTP70 || tftConfig==RTP50)
	{
		Ft_Gpu_CoCmd_Sketch(phost, BorderSz2,BorderSz,(FT_DispWidth - 2*BorderSz2),(FT_DispHeight - BorderSz - BorderSz2),(RAM_G+ending_address),L8);//sketch in L8 format
	}
	if(tftConfig==CTP70 || tftConfig==CTP50)
	{
		Ft_Gpu_CoCmd_CSketch(phost, BorderSz2,BorderSz,(FT_DispWidth - 2*BorderSz2),(FT_DispHeight - BorderSz - BorderSz2),(RAM_G+ending_address),L8,1500L);//sketch in L1 format
	}

    {
	/* Display the sketch */
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0x00,0x00,0xff));
	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Ft_App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(FT_DispWidth,(FT_DispHeight - BorderSz)));
	Ft_App_WrCoCmd_Buffer(phost,SCISSOR_XY(0,BorderSz));
	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xe0,0xe0,0xe0));
	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Ft_App_WrCoCmd_Buffer(phost,SCISSOR_SIZE((FT_DispWidth - 2*BorderSz2),(FT_DispHeight - BorderSz - BorderSz2)));
	Ft_App_WrCoCmd_Buffer(phost,SCISSOR_XY(BorderSz2,BorderSz));
	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));
	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));

	Ft_App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(2048,2048));
	Ft_App_WrCoCmd_Buffer(phost,SCISSOR_XY(0,0));
	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0,0,0));
	/* L8 bitmap display */
	Ft_App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	Ft_App_WrCoCmd_Buffer(phost,BITMAP_SOURCE((RAM_G+ending_address)));//0));
	Ft_App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L8,(FT_DispWidth - 2*BorderSz2),(FT_DispHeight  - BorderSz - BorderSz2)));
	Ft_App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT_H((((FT_DispWidth - 2*BorderSz))>>10),((FT_DispHeight - 2*BorderSz)>>9)));
	Ft_App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,(FT_DispWidth - 2*BorderSz2),(FT_DispHeight  - BorderSz - BorderSz2)));
	Ft_App_WrCoCmd_Buffer(phost,BITMAP_SIZE_H(((FT_DispWidth - 2*BorderSz)>>9),((FT_DispHeight - 2*BorderSz)>>9)));
	Ft_App_WrCoCmd_Buffer(phost,VERTEX2F(BorderSz2*16,BorderSz*16));
	Ft_App_WrCoCmd_Buffer(phost,END());
	/* Display the text */
	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), 20, 27, OPT_CENTER, "Draw test");

	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
	StringArray[0] = '\0';
	strcat(StringArray,"Next demo in ");
	Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
	strcat(StringArray,"s");
	Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);
	if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
	{
		Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
		Ft_App_WrCoCmd_Buffer(phost,TAG(249));
		Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
		CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		Ft_App_WrCoCmd_Buffer(phost,TAG(250));
		Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,12,60,30,20,0, "CLEAR");
		CurrTag3 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		if(CurrTag3==250)
		{
			Ft_Gpu_CoCmd_MemZero(phost, (RAM_G+ending_address),MemZeroSz);//Clear memory
			CurrTag3=0;
		}
	}
	Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
	Ft_Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	Ft_App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
	}
	/* Send the stop command */
	Ft_Gpu_Hal_WrCmd32(phost,  CMD_STOP);
	/* Update the command buffer pointers - both read and write pointers */
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
}

//Stopwatch reset
void StopwatchReset(void)
{
		  stopwatch.ms = 0;
		  stopwatch.enable = 0;
}

//Read multitouch registers
ft_void_t read_extended(ft_int16_t sx[5], ft_int16_t sy[5])
{
  ft_uint32_t sxy0, sxyA, sxyB, sxyC;
  sxy0 = Ft_Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH0_XY);
  sxyA = Ft_Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH1_XY);
  sxyB = Ft_Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH2_XY);
  sxyC = Ft_Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH3_XY);

  sx[0] = sxy0 >> 16;
  sy[0] = sxy0;
  sx[1] = sxyA >> 16;
  sy[1] = sxyA;
  sx[2] = sxyB >> 16;
  sy[2] = sxyB;
  sx[3] = sxyC >> 16;
  sy[3] = sxyC;

  sx[4] = Ft_Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_X);
  sy[4] = Ft_Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_Y);
}

// >>> [int(round(1024 * math.atan(i / 256.) / math.pi)) for i in range(256)]
static const FT_PROGMEM  ft_uchar8_t atan8[] = {
0,1,3,4,5,6,8,9,10,11,13,14,15,17,18,19,20,22,23,24,25,27,28,29,30,32,33,34,36,37,38,39,41,42,43,44,46,47,48,49,51,52,53,54,55,57,58,59,60,62,63,64,65,67,68,69,70,71,73,74,75,76,77,79,80,81,82,83,85,86,87,88,89,91,92,93,94,95,96,98,99,100,101,102,103,104,106,107,108,109,110,111,112,114,115,116,117,118,119,120,121,122,124,125,126,127,128,129,130,131,132,133,134,135,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,177,178,179,180,181,182,183,184,185,186,187,188,188,189,190,191,192,193,194,195,195,196,197,198,199,200,201,201,202,203,204,205,206,206,207,208,209,210,211,211,212,213,214,215,215,216,217,218,219,219,220,221,222,222,223,224,225,225,226,227,228,228,229,230,231,231,232,233,234,234,235,236,236,237,238,239,239,240,241,241,242,243,243,244,245,245,246,247,248,248,249,250,250,251,251,252,253,253,254,255,255
};

//calculate polygon angles
ft_uint16_t poly_atan2(ft_int16_t y, ft_int16_t x)
{
  ft_uint16_t a;
  ft_uint16_t xx = 0;

  //hack from prashanth
  if(0x8000 == y)
  {
	y++;
  }
  if(0x8000 == x)
  {
  	x++;
  }

  if ((x <= 0) ^ (y > 0)) {
    ft_int16_t t; t = x; x = y; y = t;
    xx ^= 0x4000;
  }
  if (x <= 0) {
    x = -x;
  } else {
    xx ^= 0x8000;
  }
  y = abs(y);
  if (x > y) {
    ft_int16_t t; t = x; x = y; y = t;
    xx ^= 0x3fff;
  }
  while ((x | y) & 0xff80) {
    x >>= 1;
    y >>= 1;
  }
  if (y == 0) {
    a = 0;
  } else if (x == y) {
    a = 0x2000;
  } else {
    // assert(x <= y);
    int r = ((x << 8) / y);
    // assert(0 <= r);
    // assert(r < 256);
    a = ft_pgm_read_byte(atan8 + r) << 5;
  }
  a ^= xx;
  return a;
}

//Restart polygon
ft_void_t poly_restart()
{
      poly_n = 0;
      poly_x0 = 16 * 480;
      poly_x1 = 0;
      poly_y0 = 16 * 272;
      poly_y1 = 0;
}

//polygon function
ft_void_t poly_perim()
{
      for (j = 0; j < poly_n; j++)
      {
    	  Ft_App_WrCoCmd_Buffer(phost,VERTEX2F(poly_x[j], poly_y[j]));
      }
      Ft_App_WrCoCmd_Buffer(phost,VERTEX2F(poly_x[0], poly_y[0]));
}

//Begin polygon drawing
ft_void_t poly_begin()
{
      poly_restart();

      Ft_App_WrCoCmd_Buffer(phost,(COLOR_MASK(0,0,0,0)));
      Ft_App_WrCoCmd_Buffer(phost,STENCIL_OP(KEEP, INVERT));
      Ft_App_WrCoCmd_Buffer(phost,STENCIL_FUNC(ALWAYS, 255, 255));
}

//polygon function
ft_void_t poly_v(ft_int32_t _x, ft_int32_t _y)
{
   	if(poly_x0 > (_x >> 4))
   		poly_x0=(_x >> 4);
   	if(poly_x1 < (_x >> 4))
   		poly_x1=(_x >> 4);
   	if(poly_y0 >( _y >> 4))
   		poly_y0=(_y >> 4);
   	if(poly_y1 < (_y >> 4))
	poly_y1=(_y >> 4);
     poly_x[poly_n] = _x;
     poly_y[poly_n] = _y;
     poly_n++;
}

//Draw polygon outline
ft_void_t poly_outline()
{
     Ft_App_WrCoCmd_Buffer(phost,BEGIN(LINE_STRIP));
     poly_perim();
}

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/


int main(void)
{
	unsigned char chipid;
	ft_uint8_t Swap_Type = DLSWAP_FRAME,Swap_Done = DLSWAP_FRAME;
	GPIO_InitTypeDef        GPIO_InitStructure;

	//Initialization
	SwitchInit();
	msTimerInit();

	/*Configure IO pins */
	Ft_Gpu_Hal_Init();

	/* Initialize SPI interface */
	Ft_Gpu_Hal_Open();

	phost=&host;

  	/*Set Power Down Pin UP*/
	Ft_Gpu_Hal_Powercycle(FT_TRUE);

	/* Access address 0 to wake up the FT800 */
	Ft_Gpu_HostCommand(FT_GPU_ACTIVE_M);
	Ft_Gpu_Hal_Sleep(100);

	/* Set the clk to external clock */
	//Ft_Gpu_HostCommand(FT_GPU_EXTERNAL_OSC);
	Ft_Gpu_HostCommand(FT_GPU_INTERNAL_OSC);
	Ft_Gpu_Hal_Sleep(10);

	  GPIO_WriteBit(CS_PORT, CS_PIN, 0);
	  SPI_SendByte(0x42); // SLEEP
	  SPI_SendByte(0x00);
	  SPI_SendByte(0x00);
	  GPIO_WriteBit(CS_PORT, CS_PIN, 1);
	Ft_Gpu_Hal_Sleep(10);

	  GPIO_WriteBit(CS_PORT, CS_PIN, 0);
	  SPI_SendByte(0x61);
	  SPI_SendByte(0x00);
	  SPI_SendByte(0x00);
	  GPIO_WriteBit(CS_PORT, CS_PIN, 1);
	Ft_Gpu_Hal_Sleep(20);

	//Tutaj budze kontroler

	/* Access address 0 to wake up the FT800 */
	Ft_Gpu_HostCommand(FT_GPU_ACTIVE_M);
	Ft_Gpu_Hal_Sleep(100);

	chipid = 0;
	chipid = Ft_Gpu_Hal_Rd8(phost, REG_ID);
	while(chipid != 0x7C)
	chipid = Ft_Gpu_Hal_Rd8(phost, REG_ID);

	ft_int16_t FT_DispWidth = 800;
	ft_int16_t FT_DispHeight = 480;
	ft_int16_t FT_DispHCycle = 1056;
	ft_int16_t FT_DispHOffset = 46;
	ft_int16_t FT_DispHSync0 = 0;
	ft_int16_t FT_DispHSync1 = 10;
	ft_int16_t FT_DispVCycle = 525;
	ft_int16_t FT_DispVOffset = 23;
	ft_int16_t FT_DispVSync0 = 0;
	ft_int16_t FT_DispVSync1 = 10;
	ft_uint8_t FT_DispPCLK = 2;
	ft_char8_t FT_DispSwizzle = 0;
	ft_char8_t FT_DispPCLKPol = 0;


    Ft_Gpu_Hal_Wr16(phost, REG_HCYCLE, FT_DispHCycle);
    Ft_Gpu_Hal_Wr16(phost, REG_HOFFSET, FT_DispHOffset);
    Ft_Gpu_Hal_Wr16(phost, REG_HSYNC0, FT_DispHSync0);
    Ft_Gpu_Hal_Wr16(phost, REG_HSYNC1, FT_DispHSync1);
    Ft_Gpu_Hal_Wr16(phost, REG_VCYCLE, FT_DispVCycle);
    Ft_Gpu_Hal_Wr16(phost, REG_VOFFSET, FT_DispVOffset);
    Ft_Gpu_Hal_Wr16(phost, REG_VSYNC0, FT_DispVSync0);
    Ft_Gpu_Hal_Wr16(phost, REG_VSYNC1, FT_DispVSync1);
    Ft_Gpu_Hal_Wr8(phost, REG_SWIZZLE, FT_DispSwizzle);
    Ft_Gpu_Hal_Wr8(phost, REG_CSPREAD, 0);
    Ft_Gpu_Hal_Wr8(phost, REG_PCLK_POL, FT_DispPCLKPol);
    Ft_Gpu_Hal_Wr8(phost, REG_PCLK,FT_DispPCLK);//after this display is visible on the LCD
    Ft_Gpu_Hal_Wr16(phost, REG_HSIZE, FT_DispWidth);
    Ft_Gpu_Hal_Wr16(phost, REG_VSIZE, FT_DispHeight);



    Ft_Gpu_Hal_Wr8(phost, REG_GPIO_DIR,0x83 | Ft_Gpu_Hal_Rd8(phost,REG_GPIO_DIR));
    Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0x083 | Ft_Gpu_Hal_Rd8(phost,REG_GPIO));

    Ft_Gpu_Hal_Wr16(phost, REG_TOUCH_RZTHRESH,1200);




	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	// Configure PC10 and PC11 in output pushpull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);



	//Restore last sub-demo using external FLASH memory as virtual EEPROM
	SPI_FLASH_Init();
	pointer=&tft_state;
	SPI_FLASH_BufferRead(pointer, 0x000000, 0x0001);
	tftConfig= tft_state-1;

	buttonPressFlag = 1;
	CurrTag2=0;
	DoTheCalibration=1;

	uint32_t freq;

	Ft_Gpu_Hal_Wr32(phost,REG_FREQUENCY,36000000);

	freq = Ft_Gpu_Hal_Rd32(phost,REG_FREQUENCY);

	while(1)
	{
		if(buttonPressFlag)
		{
			buttonPressFlag = 0;
			StopwatchReset();
			CurrTag2=0;
			if(++tftConfig == 7)
				tftConfig = 1;
			//Save current display type using external FLASH memory as virtual EEPROM
			tft_state=tftConfig;
			SPI_FLASH_SectorErase(0x000000);
			SPI_FLASH_BufferWrite(pointer, 0x000000, 0x0001);

			//Enable stopwatch
			stopwatch.enable = 1;

			//Set proper value of parameters for current sub-demo
			switch(tftConfig)
			{
			case NTP70:
				DemoTime=&DemoTime_NTP70;
				/*7.0" NTP */
				FT_DispWidth = 800;
				FT_DispHeight = 480;
				FT_DispHCycle = 1056;
				FT_DispHOffset = 46;
				FT_DispHSync0 = 0;
				FT_DispHSync1 = 10;
				FT_DispVCycle = 525;
				FT_DispVOffset = 23;
				FT_DispVSync0 = 0;
				FT_DispVSync1 = 10;
				FT_DispPCLK = 2;
				FT_DispSwizzle = 0;
				FT_DispPCLKPol = 0;
				break;
			case RTP70:
				DemoTime=&DemoTime_RTP70;
				/*7.0" RTP */
				FT_DispWidth = 800;
				FT_DispHeight = 480;
				FT_DispHCycle = 1056;
				FT_DispHOffset = 46;
				FT_DispHSync0 = 0;
				FT_DispHSync1 = 10;
				FT_DispVCycle = 525;
				FT_DispVOffset = 23;
				FT_DispVSync0 = 0;
				FT_DispVSync1 = 10;
				FT_DispPCLK = 2;
				FT_DispSwizzle = 0;
				FT_DispPCLKPol = 0;
				break;
			case CTP70:
				DemoTime=&DemoTime_CTP70;
				/*7.0" CTP */
				FT_DispWidth = 800;
				FT_DispHeight = 480;
				FT_DispHCycle = 1056;
				FT_DispHOffset = 46;
				FT_DispHSync0 = 0;
				FT_DispHSync1 = 10;
				FT_DispVCycle = 525;
				FT_DispVOffset = 23;
				FT_DispVSync0 = 0;
				FT_DispVSync1 = 10;
				FT_DispPCLK = 2;
				FT_DispSwizzle = 0;
				FT_DispPCLKPol = 0;
				break;
			case NTP50:
				DemoTime=&DemoTime_NTP50;
				/*5.0" NTP */
				FT_DispWidth = 800;
				FT_DispHeight = 480;
				FT_DispHCycle = 1056;
				FT_DispHOffset = 46;
				FT_DispHSync0 = 0;
				FT_DispHSync1 = 10;
				FT_DispVCycle = 525;
				FT_DispVOffset = 23;
				FT_DispVSync0 = 0;
				FT_DispVSync1 = 10;
				FT_DispPCLK = 2;
				FT_DispSwizzle = 0;
				FT_DispPCLKPol = 0;
				break;
			case RTP50:
				DemoTime=&DemoTime_RTP50;
				/*5.0" RTP */
				FT_DispWidth = 800;
				FT_DispHeight = 480;
				FT_DispHCycle = 1056;
				FT_DispHOffset = 46;
				FT_DispHSync0 = 0;
				FT_DispHSync1 = 10;
				FT_DispVCycle = 525;
				FT_DispVOffset = 23;
				FT_DispVSync0 = 0;
				FT_DispVSync1 = 10;
				FT_DispPCLK = 2;
				FT_DispSwizzle = 0;
				FT_DispPCLKPol = 0;
				break;
			case CTP50:
				DemoTime=&DemoTime_CTP50;
				/*5.0" CTP */
				FT_DispWidth = 800;
				FT_DispHeight = 480;
				FT_DispHCycle = 1056;
				FT_DispHOffset = 46;
				FT_DispHSync0 = 0;
				FT_DispHSync1 = 10;
				FT_DispVCycle = 525;
				FT_DispVOffset = 23;
				FT_DispVSync0 = 0;
				FT_DispVSync1 = 10;
				FT_DispPCLK = 2;
				FT_DispSwizzle = 0;
				FT_DispPCLKPol = 0;
				break;
			default:
				break;
			}

			/*Set requested registers*/
			Ft_Gpu_Hal_Wr16(phost, REG_HCYCLE, FT_DispHCycle);
			Ft_Gpu_Hal_Wr16(phost, REG_HOFFSET, FT_DispHOffset);
			Ft_Gpu_Hal_Wr16(phost, REG_HSYNC0, FT_DispHSync0);
			Ft_Gpu_Hal_Wr16(phost, REG_HSYNC1, FT_DispHSync1);
			Ft_Gpu_Hal_Wr16(phost, REG_VCYCLE, FT_DispVCycle);
			Ft_Gpu_Hal_Wr16(phost, REG_VOFFSET, FT_DispVOffset);
			Ft_Gpu_Hal_Wr16(phost, REG_VSYNC0, FT_DispVSync0);
			Ft_Gpu_Hal_Wr16(phost, REG_VSYNC1, FT_DispVSync1);
			Ft_Gpu_Hal_Wr8(phost, REG_SWIZZLE, FT_DispSwizzle);
			Ft_Gpu_Hal_Wr8(phost, REG_PCLK_POL, FT_DispPCLKPol);
			Ft_Gpu_Hal_Wr8(phost, REG_CSPREAD, 0);
			Ft_Gpu_Hal_Wr8(phost, REG_PCLK,FT_DispPCLK);//after this display is visible on the LCD
			Ft_Gpu_Hal_Wr16(phost, REG_HSIZE, FT_DispWidth);
			Ft_Gpu_Hal_Wr16(phost, REG_VSIZE, FT_DispHeight);

			Ft_Gpu_Hal_Wr8(phost, REG_GPIO_DIR,0x83 | Ft_Gpu_Hal_Rd8(phost,REG_GPIO_DIR));
			Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0x083 | Ft_Gpu_Hal_Rd8(phost,REG_GPIO));
			Ft_Gpu_Hal_Wr16(phost, REG_TOUCH_RZTHRESH,1200);
			Ft_Gpu_Hal_Wr8(phost, REG_ROTATE, 0);//turn off rotation

			if(tftConfig==CTP70)
			{
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_A,0x000072DA);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_B,0x00000000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_C,0x00000000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_D,0x00000000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_E,0x00007800);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_F,0x00000000);
			}
			if(tftConfig==CTP50)
			{
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_A,0x00010000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_B,0x00000000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_C,0x00000000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_D,0x00000000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_E,0x00010000);
				Ft_Gpu_Hal_Wr32(phost,REG_TOUCH_TRANSFORM_F,0x00000000);
			}


			CurrentDemo=0;
			ThisDemoEnd=DemoTime[CurrentDemo];
		}

		//State machine
		switch(CurrentDemo)
		{
			case 0://Info screen
			{
				Ft_Gpu_CoCmd_Dlstart(phost);

				/*Setting first screen*/
				Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));//white color
				Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));//clear screen

				Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x00,0x00));//red color
				switch(tftConfig)
				{
					case NTP70:
						Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), FT_DispHeight/2, 28, OPT_CENTERX, "Riverdi 7.0\" no touch demo");
						break;
					case RTP70:
						Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), FT_DispHeight/2, 28, OPT_CENTERX, "Riverdi 7.0\" RTP demo");
						break;
					case CTP70:
						Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), FT_DispHeight/2, 28, OPT_CENTERX, "Riverdi 7.0\" CTP demo");
						break;
					case NTP50:
						Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), FT_DispHeight/2, 28, OPT_CENTERX, "Riverdi 5.0\" no touch demo");
						break;
					case RTP50:
						Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), FT_DispHeight/2, 28, OPT_CENTERX, "Riverdi 5.0\" RTP demo");
						break;
					case CTP50:
						Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), FT_DispHeight/2, 28, OPT_CENTERX, "Riverdi 5.0\" CTP demo");
						break;
				}
				//Display time to end
				Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
				StringArray[0] = '\0';
				strcat(StringArray,"Next demo in ");
				Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
				strcat(StringArray,"s");
				Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);
				if(tftConfig == CTP70 || tftConfig == CTP50)
				{
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
					Ft_App_WrCoCmd_Buffer(phost,TAG(249));
					Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
					CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
				}
				if(((tftConfig == RTP70) || (tftConfig == RTP50)) && (DoTheCalibration == 0))
				{
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
					Ft_App_WrCoCmd_Buffer(phost,TAG(249));
					Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
					CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
				}
				Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
				Ft_Gpu_CoCmd_Swap(phost);

				/* Download the commands into fifo */
				Ft_App_Flush_Co_Buffer(phost);

				/* Wait till coprocessor completes the operation */
				Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
			}
			break;
			case 1://Bitmap animation demo
			{
				//Calibrate resistant touchpanel
				if((FirstTimeThisDemo == 1) && (DoTheCalibration == 1) && ((tftConfig == RTP70) || (tftConfig == RTP50)))
				{
					stopwatch.enable = 0;

					Ft_Gpu_CoCmd_Dlstart(phost);
					Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
					Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
					/* Draw text at center location */
					Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), (FT_DispHeight/2), 27, OPT_CENTER, "Please Tap on the dot");
					/* Start calibration process*/
					Ft_Gpu_CoCmd_Calibrate(phost,0);


					Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
					Ft_Gpu_CoCmd_Swap(phost);

					/* Download the commands into fifo */
					Ft_App_Flush_Co_Buffer(phost);

					/* Wait till coprocessor completes the operation */
					Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
					//stop
					DoTheCalibration=0;
					stopwatch.enable = 1;
					Ft_Gpu_CoCmd_Dlstart(phost);
					Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));
					Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
					Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
					Ft_Gpu_CoCmd_Swap(phost);

					/* Download the commands into fifo */
					Ft_App_Flush_Co_Buffer(phost);
					/* Wait till coprocessor completes the operation */
					Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

				}

				//bitmap animation demo
				Bitmap();

			}
			break;
			case 2://Sketch function demo
			{
				Ft_Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
				if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
				{
					uint32_t A,B,C,D,E,F;

					A = Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_TRANSFORM_A);
					B = Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_TRANSFORM_B);
					C = Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_TRANSFORM_C);
					D = Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_TRANSFORM_D);
					E = Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_TRANSFORM_E);
					F = Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_TRANSFORM_F);
					//sketch function demonstration
					Sketch();
				}
			}
			break;
			case 3://multitouch function demo - only for CTP
			{
					Ft_Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);//set mode to extended, 5 simultaneous  touch points
					Ft_App_WrCoCmd_Buffer(phost, CMD_DLSTART);

					Ft_App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(0,0,0x50));
					Ft_App_WrCoCmd_Buffer(phost, CLEAR(1,1,1));
					Ft_App_WrCoCmd_Buffer(phost, SAVE_CONTEXT());
					Ft_App_WrCoCmd_Buffer(phost, COLOR_RGB(0xff,0xff,0xff));
					Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), (FT_DispHeight/2), 27, OPT_CENTER, "Please Tap from 2 to 5 points");

					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
					StringArray[0] = '\0';
					strcat(StringArray,"Next demo in ");
					Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
					strcat(StringArray,"s");
					Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);


					Ft_App_WrCoCmd_Buffer(phost, COLOR_RGB(0x40,0x40,0x40));
					Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
					read_extended(sx, sy);
					cx = 0, cy = 0;
					n = 0;
					{
						for (i = 0; i < 5; i++)
						{
						  if (sx[i] != 0x8000)
						  {
							cx += sx[i];
							cy += sy[i];
							n++;
						  }
						}
						if(n != 0)
						{
							cx /= n;
							cy /= n;
						}
					}
					if(n>0)
					{
						for (i = 0; i < 5; i++)
						{
							angles[i] = poly_atan2(sx[i] - cx, sy[i] - cy) >> 8;
						}
					}

					poly_begin();

					for (a = 0; a < 256; a++)
				    {
						for (i = 0; i < 5; i++)
						{
							if ((angles[i] == a )&& (sx[i] != 0x8000))
							{
								poly_v(16 * sx[i], 16 * sy[i]);
							}
						}
					}

					Ft_App_WrCoCmd_Buffer(phost,COLOR_A(255));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_MASK(1,1,1,1));
					Ft_App_WrCoCmd_Buffer(phost,BLEND_FUNC(SRC_ALPHA,ONE));
					Ft_App_WrCoCmd_Buffer(phost,STENCIL_FUNC(EQUAL, 255, 255));
					Ft_App_WrCoCmd_Buffer(phost, BEGIN(RECTS));
					Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0,0,0,0));
					Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(480,272,0,0));
					Ft_App_WrCoCmd_Buffer(phost,RESTORE_CONTEXT());
					Ft_App_WrCoCmd_Buffer(phost, COLOR_RGB(0x80,0x80,0xff));
					Ft_App_WrCoCmd_Buffer(phost, LINE_WIDTH(24));
					poly_outline();
					if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
					{
						Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
						Ft_App_WrCoCmd_Buffer(phost,TAG(249));
						Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
						CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
					}
					Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
					Ft_Gpu_CoCmd_Swap(phost);
					Ft_Gpu_CoCmd_LoadIdentity(phost);
					Ft_App_Flush_Co_Buffer(phost);
			}
			break;
			case 4://Keyboard demo
				Keyboard();
				break;
			case 5://Points demo
				{
					ft_int16_t hoffset,voffset,PointSz;
					voffset = (FT_DispHeight - 49);//49 is the max height of font handle 31
					hoffset = ((FT_DispWidth)/2);

					// Draw different points
				   	Ft_Gpu_CoCmd_Dlstart(phost);
					Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));//color white
					Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(128, 0, 0));
					Ft_App_WrCoCmd_Buffer(phost,POINT_SIZE((FT_DispWidth/5) * 16));
					Ft_App_WrCoCmd_Buffer(phost,BEGIN(FTPOINTS));// start drawing points
					Ft_App_WrCoCmd_Buffer(phost,VERTEX2F((FT_DispWidth/5) * 16, (FT_DispHeight/2) * 16));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0, 128, 0));
					Ft_App_WrCoCmd_Buffer(phost,POINT_SIZE((FT_DispWidth/6) * 16));
					Ft_App_WrCoCmd_Buffer(phost,VERTEX2F((FT_DispWidth*2/5) * 16, (FT_DispHeight/2) * 16));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0, 0, 128));
					Ft_App_WrCoCmd_Buffer(phost,POINT_SIZE((FT_DispWidth/7) * 16));
					Ft_App_WrCoCmd_Buffer(phost,VERTEX2F((FT_DispWidth*3/5) * 16, (FT_DispHeight/2) * 16));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(128, 128, 0));
					Ft_App_WrCoCmd_Buffer(phost,POINT_SIZE((FT_DispWidth/8) * 16));
					Ft_App_WrCoCmd_Buffer(phost,VERTEX2F((FT_DispWidth*4/5) * 16, (FT_DispHeight/2) * 16));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0, 128, 128));
					Ft_App_WrCoCmd_Buffer(phost,END());
					Ft_Gpu_CoCmd_Text(phost,hoffset, voffset, 31, OPT_CENTERX, "POINTS");

					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
					StringArray[0] = '\0';
					strcat(StringArray,"Next demo in ");
					Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
					strcat(StringArray,"s");
					Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);
					if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
					{
						Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
						Ft_App_WrCoCmd_Buffer(phost,TAG(249));
						Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
						CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
					}

					Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
					Ft_Gpu_CoCmd_Swap(phost);
					/* Download the commands into fifo */
					Ft_App_Flush_Co_Buffer(phost);
					/* Wait till coprocessor completes the operation */
					Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
				}
				break;
			case 6://Spinner demo
				{
					Ft_Gpu_CoCmd_Dlstart(phost);
					Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
					Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
					Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), 20, 27, OPT_CENTER, "Different types of spinners");
					Ft_Gpu_CoCmd_Text(phost,(FT_DispWidth/2), 60, 27, OPT_CENTER, "Please Wait ...");

					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
					StringArray[0] = '\0';
					strcat(StringArray,"Next demo in ");
					Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
					strcat(StringArray,"s");
					Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);

					if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
					{
						Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
						Ft_App_WrCoCmd_Buffer(phost,TAG(249));
						Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
						CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
						Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
					}

					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
					Ft_Gpu_CoCmd_Stop(phost);

					if(ThisDemoEnd>(3*(DemoTime[CurrentDemo]/4)))
					{
						Ft_Gpu_CoCmd_Spinner(phost, (FT_DispWidth/2),(FT_DispHeight/2),0,0);//style 0 and scale 0
					}
					if((ThisDemoEnd<=(3*(DemoTime[CurrentDemo]/4))) && (ThisDemoEnd>(1*(DemoTime[CurrentDemo]/2))))
					{
						Ft_Gpu_CoCmd_Spinner(phost, (FT_DispWidth/2),(FT_DispHeight/2),1,0);//style 1 and scale 0
					}
					if((ThisDemoEnd<=(1*(DemoTime[CurrentDemo]/2))) && (ThisDemoEnd>(1*(DemoTime[CurrentDemo]/4))))
					{
						Ft_Gpu_CoCmd_Spinner(phost, (FT_DispWidth/2),(FT_DispHeight/2),2,0);//style 2 and scale 0
					}
					if(ThisDemoEnd<=(1*(DemoTime[CurrentDemo]/4)))
					{
						Ft_Gpu_CoCmd_Spinner(phost, (FT_DispWidth/2),(FT_DispHeight/2),3,0);//style 3 and scale 0
					}

					if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
					{
						Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
					}

					Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
					Ft_Gpu_CoCmd_Swap(phost);
					// Download the commands into fifo
					Ft_App_Flush_Co_Buffer(phost);
					// Wait till coprocessor completes the operation
					Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
				}
				break;
			case 7://Street map demo
				{
					//Exemplary map
					Ft_Gpu_CoCmd_Dlstart(phost);
					Ft_App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(236,232,224)); //light gray
					Ft_App_WrCoCmd_Buffer(phost, CLEAR(1,1,1));
					Ft_App_WrCoCmd_Buffer(phost, COLOR_RGB(170,157,136));//medium gray
					Ft_App_WrCoCmd_Buffer(phost, LINE_WIDTH(63));
					//draw the streets
					Draw_streets();
					Ft_App_WrCoCmd_Buffer(phost, COLOR_RGB(250,250,250));//white
					Ft_App_WrCoCmd_Buffer(phost, LINE_WIDTH(48));
					//draw the streets
					Draw_streets();
					Ft_App_WrCoCmd_Buffer(phost, COLOR_RGB(0,0,0));
					Ft_App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
					Ft_App_WrCoCmd_Buffer(phost, VERTEX2II(240,91,27,77  ));//draw "Main st." at (240,91)
					Ft_App_WrCoCmd_Buffer(phost, VERTEX2II(252,91,27,97	));
					Ft_App_WrCoCmd_Buffer(phost, VERTEX2II(260,91,27,105	));
					Ft_App_WrCoCmd_Buffer(phost, VERTEX2II(263,91,27,110	));
					Ft_App_WrCoCmd_Buffer(phost, VERTEX2II(275,91,27,115	));
					Ft_App_WrCoCmd_Buffer(phost, VERTEX2II(286,91,27,46	));
					Ft_App_WrCoCmd_Buffer(phost, END());

					Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
					StringArray[0] = '\0';
					strcat(StringArray,"Next demo in ");
					Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
					strcat(StringArray,"s");
					Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX, StringArray);
					if(tftConfig == RTP70 || tftConfig == CTP70 || tftConfig == RTP50 || tftConfig == CTP50)
					{
						Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
						Ft_App_WrCoCmd_Buffer(phost,TAG(249));
						Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
						CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
					}

					Ft_App_WrCoCmd_Buffer(phost, DISPLAY());
					Ft_Gpu_CoCmd_Swap(phost);
					// Download the commands into fifo
					Ft_App_Flush_Co_Buffer(phost);
					// Wait till coprocessor completes the operation
					Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
				}
				break;
			case 8:
			{
				Ft_Gpu_CoCmd_Dlstart(phost);
				Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
				Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
				Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
				Ft_Gpu_CoCmd_Swap(phost);

				/* Download the commands into fifo */
				Ft_App_Flush_Co_Buffer(phost);
				/* Wait till coprocessor completes the operation */
				Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
				/* Do a swap */
				//Ft_Gpu_CoCmd_Swap(phost);

				buttonPressFlag = 1;
				tftConfig--;
				CurrentDemo=0;
				ThisDemoEnd=DemoTime[CurrentDemo];
			}

				break;

		}
	}
  return 0;
  }

//External interrupt service
void EXTI0_1_IRQHandler (void)
{
	  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	  {
		buttonPressDetectFlag = 1;
	    EXTI_ClearITPendingBit(EXTI_Line1);
	  }
}

//SysTick 1ms interrupt service
void SysTick_Handler(void)
{
	if(stopwatch.enable == 1)
	{
		stopwatch.ms++;
		if((stopwatch.ms%10) == 0)
		{
			ThisDemoEnd--;
			if(ThisDemoEnd==0)//demo time ends
			{
				CurrentDemo++;
				ThisDemoEnd=DemoTime[CurrentDemo];
				while(ThisDemoEnd==0)
				{
					CurrentDemo++;
					ThisDemoEnd=DemoTime[CurrentDemo];
				}
				FirstTimeThisDemo=1;
			}
			if((CurrTag2 == 249) && (ThisDemoEnd < (DemoTime[CurrentDemo]-50)))//skip
			{
				CurrTag2=0;
				CurrentDemo++;
				ThisDemoEnd=DemoTime[CurrentDemo];
				while(ThisDemoEnd==0)
				{
					CurrentDemo++;
					ThisDemoEnd=DemoTime[CurrentDemo];
				}
				FirstTimeThisDemo=1;
			}
		}
	}
	if(buttonPressDetectFlag)//switch pressed
		{
			buttonFilter++;
			if(buttonFilter == BUTTON_FILTER_VALUE_MS)
			{
				buttonFilter = 0;
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
				{
					buttonPressFlag = 1;
					DoTheCalibration = 1;
				}
				buttonPressDetectFlag = 0;
			}
		}
}

//I2C1 interrupt service
void I2C1_IRQHandler(void)
{
  /* Check on I2C1 SMBALERT flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_ALERT))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_ALERT);
    SMbusAlertOccurred++;
  }
  /* Check on I2C1 Time out flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_TIMEOUT))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_TIMEOUT);
  }
  /* Check on I2C1 Arbitration Lost flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_ARLO))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_ARLO);
  }
  /* Check on I2C1 PEC error flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_PECERR))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_PECERR);
  }
  /* Check on I2C1 Overrun/Underrun error flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_OVR))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_OVR);
  }
  /* Check on I2C1 Acknowledge failure error flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_NACKF))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_NACKF);
  }
  /* Check on I2C1 Bus error flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_BERR))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_BERR);
  }
}
