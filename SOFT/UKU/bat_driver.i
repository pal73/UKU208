#line 1 "bat_driver.c"
#line 1 "bat_driver.h"

void rs485_bat_driver(void);

void rs485_bat_driver_init(void);
#line 2 "bat_driver.c"
#line 1 "eeprom_map.h"






#line 34 "eeprom_map.h"



#line 134 "eeprom_map.h"



#line 151 "eeprom_map.h"



#line 163 "eeprom_map.h"


#line 174 "eeprom_map.h"



#line 185 "eeprom_map.h"



#line 241 "eeprom_map.h"


#line 283 "eeprom_map.h"








#line 305 "eeprom_map.h"







































































































extern const unsigned short ADR_EE_BAT_ZAR_CNT[2];
extern const unsigned short ADR_EE_BAT_ZAR_CNT_KE[2];
extern const unsigned short ADR_EE_BAT_C_NOM[2];
extern const unsigned short ADR_EE_BAT_YEAR_OF_ON[2];
extern const unsigned short ADR_EE_BAT_IS_ON[2];
extern const unsigned short ADR_EE_BAT_DAY_OF_ON[2];
extern const unsigned short ADR_EE_BAT_MONTH_OF_ON[2];
extern const unsigned short ADR_EE_BAT_RESURS[2];
extern const unsigned short ADR_EE_BAT_C_REAL[2];
extern const unsigned short ADR_EE_BAT_TYPE[2];
extern const unsigned short ADR_KUBAT[2];
extern const unsigned short ADR_KUBATM[2];
extern const unsigned short ADR_KI0BAT[2];
extern const unsigned short ADR_KI1BAT[2];
extern const unsigned short ADR_KTBAT[2];
extern const unsigned short ADR_EE_BAT_TYPE[2];


extern const unsigned short ADR_TMAX_EXT_EN[3];
extern const unsigned short ADR_TMAX_EXT[3];
extern const unsigned short ADR_TMIN_EXT_EN[3];
extern const unsigned short ADR_TMIN_EXT[3];
extern const unsigned short ADR_T_EXT_REL_EN[3];
extern const unsigned short ADR_T_EXT_ZVUK_EN[3];
extern const unsigned short ADR_T_EXT_LCD_EN[3];
extern const unsigned short ADR_T_EXT_RS_EN[3];

extern const unsigned short ADR_SK_SIGN[4];
extern const unsigned short ADR_SK_REL_EN[4];
extern const unsigned short ADR_SK_ZVUK_EN[4];
extern const unsigned short ADR_SK_LCD_EN[4];
extern const unsigned short ADR_SK_RS_EN[4];

#line 3 "bat_driver.c"


void rs485_bat_driver(void)
{
if(lc640_read_int(0x10+500+200+76)==0)
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


void rs485_bat_driver_init(void)
{
if(lc640_read_int(0x10+500+200+76)==0)
	{
	UARTInit(0, 19200L);
	}
}
