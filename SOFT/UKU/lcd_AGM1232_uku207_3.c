//#include "global_define.h"
#include "lcd_AGM1232_uku207_3.h"
#include "LPC17xx.H"
#include "main.h"



//-----------------------------------------------
void lcd1_chk(void)
{
LPC_GPIO1->FIODIR&=(~((1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7)));
LPC_GPIO1->FIOSET|=(1<<RW);

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

LPC_GPIO1->FIOCLR|=(1<<A0);

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

LPC_GPIO1->FIOSET|=(1<<E1);

chk1:

if(LPC_GPIO1->FIOPIN&(1<<D7)) goto chk1;

}

//-----------------------------------------------
void lcd2_chk(void)
{
LPC_GPIO1->FIODIR&=(~((1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7)));
LPC_GPIO1->FIOSET|=(1<<RW);

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

LPC_GPIO1->FIOCLR|=(1<<A0);

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

LPC_GPIO1->FIOSET|=(1<<E2);

chk2:

if(LPC_GPIO1->FIOPIN&(1<<D7)) goto chk2;

}

//-----------------------------------------------
void lcd1_wr(char in)
{

LPC_GPIO1->FIODIR|=((1UL<<A0)|(1UL<<E1)|(1UL<<RW));

lcd1_chk();

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

LPC_GPIO1->FIOCLR|=(1UL<<A0);

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

LPC_GPIO1->FIOCLR|=(1UL<<RW);

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

LPC_GPIO1->FIODIR|=((1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
LPC_GPIO1->FIOSET|=(((long)in)<<D0);
LPC_GPIO1->FIOCLR|=(((long)(~in))<<D0)&(0xffUL<<D0);

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

LPC_GPIO1->FIOCLR|=(1<<E1);

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

}



//-----------------------------------------------
void lcd2_wr(char in)
{

LPC_GPIO1->FIODIR|=(1<<A0);
LPC_GPIO1->FIODIR|=((1<<RW)|(1<<E2));


lcd2_chk();
     
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

LPC_GPIO1->FIOCLR|=(1<<A0);

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

LPC_GPIO1->FIOCLR|=(1<<RW);

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

LPC_GPIO1->FIODIR|=((1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
LPC_GPIO1->FIOSET|=(((long)in)<<D0);
LPC_GPIO1->FIOCLR|=(((long)(~in))<<D0)&(0xffUL<<D0);

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

LPC_GPIO1->FIOCLR|=(1<<E2);

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

}

//-----------------------------------------------
char data1_wr(char in)
{
//__disable_irq();
LPC_GPIO1->FIODIR|=((1<<A0)|(1<<E1));
LPC_GPIO1->FIODIR|=(1<<RW);

lcd1_chk();

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

LPC_GPIO1->FIOSET|=(1<<A0);

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

LPC_GPIO1->FIOCLR|=(1<<RW);

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

LPC_GPIO1->FIODIR|=((1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
LPC_GPIO1->FIOSET|=(((long)in)<<D0);
LPC_GPIO1->FIOCLR|=(((long)(~in))<<D0)&(0xffUL<<D0);

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

LPC_GPIO1->FIOCLR|=(1<<E1);

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

return in;
}

//-----------------------------------------------
void data2_wr(char in)
{
LPC_GPIO1->FIODIR|=(1<<A0);
LPC_GPIO1->FIODIR|=((1<<RW)|(1<<E2));

lcd2_chk();

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

LPC_GPIO1->FIOSET|=(1<<A0);

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

LPC_GPIO1->FIOCLR|=(1<<RW);

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

LPC_GPIO1->FIODIR|=((1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));
LPC_GPIO1->FIOSET|=(((long)in)<<D0);
LPC_GPIO1->FIOCLR|=(((long)(~in))<<D0)&(0xffUL<<D0);

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

LPC_GPIO1->FIOCLR|=(1<<E2);

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

}

//-----------------------------------------------
void lcd_set_page(char in)
{
lcd1_wr(_SET_PAGE_|in);
lcd2_wr(_SET_PAGE_|in);
}

//-----------------------------------------------
void lcd_set_col(char in)
{
lcd1_wr(_SET_COLUMN_|in);
lcd2_wr(_SET_COLUMN_|in);
}    

//-----------------------------------------------
void lcd_set_raw(char in)
{
lcd1_wr(_SET_RAW_|in);
lcd2_wr(_SET_RAW_|in);
}    

//-----------------------------------------------
void lcd_init(void) 
{
int i/*,ii*/;

		   /*
#if(RES<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(RES*2))&~(1<<((RES*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((RES-16)*2))&~(1<<(((RES-16)*2)+1));
	}
#endif

LPC_PINCON->PINSEL2&=~(1<<((E1-16)*2))&~(1<<(((E1-16)*2)+1));
	
LPC_PINCON->PINSEL2&=~(1<<((E2-16)*2))&~(1<<(((E2-16)*2)+1));

LPC_PINCON->PINSEL2&=~(1<<((A0-16)*2))&~(1<<(((A0-16)*2)+1));

LPC_PINCON->PINSEL2&=~(1<<((RW-16)*2))&~(1<<(((RW-16)*2)+1));
				





#if(D0<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D0*2))&~(1<<((D0*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D0-16)*2))&~(1<<(((D0-16)*2)+1));
	}
#endif

#if(D1<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D1*2))&~(1<<((D1*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D1-16)*2))&~(1<<(((D1-16)*2)+1));
	}
#endif
	
#if(D2<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D2*2))&~(1<<((D2*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D2-16)*2))&~(1<<(((D2-16)*2)+1));
	}
#endif
	
#if(D3<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D3*2))&~(1<<((D3*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D3-16)*2))&~(1<<(((D3-16)*2)+1));
	}	
#endif
	
#if(D4<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D4*2))&~(1<<((D4*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D4-16)*2))&~(1<<(((D4-16)*2)+1));
	}
#endif

#if(D5<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D5*2))&~(1<<((D5*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D5-16)*2))&~(1<<(((D5-16)*2)+1));
	}
#endif
	
#if(D6<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D6*2))&~(1<<((D6*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D6-16)*2))&~(1<<(((D6-16)*2)+1));
	}
#endif
	
#if(D7<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D7*2))&~(1<<((D7*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D7-16)*2))&~(1<<(((D7-16)*2)+1));
	}
#endif	

 */
	
					
LPC_GPIO1->FIODIR|=(1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
LPC_GPIO1->FIODIR|=(1<<E1)|(1<<A0)|(1<<E2)|(1<<RW);
LPC_GPIO0->FIODIR|=(1<<RES)|(1<<29);

for(i=0;i<100;i++)
	{
	LPC_GPIO0->FIOCLR|=(1<<RES);
	}
for(i=0;i<166000;i++)
	{
	__nop();
	}
for(i=0;i<50;i++)
	{
	LPC_GPIO0->FIOSET|=(1<<RES);
	}	

 for(i=0;i<166000;i++)
	{
	__nop();
	}
	

//lcd_reset();
//E1d=1;
//E2d=1;
//A0d=1;
//RWd=1;

//E1=0;
//E2=0;
/*IO1CLR|=(1<<E1);
IO1CLR|=(1<<E2);
//A0=1;
IO1SET|=(1<<A0);
//RW=1;
IO1SET|=(1<<RW);

lcd1_wr(_RESET_);
lcd2_wr(_RESET_);*/
     //LCD_PORTc=0xFF;
     //LCD_PORT=0xFF;
//disp_page0(); 

//IO0CLR|=(1<<A0)|(1<<RW);
}

//-----------------------------------------------
void status(void)
{

LPC_GPIO1->FIOCLR=(1<<A0);//clr P3.2 ; A0=0 for read
LPC_GPIO1->FIOSET=(1<<RW);//setb P3.6 ; wr=1
LPC_GPIO1->FIOSET=(1<<E1);//setb P3.3 ;Left side enabled
__nop();;//mov P1, #0FFH ; load input
stat1: //clr P3.5 ; rd=0
//nop
__nop();
__nop();
__nop();
//nop
//nop
//mov a, P1 ; move status
//anl a, #80H ;check bit 8
//setb P3.5 ; rd=1
//jnz stat1 ; jump if A not 0

if(LPC_GPIO1->FIOPIN&(1<<D7)) goto stat1;
LPC_GPIO1->FIOCLR=(1<<E1);//clr P3.3 ;

//ret
}

//-----------------------------------------------
void delay(void)
{
signed short i;

for(i=0;i<100;i++)
	{
	__nop();
	}
}

//-----------------------------------------------
void ltstrobe(char in)
{
status();
LPC_GPIO1->FIOSET=(1<<RW);//setb p3.5 ;RD=1
LPC_GPIO1->FIOCLR=(1<<A0);//clr p3.2 ;A=0
LPC_GPIO1->FIOSET=(1<<E1);//setb p3.3 ;CS1=1
LPC_GPIO1->FIOSET=(1<<E2);//setb p3.4 ;CS2=1
LPC_GPIO1->FIOSET|=(((long)in)<<D0);
LPC_GPIO1->FIOCLR|=(((long)(~in))<<D0)&(0xffUL<<D0);
//delay();
LPC_GPIO1->FIOCLR=(1<<E1);//clr p3.3 ;CS1=0
LPC_GPIO1->FIOCLR=(1<<E2);//clr p3.4 ;CS2=0
LPC_GPIO1->FIOCLR=(1<<RW);//clr p3.5 ;RD=0
//ret
}

//-----------------------------------------------
void lcd_init_(void) 
{
int i/*,ii*/;
#if(RES<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(RES*2))&~(1<<((RES*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((RES-16)*2))&~(1<<(((RES-16)*2)+1));
	}
#endif	
LPC_PINCON->PINSEL2&=~(1<<((A0-16)*2))&~(1<<(((A0-16)*2)+1));
LPC_PINCON->PINSEL2&=~(1<<((E1-16)*2))&~(1<<(((E1-16)*2)+1));	
LPC_PINCON->PINSEL2&=~(1<<((E2-16)*2))&~(1<<(((E2-16)*2)+1));
LPC_PINCON->PINSEL2&=~(1<<((RW-16)*2))&~(1<<(((RW-16)*2)+1));
				





#if(D0<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D0*2))&~(1<<((D0*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D0-16)*2))&~(1<<(((D0-16)*2)+1));
	}
#endif

#if(D1<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D1*2))&~(1<<((D1*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D1-16)*2))&~(1<<(((D1-16)*2)+1));
	}
#endif
	
#if(D2<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D2*2))&~(1<<((D2*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D2-16)*2))&~(1<<(((D2-16)*2)+1));
	}
#endif
	
#if(D3<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D3*2))&~(1<<((D3*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D3-16)*2))&~(1<<(((D3-16)*2)+1));
	}	
#endif
	
#if(D4<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D4*2))&~(1<<((D4*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D4-16)*2))&~(1<<(((D4-16)*2)+1));
	}
#endif

#if(D5<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D5*2))&~(1<<((D5*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D5-16)*2))&~(1<<(((D5-16)*2)+1));
	}
#endif
	
#if(D6<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D6*2))&~(1<<((D6*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D6-16)*2))&~(1<<(((D6-16)*2)+1));
	}
#endif
	
#if(D7<16)
	{
	LPC_PINCON->PINSEL0&=~(1<<(D7*2))&~(1<<((D7*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINSEL1&=~(1<<((D7-16)*2))&~(1<<(((D7-16)*2)+1));
	}
#endif
	


	
					
LPC_GPIO1->FIODIR|=(1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7)|(1<<RES);
LPC_GPIO0->FIODIR|=(1<<E2)|(1<<RW)|(1<<E1)|(1<<A0);


for(i=0;i<10;i++)
	{
	LPC_GPIO1->FIOCLR|=(1<<RES);
	}
for(i=0;i<500;i++)
	{
	__nop();
	}
for(i=0;i<50000;i++)
	{
	LPC_GPIO1->FIOSET|=(1<<RES);
	}	

/*
mov a, #0E2H ;Reset column address, display
acall ltstrobe ;startline, page address counter=0.*/
ltstrobe(0xE2);

/*
mov a, #0AfH ;display=On
lcall ltstrobe*/
//ltstrobe(0xAF);

/*
mov a, #0C0H ;Starts on first line
lcall ltstrobe*/
//ltstrobe(0xC0);

/*
mov a, #0A4H ;static driver=Off
lcall ltstrobe*/
//ltstrobe(0xA4);

/*
mov a, #0A9H ;duty cycle=1/32
lcall ltstrobe*/
//ltstrobe(0xA9);

/*
mov a, #0A0H ;ADC=forward
lcall ltstrobe*/
//ltstrobe(0xA0);

/*
mov a, #0EEH ;Read Modified Write=End
lcall ltstrobe*/
//ltstrobe(0xEE);

/*
lcall clrsc ;Clear screen routine
mov R3, #0
mov R4, #0B8H
*/

}



//-----------------------------------------------
void lcd_clear(void)
{
char page,col/*,i*/;

for(page=0;page<=Max_page;page++)

	{
	lcd_set_page(page);
	lcd_set_col(0);
	for(col=0;col<=Max_Col;col++)
         	{
         	data1_wr(0x00);
	    	data2_wr(0x00);
     	}
     }  
}





//-----------------------------------------------
void lcd_on(void) 
{
lcd1_wr(_DISPLAY_ON_);
lcd2_wr(_DISPLAY_ON_);
}

//-----------------------------------------------
void lcd_off(void)
{
lcd1_wr(_DISPLAY_OFF_);
lcd2_wr(_DISPLAY_OFF_);
}

//-----------------------------------------------
void lcd_out(char* adr)
{
char* ptr0;
char* ptr1;
char i,n;
ptr0=adr;
ptr1=adr+61;
lcd_set_raw(0);

for(n=0;n<=3;n++)
	{
	ptr0=adr+(122*(unsigned)n);
	ptr1=ptr0+61;
	lcd_set_page(n);
	lcd_set_col(0);
	for(i=0;i<61;i++)
		{
		data1_wr(*ptr0);
		data2_wr(*ptr1);
		ptr0++;
		ptr1++;
	    	}
	}
}

