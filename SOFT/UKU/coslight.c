#include "coslight.h"

char portForCoslightBatteryIsInitiated=0;
char coslightBatteryHndlPhase;
char coslightBatteryInBuff[400];
short coslightBatteryInBuffPtr;
char coslightRequestPhase;
short coslightSilentCnt;
char bCoslightPacketIn;
short coslightBatteryInBuffPtr_plazma;

void coslight_bat_hndl(void)
{

if(portForCoslightBatteryIsInitiated==0)
	{
	sc16is700_init(19200UL);
	portForCoslightBatteryIsInitiated=1;
	}

coslightBatteryHndlPhase++;

if(coslightBatteryHndlPhase==5)
	{
	char coslightButteryOutBuff[]={0x7e,0x31,0x31,0x30,0x31,0x44,0x30,0x38,0x32,0x45,0x30,0x30,0x32,0x30,0x31,0x46,0x44,0x32,0x37,0x0d};
	sc16is700_out_buff(coslightButteryOutBuff,20);
	coslightRequestPhase=0;

	if(coslightSilentCnt<10) coslightSilentCnt++;
	coslightBatteryInBuffPtr_plazma=0;
	coslightBatteryInBuffPtr=0;
	}
else if(coslightBatteryHndlPhase==10)
	{
	char coslightButteryOutBuff[]={0x7e,0x31,0x31,0x30,0x31,0x44,0x30,0x38,0x33,0x45,0x30,0x30,0x32,0x30,0x31,0x46,0x44,0x32,0x36,0x0d};
	sc16is700_out_buff(coslightButteryOutBuff,20);
	coslightRequestPhase=1;
	coslightBatteryHndlPhase=0;

	if(coslightSilentCnt<10) coslightSilentCnt++;

	}





}


//-----------------------------------------------
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