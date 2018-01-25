#include "bat_driver.h"
#include "eeprom_map.h"

//-----------------------------------------------
void rs485_bat_driver(void)
{
if(lc640_read_int(EE_BAT_LINK)==0)
	{
	char bb[30];
	bb[0]=0x7e;
	bb[1]=0x31;
	bb[2]=0x31;
	bb[3]=0x30;
	bb[4]=0x31;
	bb[5]=0x44;
	bb[6]=0x30;
	bb[7]=0x38;
	bb[8]=0x32;
	bb[9]=0x45;
	bb[10]=0x30;
	bb[11]=0x30;
	bb[12]=0x32;
	bb[13]=0x30;
	bb[14]=0x31;
	bb[15]=0x46;
	bb[16]=0x44;
	bb[17]=0x32;
	bb[18]=0x37;
	bb[19]=0x0d;

	uart_out_buff0 (bb, 20);
	}
}

//-----------------------------------------------
void rs485_bat_driver_init(void)
{
if(lc640_read_int(EE_BAT_LINK)==0)
	{
	UARTInit(0, 19200L);
	}
}