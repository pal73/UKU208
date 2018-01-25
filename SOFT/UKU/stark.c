#include "stark.h"

char portForStarkBatteryIsInitiated=0;
char starkBatteryHndlPhase;
char starkBatteryInBuff[100];
short starkBatteryInBuffPtr;
char starkRequestPhase;
//short coslightSilentCnt;
//char bCoslightPacketIn;
//short coslightBatteryInBuffPtr_plazma;

void stark_bat_hndl(void)
{

if(portForStarkBatteryIsInitiated==0)
	{
	sc16is700_init(19200UL);
	portForStarkBatteryIsInitiated=1;
	}

starkBatteryHndlPhase++;
if(starkBatteryHndlPhase>10)starkBatteryHndlPhase=0;

if(starkBatteryHndlPhase==2)
	{
	char starkButteryOutBuff[]={0x01,0x03,0x00,0x00,0x00,0x01,0x00,0x00};
	sc16is700_out_buff(starkButteryOutBuff,8);
	starkRequestPhase=0;

	}
else if(starkBatteryHndlPhase==4)
	{
	char starkButteryOutBuff[]={0x01,0x03,0x00,0x01,0x00,0x01,0x00,0x00};
	sc16is700_out_buff(starkButteryOutBuff,8);
	starkRequestPhase=1;
	}

else if(starkBatteryHndlPhase==6)
	{
	char starkButteryOutBuff[]={0x01,0x03,0x00,0x28,0x00,0x01,0x00,0x00};
	sc16is700_out_buff(starkButteryOutBuff,8);
	starkRequestPhase=2;
	}

else if(starkBatteryHndlPhase==8)
	{
	char starkButteryOutBuff[]={0x01,0x03,0x00,0x18,0x00,0x01,0x00,0x00};
	sc16is700_out_buff(starkButteryOutBuff,8);
	starkRequestPhase=3;
	}

else if(starkBatteryHndlPhase==10)
	{
	char starkButteryOutBuff[]={0x01,0x03,0x00,0x12,0x00,0x06,0x00,0x00};
	sc16is700_out_buff(starkButteryOutBuff,8);
	starkRequestPhase=4;
	}

else if(starkBatteryHndlPhase==12)
	{
	char starkButteryOutBuff[]={0x01,0x03,0x00,0x1a,0x00,0x04,0x00,0x00};
	sc16is700_out_buff(starkButteryOutBuff,8);
	starkRequestPhase=4;
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