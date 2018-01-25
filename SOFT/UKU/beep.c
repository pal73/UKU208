#include "beep.h"
#include "main.h"
#include "LPC17XX.H"
#include "avar_hndl.h"
#include "mess.h"

unsigned long beep_stat_temp,beep_stat;
char beep_stat_cnt;
char beep_cnt;
char bU_BAT2REL_AV_BAT;

//-----------------------------------------------
void beep_drv(void)
{

}

//-----------------------------------------------
void beep_init(long zvuk,char fl) 
{
if(fl=='O')
	{
	beep_stat_temp=zvuk;
	beep_stat=0x0L;
	beep_stat_cnt=32;
	} 
else if(fl=='A')
	{
	beep_stat_temp=zvuk;
	beep_stat=zvuk;
	beep_stat_cnt=32;
	}	 

else if(fl=='R')
	{
	beep_stat=zvuk;
	}	
		          
else if(fl=='S')
	{
	beep_stat_temp=0x0L;
	beep_stat=0x0L;
	beep_stat_cnt=32;
	}	
}

//-----------------------------------------------
void beep_hndl(void) 
{ 


}
