
#include "sc16is7xx.h"
#include <LPC17xx.H>
#include "main.h"
#include "modbus.h"
#include "stark.h"

short sc16is700ByteAvailable;
char sc16is700TxFifoLevel;
char tx_buffer_sc16is700[TX_BUFFER_SIZE_SC16IS700];//программный буфер передачи
char tx_wr_index_sc16is700;//указатель записи в программный буфер передачи
char tx_rd_index_sc16is700;//указатель чтения из программного буфера передачи
char sc16is700TxFifoEmptyCnt; //Временной счетчик свободности ФИФО передачи
char sc16is700TxPossibleFlag;//Флаг возможности передачи
char sc16is700RecieveDisableFlag;

//----------------------------------------------- 
//настройка SPI1
void sc16is700_spi_init(void)
{
SET_REG( LPC_PINCON->PINSEL0, 0, 0*2, 2);
SET_REG( LPC_PINCON->PINSEL0, 3, 15*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 0, (16-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 3, (17-16)*2, 2);
SET_REG( LPC_PINCON->PINSEL1, 3, (18-16)*2, 2); 
/*
S1SPCCR=100;
S1SPCR=0x3f; */

LPC_SPI->SPCCR=20;
LPC_SPI->SPCR=0x20;
}

//----------------------------------------------- 
//Отправка num байт из программного буфера передачи в sc16is700
void sc16is700_wr_buff(char reg_num,char num)
{
short i;
sc16is700_spi_init();
delay_us(2);
sc16is700_CS_ON 
spi1((reg_num&0x0f)<<3);
for (i=0;i<num;i++)spi1(tx_buffer_sc16is700[i]);
sc16is700_CS_OFF
}

void sc16is700_wr_byte(char reg_num,char data)
{
sc16is700_spi_init();
delay_us(2);
sc16is700_CS_ON
spi1((reg_num&0x0f)<<3);
spi1(data);
sc16is700_CS_OFF
}


char sc16is700_rd_byte(char reg_num)
{
char out;
sc16is700_spi_init();
delay_us(2);
sc16is700_CS_ON
spi1(((reg_num&0x0f)<<3)|0x80);
out = spi1(0xff);
sc16is700_CS_OFF
return out;
}

void sc16is700_init_(void)
{
sc16is700_wr_byte(CS16IS7xx_LCR, 0x80);
sc16is700_wr_byte(CS16IS7xx_DLL, 0x41);
sc16is700_wr_byte(CS16IS7xx_DLH, 0x00);
sc16is700_wr_byte(CS16IS7xx_LCR, 0xBF);
sc16is700_wr_byte(CS16IS7xx_EFR, 0X10);
sc16is700_wr_byte(CS16IS7xx_LCR, 0x03);
sc16is700_wr_byte(CS16IS7xx_FCR, 0x06);
sc16is700_wr_byte(CS16IS7xx_FCR, 0x01);
sc16is700_wr_byte(CS16IS7xx_EFCR, 0X30);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
}



void sc16is700_init(uint32_t baudrate)
{

unsigned char baud_h,baud_l;

baud_h = (char)((10000000U/16U/baudrate)>>8);
baud_l = (char)((10000000U/16U/baudrate)); 

sc16is700_wr_byte(CS16IS7xx_LCR, 0x80);
sc16is700_wr_byte(CS16IS7xx_DLL, baud_l);
sc16is700_wr_byte(CS16IS7xx_DLH, baud_h);
sc16is700_wr_byte(CS16IS7xx_LCR, 0xBF);
sc16is700_wr_byte(CS16IS7xx_EFR, 0X10);
sc16is700_wr_byte(CS16IS7xx_LCR, 0x03);
sc16is700_wr_byte(CS16IS7xx_FCR, 0x06);
sc16is700_wr_byte(CS16IS7xx_FCR, 0x01);
sc16is700_wr_byte(CS16IS7xx_EFCR, 0X30);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
//sc16is700_wr_byte(CS16IS7xx_DLH, 0x04);
}

/*
Void SC16IS752_Init_ChA (void) // program channel A for SPI-UART
{ // set 115200 baud, 8N1
SPI_wr_752 (LCR, 0x80, 0); // 0x80 to program baud rate
SPI_wr_752 (DLL, 0x08, 0); // 0x08 = 115.2K with X1 = 14.7456 MHz
SPI_wr_752 (DLM, 0x00, 0); // divisor = 0x0008 for 115200 bps
SPI_wr_752 (LCR, 0xBF, 0); // access EFR register
SPI_wr_752 (EFR, 0X10, 0); // enable enhanced registers
SPI_wr_752 (LCR, 0x03, 0); // 8 data bit, 1 stop bit, no parity
SPI_wr_752 (FCR, 0x01, 0); // enable FIFO mode
SPI_wr_752 (SPR, 'A', 0); // scratch pad = character A (0x41)
SPI_wr_752 (IODIR, 0xFF, 0); // set GPIO [7:0] to output
// (default: 0x00=input)
SPI_wr_752 (IOSTATE, 0x00, 0); // set GPIO [7:0] to 0x00 (LEDs on)
SPI_wr_752 (IER, 0x01, 0); // enable Rx data ready interrupt
}*/

//----------------------------------------------- 
//Посылка байта через sc16is700
void putchar_sc16is700(char out_byte)
{
tx_buffer_sc16is700[tx_wr_index_sc16is700]=out_byte;
if (++tx_wr_index_sc16is700 == TX_BUFFER_SIZE_SC16IS700) tx_wr_index_sc16is700=0;
}

//----------------------------------------------- 
//Отправка пакета через sc16is700
void sc16is700_out_buff(char* buff, char num)
{
char i;
for (i=0;i<num;i++)
	{
	putchar_sc16is700(buff[i]);
	}
}



//----------------------------------------------- 
//Обработчик sc16is700
void sc16is700_uart_hndl(void)
{

sc16is700ByteAvailable=sc16is700_rd_byte(CS16IS7xx_RXLVL); //Читаем состояние ФИФО приема микросхемы

if(sc16is700ByteAvailable) //Если в приемном ФИФО	микросхемы есть данные
	{
	short i;
	for(i=0;(i<sc16is700ByteAvailable)&&(i<5);i++) //Читаем их пачками не больше 5 в программный буфер 
		{
		if(!sc16is700RecieveDisableFlag)
			{
			char temp=sc16is700_rd_byte(CS16IS7xx_RHR);
			starkBatteryInBuff[starkBatteryInBuffPtr]=temp; 
			starkBatteryInBuffPtr++;

			modbus_timeout_cnt=0;   //Запускаем таймер опознавания конца посылки 
			}
		else sc16is700_rd_byte(CS16IS7xx_RHR);
		}
	}

/*if(sc16is700ByteAvailable)
	{
	short i;

	for(i=0;(i<sc16is700ByteAvailable)&&(i<5);i++)
		{
		char temp=sc16is700_rd_byte(CS16IS7xx_RHR);
		coslightBatteryInBuffPtr++;

		coslightBatteryInBuffPtr_plazma++;
		}
	}*/

sc16is700TxFifoLevel=sc16is700_rd_byte(CS16IS7xx_TXLVL);//Читаем состояние ФИФО передачи

if(sc16is700TxFifoLevel!=64) sc16is700TxFifoEmptyCnt=0;//Если ФИФО не пустой обнуляем счетчик свободности ФИФО передачи
if(sc16is700TxFifoLevel==64) //если ФИФО пустой то плюсуем счетчик если он меньше константы
	{
	if(sc16is700TxFifoEmptyCnt<SC16IS700TXFIFOEMPTYCNTMAX)sc16is700TxFifoEmptyCnt++;
	}
if(sc16is700TxFifoEmptyCnt==SC16IS700TXFIFOEMPTYCNTMAX) sc16is700TxPossibleFlag=1;//Если счетчик сравнялся с константой поднимаем флаг возможности передачи
else sc16is700TxPossibleFlag=0;//Если не сравнялся - флаг сбрасываем.


if((tx_wr_index_sc16is700)&&(tx_wr_index_sc16is700!=tx_rd_index_sc16is700)) //Если программный буфер передачи не пуст
	{
	if(sc16is700TxPossibleFlag)//проверяем возможность передачи
		{
		//char i;
		//for(;tx_rd_index_sc16is700++;tx_rd_index_sc16is700<=tx_wr_index_sc16is700)
			//{
		sc16is700RecieveDisableFlag=1;
		sc16is700_wr_buff(CS16IS7xx_THR, tx_wr_index_sc16is700);
			//}
		tx_wr_index_sc16is700=0;
		}
	}

if((sc16is700_rd_byte(CS16IS7xx_LSR))&0x40)	sc16is700RecieveDisableFlag=0;


}
