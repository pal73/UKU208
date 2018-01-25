#line 1 "watchdog.c"
#line 1 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"
 
 
 
 
 
 
 
 
 
 




 
#line 59 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 




 
#line 82 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 




 





 


 



 





 
#line 124 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 142 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 159 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 171 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 185 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 194 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 






 






 
#line 236 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 



 


 
#line 253 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 




 
#line 284 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 310 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 336 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 
#line 362 "C:\\Keil\\ARM\\INC\\Philips\\LPC21XX.h"

 





#line 2 "watchdog.c"
#line 1 "watchdog.h"

void watchdog_init(unsigned long f,unsigned long time_out);
void watchdog_reset(void);





#line 3 "watchdog.c"


void watchdog_init(unsigned long f,unsigned long time_out)
{
unsigned long tempUL;
unsigned 	current_interrupt_status;
tempUL=f/4000UL;
tempUL*=time_out;
(*((volatile unsigned long *) 0xE0000004))=tempUL;
(*((volatile unsigned char *) 0xE0000000)) = 0x03;

(*((volatile unsigned long *) 0xFFFFF020)) = 0; 
current_interrupt_status = (*((volatile unsigned long *) 0xFFFFF010)); 
(*((volatile unsigned long *) 0xFFFFF014)) = 0xffffffff;  

(*((volatile unsigned char *) 0xE0000008)) = 0xAA; 
(*((volatile unsigned char *) 0xE0000008)) = 0x55;

(*((volatile unsigned long *) 0xFFFFF010)) = current_interrupt_status;
(*((volatile unsigned long *) 0xFFFFF020)) = 1;
}


void watchdog_reset()
{
volatile unsigned 	current_interrupt_status;

(*((volatile unsigned long *) 0xFFFFF020)) = 0; 
current_interrupt_status = (*((volatile unsigned long *) 0xFFFFF010)); 
(*((volatile unsigned long *) 0xFFFFF014)) = 0xffffffff;  
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
(*((volatile unsigned char *) 0xE0000008)) = 0xAA; 
(*((volatile unsigned char *) 0xE0000008)) = 0x55;

(*((volatile unsigned long *) 0xFFFFF010)) = current_interrupt_status;
(*((volatile unsigned long *) 0xFFFFF020)) = 1;
}

