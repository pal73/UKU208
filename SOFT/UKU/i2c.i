#line 1 "i2c.c"
#line 1 "i2c.h"


 
#line 14 "i2c.h"






void i2c_Start(void);
void i2c_Restart(void);
unsigned char i2c_SendByte(unsigned char byte);
unsigned char i2c_SendAddress(unsigned char address, unsigned char rw);
signed char i2c_ReadAcknowledge(void);
char i2c_ReadByte(void);
void i2c_SendAcknowledge(unsigned char status);
void i2c_Stop(void);
#line 2 "i2c.c"
#line 1 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"
 
 
 
 
 
 
 
 
 
 




 
#line 59 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 




 
#line 82 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 




 





 


 



 





 
#line 124 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 142 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 159 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 171 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 185 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 194 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 






 






 
#line 236 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 



 


 
#line 253 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 




 
#line 284 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 310 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 336 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 
#line 362 "C:\\Keil\\ARM\\INC\\Philips\\LPC21xx.H"

 





#line 3 "i2c.c"











 







void i2c_Start(void)
{
                      









(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);                      




return;
}    


void i2c_Restart(void)
{
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);                      
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);                     


(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);


(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);                      

(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);
return;
}    




unsigned char i2c_SendByte(unsigned char byte)
{
signed char i;
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);

for(i=8; i>=1; i--)
	{
     if(byte&0x80)
         	{
         	(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
         	}
     else
         	{
         	(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);
         	}
     
     byte<<=1;
     (*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
     (*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
     (*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
     (*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
	
	(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);


	
 	}

(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
return 0;
}


unsigned char i2c_SendAddress(unsigned char address, unsigned char rw)
{
return i2c_SendByte(address | (rw&0x01));
} 



signed char i2c_ReadAcknowledge(void)
{
unsigned char ack;
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);                               
		 

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);

if((*((volatile unsigned long *) 0xE0028000))&(1<<3)) ack = 1;
else ack = 0;

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);		 

					 
return	ack;				
}


char i2c_ReadByte(void)
{
unsigned char i;
unsigned char byte = 0;
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);;
for(i=0; i<8; i++)
	{
	                       
	
	
	
	
	(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
	(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);;		 
	
	
	
	(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);;
	(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);;
	byte = byte << 1;		  
	if((*((volatile unsigned long *) 0xE0028000))&(1<<3)) byte|=1;
	else byte&=0xfe;
	(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
	}
return byte;
}


void i2c_SendAcknowledge(unsigned char status)
{

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
if(status&0x01)
	{
     (*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);                           
     }
else
	{
     (*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
	}

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);			 

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<2);
return;
}


void i2c_Stop(void)
{
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))|=(1UL<<3);                       
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);



(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<2);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<2);

(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);                      

(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);


(*((volatile unsigned long *) 0xE002800C))=(1UL<<3);(*((volatile unsigned long *) 0xE0028008))&=~(1UL<<3);
return;
}
