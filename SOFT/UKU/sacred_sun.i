#line 1 "sacred_sun.c"
#line 1 "sacred_sun.h"

extern char portForSacredSunBatteryIsInitiated;
extern char sacredSunBatteryHndlPhase;
extern char liBatteryInBuff[300];
extern char sacredSunRequestPhase;
extern short sacredSunSilentCnt;

void sacred_san_bat_hndl(void);
short ascii2halFhex(char in);
#line 2 "sacred_sun.c"

char portForSacredSunBatteryIsInitiated=0;
char sacredSunBatteryHndlPhase;
char liBatteryInBuff[300];
char sacredSunRequestPhase;
short sacredSunSilentCnt;

void sacred_san_bat_hndl(void)
{

if(portForSacredSunBatteryIsInitiated==0)
	{
	UARTInit(0, 1200);	 
	portForSacredSunBatteryIsInitiated=1;
	}

sacredSunBatteryHndlPhase++;

if(sacredSunBatteryHndlPhase==5)
	{
	char sacredSunButteryOutBuff[]={0x7e,0x32,0x35,0x30,0x31,0x34,0x36,0x34,0x32,0x45,0x30,0x30,0x32,0x30,0x31,0x46,0x44,0x33,0x30,0x0d};
	uart_out_buff0(sacredSunButteryOutBuff,20);
	sacredSunRequestPhase=0;

	if(sacredSunSilentCnt<10) sacredSunSilentCnt++;
	
	}
else if(sacredSunBatteryHndlPhase==10)
	{
	char sacredSunButteryOutBuff[]={0x7e,0x32,0x35,0x30,0x31,0x34,0x36,0x34,0x34,0x45,0x30,0x30,0x32,0x30,0x31,0x46,0x44,0x32,0x45,0x0d};
	uart_out_buff0(sacredSunButteryOutBuff,20);
	sacredSunRequestPhase=1;
	sacredSunBatteryHndlPhase=0;

	if(sacredSunSilentCnt<10) sacredSunSilentCnt++;

	}

}



short ascii2halFhex(char in)
{
if(isalnum(in))
	{
	if(isdigit(in))
		{
		return (short)(in-'0');
		}
	if(islower(in))
		{
		return (short)(in-'a'+10);
		}
	if(isupper(in))
		{
		return (short)(in-'A'+10);
		}
	}
}
