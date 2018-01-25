#include "FT_DataTypes.h"
#include "FT_Platform.h"
#include "riverdi.h"
#include "LPC17xx.H"
#include "main.h"

unsigned char SPI_SendByte(unsigned char data);

/* API to initialize the SPI interface */
ft_bool_t  Ft_Gpu_Hal_Init( void )
{
/*	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_StructInit(&GPIO_InitStruct);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	//Chip Select Pin
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Power Down Pin
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// INT Pin
	GPIO_StructInit(&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_WriteBit(PD_PORT,PD_PIN,Bit_SET);
	// Deselect the FT800: Chip Select high
	GPIO_WriteBit(CS_PORT,CS_PIN,Bit_SET); */

	//return TRUE;
}

//#ifdef FT_81X_ENABLE
//This API can only be called when PLL is stopped(SLEEP mode).  For compatibility, set frequency to the FT_GPU_12MHZ option in the FT_GPU_SETPLLSP1_T table.
ft_void_t Ft_Gpu_81X_SelectSysCLK(Ft_Gpu_Hal_Context_t *host, FT_GPU_81X_PLL_FREQ_T freq){
		if(FT_GPU_SYSCLK_72M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x40 << 8) | (0x06 << 8));
		else if(FT_GPU_SYSCLK_60M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x40 << 8) | (0x05 << 8));
		else if(FT_GPU_SYSCLK_48M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x40 << 8) | (0x04 << 8));
		else if(FT_GPU_SYSCLK_36M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x03 << 8));
		else if(FT_GPU_SYSCLK_24M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x02 << 8));
		else if(FT_GPU_SYSCLK_DEFAULT == freq)//default clock
			Ft_Gpu_HostCommand_Ext3(host, 0x61);
}
//#endif

ft_void_t Ft_Gpu_HostCommand_Ext3(Ft_Gpu_Hal_Context_t *host,ft_uint32_t cmd)
{
/*	#ifdef FT900_PLATFORM
		ft_uint8_t hcmd[4] = {0};
		hcmd[0] = cmd & 0xff;
		hcmd[1] = (cmd>>8) & 0xff;
		hcmd[2] = (cmd>>16) & 0xff;
		hcmd[3] = 0;
		dqspiEnableSS(SPIM,FT800_SEL_PIN);
		dqspiWritePool(SPIM, hcmd, 3,DQSPI_M_DISCARD_INCOMING_DATA);
		dqspiDisableSS(SPIM,FT800_SEL_PIN);
	#endif
	#ifdef MSVC_PLATFORM_SPI
	  ft_uint8_t Transfer_Array[3];
	  ft_uint32_t SizeTransfered;

	  Transfer_Array[0] = cmd;
	  Transfer_Array[1] = (cmd>>8) & 0xff;
	  Transfer_Array[2] = (cmd>>16) & 0xff;

	  SPI_Write(host->hal_handle,Transfer_Array,sizeof(Transfer_Array),&SizeTransfered,SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES | SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE | SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE);
	#endif
	#ifdef ARDUINO_PLATFORM_SPI
	  digitalWrite(FT_ARDUINO_PRO_SPI_CS, LOW);
	  SPI.transfer(cmd);
	  SPI.transfer((cmd>>8) & 0xff);
	  SPI.transfer((cmd>>16) & 0xff);
	  digitalWrite(FT_ARDUINO_PRO_SPI_CS, HIGH);
	#endif
	#ifdef MSVC_FT800EMU
	  //Not implemented in FT800EMU
	#endif

	  GPIO_WriteBit(CS_PORT, CS_PIN, 0);
	  SPI_SendByte(cmd);
	  SPI_SendByte((cmd>>8) & 0xff);
	  SPI_SendByte((cmd>>16) & 0xff);
	  GPIO_WriteBit(CS_PORT, CS_PIN, 1);  */
}

#ifdef NOTPAVLIK
ft_bool_t    Ft_Gpu_Hal_Open( void )
{


	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/* SPI Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	/* Configure SPI pins: SCK */
	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	   GPIO_Init(GPIOA, &GPIO_InitStructure);

	   /* Configure SPI pins: MISO */
	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	   GPIO_Init(GPIOA, &GPIO_InitStructure);

	   /* Configure SPI pins: MOSI */
	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	   GPIO_Init(GPIOA, &GPIO_InitStructure);

	   /* Configure SPI_CS_PIN pin:  CS pin */
	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	   GPIO_Init(GPIOA, &GPIO_InitStructure);


   /* Connect PXx to SPI_SCK */
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);

	   /* Connect PXx to SD_SPI_MISO */
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);

   /* Connect PXx to SD_SPI_MOSI */
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);

	   /* SPI configuration -------------------------------------------------------*/
	   SPI_I2S_DeInit(SPI1);

	   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

	   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	   SPI_InitStructure.SPI_CRCPolynomial = 7;
	   SPI_Init(SPI1, &SPI_InitStructure);

	   SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);

	   SPI_Cmd(SPI1, ENABLE); /* SD_SPI enable */





	return TRUE;
}
#endif

ft_void_t  Ft_Gpu_Hal_Close(Ft_Gpu_Hal_Context_t *host)
{
	host->status = FT_GPU_HAL_CLOSED;
#ifdef MSVC_PLATFORM_SPI
	/* Close the channel*/
	SPI_CloseChannel(host->hal_handle);
#endif
#ifdef ARDUINO_PLATFORM_SPI
        SPI.end();
#endif
#ifdef STM32F4XX
SPI_Cmd(SPI2, DISABLE);

#endif
#ifdef STM32F031C6
SPI_Cmd(SPI1, DISABLE);

#endif
}

ft_void_t Ft_Gpu_Hal_DeInit()
{
#ifdef MSVC_PLATFORM_SPI
   //Cleanup the MPSSE Lib
   Cleanup_libMPSSE();
#endif
}

/*The APIs for reading/writing transfer continuously only with small buffer system*/
ft_void_t  Ft_Gpu_Hal_StartTransfer(Ft_Gpu_Hal_Context_t *host,FT_GPU_TRANSFERDIR_T rw,ft_uint32_t addr)
{
	if (FT_GPU_READ == rw){

		RIV_CS_ON
		spi1((char)((addr>>16)&0x3f));
		spi1((char)((addr>>8)&0xff));
		spi1((char)((addr)&0xff));
		spi1((char)(0x55));

		host->status = FT_GPU_HAL_READING;
	}else{

		RIV_CS_ON
		spi1((char)(((addr>>16)&0x3f)|0x80));
		spi1((char)((addr>>8)&0xff));
		spi1((char)((addr)&0xff));

		host->status = FT_GPU_HAL_WRITING;
	}
}



/*The APIs for writing transfer continuously only*/
ft_void_t  Ft_Gpu_Hal_StartCmdTransfer(Ft_Gpu_Hal_Context_t *host,FT_GPU_TRANSFERDIR_T rw, ft_uint16_t count)
{
	Ft_Gpu_Hal_StartTransfer(host,rw,host->ft_cmd_fifo_wp + RAM_CMD);
}

ft_uint8_t    Ft_Gpu_Hal_TransferString(Ft_Gpu_Hal_Context_t *host,const ft_char8_t *string)
{
    ft_uint16_t length = strlen(string);
    while(length --){
       Ft_Gpu_Hal_Transfer8(host,*string);
       string ++;
    }
    //Append one null as ending flag
    Ft_Gpu_Hal_Transfer8(host,0);
}


ft_uint8_t    Ft_Gpu_Hal_Transfer8(Ft_Gpu_Hal_Context_t *host,ft_uint8_t value)
{
return spi1(value);
}


ft_uint16_t  Ft_Gpu_Hal_Transfer16(Ft_Gpu_Hal_Context_t *host,ft_uint16_t value)
{
	ft_uint16_t retVal = 0;

        if (host->status == FT_GPU_HAL_WRITING){
		Ft_Gpu_Hal_Transfer8(host,value & 0xFF);//LSB first
		Ft_Gpu_Hal_Transfer8(host,(value >> 8) & 0xFF);
	}else{
		retVal = Ft_Gpu_Hal_Transfer8(host,0);
		retVal |= (ft_uint16_t)Ft_Gpu_Hal_Transfer8(host,0) << 8;
	}

	return retVal;
}
ft_uint32_t  Ft_Gpu_Hal_Transfer32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t value)
{
	ft_uint32_t retVal = 0;
	if (host->status == FT_GPU_HAL_WRITING){
		Ft_Gpu_Hal_Transfer16(host,value & 0xFFFF);//LSB first
		Ft_Gpu_Hal_Transfer16(host,(value >> 16) & 0xFFFF);
	}else{
		retVal = Ft_Gpu_Hal_Transfer16(host,0);
		retVal |= (ft_uint32_t)Ft_Gpu_Hal_Transfer16(host,0) << 16;
	}
	return retVal;
}

ft_void_t   Ft_Gpu_Hal_EndTransfer(Ft_Gpu_Hal_Context_t *host)
{
#ifdef MSVC_PLATFORM_SPI
	//just disbale the CS - send 0 bytes with CS disable
	SPI_ToggleCS((FT_HANDLE)host->hal_handle,FALSE);
#endif
#ifdef ARDUINO_PLATFORM_SPI
	digitalWrite(FT_ARDUINO_PRO_SPI_CS, HIGH);
#endif
#if defined (STM32F4XX) || defined (STM32F031C6)
	GPIO_WriteBit(CS_PORT, CS_PIN, 1);
#endif

	RIV_CS_OFF
	host->status = FT_GPU_HAL_OPENED;
}


ft_uint8_t  Ft_Gpu_Hal_Rd8(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr)
{
	ft_uint8_t value;
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);
	value = Ft_Gpu_Hal_Transfer8(host,0);
	Ft_Gpu_Hal_EndTransfer(host);
	return value;
}
ft_uint16_t Ft_Gpu_Hal_Rd16(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr)
{
	ft_uint16_t value;
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);
	value = Ft_Gpu_Hal_Transfer16(host,0);
	Ft_Gpu_Hal_EndTransfer(host);
	RIV_CS_OFF
	return value;
}
ft_uint32_t Ft_Gpu_Hal_Rd32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr)
{
	ft_uint32_t value;
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);
	value = Ft_Gpu_Hal_Transfer32(host,0);
	Ft_Gpu_Hal_EndTransfer(host);
	return value;
}

ft_void_t Ft_Gpu_Hal_Wr8(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint8_t v)
{	
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);
	Ft_Gpu_Hal_Transfer8(host,v);
	Ft_Gpu_Hal_EndTransfer(host);
}
ft_void_t Ft_Gpu_Hal_Wr16(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint16_t v)
{
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);
	Ft_Gpu_Hal_Transfer16(host,v);
	Ft_Gpu_Hal_EndTransfer(host);
}
ft_void_t Ft_Gpu_Hal_Wr32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint32_t v)
{
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);
	Ft_Gpu_Hal_Transfer32(host,v);
	Ft_Gpu_Hal_EndTransfer(host);
}

#ifdef NOTPAVLIK
ft_void_t Ft_Gpu_HostCommand(ft_uint8_t cmd)
{


  GPIO_WriteBit(CS_PORT, CS_PIN, 0);
  SPI_SendByte(cmd);
  SPI_SendByte(0x00);
  SPI_SendByte(0x00);
  GPIO_WriteBit(CS_PORT, CS_PIN, 1);



}
#endif
ft_void_t Ft_Gpu_Hal_Updatecmdfifo(Ft_Gpu_Hal_Context_t *host,ft_uint16_t count)
{
	host->ft_cmd_fifo_wp  = (host->ft_cmd_fifo_wp + count) & 4095;

	//4 byte alignment
	host->ft_cmd_fifo_wp = (host->ft_cmd_fifo_wp + 3) & 0xffc;
	Ft_Gpu_Hal_Wr16(host,REG_CMD_WRITE,host->ft_cmd_fifo_wp);
}

ft_uint16_t Ft_Gpu_Cmdfifo_Freespace(Ft_Gpu_Hal_Context_t *host)
{
	ft_uint16_t fullness,retval;
	
	fullness = (host->ft_cmd_fifo_wp - Ft_Gpu_Hal_Rd16(host,REG_CMD_READ)) & 4095;
	retval = (FT_CMD_FIFO_SIZE - 4) - fullness;
	return (retval);
}
/*
ft_uint16_t Ft_Gpu_Cmdfifo_Freespace_(Ft_Gpu_Hal_Context_t *host)
{
	ft_uint16_t fullness,retval;
	ft_plazma= Ft_Gpu_Hal_Rd16(host,REG_CMD_READ);

	fullness = (host->ft_cmd_fifo_wp - Ft_Gpu_Hal_Rd16(host,REG_CMD_READ)) & 4095;
	retval = (FT_CMD_FIFO_SIZE - 4) - fullness;
	return (retval);
}
*/
ft_void_t Ft_Gpu_Hal_WrCmdBuf(Ft_Gpu_Hal_Context_t *host,ft_uint8_t *buffer,ft_uint16_t count)
{
ft_uint32_t length =0, SizeTransfered = 0;   

#define MAX_CMD_FIFO_TRANSFER   Ft_Gpu_Cmdfifo_Freespace(host)  
do {
	length = count;                
	if (length > MAX_CMD_FIFO_TRANSFER)
		{
		length = MAX_CMD_FIFO_TRANSFER;
		}		
	
    Ft_Gpu_Hal_CheckCmdBuffer(host,length);

    Ft_Gpu_Hal_StartCmdTransfer(host,FT_GPU_WRITE,length);

    SizeTransfered = 0;
	while (length--) 
		{
        Ft_Gpu_Hal_Transfer8(host,*buffer);
		buffer++;
        SizeTransfered ++;
		}
   	length = SizeTransfered;

	Ft_Gpu_Hal_EndTransfer(host);
	Ft_Gpu_Hal_Updatecmdfifo(host,length);

	Ft_Gpu_Hal_WaitCmdfifo_empty(host);
	count -= length;
	}
while (count > 0);
}

//#ifdef ARDUINO_PLATFORM_SPI
#if defined  (STM32F4XX) || defined (STM32F031C6)
//#ifdef  (STM32F031C6)
ft_void_t Ft_Gpu_Hal_WrCmdBufFromFlash(Ft_Gpu_Hal_Context_t *host,FT_PROGMEM ft_prog_uchar8_t *buffer,ft_uint16_t count)
{
	ft_uint32_t length =0, SizeTransfered = 0;   

#define MAX_CMD_FIFO_TRANSFER   Ft_Gpu_Cmdfifo_Freespace(host)  
	do {                
		length = count;
		if (length > MAX_CMD_FIFO_TRANSFER){
		    length = MAX_CMD_FIFO_TRANSFER;
		}
      	        Ft_Gpu_Hal_CheckCmdBuffer(host,length);

                Ft_Gpu_Hal_StartCmdTransfer(host,FT_GPU_WRITE,length);


                SizeTransfered = 0;
		while (length--) {
                    Ft_Gpu_Hal_Transfer8(host,ft_pgm_read_byte_near(buffer));
		    buffer++;
                    SizeTransfered ++;
		}
                length = SizeTransfered;

    	        Ft_Gpu_Hal_EndTransfer(host);
		Ft_Gpu_Hal_Updatecmdfifo(host,length);

		Ft_Gpu_Hal_WaitCmdfifo_empty(host);

		count -= length;
	}while (count > 0);
}
#endif


ft_void_t Ft_Gpu_Hal_CheckCmdBuffer(Ft_Gpu_Hal_Context_t *host,ft_uint16_t count)
{
   ft_uint16_t getfreespace;
   do{
        getfreespace = Ft_Gpu_Cmdfifo_Freespace(host);
   }while(getfreespace < count);
}

/*
ft_void_t Ft_Gpu_Hal_CheckCmdBuffer_(Ft_Gpu_Hal_Context_t *host,ft_uint16_t count)
{
   ft_uint16_t getfreespace;
   do{
        getfreespace = Ft_Gpu_Cmdfifo_Freespace_(host);
   }while(getfreespace < count);
}*/

ft_void_t Ft_Gpu_Hal_WaitCmdfifo_empty(Ft_Gpu_Hal_Context_t *host)
{
   while(Ft_Gpu_Hal_Rd16(host,REG_CMD_READ) != Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE));
   
   host->ft_cmd_fifo_wp = Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE);
}

ft_void_t Ft_Gpu_Hal_WaitLogo_Finish(Ft_Gpu_Hal_Context_t *host)
{
    ft_int16_t cmdrdptr,cmdwrptr;

    do{
         cmdrdptr = Ft_Gpu_Hal_Rd16(host,REG_CMD_READ);
         cmdwrptr = Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE);
    }while ((cmdwrptr != cmdrdptr) || (cmdrdptr != 0));
    host->ft_cmd_fifo_wp = 0;
}


ft_void_t Ft_Gpu_Hal_ResetCmdFifo(Ft_Gpu_Hal_Context_t *host)
{
   host->ft_cmd_fifo_wp = 0;
}


ft_void_t Ft_Gpu_Hal_WrCmd32(Ft_Gpu_Hal_Context_t *host,ft_uint32_t cmd)
{
         Ft_Gpu_Hal_CheckCmdBuffer(host,sizeof(cmd));
      
         Ft_Gpu_Hal_Wr32(host,RAM_CMD + host->ft_cmd_fifo_wp,cmd);
      
         Ft_Gpu_Hal_Updatecmdfifo(host,sizeof(cmd));
}


ft_void_t Ft_Gpu_Hal_ResetDLBuffer(Ft_Gpu_Hal_Context_t *host)
{
           host->ft_dl_buff_wp = 0;
}
#ifdef NOTPAVLIK
/* Toggle PD_N pin of FT800 board for a power cycle*/
ft_void_t Ft_Gpu_Hal_Powercycle(ft_bool_t up)
{
	if (up)
	{

            GPIO_WriteBit(PD_PORT, PD_PIN, 0);
            Ft_Gpu_Hal_Sleep(20);
            //while(1);
            GPIO_WriteBit(PD_PORT, PD_PIN, 1);
            Ft_Gpu_Hal_Sleep(20);

	}else
	{

            GPIO_WriteBit(PD_PORT, PD_PIN, 1);
            Ft_Gpu_Hal_Sleep(20);
            GPIO_WriteBit(PD_PORT, PD_PIN, 0);
            Ft_Gpu_Hal_Sleep(20);

	}
}
#endif

ft_void_t Ft_Gpu_Hal_WrMemFromFlash(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr,const ft_prog_uchar8_t *buffer, ft_uint32_t length)
{
	ft_uint32_t SizeTransfered = 0;      

	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);

	while (length--) {
            Ft_Gpu_Hal_Transfer8(host,ft_pgm_read_byte_near(buffer));
	    buffer++;
	}

	Ft_Gpu_Hal_EndTransfer(host);
}

ft_void_t Ft_Gpu_Hal_WrMem(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr,const ft_uint8_t *buffer, ft_uint32_t length)
{
	ft_uint32_t SizeTransfered = 0;      

	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);

#if defined(ARDUINO_PLATFORM) || defined (STM32F4XX) || defined (STM32F031C6)
	while (length--) {
            Ft_Gpu_Hal_Transfer8(host,*buffer);
	    buffer++;
	}
#endif

#ifdef MSVC_PLATFORM_SPI
	{
	    SPI_Write((FT_HANDLE)host->hal_handle,buffer,length,&SizeTransfered,SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
	}
#endif


	Ft_Gpu_Hal_EndTransfer(host);
}


ft_void_t Ft_Gpu_Hal_RdMem(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr, ft_uint8_t *buffer, ft_uint32_t length)
{
	ft_uint32_t SizeTransfered = 0;      

	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);

#if defined(ARDUINO_PLATFORM) || defined (STM32F4XX) || defined (STM32F031C6)
	while (length--) {
	   *buffer = Ft_Gpu_Hal_Transfer8(host,0);
	   buffer++;
	}
#endif

#ifdef MSVC_PLATFORM_SPI
	{
	   SPI_Read((FT_HANDLE)host->hal_handle,buffer,length,&SizeTransfered,SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
	}
#endif

	Ft_Gpu_Hal_EndTransfer(host);
}

ft_int32_t Ft_Gpu_Hal_Dec2Ascii(ft_char8_t *pSrc,ft_int32_t value)
{
	ft_int16_t Length;
	ft_char8_t *pdst,charval;
	ft_int32_t CurrVal = value,tmpval,i;
	ft_char8_t tmparray[16],idx = 0;

	Length = strlen(pSrc);
	pdst = pSrc + Length;

	if(0 == value)
	{
		*pdst++ = '0';
		*pdst++ = '\0';
		return 0;
	}

	if(CurrVal < 0)
	{
		*pdst++ = '-';
		CurrVal = - CurrVal;
	}
	/* insert the value */
	while(CurrVal > 0){
		tmpval = CurrVal;
		CurrVal /= 10;
		tmpval = tmpval - CurrVal*10;
		charval = '0' + tmpval;
		tmparray[idx++] = charval;
	}

	for(i=0;i<idx;i++)
	{
		*pdst++ = tmparray[idx - i - 1];
	}
	*pdst++ = '\0';

	return 0;
}



ft_void_t Ft_Gpu_Hal_Sleep(ft_uint16_t ms)
{
#ifdef MSVC_PLATFORM
	Sleep(ms);
#endif
#if defined(ARDUINO_PLATFORM) || defined(STM32F4XX) || defined(STM32F031C6)
	delay(ms);
#endif
}
#ifdef STM32F4XX
unsigned char SPI_SendByte(unsigned char data)
{
  // Loop while DR register in not emplty
  while(SPI_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET);

  // Send byte through the  peripheral
  SPI_SendData(SPI2, data);

  // Wait to receive a byte
  while(SPI_GetFlagStatus(SPI2, SPI_FLAG_RXNE) == RESET);

  // Return the byte read from the SPI bus
  return SPI_ReceiveData(SPI2);
}
#endif

#ifdef STM32F031C6
unsigned char SPI_SendByte(unsigned char data)
{
	  /* Wait until the transmit buffer is empty */
	   while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	   {
	   }

	   /* Send the byte */
	   SPI_SendData8(SPI1, data);

	   /* Wait to receive a byte*/
	   while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
	   {
	   }

	   /* Return the byte read from the SPI bus */
	   return SPI_ReceiveData8(SPI1);

}
#endif

#ifdef NOTPAVLIK
void delay(uint32_t ms)
{
#ifdef STM32F4XX
#define STM32_CLOCK_HZ 72000000UL
#define STM32_CYCLES_PER_LOOP 6 // This will need tweaking or calculating
    ms *= STM32_CLOCK_HZ / 1000 / STM32_CYCLES_PER_LOOP;



    asm volatile(" mov r0, %[ms] \n\t"
             "1: subs r0, #1 \n\t"
             " bhi 1b \n\t"
             :
             : [ms] "r" (ms)
             : "r0");
#endif
#ifdef STM32F031C6
#define STM32_CLOCK_HZ 8000000UL
#define STM32_CYCLES_PER_LOOP 40 // This will need tweaking or calculating
    __IO uint32_t index = 0;
       for(index = ((STM32_CLOCK_HZ / 1000 / STM32_CYCLES_PER_LOOP) * ms); index != 0; index--)
       {
       }
#endif
}
#endif
