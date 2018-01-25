#include "ztt.h"
#include "main.h"

char portForZTTBatteryIsInitiated=0;
char zTTBatteryHndlPhase;
//char zTTBatteryInBuff[300];
char zTTRequestPhase;
short zTTSilentCnt[3];
char zTTButteryCnter=0;
char zTTBatteryHndlCmnd;



#ifdef UKU_TELECORE2015

#ifdef UKU_TELECORE2016 
void ztt_bat_hndl_can(void)
{
zTTBatteryHndlPhase++;

if(zTTBatteryHndlPhase==5)	
	{
	if(zTTButteryCnter==0)
		{
		zTTBatteryHndlCmnd=0x11;
		zTTSilentCnt[0]=10;
		}
	else if(zTTButteryCnter==1)
		{
		zTTBatteryHndlCmnd=0x21;
		zTTSilentCnt[1]=10;
		}
	else if(zTTButteryCnter==2)
		{
		zTTBatteryHndlCmnd=0x31;
		zTTSilentCnt[2]=10;
		}
	zTTRequestPhase=0;
	}
else if(zTTBatteryHndlPhase==10)
	{
	if(zTTButteryCnter==0)
		{
		zTTBatteryHndlCmnd=0x12;
		zTTSilentCnt[0]=10;
		}
	else if(zTTButteryCnter==1)
		{
		zTTBatteryHndlCmnd=0x22;
		zTTSilentCnt[1]=10;
		}
	else if(zTTButteryCnter==2)
		{
		zTTBatteryHndlCmnd=0x32;
		zTTSilentCnt[2]=10;
		}

	zTTRequestPhase=1;

	zTTBatteryHndlPhase=0;
	
	zTTButteryCnter++;
	if(zTTButteryCnter>=NUMBAT_TELECORE)zTTButteryCnter=0;

	}

}
#else
void ztt_bat_hndl(void)
{

if(portForZTTBatteryIsInitiated==0)
	{
	UARTInit(0, 9600);	/* baud rate setting */
	portForZTTBatteryIsInitiated=1;
	}

zTTBatteryHndlPhase++;

if((zTTSilentCnt[0])&&(zTTSilentCnt[0]<=10))zTTSilentCnt[0]--;
if((zTTSilentCnt[1])&&(zTTSilentCnt[1]<=10))zTTSilentCnt[1]--;
if((zTTSilentCnt[2])&&(zTTSilentCnt[2]<=10))zTTSilentCnt[2]--;

if(zTTBatteryHndlPhase==5)	//7E 32 36 30 30 34 36 34 32 45 30 30 32 30 31 46 44 33 30 0D
	{
	if(zTTButteryCnter==0)
		{
		char zTTButteryOutBuff[]={0x7e,0x32,0x36,0x30,0x30,0x34,0x36,0x34,0x32,0x45,0x30,0x30,0x32,0x30,0x31,0x46,0x44,0x33,0x30,0x0d};
		uart_out_buff0(zTTButteryOutBuff,20);
		zTTSilentCnt[0]=10;
		}
	else if(zTTButteryCnter==1)
		{
		char zTTButteryOutBuff[]={0x7e,0x32,0x36,0x30,0x30,0x34,0x36,0x34,0x32,0x45,0x30,0x30,0x32,0x30,0x32,0x46,0x44,0x32,0x46,0x0d};
		uart_out_buff0(zTTButteryOutBuff,20);
		zTTSilentCnt[1]=10;
		}
	else if(zTTButteryCnter==2)
		{
		char zTTButteryOutBuff[]={0x7e,0x32,0x36,0x30,0x30,0x34,0x36,0x34,0x32,0x45,0x30,0x30,0x32,0x30,0x33,0x46,0x44,0x32,0x45,0x0d};
		uart_out_buff0(zTTButteryOutBuff,20);
		zTTSilentCnt[2]=10;
		}

	zTTRequestPhase=0;

	}
else if(zTTBatteryHndlPhase==10)
	{
	if(zTTButteryCnter==0)
		{
		char zTTButteryOutBuff[]={0x7e,0x32,0x36,0x30,0x30,0x34,0x36,0x34,0x34,0x45,0x30,0x30,0x32,0x30,0x31,0x46,0x44,0x32,0x45,0x0d};
		uart_out_buff0(zTTButteryOutBuff,20);
		zTTSilentCnt[0]=10;
		}
	else if(zTTButteryCnter==1)
		{
		char zTTButteryOutBuff[]={0x7e,0x32,0x36,0x30,0x30,0x34,0x36,0x34,0x34,0x45,0x30,0x30,0x32,0x30,0x32,0x46,0x44,0x32,0x44,0x0d};
		uart_out_buff0(zTTButteryOutBuff,20);
		zTTSilentCnt[1]=10;
		}
	else if(zTTButteryCnter==2)
		{
		char zTTButteryOutBuff[]={0x7e,0x32,0x36,0x30,0x30,0x34,0x36,0x34,0x34,0x45,0x30,0x30,0x32,0x30,0x33,0x46,0x44,0x32,0x45,0x0d};
		uart_out_buff0(zTTButteryOutBuff,20);
		zTTSilentCnt[2]=10;
		}

	zTTRequestPhase=1;

	zTTBatteryHndlPhase=0;
	
	zTTButteryCnter++;
	if(zTTButteryCnter>=NUMBAT_TELECORE)zTTButteryCnter=0;
	}

}

#endif

#endif


