	#include "main.h"
#include <LPC21xx.H>
#include "full_can.h"
#include "cmd.h"
#include "mess.h"
#include "global_define.h"


// Counts number of filters (CAN message objects) used so far
short volatile gCANFilter = 0;

char ptr_can1_tx_wr,ptr_can1_tx_rd;
long can1_info[8];
long can1_id[8];
long can1_data[8];
long can1_datb[8];
																							 
char ptr_can2_tx_wr,ptr_can2_tx_rd;

long can2_info[8];
long can2_id[8];
long can2_data[8];
long can2_datb[8];

unsigned short rotor_can[6];

// Type definition to hold a FullCAN message
// Compatible to FullCAN Mode Stored Messages in LPC User Manual
typedef struct
{
  unsigned int Dat1; // Bits  0..10: CAN Message ID
                     // Bits 13..15: CAN interface number (1..4)
                     // Bits 16..19: DLC - Data Length Counter
                     // Bits 24..25: Semaphore bits
  unsigned int DatA; // CAN Message Data Bytes 0-3
  unsigned int DatB; // CAN Message Data Bytes 4-7
} FULLCAN_MSG;


// FullCAN Message List
FULLCAN_MSG volatile gFullCANList[MAX_FILTERS];

char bR;
char RXBUFF[40],TXBUFF[40];
char bIN,bIN2;
char bd_dumm[25];
char bd[25];
char TX_len;
char bOUT;
char RXBUFF2[40],TXBUFF2[40];
extern char can_tx_cnt;
extern char can_tx_cnt2;
char bOUT_FREE=1;
char bOUT_FREE2=1;
char rotor_rotor_rotor[2];
char can_tx_cnt;

const char Table87[]={
0x00, 0x0E, 0x1C, 0x12, 0x38, 0x36, 0x24, 0x2A, 0x70, 0x7E, 0x6C, 0x62, 0x48, 0x46, 0x54, 0x5A,
0xE0, 0xEE, 0xFC, 0xF2, 0xD8, 0xD6, 0xC4, 0xCA, 0x90, 0x9E, 0x8C, 0x82, 0xA8, 0xA6, 0xB4, 0xBA,
0xCE, 0xC0, 0xD2, 0xDC, 0xF6, 0xF8, 0xEA, 0xE4, 0xBE, 0xB0, 0xA2, 0xAC, 0x86, 0x88, 0x9A, 0x94,
0x2E, 0x20, 0x32, 0x3C, 0x16, 0x18, 0x0A, 0x04, 0x5E, 0x50, 0x42, 0x4C, 0x66, 0x68, 0x7A, 0x74,
0x92, 0x9C, 0x8E, 0x80, 0xAA, 0xA4, 0xB6, 0xB8, 0xE2, 0xEC, 0xFE, 0xF0, 0xDA, 0xD4, 0xC6, 0xC8,
0x72, 0x7C, 0x6E, 0x60, 0x4A, 0x44, 0x56, 0x58, 0x02, 0x0C, 0x1E, 0x10, 0x3A, 0x34, 0x26, 0x28,
0x5C, 0x52, 0x40, 0x4E, 0x64, 0x6A, 0x78, 0x76, 0x2C, 0x22, 0x30, 0x3E, 0x14, 0x1A, 0x08, 0x06,
0xBC, 0xB2, 0xA0, 0xAE, 0x84, 0x8A, 0x98, 0x96, 0xCC, 0xC2, 0xD0, 0xDE, 0xF4, 0xFA, 0xE8, 0xE6,
0x2A, 0x24, 0x36, 0x38, 0x12, 0x1C, 0x0E, 0x00, 0x5A, 0x54, 0x46, 0x48, 0x62, 0x6C, 0x7E, 0x70,
0xCA, 0xC4, 0xD6, 0xD8, 0xF2, 0xFC, 0xEE, 0xE0, 0xBA, 0xB4, 0xA6, 0xA8, 0x82, 0x8C, 0x9E, 0x90,
0xE4, 0xEA, 0xF8, 0xF6, 0xDC, 0xD2, 0xC0, 0xCE, 0x94, 0x9A, 0x88, 0x86, 0xAC, 0xA2, 0xB0, 0xBE,
0x04, 0x0A, 0x18, 0x16, 0x3C, 0x32, 0x20, 0x2E, 0x74, 0x7A, 0x68, 0x66, 0x4C, 0x42, 0x50, 0x5E,
0xB8, 0xB6, 0xA4, 0xAA, 0x80, 0x8E, 0x9C, 0x92, 0xC8, 0xC6, 0xD4, 0xDA, 0xF0, 0xFE, 0xEC, 0xE2,
0x58, 0x56, 0x44, 0x4A, 0x60, 0x6E, 0x7C, 0x72, 0x28, 0x26, 0x34, 0x3A, 0x10, 0x1E, 0x0C, 0x02,
0x76, 0x78, 0x6A, 0x64, 0x4E, 0x40, 0x52, 0x5C, 0x06, 0x08, 0x1A, 0x14, 0x3E, 0x30, 0x22, 0x2C,
0x96, 0x98, 0x8A, 0x84, 0xAE, 0xA0, 0xB2, 0xBC, 0xE6, 0xE8, 0xFA, 0xF4, 0xDE, 0xD0, 0xC2, 0xCC};



const char Table95[]={
0x00, 0x2A, 0x54, 0x7E, 0xA8, 0x82, 0xFC, 0xD6, 0x7A, 0x50, 0x2E, 0x04, 0xD2, 0xF8, 0x86, 0xAC,
0xF4, 0xDE, 0xA0, 0x8A, 0x5C, 0x76, 0x08, 0x22, 0x8E, 0xA4, 0xDA, 0xF0, 0x26, 0x0C, 0x72, 0x58,
0xC2, 0xE8, 0x96, 0xBC, 0x6A, 0x40, 0x3E, 0x14, 0xB8, 0x92, 0xEC, 0xC6, 0x10, 0x3A, 0x44, 0x6E,
0x36, 0x1C, 0x62, 0x48, 0x9E, 0xB4, 0xCA, 0xE0, 0x4C, 0x66, 0x18, 0x32, 0xE4, 0xCE, 0xB0, 0x9A,
0xAE, 0x84, 0xFA, 0xD0, 0x06, 0x2C, 0x52, 0x78, 0xD4, 0xFE, 0x80, 0xAA, 0x7C, 0x56, 0x28, 0x02,
0x5A, 0x70, 0x0E, 0x24, 0xF2, 0xD8, 0xA6, 0x8C, 0x20, 0x0A, 0x74, 0x5E, 0x88, 0xA2, 0xDC, 0xF6,
0x6C, 0x46, 0x38, 0x12, 0xC4, 0xEE, 0x90, 0xBA, 0x16, 0x3C, 0x42, 0x68, 0xBE, 0x94, 0xEA, 0xC0,
0x98, 0xB2, 0xCC, 0xE6, 0x30, 0x1A, 0x64, 0x4E, 0xE2, 0xC8, 0xB6, 0x9C, 0x4A, 0x60, 0x1E, 0x34,
0x76, 0x5C, 0x22, 0x08, 0xDE, 0xF4, 0x8A, 0xA0, 0x0C, 0x26, 0x58, 0x72, 0xA4, 0x8E, 0xF0, 0xDA,
0x82, 0xA8, 0xD6, 0xFC, 0x2A, 0x00, 0x7E, 0x54, 0xF8, 0xD2, 0xAC, 0x86, 0x50, 0x7A, 0x04, 0x2E,
0xB4, 0x9E, 0xE0, 0xCA, 0x1C, 0x36, 0x48, 0x62, 0xCE, 0xE4, 0x9A, 0xB0, 0x66, 0x4C, 0x32, 0x18,
0x40, 0x6A, 0x14, 0x3E, 0xE8, 0xC2, 0xBC, 0x96, 0x3A, 0x10, 0x6E, 0x44, 0x92, 0xB8, 0xC6, 0xEC, 
0xD8, 0xF2, 0x8C, 0xA6, 0x70, 0x5A, 0x24, 0x0E, 0xA2, 0x88, 0xF6, 0xDC, 0x0A, 0x20, 0x5E, 0x74, 
0x2C, 0x06, 0x78, 0x52, 0x84, 0xAE, 0xD0, 0xFA, 0x56, 0x7C, 0x02, 0x28, 0xFE, 0xD4, 0xAA, 0x80, 
0x1A, 0x30, 0x4E, 0x64, 0xB2, 0x98, 0xE6, 0xCC, 0x60, 0x4A, 0x34, 0x1E, 0xC8, 0xE2, 0x9C, 0xB6, 
0xEE, 0xC4, 0xBA, 0x90, 0x46, 0x6C, 0x12, 0x38, 0x94, 0xBE, 0xC0, 0xEA, 0x3C, 0x16, 0x68, 0x42};



char can_debug_plazma[2][10];

//-----------------------------------------------
char CRC1_in(void)
{
char r,j,lb;
lb=(RXBUFF[1]&0x1f)+0x04;
r=RXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(RXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 

//-----------------------------------------------
char CRC2_in(void)
{
char r,j,lb;
lb=(RXBUFF[1]&0x1f)+0x04;
r=RXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(RXBUFF[j]^Table95[r]);
	}
if(r==0)r=0xFF;
return r;	
}  

//-----------------------------------------------
char CRC1_out(void)
{
char r,j,lb;
lb=(TXBUFF[1]&0x1f)+0x04;
r=TXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(TXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 

//-----------------------------------------------
char CRC2_out(void)
{
char r,j,lb;
lb=(TXBUFF[1]&0x1f)+0x04;
r=TXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(TXBUFF[j]^Table95[r]);
	}
if(r==0)r=0xFF;
return r;	
}

//-----------------------------------------------
void can1_out_adr(char* ptr,char num)
{

if(num<=8)
	{
	can1_info[ptr_can1_tx_wr]=(((long)num)<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	}
	
else if(num<=16)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-8))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	

else if(num<=24)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;

	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-16))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[17];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[19];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[20];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[21];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[22];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[23];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	

else if(num<=32)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;

	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[17];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[18];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[19];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[20];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[21];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[22];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[23];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-24))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[24];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[25];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[26];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[27];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[28];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[29];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[30];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[31];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	


if(bOUT_FREE)
	{
	C1TFI1=can1_info[ptr_can1_tx_rd];
     C1TID1=can1_id[ptr_can1_tx_rd];
     C1TDA1=can1_data[ptr_can1_tx_rd];
     C1TDB1=can1_datb[ptr_can1_tx_rd];
     C1CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}

}	

//-----------------------------------------------
void can2_out(char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7)
{

can2_info[ptr_can2_tx_wr]=((8UL)<<16)&0x000f0000UL;
can2_id[ptr_can2_tx_wr]=0x0000009eUL;
*((char*)&can2_data[ptr_can2_tx_wr])=data0;
*(((char*)&can2_data[ptr_can2_tx_wr])+1)=data1;
*(((char*)&can2_data[ptr_can2_tx_wr])+2)=data2;
*(((char*)&can2_data[ptr_can2_tx_wr])+3)=data3;
*((char*)&can2_datb[ptr_can2_tx_wr])=data4;
*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=data5;
*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=data6;
*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=data7;	
ptr_can2_tx_wr++;
if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;



if(bOUT_FREE2)
	{
	C2TFI1=can2_info[ptr_can2_tx_rd];
     C2TID1=can2_id[ptr_can2_tx_rd];
     C2TDA1=can2_data[ptr_can2_tx_rd];
     C2TDB1=can2_datb[ptr_can2_tx_rd];
     C2CMR=0x00000021;
     ptr_can2_tx_rd++;
     if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
     bOUT_FREE2=0;	
	}

}	

//-----------------------------------------------
void can_adr_hndl(void)
{
	TXBUFF[2]=RXBUFF[3];
	TXBUFF[3]=RXBUFF[2];
	TXBUFF[4]=((RXBUFF[4]&0xF0)>>4)|((RXBUFF[4]&0x0f)<<4);
	TXBUFF[5]=((RXBUFF[5]&0xF0)>>4)|((RXBUFF[5]&0x0f)<<4);	
}	

//-----------------------------------------------
void can_in_an1(void)
{
if(!bIN) goto CAN_IN_AN_end; 
can_debug_plazma[0][2]++;

CAN_IN_AN_end:
bIN=0;
}

//-----------------------------------------------
void can_in_an2(void)
{
//char i;
//signed short temp_SS;
char slave_num;

if(!bIN2) goto CAN_IN_AN2_end; 

can_debug_plazma[1][2]++;

if((RXBUFF2[0]==sub_ind1)&&(RXBUFF2[1]==PUTID)&&(RXBUFF2[2]==0xdd)&&(RXBUFF2[3]==0xdd)&&(sub_ind==6))
	{
	mess_send(MESS2IND_HNDL,PARAM_U_AVT_GOOD,0,10);
	}


if((RXBUFF2[1]==PUTTM1)&&((RXBUFF2[0]&0x1f)>=0)&&((RXBUFF2[0]&0x1f)<20))
     {
     slave_num=RXBUFF2[0]&0x1f;
     
     if((RXBUFF2[0]&0xe0)==0)bps[slave_num]._device=dSRC;
     else if((RXBUFF2[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     	
	bps[slave_num]._buff[0]=RXBUFF2[2]; 
	bps[slave_num]._buff[1]=RXBUFF2[3];
	bps[slave_num]._buff[2]=RXBUFF2[4];
	bps[slave_num]._buff[3]=RXBUFF2[5];
	bps[slave_num]._buff[4]=RXBUFF2[6];
	bps[slave_num]._buff[5]=RXBUFF2[7];
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10;
	
 	if((bps[slave_num]._cnt==0)&&(bps[slave_num]._av&(1<<3))) avar_bps_hndl(slave_num,3,0);
     }

if((RXBUFF2[1]==PUTTM2)&&((RXBUFF2[0]&0x1f)>=0)&&((RXBUFF2[0]&0x1f)<9))
     {
     slave_num=RXBUFF2[0]&0x1f;  

     if((RXBUFF2[0]&0xe0)==0)bps[slave_num]._device=dSRC;
     else if((RXBUFF2[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     
	bps[slave_num]._buff[6]=RXBUFF2[2]; 
	bps[slave_num]._buff[7]=RXBUFF2[3];
	bps[slave_num]._buff[8]=RXBUFF2[4];
	bps[slave_num]._buff[9]=RXBUFF2[5];
	bps[slave_num]._buff[10]=RXBUFF2[6];
	bps[slave_num]._buff[11]=RXBUFF2[7];
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	//if((src[slave_num]._cnt==0)&&(src[slave_num]._av_net)) avar_s_hndl(slave_num,3,0); 
     }



CAN_IN_AN2_end:
bIN2=0;
}


/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
__irq void can_isr_rx1 (void) 
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;
//can_cnt++;

can_debug_plazma[0][0]++;

//rotor_can[0]++;
 if(C1ICR & 0x00000001L)
	{
	can_debug_plazma[0][1]++;
	if (!(C1RFS & 0xC0000400L))
    		{ // 11-bit ID, no RTR, matched a filter

    		//rotor_can[1]++;
    		// initialize destination pointer
    		// filter number is in lower 10 bits of C1RFS
    		pDest = (unsigned int *) &(gFullCANList[(C1RFS & 0x000003FFL)].Dat1);
    
    		// calculate contents for first entry into FullCAN list
    		buf = C1RFS & 0xC00F0000L; // mask FF, RTR and DLC
    		buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
    		buf |= C1RID & 0x000007FFL; // get CAN message ID

    		// now copy entire message to FullCAN list
    		*pDest = buf; 
    		pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
    		*pDest = C1RDA; 
    		pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
    		*pDest = C1RDB; 

    		// now set the sempahore to complete
    		buf |= 0x03000000L; // set semaphore to 11b
    		pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
    		*pDest = buf; 
    
		temp=(char)gFullCANList[0].DatA;
		if(temp==0x30) bR=0;
		else bR++;
	
		temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     	ptr=(char*)(&gFullCANList[0].DatA);
	
		if(!bR)
			{
			for(j=0;j<temp;j++)
				{
				RXBUFF[j]=*ptr;
				ptr++;
				}
			}
		else if(bR==1)
			{
			for(j=8;j<(temp+8);j++)
				{
				RXBUFF[j]=*ptr;
				ptr++;
				}                      
			
			} 		
	
	
	
		
		temp=((RXBUFF[1]&0x1f)+4);
    		//rotor_can[2]++;
		if((CRC1_in()==RXBUFF[temp+1])&&(CRC2_in()==RXBUFF[temp+2])&&bR)
			{
  
			bIN=1;
  			//rotor_can[3]++;
  			can_in_an1();
			}    
    
  		}

	C1CMR = 0x04; // release receive buffer
	}


VICVectAddr = 0xFFFFFFFFL; // acknowledge Interrupt

}

  
/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
__irq void can_isr_rx2 (void) 
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;
//can_cnt++;

can_debug_plazma[1][0]++;


	
if(C2ICR & 0x00000001L)
	{
	can_debug_plazma[1][1]++;	
	if (!(C2RFS & 0xC0000400L))
  		{ // 11-bit ID, no RTR, matched a filter

		//rotor_can[3]++;
    		// initialize destination pointer
    		// filter number is in lower 10 bits of C1RFS
    		pDest = (unsigned int *) &(gFullCANList[(C2RFS & 0x000003FFL)].Dat1);
    
    		// calculate contents for first entry into FullCAN list
    		buf = C2RFS & 0xC00F0000L; // mask FF, RTR and DLC
    		buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
    		buf |= C2RID & 0x000007FFL; // get CAN message ID

    		// now copy entire message to FullCAN list
    		*pDest = buf; 
    		pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
    		*pDest = C2RDA; 
    		pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
    		*pDest = C2RDB; 

    		// now set the sempahore to complete
    		buf |= 0x03000000L; // set semaphore to 11b
    		pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
    		*pDest = buf; 
    
		temp=(char)gFullCANList[0].DatA;
		/*if(temp==0x30) bR=0;
		else bR++;*/
	
		temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     	ptr=(char*)(&gFullCANList[0].DatA);
	
		for(j=0;j<temp;j++)
			{
			RXBUFF2[j]=*ptr;
			ptr++;
			}
		}
			
	bIN2=1;
	can_in_an2();


	C2CMR = 0x04; // release receive buffer
	}

VICVectAddr = 0xFFFFFFFFL; // acknowledge Interrupt

}

/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 

__irq void can_isr_tx1 (void) 
{
//unsigned int buf;
//unsigned int *pDest;
//char temp;
//char *ptr,j;
/*
can_tx_cnt++;

rotor_can[2]++;

if(C1ICR & 0x00000002L)
	{
	if(ptr_can1_tx_wr!=ptr_can1_tx_rd)
		{
		C1TFI1=can1_info[ptr_can1_tx_rd];
     	C1TID1=can1_id[ptr_can1_tx_rd];
     	C1TDA1=can1_data[ptr_can1_tx_rd];
     	C1TDB1=can1_datb[ptr_can1_tx_rd];
     	C1CMR=0x00000021;
     	ptr_can1_tx_rd++;
     	if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
		}
	else bOUT_FREE=1;
	}
	
else if(C2ICR & 0x00000002L)
	{
	if(ptr_can2_tx_wr!=ptr_can2_tx_rd)
		{
		C2TFI1=can1_info[ptr_can2_tx_rd];
     	C2TID1=can1_id[ptr_can2_tx_rd];
     	C2TDA1=can1_data[ptr_can2_tx_rd];
     	C2TDB1=can1_datb[ptr_can2_tx_rd];
     	C2CMR=0x00000021;
     	ptr_can2_tx_rd++;
     	if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
		}
	else bOUT_FREE2=1;
	} */
VICVectAddr = 0xFFFFFFFFL; // acknowledge Interrupt
}


/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 

__irq void can_isr_tx2 (void) 
{
//unsigned int buf;
//unsigned int *pDest;
//char temp;
//char *ptr,j;

can_tx_cnt++;

rotor_can[2]++;

/*if(C1ICR & 0x00000002L)
	{
	if(ptr_can1_tx_wr!=ptr_can1_tx_rd)
		{
		C1TFI1=can1_info[ptr_can1_tx_rd];
     	C1TID1=can1_id[ptr_can1_tx_rd];
     	C1TDA1=can1_data[ptr_can1_tx_rd];
     	C1TDB1=can1_datb[ptr_can1_tx_rd];
     	C1CMR=0x00000021;
     	ptr_can1_tx_rd++;
     	if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
		}
	else bOUT_FREE=1;
	}
	
else*/ if(C2ICR & 0x00000002L)
	{
	if(ptr_can2_tx_wr!=ptr_can2_tx_rd)
		{
		C2TFI1=can1_info[ptr_can2_tx_rd];
     	C2TID1=can1_id[ptr_can2_tx_rd];
     	C2TDA1=can1_data[ptr_can2_tx_rd];
     	C2TDB1=can1_datb[ptr_can2_tx_rd];
     	C2CMR=0x00000021;
     	ptr_can2_tx_rd++;
     	if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
		}
	else bOUT_FREE2=1;
	}
VICVectAddr = 0xFFFFFFFFL; // acknowledge Interrupt
}

/***************************************************************************/
__irq void can_isr_err (void) 
{
//unsigned int buf;
//unsigned int *pDest;
//char temp;
//char *ptr,j;


//rotor_can[2]++;

if(C2ICR & 0x00000080L)
	{
	SET_REG(C2GSR,3,24,8);
	C2MOD=0;
	bOUT_FREE2=1;
	}
VICVectAddr = 0xFFFFFFFFL; // acknowledge Interrupt
}


/**************************************************************************
Initialization of a CAN interface
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short can1_init (unsigned short can_rx_vector, unsigned short can_tx_vector, unsigned int can_btr)
{
unsigned int *pSFR; // pointer into SFR space
unsigned int *pSFR2; // pointer into SFR space
unsigned int offset; // offset added to pSFR
                                               
PINSEL1 |= 0x00040000L; // Set bit 18
offset = 0x00000000L; // Use 1st set of CAN registers

// Reset and disable all message filters
gCANFilter = 0;

// Acceptance Filter Mode Register = off !
AFMR = 0x00000001L;

pSFR = (unsigned int *) &C1MOD + offset; // Select Mode register
*pSFR = 1; // Go into Reset mode

pSFR = (unsigned int *) &C1IER + offset; // Select Interrupt Enable Register
*pSFR = 0;// Disable All Interrupts

pSFR = (unsigned int *) &C1GSR + offset; // Select Status Register
*pSFR = 0; // Clear Status register

pSFR = (unsigned int *) &C1BTR + offset; // Select BTR Register
*pSFR = can_btr; // Set bit timing

  // Set and enable receive interrupt
pSFR = (unsigned int *) &VICVectAddr0;
pSFR += can_rx_vector; // Set to desired interrupt vector
  
pSFR2 = (unsigned int *) &VICVectCntl0;
pSFR2 += can_rx_vector; // Set to desired interrupt control

// Set interrupt vector
*pSFR = (unsigned long) can_isr_rx1; 
// Use this Interrupt for CAN Rx1 Interrupt
*pSFR2 = 0x20 | 26;
// Enable CAN Rx1 Interrupt
//VICIntEnable |= 0x04000000L;  

  // Set and enable transmit interrupt
pSFR = (unsigned int *) &VICVectAddr0;
pSFR += can_tx_vector; // Set to desired interrupt vector
  
pSFR2 = (unsigned int *) &VICVectCntl0;
pSFR2 += can_tx_vector; // Set to desired interrupt control

// Set interrupt vector
*pSFR = (unsigned long) can_isr_tx1; 
// Use this Interrupt for CAN Rx1 Interrupt
*pSFR2 = 0x20 | 20;
// Enable CAN Rx1 Interrupt
VICIntEnable = 0x00100000L;

pSFR = (unsigned int *) &C1IER + offset; // Select Interrupt register
*pSFR = 3; // Enable Receive & Transmit Interrupt

// Enter Normal Operating Mode
pSFR = (unsigned int *) &C1MOD + offset; // Select Mode register
*pSFR = 0; // Operating Mode 

return 1;	
}

/**************************************************************************
Initialization of a CAN interface
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short can2_init (unsigned short can_rx_vector, unsigned short can_tx_vector, unsigned int can_btr)
{
unsigned int *pSFR; // pointer into SFR space
unsigned int *pSFR2; // pointer into SFR space
unsigned int offset; // offset added to pSFR
                                               
PINSEL1 |= 0x00014000L; // Set bit 18
offset = 0x00001000L; // Use 1st set of CAN registers

// Reset and disable all message filters
gCANFilter = 0;

// Acceptance Filter Mode Register = off !
AFMR = 0x00000001L;

pSFR = (unsigned int *) &C1MOD + offset; // Select Mode register
*pSFR = 1; // Go into Reset mode

pSFR = (unsigned int *) &C1IER + offset; // Select Interrupt Enable Register
*pSFR = 0;// Disable All Interrupts

pSFR = (unsigned int *) &C1GSR + offset; // Select Status Register
*pSFR = 0; // Clear Status register

pSFR = (unsigned int *) &C1BTR + offset; // Select BTR Register
*pSFR = can_btr; // Set bit timing



  // Set and enable error interrupt
pSFR = (unsigned int *) &VICVectAddr0;
pSFR += 12; // Set to desired interrupt vector
  
pSFR2 = (unsigned int *) &VICVectCntl0;
pSFR2 += 12; // Set to desired interrupt control

// Set interrupt vector
*pSFR = (unsigned long) can_isr_err; 
// Use this Interrupt for CAN Rx1 Interrupt
*pSFR2 = 0x20 | 19;
// Enable CAN Rx1 Interrupt
VICIntEnable = 1<<19; 



  // Set and enable receive interrupt
pSFR = (unsigned int *) &VICVectAddr0;
pSFR += can_rx_vector; // Set to desired interrupt vector
  
pSFR2 = (unsigned int *) &VICVectCntl0;
pSFR2 += can_rx_vector; // Set to desired interrupt control

// Set interrupt vector
*pSFR = (unsigned long) can_isr_rx2; 
// Use this Interrupt for CAN Rx1 Interrupt
*pSFR2 = 0x20 | 27;
// Enable CAN Rx1 Interrupt
VICIntEnable = 0x08000000L;  

  // Set and enable transmit interrupt
pSFR = (unsigned int *) &VICVectAddr0;
pSFR += can_tx_vector; // Set to desired interrupt vector
  
pSFR2 = (unsigned int *) &VICVectCntl0;
pSFR2 += can_tx_vector; // Set to desired interrupt control

// Set interrupt vector
*pSFR = (unsigned long) can_isr_tx2; 
// Use this Interrupt for CAN Rx1 Interrupt
*pSFR2 = 0x20 | 21;
// Enable CAN Rx1 Interrupt
VICIntEnable = 0x00200000L;

pSFR = (unsigned int *) &C1IER + offset; // Select Interrupt register
*pSFR = 128+3; // Enable Receive & Transmit Interrupt

// Enter Normal Operating Mode
pSFR = (unsigned int *) &C1MOD + offset; // Select Mode register
*pSFR = 0; // Operating Mode 

return 1;
}

/**************************************************************************
Setting a CAN receive filter
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short FullCAN_SetFilter (
  unsigned short can_port, // CAN interface number
  unsigned int CANID // 11-bit CAN ID
  )
{
unsigned int p, n;
unsigned int buf0, buf1;
unsigned int ID_lower, ID_upper;
unsigned int candata;
unsigned int *pAddr;

#ifdef REVISION_C
  if ((can_port < 0) || (can_port > (MAX_CANPORTS-1))) 
#endif

#ifndef REVISION_C
  if ((can_port < 1) || (can_port > (MAX_CANPORTS))) 
#endif



 { // Illegal value for can_port
    return 0;
  }

  // Acceptance Filter Mode Register = off !
  AFMR = 0x00000001L;

  if (gCANFilter == 0)
  { // First call, init entry zero
    gFullCANList[0].Dat1 = 0x000037FFL; // CAN 1, disabled and unused
  }
  if (gCANFilter >= MAX_FILTERS)
  {
    return 0;
  }

  CANID &= 0x000007FFL; // Mask out 11-bit ID
  CANID |= (can_port << 13); // Put can_port info in bits 13-15

  // Filters must be sorted by interface, then by priority
  // new filter is sorted into array
  p = 0;
  while (p < gCANFilter) // loop through all existing filters 
  {
    if ((gFullCANList[p].Dat1 & 0x0000FFFFL) > CANID)
    {
      break;
    }
    p++;
  }

  // insert new filter here
  buf0 = gFullCANList[p].Dat1; // save current entry
  gFullCANList[p].Dat1 = CANID; // insert the new entry

  // move all remaining entries one row up
  gCANFilter++;
  while (p < gCANFilter)
  {
    p++;
    buf1 = gFullCANList[p].Dat1;
    gFullCANList[p].Dat1 = buf0;
    buf0 = buf1;
  }

  // Now work on Acceptance Filter Configuration     
  // Set CAN filter for 11-bit standard identifiers
  p = 0;

  // Set pointer for Standard Frame Individual
  // Standard Frame Explicit
  SFF_sa = p;

  pAddr = (unsigned int *) ACCEPTANCE_FILTER_RAM_BASE;
  for (n = 0; n < ((gCANFilter+1)/2); n++)
  {
    ID_lower = gFullCANList[n * 2].Dat1 & 0x0000FFFFL;
    ID_upper = gFullCANList[n * 2 + 1].Dat1 & 0x0000FFFFL;
    candata = (ID_lower << 16) + ID_upper;
    *pAddr = candata;
    p += 4;
    pAddr++;
  }

  // p is still pointing to ENDofTable;
  
  // Set pointer for Standard Frame Groups
  // Standard Frame Group Start Address Register
  SFF_GRP_sa = p;

  // Set pointer for Extended Frame Individual
  // Extended Frame Start Address Register
  EFF_sa = p;

  // Set pointer for Extended Frame Groups
  // Extended Frame Group Start Address Register
  EFF_GRP_sa = p;

  // Set ENDofTable 
  // End of AF Tables Register
  ENDofTable = p;

  // Acceptance Filter Mode Register, start using filter
  AFMR = 0;
  
  return 1;
}






