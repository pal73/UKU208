#ifndef _FT_PLATFORM_H_
#define _FT_PLATFORM_H_

//#define ARDUINO_PLATFORM
//#define MSVC_PLATFORM

#define SAMAPP_ENABLE_APIS_SET0
#define SAMAPP_ENABLE_APIS_SET1
#define SAMAPP_ENABLE_APIS_SET2
//#define SAMAPP_ENABLE_APIS_SET3
//#define SAMAPP_ENABLE_APIS_SET4
//#define SAMAPP_DISPLAY_QVGA

#ifdef  ARDUINO_PLATFORM
#define FT800_INT (3)
#define FT800_PD_N (4)
#define FT_ARDUINO_PRO_SPI_CS (10)
#define ARDUINO_PLATFORM_SPI
#define ARDUINO_PLATFORM_COCMD_BURST
#endif

#ifdef ARDUINO_PLATFORM
#include <stdio.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <avr/pgmspace.h>
#endif

#ifdef MSVC_PLATFORM
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#include "ftd2xx.h"
#include "LibMPSSE_spi.h"
#endif

#ifdef STM32F4XX
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"

#endif
#ifdef STM32F031C6
#include <stdio.h>
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_spi.h"
#include "stm32f0xx_gpio.h"

#endif

#include "FT_DataTypes.h"
#include "FT_Gpu_Hal.h"
#include "FT_Gpu.h"
#include "FT_CoPro_Cmds.h"



#ifdef MSVC_PLATFORM
#define BUFFER_OPTIMIZATION
#define MSVC_PLATFORM_SPI
/* Compile time switch for enabling sample app api sets - please cross check the same in SampleApp_RawData.cpp file as well */

#define SAMAPP_ENABLE_APIS_SET0
#define SAMAPP_ENABLE_APIS_SET1
#define SAMAPP_ENABLE_APIS_SET2
#define SAMAPP_ENABLE_APIS_SET3
#define SAMAPP_ENABLE_APIS_SET4
#define SAMAPP_ENABLE_APIS_SET5
#endif

#ifdef ARDUINO_PLATFORM
/* Compile time switch for enabling sample app api sets - please cross check the same in SampleApp_RawData.cpp file as well */
/*
#define SAMAPP_ENABLE_APIS_SET0
#define SAMAPP_ENABLE_APIS_SET1
#define SAMAPP_ENABLE_APIS_SET2
#define SAMAPP_ENABLE_APIS_SET3
*/
#define SAMAPP_ENABLE_APIS_SET3

#endif

extern Ft_Gpu_Hal_Context_t host,*phost;

extern ft_int16_t FT_DispWidth;
extern ft_int16_t FT_DispHeight;
extern ft_int16_t FT_DispHCycle;
extern ft_int16_t FT_DispHOffset;
extern ft_int16_t FT_DispHSync0;
extern ft_int16_t FT_DispHSync1;
extern ft_int16_t FT_DispVCycle;
extern ft_int16_t FT_DispVOffset;
extern ft_int16_t FT_DispVSync0;
extern ft_int16_t FT_DispVSync1;
extern ft_uint8_t FT_DispPCLK;
extern ft_char8_t FT_DispSwizzle;
extern ft_char8_t FT_DispPCLKPol;

#endif /*_FT_PLATFORM_H_*/
/* Nothing beyond this*/




