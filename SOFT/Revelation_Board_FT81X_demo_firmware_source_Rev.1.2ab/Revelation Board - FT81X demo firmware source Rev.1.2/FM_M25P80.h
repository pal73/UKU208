/*
 * FM_EN25Q64.h
 *
 *  Created on: Oct 2, 2013
 *      Author: user
 */

#ifndef FM_M25P80_H_
#define FM_M25P80_H_

#include "stm32f0xx.h"
#include "stm32f0xx_spi.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

#define Low     0x00  /* Chip Select line low */
#define High    0x01  /* Chip Select line high */

#define u32 unsigned int
#define u8 unsigned char
#define u16 unsigned short int

void SPI_FLASH_Init(void);
void SPI_FLASH_SectorErase(unsigned int SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
u32 SPI_FLASH_ReadID(void);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);

/*----- Low layer function -----*/
u8 SPI_FLASH_ReadByte(void);
void SPI_FLASH_ChipSelect(u8 State);
u8 SPI_FLASH_SendByte(u8 byte);
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);

#endif /* FM_M25P80_H_ */
