#include <LPC21XX.h>
#include "watchdog.h"

//-----------------------------------------------
void watchdog_init(unsigned long f,unsigned long time_out)
{
unsigned long tempUL;
unsigned 	current_interrupt_status;
tempUL=f/4000UL;
tempUL*=time_out;
WDTC=tempUL;
WDMOD = 0x03;

VICProtection = 0; 
current_interrupt_status = VICIntEnable; 
VICIntEnClr = 0xffffffff;  

WDFEED = 0xAA; 
WDFEED = 0x55;

VICIntEnable = current_interrupt_status;
VICProtection = 1;
}

//-----------------------------------------------
void watchdog_reset()
{
__disable_irq();	
WDFEED = 0xAA; 
WDFEED = 0x55;
__enable_irq();
}

