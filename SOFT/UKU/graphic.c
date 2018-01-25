#include "graphic.h"
#include <LPC17XX.H> 
#include "main.h"
#include "simbols.h"

//-----------------------------------------------
void draw(signed short x_b,signed short y_b,signed short x_o,signed short y_o,char inverse)
{
unsigned short num_byte;
//signed short byte_offset;
//unsigned short x_target;
unsigned short i;
char num_bite;
unsigned short y_begin,y_bit_begin;
unsigned short y_target,y_bit_target;
if((y_b<0)||(y_b>31)) return;
/*if((x_b<0)||(x_b>121)) return;

if(((x_b+x_o)<0)||((x_b+x_o)>121)) return;
if(((y_b+y_o)<0)||((y_b+y_o)>31)) return;
if(y_o&&x_o) return;*/

if(x_o)
	{
	num_byte=366-(122*(y_b/8))+(x_b);
	//x_target
	//byte_offset=x_o;
	num_bite=7-(y_b%8);
	if(x_o>0)
		{
		for(i=num_byte;i<(num_byte+x_o);i++)
			{
			if(!inverse)lcd_bitmap[i]|=(1<<num_bite);
			else if(inverse==1) lcd_bitmap[i]^=(1<<num_bite);
			else if(inverse==2) lcd_bitmap[i]&=((1<<num_bite)&0xff);
			}
		}
	else if(x_o<0)
		{
		for(i=num_byte;i>(num_byte+x_o);i--)
			{
			if(!inverse)lcd_bitmap[i]|=(1<<num_bite);
			else if(inverse==1) lcd_bitmap[i]^=(1<<num_bite);
			else if(inverse==2) lcd_bitmap[i]&=((1<<num_bite)&0xff);
			}
		}		
	}
else if(y_o)
	{
	num_byte=366-(122*(y_b/8))+(x_b);
	y_begin=y_b/8;
	y_target=(y_b+y_o)/8;
	y_bit_begin=y_b%8;
	y_bit_target=(y_b+y_o)%8;	
	
	if(y_o>0)
		{
		
		if(y_begin==y_target)
			{
			for(i=y_bit_begin;i<y_bit_target;i++)
				{
				if(!inverse)lcd_bitmap[x_b+(122*(3-y_begin))]|=(1<<(7-i));
				else if(inverse==1) lcd_bitmap[x_b+(122*(3-y_begin))]^=(1<<(7-i));
				else if(inverse==2) lcd_bitmap[x_b+(122*(3-y_begin))]&=((1<<(7-i))^0xff);
				}
			}
		else
			{
			if(!inverse)lcd_bitmap[x_b+(122*(3-y_begin))]|=(0xff>>y_bit_begin);
			else if(inverse==1) lcd_bitmap[x_b+(122*(3-y_begin))]^=(0xff>>y_bit_begin);
			else if(inverse==2) lcd_bitmap[x_b+(122*(3-y_begin))]&=((0xff>>y_bit_begin)^0xff);
			
			if(!inverse)lcd_bitmap[x_b+(122*(3-y_target))]|=(0xff<<(8-y_bit_target));
			else if(inverse==1) lcd_bitmap[x_b+(122*(3-y_target))]^=(0xff<<(8-y_bit_target));
			else if(inverse==2) lcd_bitmap[x_b+(122*(3-y_target))]&=((0xff<<(8-y_bit_target))^0xff);
			
			if((y_target-y_begin)>1)
				{
				for(i=y_begin+1;i<y_target;i++)
					{
					if(!inverse)lcd_bitmap[x_b+(122*(3-i))]|=0xff;
					else if(inverse==1) lcd_bitmap[x_b+(122*(3-i))]^=0xff;
					else if(inverse==2) lcd_bitmap[x_b+(122*(3-i))]&=0;
					}
				}
			}	
		
		}	
	if(y_o<0)
		{
		
		if(y_begin==y_target)
			{
			for(i=y_bit_begin-1;i>=y_bit_target;i--)
				{
				if(!inverse)lcd_bitmap[x_b+(122*(3-y_begin))]|=(1<<(7-i));
				else if(inverse==1) lcd_bitmap[x_b+(122*(3-y_begin))]^=(1<<(7-i));
				else if(inverse==2) lcd_bitmap[x_b+(122*(3-y_begin))]&=((1<<(7-i))^0xff);
				}
			}
		else
			{
			if(!inverse)lcd_bitmap[x_b+(122*(3-y_begin))]|=(0xff<<(8-y_bit_begin));
			else if(inverse==1) lcd_bitmap[x_b+(122*(3-y_begin))]^=(0xff<<(8-y_bit_begin));
			else if(inverse==2) lcd_bitmap[x_b+(122*(3-y_begin))]&=((0xff<<(8-y_bit_begin))^0xff);
			
			if(!inverse)lcd_bitmap[x_b+(122*(3-y_target))]|=(0xff>>y_bit_target);
			else if(inverse==1) lcd_bitmap[x_b+(122*(3-y_target))]^=(0xff>>y_bit_target);
			else if(inverse==2) lcd_bitmap[x_b+(122*(3-y_target))]&=((0xff>>y_bit_target)^0xff);
			
			if((y_begin-y_target)>1)
				{
				for(i=y_begin-1;i>y_target;i--)
					{
					if(!inverse)lcd_bitmap[x_b+(122*(3-i))]|=0xff;
					else if(inverse==1) lcd_bitmap[x_b+(122*(3-i))]^=0xff;
					else if(inverse==2) lcd_bitmap[x_b+(122*(3-i))]&=0;
					}
				}
			}	
		
		}			
	}	
}	
//---------------------------------------------
void draw_rectangle(signed short x_b,signed short y_b,signed short x_o,signed short y_o,char solid,char inverse)
{

signed short i;
/*draw(x_b,y_b,0,y_o,inverse);
draw(x_b,y_b+y_o,x_o,0,inverse);
draw(x_b+x_o,y_b+y_o,0,-y_o,inverse);
draw(x_b+x_o,y_b,-x_o,0,inverse);*/

if(solid)
	{
	for(i=x_b;i<=(x_b+x_o);i++)
		{
		draw(i,y_b,0,y_o,inverse);
		}
	}
else
	{
	draw(x_b,y_b,0,y_o,inverse);
	draw(x_b,y_b+y_o-1,x_o,0,inverse);
	draw(x_b+x_o-1,y_b+y_o,0,-y_o,inverse);
	draw(x_b+x_o-1,y_b,-x_o,0,inverse);	
	}	

}

//---------------------------------------------
void draw_ptr(char x_b,char y_b,char ptr,char vol)
{
char i;
if(ptr==0)
	{
	for(i=0;i<vol;i++)
		{
		draw(x_b,y_b+i,-(vol-i),0,0);
		draw(x_b,y_b+i,(vol-i),0,0);
		}
	}
else if(ptr==2)
	{
	for(i=0;i<vol;i++)
		{
		draw(x_b,y_b-i,-(vol-i),0,0);
		draw(x_b,y_b-i,(vol-i),0,0);
		}
	}	
}

//-----------------------------------------------
void plot(signed short x_b,signed short y_b,unsigned long data,signed short len,char inverse)
{
//unsigned short num_byte;
//signed short byte_offset;
//unsigned short x_target;
//unsigned short i;
char num_bite;
unsigned short /*y_begin*/y_bit_begin;
//unsigned short y_target,y_bit_target;
unsigned long data1/*,data2*/;
char data1_0,data1_1,data1_2,data1_3;

data1=0xffffffffUL;
data1<<=(32-len);
data1&=data;
data1=data1>>y_b;

data1_0=*((char*)&data1);
data1_1=*(((char*)&data1)+1);
data1_2=*(((char*)&data1)+2);
data1_3=*(((char*)&data1)+3);

if(!inverse)
	{
	lcd_bitmap[x_b]|=data1_0;
	lcd_bitmap[122+x_b]|=data1_1;
	lcd_bitmap[244+x_b]|=data1_2;
	lcd_bitmap[366+x_b]|=data1_3;
	}
else if(inverse)
	{
	lcd_bitmap[x_b]^=data1_0;
	lcd_bitmap[122+x_b]^=data1_1;
	lcd_bitmap[244+x_b]^=data1_2;
	lcd_bitmap[366+x_b]^=data1_3;
	}

}	


//-----------------------------------------------
void graphic_print(signed short x_b,signed short y_b,signed short x_l,signed short y_l,signed short x_d,signed short y_d,const char* adress,char inverse)
{
signed short i;

for(i=0;i<x_l;i++)
	{
	long data;
	
	*(((char*)&data)+3)=adress[(i*y_d)+y_d-1];
	*(((char*)&data)+2)=adress[(i*y_d)+y_d-2];
	*(((char*)&data)+1)=adress[(i*y_d)+y_d-3];
	*((char*)&data)=adress[(i*y_d)+y_d-4];
	
	//data=0x08000000;
	
	plot(x_b+i,y_b,data,y_l,inverse);
	}
}

//-----------------------------------------------
void graphic_print_text(signed short x_b,signed short y_b,const char* bgnd,signed short num,signed short data,signed short des,signed short pos,char inverse)
{
signed short i;
char buffer[10];
char bitmap_buffer[60];
for(i=0;i<10;i++)
	{
	buffer[i]=' ';
	}
for(i=0;i<num;i++)
	{
	buffer[i]=bgnd[i];
	}	
	
{	
signed char i;
//char n;
char s[10];
char minus='+';
char zero_on;
char simb_num;

if(data<0)
	{
	data=-data;
	minus='-';
	}

for(i=0;i<10;i++)
	{
	s[i]=data%10;
	data/=10;
	}   

zero_on=1;
simb_num=0;

for (i=9;i>=0;i--)
	{
	if(zero_on&&(!s[i])&&(i>(des)))
	     {
	     s[i]=0x20;
	     }
	else 
	     {
	     s[i]=s[i]+0x30;
	     zero_on=0;
	     simb_num++;
	     }
	 }
	          
if(minus=='-')	
     {
     s[simb_num++]=minus; 
     }    
if(des)
     {
     for(i=simb_num;i>des;i--)
          {
          s[i]=s[i-1];
          }
     s[des]='.';
     simb_num++;     
     }
	
for (i=0;i<simb_num;i++)
	{
     buffer[pos-1-i]=s[i];
	}
}	
	
		
for(i=0;i<num;i++)
	{
	bitmap_buffer[(6*i)+0]=caracter[(unsigned)buffer[i]*6];
	bitmap_buffer[(6*i)+1]=caracter[((unsigned)buffer[i]*6)+1];
	bitmap_buffer[(6*i)+2]=caracter[((unsigned)buffer[i]*6)+2];
	bitmap_buffer[(6*i)+3]=caracter[((unsigned)buffer[i]*6)+3];
	bitmap_buffer[(6*i)+4]=caracter[((unsigned)buffer[i]*6)+4];
	bitmap_buffer[(6*i)+5]=caracter[((unsigned)buffer[i]*6)+5];
	}
for(i=0;i<(num*6);i++)
	{
	long data;
	
	*(((char*)&data)+3)=bitmap_buffer[i];
	
	//data=0x08000000;
	
	plot(x_b+i,y_b,data,8,inverse);
	}
}

//-----------------------------------------------
void graphic_print_text_text(signed short x_b,signed short y_b,const char* bgnd,signed short num,signed short data,signed short des,signed short pos,char inverse)
{
signed short i;
char buffer[10];
char bitmap_buffer[60];
for(i=0;i<10;i++)
	{
	buffer[i]=' ';
	}
for(i=0;i<num;i++)
	{
	buffer[i]=bgnd[i];
	}	
	
{	
signed char i;
//char n;
char s[10];
char minus='+';
char zero_on;
char simb_num;

if(data<0)
	{
	data=-data;
	minus='-';
	}

for(i=0;i<10;i++)
	{
	s[i]=data%10;
	data/=10;
	}   

zero_on=1;
simb_num=0;
/*
for (i=9;i>=0;i--)
	{
	if(zero_on&&(!s[i])&&(i>(des)))
	     {
	     s[i]=0x20;
	     }
	else 
	     {
	     s[i]=s[i]+0x30;
	     zero_on=0;
	     simb_num++;
	     }
	 }
	          
	
*/
}	
	
		
for(i=0;i<num;i++)
	{
	bitmap_buffer[(6*i)+0]=caracter[(unsigned)buffer[i]*6];
	bitmap_buffer[(6*i)+1]=caracter[((unsigned)buffer[i]*6)+1];
	bitmap_buffer[(6*i)+2]=caracter[((unsigned)buffer[i]*6)+2];
	bitmap_buffer[(6*i)+3]=caracter[((unsigned)buffer[i]*6)+3];
	bitmap_buffer[(6*i)+4]=caracter[((unsigned)buffer[i]*6)+4];
	bitmap_buffer[(6*i)+5]=caracter[((unsigned)buffer[i]*6)+5];
	}
for(i=0;i<(num*6);i++)
	{
	long data;
	
	*(((char*)&data)+3)=bitmap_buffer[i];
	
	//data=0x08000000;
	
	plot(x_b+i,y_b,data,8,inverse);
	}
}
