/*!
 * \file FT_GPU_HAL.h
 *
 * \author FTDI
 * \date 2013.04.24
 *
 * Copyright 2013 Future Technology Devices International Limited
 *
 * Project: FT800 or EVE compatible silicon
 * File Description:
 *    This file defines the generic APIs of host access layer for the FT800 or EVE compatible silicon.
 *    Application shall access FT800 or EVE resources over these APIs,regardless of I2C or SPI protocol.
 *    I2C and SPI is selected by compiler switch "FT_I2C_MODE"  and "FT_SPI_MODE". In addition, there are
 *    some helper functions defined for FT800 coprocessor engine as well as host commands.
 * Rivision History:
 */
#ifndef FT_GPU_HAL_H
#define FT_GPU_HAL_H

#define ft_uint8_t unsigned char
#define ft_uint32_t unsigned int
#define ft_uint16_t unsigned short int

#define CS_PORT GPIOA
#define CS_PIN GPIO_Pin_4
//#define CS_PIN GPIO_Pin_8
#define PD_PORT GPIOA
#define PD_PIN GPIO_Pin_2

#define DUMMY_BYTE 0x00


typedef enum {
	FT_GPU_I2C_MODE = 0,
	FT_GPU_SPI_MODE,

	FT_GPU_MODE_COUNT,
	FT_GPU_MODE_UNKNOWN = FT_GPU_MODE_COUNT
}FT_GPU_HAL_MODE_E;

typedef enum {
	FT_GPU_HAL_OPENED,
	FT_GPU_HAL_READING,
	FT_GPU_HAL_WRITING,
	FT_GPU_HAL_CLOSED,

	FT_GPU_HAL_STATUS_COUNT,
	FT_GPU_HAL_STATUS_ERROR = FT_GPU_HAL_STATUS_COUNT
}FT_GPU_HAL_STATUS_E;

typedef struct {
	union {
		ft_uint8_t spi_cs_pin_no;
		ft_uint8_t i2c_addr;
	};
	union {
		ft_uint16_t spi_clockrate_khz;  //In KHz
		ft_uint16_t i2c_clockrate_khz;  //In KHz
	};
	ft_uint8_t channel_no;
}Ft_Gpu_Hal_Config_t;

typedef struct {
	ft_uint8_t reserved;
}Ft_Gpu_App_Context_t;

typedef struct {
	/* Total number channels for libmpsse */
	ft_uint32_t TotalChannelNum;
}Ft_Gpu_HalInit_t;

typedef enum {
	FT_GPU_READ = 0,
	FT_GPU_WRITE,
}FT_GPU_TRANSFERDIR_T;


typedef struct {	
	ft_uint32_t length; //IN and OUT
	ft_uint32_t address;
	ft_uint8_t  *buffer;
}Ft_Gpu_App_Transfer_t;

typedef struct {
	Ft_Gpu_App_Context_t        app_header;         
	Ft_Gpu_Hal_Config_t         hal_config;

        ft_uint16_t ft_cmd_fifo_wp; //coprocessor fifo write pointer
        ft_uint16_t ft_dl_buff_wp;  //display command memory write pointer

	FT_GPU_HAL_STATUS_E        status;        //OUT
	ft_void_t*                 hal_handle;        //IN/OUT
}Ft_Gpu_Hal_Context_t;

/*The basic APIs Level 1*/
ft_bool_t              Ft_Gpu_Hal_Init( void );
ft_bool_t              Ft_Gpu_Hal_Open( void );

/*The APIs for reading/writing transfer continuously only with small buffer system*/
ft_void_t               Ft_Gpu_Hal_StartTransfer(Ft_Gpu_Hal_Context_t *host,FT_GPU_TRANSFERDIR_T rw,ft_uint32_t addr);
ft_uint8_t              Ft_Gpu_Hal_Transfer8(Ft_Gpu_Hal_Context_t *host,ft_uint8_t value);
ft_uint16_t             Ft_Gpu_Hal_Transfer16(Ft_Gpu_Hal_Context_t *host,ft_uint16_t value);
ft_uint32_t             Ft_Gpu_Hal_Transfer32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t value);
ft_void_t               Ft_Gpu_Hal_EndTransfer(Ft_Gpu_Hal_Context_t *host);

/*Read & Write APIs for both burst and single transfer,depending on buffer size*/
ft_void_t              Ft_Gpu_Hal_Read(Ft_Gpu_Hal_Context_t *host, Ft_Gpu_App_Transfer_t *transfer);
ft_void_t              Ft_Gpu_Hal_Write(Ft_Gpu_Hal_Context_t *host,Ft_Gpu_App_Transfer_t *transfer);

ft_void_t              Ft_Gpu_Hal_Close(Ft_Gpu_Hal_Context_t *host);
ft_void_t              Ft_Gpu_Hal_DeInit();

/*Helper function APIs Read*/
ft_uint8_t  Ft_Gpu_Hal_Rd8(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr);
ft_uint16_t Ft_Gpu_Hal_Rd16(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr);
ft_uint32_t Ft_Gpu_Hal_Rd32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr);

/*Helper function APIs Write*/
ft_void_t Ft_Gpu_Hal_Wr8(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint8_t v);
ft_void_t Ft_Gpu_Hal_Wr16(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint16_t v);
ft_void_t Ft_Gpu_Hal_Wr32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint32_t v);

/*******************************************************************************/
/*******************************************************************************/
/*APIs for coprocessor Fifo read/write and space management*/
ft_void_t Ft_Gpu_Hal_Updatecmdfifo(Ft_Gpu_Hal_Context_t *host,ft_uint16_t count);
ft_void_t Ft_Gpu_Hal_WrCmd32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t cmd);
ft_void_t Ft_Gpu_Hal_WrCmdBuf(Ft_Gpu_Hal_Context_t *host,ft_uint8_t *buffer,ft_uint16_t count);
ft_void_t Ft_Gpu_Hal_WaitCmdfifo_empty(Ft_Gpu_Hal_Context_t *host);
ft_void_t Ft_Gpu_Hal_ResetCmdFifo(Ft_Gpu_Hal_Context_t *host);
ft_void_t Ft_Gpu_Hal_CheckCmdBuffer(Ft_Gpu_Hal_Context_t *host,ft_uint16_t count);

ft_void_t Ft_Gpu_Hal_ResetDLBuffer(Ft_Gpu_Hal_Context_t *host);

ft_void_t  Ft_Gpu_Hal_StartCmdTransfer(Ft_Gpu_Hal_Context_t *host,FT_GPU_TRANSFERDIR_T rw, ft_uint16_t count);

ft_void_t Ft_Gpu_Hal_Powercycle(ft_bool_t up);


/*******************************************************************************/
/*******************************************************************************/
/*APIs for Host Commands*/
typedef enum {
	FT_GPU_INTERNAL_OSC = 0x48, //default
	FT_GPU_EXTERNAL_OSC = 0x44,
}FT_GPU_PLL_SOURCE_T;
typedef enum {
	FT_GPU_PLL_48M = 0x62,  //default
	FT_GPU_PLL_36M = 0x61,
	FT_GPU_PLL_24M = 0x64,
}FT_GPU_PLL_FREQ_T;

typedef enum {
	FT_GPU_ACTIVE_M =  0x00,  
	FT_GPU_STANDBY_M = 0x41,//default
	FT_GPU_SLEEP_M =   0x42,
	FT_GPU_POWERDOWN_M = 0x50,
}FT_GPU_POWER_MODE_T;

typedef enum {
	FT_GPU_SYSCLK_DEFAULT = 0x00,  //default 60mhz
	FT_GPU_SYSCLK_72M = 0x06,
	FT_GPU_SYSCLK_60M = 0x05,
	FT_GPU_SYSCLK_48M = 0x04,
	FT_GPU_SYSCLK_36M = 0x03,
	FT_GPU_SYSCLK_24M = 0x02,
}FT_GPU_81X_PLL_FREQ_T;

typedef enum{
	FT_GPU_MAIN_ROM = 0x80,  //main graphicas ROM used
	FT_GPU_RCOSATAN_ROM = 0x40,  //line slope table used for
	FT_GPU_SAMPLE_ROM = 0x20,  //JA samples
	FT_GPU_JABOOT_ROM = 0x10, //JA microcode
	FT_GPU_J1BOOT_ROM = 0x08, //J1 microcode
	FT_GPU_ADC = 0x01,  //
	FT_GPU_POWER_ON_ROM_AND_ADC = 0x00,  //specify this element to power on all ROMs and ADCs
}FT_GPU_81X_ROM_AND_ADC_T;

typedef enum{
	FT_GPU_5MA = 0x00,  //default current
	FT_GPU_10MA = 0x01,
	FT_GPU_15MA = 0x02,
	FT_GPU_20MA = 0x03,
}FT_GPU_81X_GPIO_DRIVE_STRENGTH_T;

typedef enum{
	FT_GPU_GPIO0 = 0x00,
	FT_GPU_GPIO1 = 0x04,
	FT_GPU_GPIO2 = 0x08,
	FT_GPU_GPIO3 = 0x0C,
	FT_GPU_GPIO4 = 0x04,
	FT_GPU_DISP = 0x10,
	FT_GPU_DE = 0x24,
	FT_GPU_VSYNC_HSYNC = 0x28,
	FT_GPU_PCLK = 0x2C,
	FT_GPU_BACKLIGHT = 0x30,
	FT_GPU_R_G_B = 0x34,
	FT_GPU_AUDIO_L = 0x38,
	FT_GPU_INT_N = 0x3C,
	FT_GPU_TOUCHWAKE = 0x40,
	FT_GPU_SCL = 0x44,
	FT_GPU_SDA = 0x48,
	FT_GPU_SPI_MISO_MOSI_IO2_IO3 = 0x4C,
}FT_GPU_81X_GPIO_GROUP_T;

ft_void_t Ft_Gpu_PLL_FreqSelect(Ft_Gpu_Hal_Context_t *host,FT_GPU_PLL_FREQ_T freq);
ft_void_t Ft_Gpu_HostCommand_Ext3(Ft_Gpu_Hal_Context_t *host,ft_uint32_t cmd);

#define FT_GPU_CORE_RESET  (0x68)

ft_int32_t hal_strlen(const ft_char8_t *s);
ft_void_t Ft_Gpu_Hal_Sleep(ft_uint16_t ms);
ft_void_t Ft_Gpu_ClockSelect(Ft_Gpu_Hal_Context_t *host,FT_GPU_PLL_SOURCE_T pllsource);
ft_void_t Ft_Gpu_PLL_FreqSelect(Ft_Gpu_Hal_Context_t *host,FT_GPU_PLL_FREQ_T freq);
ft_void_t Ft_Gpu_PowerModeSwitch(Ft_Gpu_Hal_Context_t *host,FT_GPU_POWER_MODE_T pwrmode);
ft_void_t Ft_Gpu_CoreReset(Ft_Gpu_Hal_Context_t *host);
ft_void_t Ft_Gpu_Hal_StartTransfer(Ft_Gpu_Hal_Context_t *host,FT_GPU_TRANSFERDIR_T rw,ft_uint32_t addr);
ft_void_t Ft_Gpu_Hal_WrMem(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, const ft_uint8_t *buffer, ft_uint32_t length);
ft_void_t Ft_Gpu_Hal_WrMemFromFlash(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr,const ft_prog_uchar8_t *buffer, ft_uint32_t length);
ft_void_t Ft_Gpu_Hal_WrCmdBufFromFlash(Ft_Gpu_Hal_Context_t *host,FT_PROGMEM ft_prog_uchar8_t *buffer,ft_uint16_t count);
ft_void_t Ft_Gpu_Hal_RdMem(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint8_t *buffer, ft_uint32_t length);
ft_void_t Ft_Gpu_Hal_WaitLogo_Finish(Ft_Gpu_Hal_Context_t *host);
ft_uint8_t    Ft_Gpu_Hal_TransferString(Ft_Gpu_Hal_Context_t *host,const ft_char8_t *string);
ft_void_t Ft_Gpu_HostCommand(ft_uint8_t cmd);
ft_int32_t Ft_Gpu_Hal_Dec2Ascii(ft_char8_t *pSrc,ft_int32_t value);

#endif  /*FT_GPU_HAL_H*/
