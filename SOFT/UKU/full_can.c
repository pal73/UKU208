#include "main.h"
#include <LPC17xx.H>
#include "full_can.h"
#include "cmd.h"
#include "mess.h"
#include "global_define.h"
#include "avar_hndl.h"
#include "eeprom_map.h"
#include "control.h"
#include "25lc640.h"

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




// FullCAN Message List
FULLCAN_MSG volatile gFullCANList[MAX_FILTERS];

char bR;
char RXBUFF[40],TXBUFF[40];
char bIN,bIN2;
char bd_dumm[25];
char bd[25];
char TX_len;
//char bOUT;
char RXBUFF2[40],TXBUFF2[40];
extern char can_tx_cnt;
extern char can_tx_cnt2;
char bOUT_FREE=1;
char bOUT_FREE2=1;
char rotor_rotor_rotor[2];
char can_tx_cnt;
char can_rotor[10];

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
volatile uint32_t CANStatus;

char can_reset_cnt=0;

char plazma_can_pal[20];
char cnt_can_pal;
char plazma_can_pal_index;

// char can_reset_cnt=0;
char plazma_can;
char plazma_can1,plazma_can2,plazma_can3,plazma_can4;
short can2_tx_cnt;
char ccc_plazma[20];

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
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[18];
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
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}

}	

//-----------------------------------------------
void can2_out_adr(char* ptr,char num)
{

if(num<=8)
	{
	can2_info[ptr_can2_tx_wr]=(((long)num)<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	}
	
else if(num<=16)
	{
	
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(((long)(num-8))<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[8];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[9];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[10];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[11];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[12];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[13];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[14];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[15];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
		
	}	

else if(num<=24)
	{
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;

	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[8];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[9];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[10];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[11];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[12];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[13];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[14];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[15];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(((long)(num-16))<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[16];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[17];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[18];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[19];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[20];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[21];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[22];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[23];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;	
	}	

else if(num<=32)
	{
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[0];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[1];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[2];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[3];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[4];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[5];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[6];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[7];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;

	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[8];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[9];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[10];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[11];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[12];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[13];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[14];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[15];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(8UL<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[16];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[17];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[18];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[19];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[20];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[21];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[22];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[23];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;
	
	can2_info[ptr_can2_tx_wr]=(((long)(num-24))<<16)&0x000f0000UL;
	can2_id[ptr_can2_tx_wr]=0x0000009eUL;
	*((char*)&can2_data[ptr_can2_tx_wr])=ptr[24];
	*(((char*)&can2_data[ptr_can2_tx_wr])+1)=ptr[25];
	*(((char*)&can2_data[ptr_can2_tx_wr])+2)=ptr[26];
	*(((char*)&can2_data[ptr_can2_tx_wr])+3)=ptr[27];
	*((char*)&can2_datb[ptr_can2_tx_wr])=ptr[28];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=ptr[29];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=ptr[30];
	*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=ptr[31];	
	ptr_can2_tx_wr++;
	if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;	
	}	


if(bOUT_FREE2)
	{
	LPC_CAN2->TFI1=can2_info[ptr_can2_tx_rd];
     LPC_CAN2->TID1=can2_id[ptr_can2_tx_rd];
     LPC_CAN2->TDA1=can2_data[ptr_can2_tx_rd];
     LPC_CAN2->TDB1=can2_datb[ptr_can2_tx_rd];
     LPC_CAN2->CMR=0x00000021;
     ptr_can2_tx_rd++;
     if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
     bOUT_FREE2=0;	
	}

}

//-----------------------------------------------
void paking(char* data_ptr,char data_len)
{
char i,ii,iii;
for(i=0;i<data_len;i++)
	{
	ii=data_len+(i/7);
	iii=i-(7*(i/7)); 
	if(iii==0) data_ptr[ii]=0;
	data_ptr[ii]<<=1;
	if(data_ptr[i]&0x01)
		{
		data_ptr[ii]|=0x01;//(1<<(6-iii));
		}                      
	else 
		{
		data_ptr[ii]&=0xfe;//~(1<<(6-iii));
		}              
	data_ptr[i]>>=1;	        
	data_ptr[i]|=0x80;	
	}                       
for(i=data_len;i<(data_len+(data_len/7)+1);i++)
	{
	data_ptr[i]|=0x80;
	}	
}

//-----------------------------------------------
void can1_out(char dat0,char dat1,char dat2,char dat3,char dat4,char dat5,char dat6,char dat7)
{
//new_rotor[0]++;
can1_info[ptr_can1_tx_wr]=((8UL)<<16)&0x000f0000UL;
can1_id[ptr_can1_tx_wr]=0x0000009eUL;
*((char*)&can1_data[ptr_can1_tx_wr])=dat0;
*(((char*)&can1_data[ptr_can1_tx_wr])+1)=dat1;
*(((char*)&can1_data[ptr_can1_tx_wr])+2)=dat2;
*(((char*)&can1_data[ptr_can1_tx_wr])+3)=dat3;
*((char*)&can1_datb[ptr_can1_tx_wr])=dat4;
*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=dat5;
*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=dat6;
*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=dat7;	
ptr_can1_tx_wr++;
if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;


if(bOUT_FREE)
	{
	//rotor_rotor_rotor[1]++;
//	new_rotor[1]++;
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}
}	

//-----------------------------------------------
void can2_out(char dat0,char dat1,char dat2,char dat3,char dat4,char dat5,char dat6,char dat7)
{

//new_rotor[0]++;
can2_info[ptr_can2_tx_wr]=((8UL)<<16)&0x000f0000UL;
can2_id[ptr_can2_tx_wr]=0x0000018eUL;
*((char*)&can2_data[ptr_can2_tx_wr])=dat0;
*(((char*)&can2_data[ptr_can2_tx_wr])+1)=dat1;
*(((char*)&can2_data[ptr_can2_tx_wr])+2)=dat2;
*(((char*)&can2_data[ptr_can2_tx_wr])+3)=dat3;
*((char*)&can2_datb[ptr_can2_tx_wr])=dat4;
*(((char*)&can2_datb[ptr_can2_tx_wr])+1)=dat5;
*(((char*)&can2_datb[ptr_can2_tx_wr])+2)=dat6;
*(((char*)&can2_datb[ptr_can2_tx_wr])+3)=dat7;	
ptr_can2_tx_wr++;
if(ptr_can2_tx_wr>=8)ptr_can2_tx_wr=0;


if(bOUT_FREE2)
	{
	//rotor_rotor_rotor[1]++;
//	new_rotor[1]++;
	LPC_CAN2->TFI1=can2_info[ptr_can2_tx_rd];
     LPC_CAN2->TID1=can2_id[ptr_can2_tx_rd];
     LPC_CAN2->TDA1=can2_data[ptr_can2_tx_rd];
     LPC_CAN2->TDB1=can2_datb[ptr_can2_tx_rd];
     LPC_CAN2->CMR=0x00000021;
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
void can_in_an2(void)
{
if(!bIN) goto CAN_IN_AN_end; 
can_debug_plazma[0][1]++;
 

// Версия ПО
if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x01))
	{ 
     

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+4;
	can_adr_hndl();
	TXBUFF[6]=0x01;
	TXBUFF[7]=3;
	TXBUFF[8]=5;
	TXBUFF[9]=CRC1_out();
	TXBUFF[10]=CRC2_out();
	TX_len=11;

	can2_out_adr(TXBUFF,11);  
	}
// Общее состояние источника 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB0))
	{ 
	can_debug_plazma[0][2]++;
    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+13;
	can_adr_hndl(); 
	
	TXBUFF[6]=0xB0;
	
	//net_U=231;
	//net_F=501;

	if(net_U>=254)TXBUFF[7]=0xff;
	else TXBUFF[7]=net_U;
	
	if(net_F<400) TXBUFF[8]=1;
	else if(net_F>654) TXBUFF[8]=0xff;
	else TXBUFF[8]=(unsigned char)((net_F-400)+1);
	
	TXBUFF[9]=*((char*)(&load_U));
	TXBUFF[10]=*(((char*)(&load_U))+1);
	TXBUFF[11]=*((char*)(&load_I));
	TXBUFF[12]=*(((char*)(&load_I))+1);
	
	TXBUFF[13]=0xcc;
	TXBUFF[13]|=4;(NUMIST&0x07);
	TXBUFF[13]|=((NUMBAT&0x03)<<4);
	

	TXBUFF[14]=0x80;
	if(avar_stat&0x00000001)TXBUFF[14]|=0x01;
	if(PAR)TXBUFF[14]|=0x40;
	
	TXBUFF[15]=25;//tbat[2];
     
	paking(&TXBUFF[6],10);
	
	TXBUFF[18]=CRC1_out();
	TXBUFF[19]=CRC2_out();
	TX_len=20;
				
	can2_out_adr(TXBUFF,20);  
	} 

// Состояние Батареи №1 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB1)&&(RXBUFF[7]==0x01))
	{ 
	signed short temp_S;

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+14;
	can_adr_hndl();
	TXBUFF[6]=0xB1;
	TXBUFF[7]=1;
	
	if(BAT_IS_ON[0]!=bisON) TXBUFF[8]=0xFF;
	else if(bat[0]._av)TXBUFF[8]=0xF7;
	else TXBUFF[8]=0xF0;
	
	if((spc_stat==spcKE))TXBUFF[9]=0xF9;
	else if(spc_stat==spcVZ)TXBUFF[9]=0xF8;                      
	else TXBUFF[9]=0xF0;
	
	
	temp_S=(bat[0]._Ib/10)+10000;
			
	TXBUFF[10]=*((char*)(&bat[0]._Ub));
	TXBUFF[11]=*(((char*)(&bat[0]._Ub))+1);
	TXBUFF[12]=*((char*)(&temp_S));
	TXBUFF[13]=*(((char*)(&temp_S))+1);
	TXBUFF[14]=bat[0]._Tb;
	TXBUFF[15]=bat[0]._zar; 
	
	if(BAT_C_REAL[0]==0x5555)TXBUFF[16]=BAT_C_NOM[0];
	else TXBUFF[16]=BAT_C_REAL[0]/10;	
	
    	paking(&TXBUFF[6],11);
    
	TXBUFF[19]=CRC1_out();
	TXBUFF[20]=CRC2_out();
	TX_len=21; 
 
	can2_out_adr(TXBUFF,21);  
	}	

// Состояние Батареи №2 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB1)&&(RXBUFF[7]==0x02))
	{ 
	signed short temp_S;

    TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+14;
	can_adr_hndl();
	TXBUFF[6]=0xB1;
	TXBUFF[7]=2;
	
	if(BAT_IS_ON[1]!=bisON) TXBUFF[8]=0xFF;
	else if(bat[1]._av)TXBUFF[8]=0xF7;
	else TXBUFF[8]=0xF0;

	if((spc_stat==spcKE))TXBUFF[9]=0xF9;
	else if(spc_stat==spcVZ)TXBUFF[9]=0xF8;                      
	else TXBUFF[9]=0xF0;
	
	
	temp_S=(bat[1]._Ib/10)+10000;
			
	TXBUFF[10]=*((char*)(&bat[1]._Ub));
	TXBUFF[11]=*(((char*)(&bat[1]._Ub))+1);
	TXBUFF[12]=*((char*)(&temp_S));
	TXBUFF[13]=*(((char*)(&temp_S))+1);
	TXBUFF[14]=bat[1]._Tb;
	TXBUFF[15]=bat[1]._zar; 
	
	if(BAT_C_REAL[1]==0x5555)TXBUFF[16]=BAT_C_NOM[1];
	else TXBUFF[16]=BAT_C_REAL[1]/10;	
	
    	paking(&TXBUFF[6],11);
    
	TXBUFF[19]=CRC1_out();
	TXBUFF[20]=CRC2_out();
	TX_len=21; 
 
	can2_out_adr(TXBUFF,21);  
	}		
		



	// Состояние БПС1 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x01))
	{ 
    //	plazma++;

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=1;
		
	
	if(NUMIST<1)TXBUFF[8]=0xff;	
	else if(bps[0]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[0]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[0]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[0]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[0]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[0]._Uii));
	TXBUFF[10]=*(((char*)(&bps[0]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[0]._Ii));
	TXBUFF[12]=*(((char*)(&bps[0]._Ii))+1);
	TXBUFF[13]=bps[0]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}	
	// Состояние БПС2 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x02))
	{ 
    //	plazma++;

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=2;
		
	
	if(NUMIST<3)TXBUFF[8]=0xff;	
	else if(bps[1]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[1]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[1]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[1]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[1]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[1]._Uii));
	TXBUFF[10]=*(((char*)(&bps[1]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[1]._Ii));
	TXBUFF[12]=*(((char*)(&bps[1]._Ii))+1);
	TXBUFF[13]=bps[1]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}	


	// Состояние БПС3 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x03))
	{ 
    //	plazma++;

    	TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=3;
		
	
	if(NUMIST<3)TXBUFF[8]=0xff;	
	else if(bps[2]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[2]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[2]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[2]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[2]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[2]._Uii));
	TXBUFF[10]=*(((char*)(&bps[2]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[2]._Ii));
	TXBUFF[12]=*(((char*)(&bps[2]._Ii))+1);
	TXBUFF[13]=bps[2]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}	

	// Состояние БПС4 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xc0)==0x40)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0xB2)&&(RXBUFF[7]==0x04))
	{ 
    //	plazma++;

    TXBUFF[0]=0x30;
	TXBUFF[1]=(RXBUFF[1]&0xa0)+11;
	can_adr_hndl();
	TXBUFF[6]=0xB2;
	TXBUFF[7]=4;
		
	
	if(NUMIST<4)TXBUFF[8]=0xff;	
	else if(bps[3]._state==bsWRK)TXBUFF[8]=0xf1; 
	else if(bps[3]._av&(1<<3))TXBUFF[8]=0xf4;
	else if(bps[3]._av&(1<<0))TXBUFF[8]=0xf5;
	else if(bps[3]._av&(1<<1))TXBUFF[8]=0xf5;
	else if(bps[3]._av&(1<<2))TXBUFF[8]=0xf7;
	else TXBUFF[8]=0xf0;

	TXBUFF[9]=*((char*)(&bps[3]._Uii));
	TXBUFF[10]=*(((char*)(&bps[3]._Uii))+1);
	TXBUFF[11]=*((char*)(&bps[3]._Ii));
	TXBUFF[12]=*(((char*)(&bps[3]._Ii))+1);
	TXBUFF[13]=bps[3]._Ti;
	
    	paking(&TXBUFF[6],8);
    
    	TXBUFF[16]=CRC1_out();
	TXBUFF[17]=CRC2_out();
	TX_len=18;

	can2_out_adr(TXBUFF,18);  
	}

// Выравнивающий заряд  часа
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x03)
	&&((RXBUFF[7])&&(RXBUFF[7]<25)))
 	  
	{ 
     char temp;      		

	temp=vz_start(RXBUFF[7]);

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x03;
	TXBUFF[7]=0x01;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);
	}

// Выключение выравнивающего заряда
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x08))
 	  
	{ 
	if(spc_stat==spcVZ) spc_stat=spcOFF;

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
	can_adr_hndl();
	TXBUFF[6]=0x08;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;
	can2_out_adr(TXBUFF,9);
	}


// Контроль ёмкости батареи №1
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x04)
	&&(RXBUFF[7]==0x01))
	  
	{
	ke_start(0);

	if(ke_start_stat==kssYES)TXBUFF[7]=0xff;
	else TXBUFF[7]=0x01;

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x04;
	TXBUFF[7]=0x01;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);
	} 
	
// Контроль ёмкости батареи №2
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x04)
	&&(RXBUFF[7]==0x02))
	  
	{
	ke_start(1);

	if(ke_start_stat==kssYES)TXBUFF[7]=0xff;
	else TXBUFF[7]=0x01;

     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x04;
	TXBUFF[7]=0x02;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);
	}	
	
	// Выключение контроля ёмкости 
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x07))
	  
	{
   	
	if(spc_stat==spcKE)spc_stat=spcOFF;
	
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
	can_adr_hndl();
	TXBUFF[6]=0x07;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;
	can2_out_adr(TXBUFF,9);
	}



// БПС1 - выключить
if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x01))
	  
	{
	bps[0]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x01;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;
	can2_out_adr(TXBUFF,10);

	}

// БПС2 - выключить
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x02))
	  
	{                  
	bps[1]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
 	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x02;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;     

	can2_out_adr(TXBUFF,10);

	}

// БПС3 - выключить
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x03))
	  
	{                  
	bps[2]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
 	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x03;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;     

	can2_out_adr(TXBUFF,10);

	}


// БПС4 - выключить
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x05)
	&&(RXBUFF[7]==0x04))
	  
	{                  
	bps[3]._ist_blok_host_cnt=3000;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+3;
 	can_adr_hndl();
	TXBUFF[6]=0x05;
	TXBUFF[7]=0x03;
	TXBUFF[8]=CRC1_out();
	TXBUFF[9]=CRC2_out();
	TX_len=10;     

	can2_out_adr(TXBUFF,10);

	}


//Разблокировать все источники
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x06))
	  
	{                  
	bps[0]._ist_blok_host_cnt=0;
	bps[1]._ist_blok_host_cnt=0;
	bps[2]._ist_blok_host_cnt=0;
	bps[3]._ist_blok_host_cnt=0;
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
 	can_adr_hndl();
	TXBUFF[6]=0x05;

	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;     

	can2_out_adr(TXBUFF,9);

	}

// Включить параллельную работу источников
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x0a))
	  
	{                  
	PAR=1;
	lc640_write_int(EE_PAR,PAR);
	
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
 	can_adr_hndl();
	TXBUFF[6]=0x0a;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();

	can2_out_adr(TXBUFF,9);    

	}

// Выключить параллельную работу источников
else if((RXBUFF[0]==0x30)&&((RXBUFF[1]&0xe0)==0x60)&&
	((RXBUFF[4]&0xf0)==0xe0)&&((RXBUFF[5]&0xf0)==0x20)&&(RXBUFF[6]==0x0b))
	  
	{                  
	PAR=0;
	lc640_write_int(EE_PAR,PAR);
	
     TXBUFF[0]=0x30;
	TXBUFF[1]=0x20+2;
 	can_adr_hndl();
	TXBUFF[6]=0x0b;
	TXBUFF[7]=CRC1_out();
	TXBUFF[8]=CRC2_out();
	TX_len=9;     

	can2_out_adr(TXBUFF,9);

	}

CAN_IN_AN_end:
bIN=0;
}
//-----------------------------------------------
void can_in_an1(void)
{
//char i;
//signed short temp_SS;
char slave_num;

//if(!bIN2) goto CAN_IN_AN1_end; 

//can_debug_plazma[1][2]++;
can_rotor[1]++;

if((RXBUFF[0]==sub_ind1)&&(RXBUFF[1]==PUTID)&&(RXBUFF[2]==0xdd)&&(RXBUFF[3]==0xdd)/*&&(sub_ind==6)*/)
	{
	mess_send(MESS2IND_HNDL,PARAM_U_AVT_GOOD,0,10);
	can_reset_cnt=0;
	}


if((RXBUFF[1]==PUTTM1)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
     {
	//can_debug_plazma[1][2]++;
     slave_num=RXBUFF[0]&0x1f;
     
    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     	
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];


/*	can_slot[slave_num,0]=RXBUFF[0];
	can_slot[slave_num,1]=RXBUFF[1];
	can_slot[slave_num,2]=RXBUFF[2];
	can_slot[slave_num,3]=RXBUFF[3];
	can_slot[slave_num,4]=RXBUFF[4];
	can_slot[slave_num,5]=RXBUFF[5];
	can_slot[slave_num,6]=RXBUFF[6];
	can_slot[slave_num,7]=RXBUFF[7]; */
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10;
	
 	if((bps[slave_num]._cnt==0)&&(bps[slave_num]._av&(1<<3))) avar_bps_hndl(slave_num,3,0);

	can_reset_cnt=0;
     }

if((RXBUFF[1]==PUTTM2)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
     slave_num=RXBUFF[0]&0x1f;  

    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     
	bps[slave_num]._buff[6]=RXBUFF[2]; 
	bps[slave_num]._buff[7]=RXBUFF[3];
	bps[slave_num]._buff[8]=RXBUFF[4];
	bps[slave_num]._buff[9]=RXBUFF[5];
	bps[slave_num]._buff[10]=RXBUFF[6];
	bps[slave_num]._buff[11]=RXBUFF[7];	


/*	can_slot[slave_num,8]=RXBUFF[0];
	can_slot[slave_num,9]=RXBUFF[1];
	can_slot[slave_num,10]=RXBUFF[2];
	can_slot[slave_num,11]=RXBUFF[3];
	can_slot[slave_num,12]=RXBUFF[4];
	can_slot[slave_num,13]=RXBUFF[5];
	can_slot[slave_num,14]=RXBUFF[6];
	can_slot[slave_num,15]=RXBUFF[7]; */
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	//if((src[slave_num]._cnt==0)&&(src[slave_num]._av_net)) avar_s_hndl(slave_num,3,0); 
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==PUTTM1INV2)&&((RXBUFF[0]&0x1f)>=MINIM_INV_ADRESS)&&((RXBUFF[0]&0x1f)<MINIM_INV_ADRESS+NUMINV))
     {
	//can_debug_plazma[1][2]++;
     slave_num=RXBUFF[0]&0x1f;

	plazma_can_inv[0]++;
     
    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     	
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];


/*	can_slot[slave_num,0]=RXBUFF[0];
	can_slot[slave_num,1]=RXBUFF[1];
	can_slot[slave_num,2]=RXBUFF[2];
	can_slot[slave_num,3]=RXBUFF[3];
	can_slot[slave_num,4]=RXBUFF[4];
	can_slot[slave_num,5]=RXBUFF[5];
	can_slot[slave_num,6]=RXBUFF[6];
	can_slot[slave_num,7]=RXBUFF[7]; */
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10;
	
 	if((bps[slave_num]._cnt==0)&&(bps[slave_num]._av&(1<<3))) avar_bps_hndl(slave_num,3,0);

	can_reset_cnt=0;
     }

if((RXBUFF[1]==PUTTM2INV2)&&((RXBUFF[0]&0x1f)>=MINIM_INV_ADRESS)&&((RXBUFF[0]&0x1f)<MINIM_INV_ADRESS+NUMINV))
 	{
     slave_num=RXBUFF[0]&0x1f;
	
	plazma_can_inv[1]++;  

    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     
	bps[slave_num]._buff[6]=RXBUFF[2]; 
	bps[slave_num]._buff[7]=RXBUFF[3];
	bps[slave_num]._buff[8]=RXBUFF[4];
	bps[slave_num]._buff[9]=RXBUFF[5];
	bps[slave_num]._buff[10]=RXBUFF[6];
	bps[slave_num]._buff[11]=RXBUFF[7];	


/*	can_slot[slave_num,8]=RXBUFF[0];
	can_slot[slave_num,9]=RXBUFF[1];
	can_slot[slave_num,10]=RXBUFF[2];
	can_slot[slave_num,11]=RXBUFF[3];
	can_slot[slave_num,12]=RXBUFF[4];
	can_slot[slave_num,13]=RXBUFF[5];
	can_slot[slave_num,14]=RXBUFF[6];
	can_slot[slave_num,15]=RXBUFF[7]; */
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	//if((src[slave_num]._cnt==0)&&(src[slave_num]._av_net)) avar_s_hndl(slave_num,3,0); 
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==PUTTM3INV2)&&((RXBUFF[0]&0x1f)>=MINIM_INV_ADRESS)&&((RXBUFF[0]&0x1f)<MINIM_INV_ADRESS+NUMINV))
 	{
     slave_num=RXBUFF[0]&0x1f; 

	plazma_can_inv[2]++; 

    if((RXBUFF[0]&0xe0)==0)bps[slave_num]._device=dSRC;
    else if((RXBUFF[0]&0xe0)==0x40)bps[slave_num]._device=dINV;
     
	bps[slave_num]._buff[12]=RXBUFF[2]; 
	bps[slave_num]._buff[13]=RXBUFF[3];
	bps[slave_num]._buff[14]=RXBUFF[4];
	bps[slave_num]._buff[15]=RXBUFF[5];
	bps[slave_num]._buff[16]=RXBUFF[6];
	bps[slave_num]._buff[17]=RXBUFF[7];	


/*	can_slot[slave_num,8]=RXBUFF[0];
	can_slot[slave_num,9]=RXBUFF[1];
	can_slot[slave_num,10]=RXBUFF[2];
	can_slot[slave_num,11]=RXBUFF[3];
	can_slot[slave_num,12]=RXBUFF[4];
	can_slot[slave_num,13]=RXBUFF[5];
	can_slot[slave_num,14]=RXBUFF[6];
	can_slot[slave_num,15]=RXBUFF[7]; */
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	//if((src[slave_num]._cnt==0)&&(src[slave_num]._av_net)) avar_s_hndl(slave_num,3,0); 
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==PUTTM1BYPS))
     {
	//can_debug_plazma[1][2]++;
     byps._adress=RXBUFF[0]&0x1f;
     
     	
	byps._Iout=(signed short)RXBUFF[2]+(((signed short)RXBUFF[3])*256);
	byps._Pout=(signed short)RXBUFF[4]+(((signed short)RXBUFF[5])*256);
	byps._Uout=(signed short)RXBUFF[6]+(((signed short)RXBUFF[7])*256);
	
	byps._cnt=0;
     }

if((RXBUFF[1]==PUTTM2BYPS))
 	{
	byps._T=(char)RXBUFF[2];
	byps._flags=(char)RXBUFF[3];
	byps._Unet=(signed short)RXBUFF[4]+(((signed short)RXBUFF[5])*256);
	byps._Uin=(signed short)RXBUFF[6]+(((signed short)RXBUFF[7])*256);

	byps._cnt=0;
   	}

if((RXBUFF[1]==PUTTM_IBATMETER)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
    slave_num=RXBUFF[0]&0x1f;  

    bps[slave_num]._device=dIBAT_METR;
         
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];	


/*	can_slot[slave_num,8]=RXBUFF[0];
	can_slot[slave_num,9]=RXBUFF[1];
	can_slot[slave_num,10]=RXBUFF[2];
	can_slot[slave_num,11]=RXBUFF[3];
	can_slot[slave_num,12]=RXBUFF[4];
	can_slot[slave_num,13]=RXBUFF[5];
	can_slot[slave_num,14]=RXBUFF[6];
	can_slot[slave_num,15]=RXBUFF[7]; */
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	//if((src[slave_num]._cnt==0)&&(src[slave_num]._av_net)) avar_s_hndl(slave_num,3,0); 
	can_reset_cnt=0;
   	}

if((RXBUFF[1]==PUTTM_NET)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
    slave_num=RXBUFF[0]&0x1f;  

    bps[slave_num]._device=dNET_METR;
         
	bps[slave_num]._buff[0]=RXBUFF[2]; 
	bps[slave_num]._buff[1]=RXBUFF[3];
	bps[slave_num]._buff[2]=RXBUFF[4];
	bps[slave_num]._buff[3]=RXBUFF[5];
	bps[slave_num]._buff[4]=RXBUFF[6];
	bps[slave_num]._buff[5]=RXBUFF[7];	


/*	can_slot[slave_num,8]=RXBUFF[0];
	can_slot[slave_num,9]=RXBUFF[1];
	can_slot[slave_num,10]=RXBUFF[2];
	can_slot[slave_num,11]=RXBUFF[3];
	can_slot[slave_num,12]=RXBUFF[4];
	can_slot[slave_num,13]=RXBUFF[5];
	can_slot[slave_num,14]=RXBUFF[6];
	can_slot[slave_num,15]=RXBUFF[7]; */
	
	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	//if((src[slave_num]._cnt==0)&&(src[slave_num]._av_net)) avar_s_hndl(slave_num,3,0); 
	can_reset_cnt=0;
   	}


if((RXBUFF[1]==PUTTM_NET1)&&((RXBUFF[0]&0x1f)>=0)&&((RXBUFF[0]&0x1f)<12))
 	{
    slave_num=RXBUFF[0]&0x1f;  

    bps[slave_num]._device=dNET_METR;
         
	bps[slave_num]._buff[6]=RXBUFF[2]; 
	bps[slave_num]._buff[7]=RXBUFF[3];
	
	//net_F= RXBUFF[2]+ (RXBUFF[3]*256);

	bps[slave_num]._cnt=0;
	bps[slave_num]._is_on_cnt=10; 

   	//if((src[slave_num]._cnt==0)&&(src[slave_num]._av_net)) avar_s_hndl(slave_num,3,0); 
	can_reset_cnt=0;
   	}

if( (RXBUFF[0]==MEM_KF)&&(RXBUFF[1]==1)&&(RXBUFF[2]==1))
     {
     power_summary_tempo=*((signed short*)&RXBUFF[3]);
     power_current_tempo=*((signed short*)&RXBUFF[5]);
	//ext_can_cnt++;
	can_reset_cnt=0;
     }


if( ((RXBUFF[0]&0x1f)==8)&&((RXBUFF[1])==PUTTM) )
     {
     adc_buff_ext_[0]=*((short*)&RXBUFF[2]);
     adc_buff_ext_[1]=*((short*)&RXBUFF[4]);
     adc_buff_ext_[2]=*((short*)&RXBUFF[6]);
	if((adc_buff_ext_[2]>=-50) && (adc_buff_ext_[2]<=100))
		{
		t_ext_can=adc_buff_ext_[2];
		t_ext_can_nd=0;
		}
		t_ext_can=adc_buff_ext_[2];
	//ext_can_cnt++;
	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==9)&&((RXBUFF[1])==PUTTM) )
     {
     vvod_pos=RXBUFF[2];
	ext_can_cnt=RXBUFF[3];
	if(ext_can_cnt<10)bRESET_EXT=0;
	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==10)&&((RXBUFF[1])==PUTTM) )
     {
     power_current=*((signed short*)&RXBUFF[2]);
     power_summary=*((signed long*)&RXBUFF[4]);
	//ext_can_cnt++;
	can_reset_cnt=0;
     }


if( ((RXBUFF[0]&0x1f)==20)&&((RXBUFF[1])==PUTTM) )
     {
     eb2_data[0]=RXBUFF[2];
	eb2_data[1]=RXBUFF[3];
     eb2_data[2]=RXBUFF[4];
	eb2_data[3]=RXBUFF[5];
	eb2_data[4]=RXBUFF[6];
	eb2_data[5]=RXBUFF[7];
     power_current=*((signed short*)&RXBUFF[2]);
     power_summary=*((signed long*)&RXBUFF[4]);

	 can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==21)&&((RXBUFF[1])==PUTTM) )
     {
     eb2_data[6]=RXBUFF[2];
	eb2_data[7]=RXBUFF[3];
     eb2_data[8]=RXBUFF[4];
	eb2_data[9]=RXBUFF[5];
	eb2_data[10]=RXBUFF[6];
	eb2_data[11]=RXBUFF[7];
	eb2_data_short[6]=*((short*)&eb2_data[6]);

	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==22)&&((RXBUFF[1])==PUTTM) )
     {
     eb2_data[12]=RXBUFF[2];
	eb2_data[13]=RXBUFF[3];
     eb2_data[14]=RXBUFF[4];
	eb2_data[15]=RXBUFF[5];
	eb2_data[16]=RXBUFF[6];
	eb2_data[17]=RXBUFF[7];
	eb2_data_short[0]=*((short*)&eb2_data[12]);
	eb2_data_short[1]=*((short*)&eb2_data[14]);
	eb2_data_short[2]=*((short*)&eb2_data[16]);

	can_reset_cnt=0;
     }

if( ((RXBUFF[0]&0x1f)==23)&&((RXBUFF[1])==PUTTM) )
     {
     eb2_data[18]=RXBUFF[2];
	eb2_data[19]=RXBUFF[3];
     eb2_data[20]=RXBUFF[4];
	eb2_data[21]=RXBUFF[5];
	eb2_data[22]=RXBUFF[6];
	eb2_data[23]=RXBUFF[7];
	eb2_data_short[3]=*((short*)&eb2_data[18]);
	eb2_data_short[4]=*((short*)&eb2_data[20]);
	eb2_data_short[5]=*((short*)&eb2_data[22]);

	can_reset_cnt=0;
     }

if( (RXBUFF[1]==PUTTM_MAKB1)&&(RXBUFF[0]>=0)&&(RXBUFF[0]<=3))
     {
	makb[RXBUFF[0]]._U[0]=*((short*)&RXBUFF[2]);
	makb[RXBUFF[0]]._U[1]=*((short*)&RXBUFF[4]);
	makb[RXBUFF[0]]._U[2]=*((short*)&RXBUFF[6]);

	makb[RXBUFF[0]]._Ub[0]=makb[RXBUFF[0]]._U[0];
	if(makb[RXBUFF[0]]._Ub[0]<0)makb[RXBUFF[0]]._Ub[0]=0;
	makb[RXBUFF[0]]._Ub[1]=makb[RXBUFF[0]]._U[1]-makb[RXBUFF[0]]._U[0];
	if(makb[RXBUFF[0]]._Ub[1]<0)makb[RXBUFF[0]]._Ub[1]=0;
	makb[RXBUFF[0]]._Ub[2]=makb[RXBUFF[0]]._U[2]-makb[RXBUFF[0]]._U[1];
	if(makb[RXBUFF[0]]._Ub[2]<0)makb[RXBUFF[0]]._Ub[2]=0;

	makb[RXBUFF[0]]._cnt=0;
     }

if( (RXBUFF[1]==PUTTM_MAKB2)&&(RXBUFF[0]>=0)&&(RXBUFF[0]<=3))
     {
	makb[RXBUFF[0]]._U[3]=*((short*)&RXBUFF[2]);
	makb[RXBUFF[0]]._U[4]=*((short*)&RXBUFF[4]);
	makb[RXBUFF[0]]._T[0]=(signed short)(*((signed char*)&RXBUFF[6]));
	makb[RXBUFF[0]]._T[1]=(signed short)(*((signed char*)&RXBUFF[7]));

	makb[RXBUFF[0]]._Ub[3]=makb[RXBUFF[0]]._U[3]-makb[RXBUFF[0]]._U[2];
	if(makb[RXBUFF[0]]._Ub[3]<0)makb[RXBUFF[0]]._Ub[3]=0;
	makb[RXBUFF[0]]._Ub[4]=makb[RXBUFF[0]]._U[4]-makb[RXBUFF[0]]._U[3];
	if(makb[RXBUFF[0]]._Ub[4]<0)makb[RXBUFF[0]]._Ub[4]=0;

	makb[RXBUFF[0]]._cnt=0;
     }

if( (RXBUFF[1]==PUTTM_MAKB3)&&(RXBUFF[0]>=0)&&(RXBUFF[0]<=3))
     {
	makb[RXBUFF[0]]._T[2]=(signed short)(*((signed char*)&RXBUFF[2]));
	makb[RXBUFF[0]]._T[3]=(signed short)(*((signed char*)&RXBUFF[3]));
	makb[RXBUFF[0]]._T[4]=(signed short)(*((signed char*)&RXBUFF[4]));

	if(RXBUFF[5]&0x01)makb[RXBUFF[0]]._T_nd[0]=1;
	else makb[RXBUFF[0]]._T_nd[0]=0;
	if(RXBUFF[5]&0x02)makb[RXBUFF[0]]._T_nd[1]=1;
	else makb[RXBUFF[0]]._T_nd[1]=0;
	if(RXBUFF[5]&0x04)makb[RXBUFF[0]]._T_nd[2]=1;
	else makb[RXBUFF[0]]._T_nd[2]=0;
	if(RXBUFF[5]&0x08)makb[RXBUFF[0]]._T_nd[3]=1;
	else makb[RXBUFF[0]]._T_nd[3]=0;
	if(RXBUFF[5]&0x10)makb[RXBUFF[0]]._T_nd[4]=1;
	else makb[RXBUFF[0]]._T_nd[4]=0;

	makb[RXBUFF[0]]._cnt=0;
     }

/*if(RXBUFF[0]==PUT_LB_TM1)
     {
	lakb[0]._max_cell_volt=(unsigned short)(*((unsigned short*)&RXBUFF[1]));
	lakb[0]._min_cell_volt=(unsigned short)(*((unsigned short*)&RXBUFF[3]));
	lakb[0]._tot_bat_volt=(unsigned short)(*((unsigned short*)&RXBUFF[5]));
	lakb[0]._max_cell_temp=(unsigned short)RXBUFF[7];
	lakb[0]._cnt=0;
	lakb[0]._plazma[0]++;
     }
if(RXBUFF[0]==PUT_LB_TM2)
     {
	lakb[0]._ch_curr=(unsigned short)(*((unsigned short*)&RXBUFF[1]));
	lakb[0]._dsch_curr=(unsigned short)(*((unsigned short*)&RXBUFF[3]));
	lakb[0]._rat_cap=(unsigned short)(*((unsigned short*)&RXBUFF[5]));
	lakb[0]._min_cell_temp=(unsigned short)RXBUFF[7];
	lakb[0]._cnt=0;
	lakb[0]._plazma[1]++;
     }
if(RXBUFF[0]==PUT_LB_TM3)
     {
	lakb[0]._s_o_h=(unsigned short)RXBUFF[1];
	lakb[0]._s_o_c=(unsigned short)RXBUFF[2];
	lakb[0]._c_c_l_v=(unsigned short)(*((unsigned short*)&RXBUFF[3]));
	lakb[0]._r_b_t=(unsigned short)RXBUFF[5];
	lakb[0]._flags1=(unsigned short)RXBUFF[6];
	lakb[0]._flags2=(unsigned short)RXBUFF[7];
	lakb[0]._cnt=0;
	lakb[0]._plazma[2]++;
     }
if(RXBUFF[0]==PUT_LB_TM4)
     {
	lakb[0]._bRS485ERR=(unsigned short)RXBUFF[1];
	lakb[0]._rs485_cnt=(unsigned short)RXBUFF[2];
	lakb[0]._cnt=0;
	lakb[0]._plazma[3]++;
     }*/
	
if((RXBUFF[1]&0xf8)==PUT_LB_TM1)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
	
	if(temp==0) //у нас только одна батарея
		{	
		lakb_damp[temp][0]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][1],&RXBUFF[2],6);
	
		ccc_plazma[0]++;
		ccc_plazma[7]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}	

if((RXBUFF[1]&0xf8)==PUT_LB_TM2)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
	
	if(temp==0) //у нас только одна батарея
		{		
		lakb_damp[temp][7]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][8],&RXBUFF[2],6);
		
		ccc_plazma[1]++;
		ccc_plazma[8]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}

if((RXBUFF[1]&0xf8)==PUT_LB_TM3)
     {
	char temp;
	temp=RXBUFF[1]&0x07;

	if(temp==0) //у нас только одна батарея
		{
		lakb_damp[temp][14]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][15],&RXBUFF[2],6);
		
		ccc_plazma[2]++;
		ccc_plazma[9]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}	

if((RXBUFF[1]&0xf8)==PUT_LB_TM4)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
	
	if(temp==0) //у нас только одна батарея
		{
		lakb_damp[temp][21]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][22],&RXBUFF[2],6);
		
		ccc_plazma[3]++;
		ccc_plazma[10]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}

if((RXBUFF[1]&0xf8)==PUT_LB_TM5)
     {
	char temp;
	temp=RXBUFF[1]&0x07;

	if(temp==0) //у нас только одна батарея
		{		
		lakb_damp[temp][28]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][29],&RXBUFF[2],6);

		ccc_plazma[4]++;
		ccc_plazma[11]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;
		}
	}

if((RXBUFF[1]&0xf8)==PUT_LB_TM6)
     {
	char temp;
	temp=RXBUFF[1]&0x07;
		
	if(temp==0) //у нас только одна батарея
		{
		lakb_damp[temp][35]=RXBUFF[0];
		mem_copy(&lakb_damp[temp][36],&RXBUFF[2],6);
		
		ccc_plazma[5]++;
		ccc_plazma[12]=temp;
		li_bat._canErrorCnt=0;
		li_bat._canError=0;	
		}
	}


if(RXBUFF[1]==PUT_ZTT_TM1)
    {
	lakb[0]._communication2lvlErrorCnt=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[0]._ch_curr=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[0]._tot_bat_volt=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[0]._cell_temp_1=(signed char)(RXBUFF[6]);
	lakb[0]._cell_temp_2=(signed char)(RXBUFF[7]);
	
	//lakb[0]._cell_temp_1=37;
	//lakb[0]._cell_temp_2=38;
	plazma_ztt[0]++;

	}

if(RXBUFF[1]==PUT_ZTT_TM2)
    {
	lakb[0]._communication2lvlErrorStat=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[0]._s_o_c=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[0]._s_o_h=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[0]._cell_temp_3=(signed char)(RXBUFF[6]);
	lakb[0]._cell_temp_4=(signed char)(RXBUFF[7]);
	//lakb[0]._cell_temp_3=39;
	//lakb[0]._cell_temp_4=40;
	
	plazma_ztt[1]++;
	}		

if(RXBUFF[1]==PUT_ZTT_TM3)
    {
	lakb[1]._communication2lvlErrorCnt=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[1]._ch_curr=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[1]._tot_bat_volt=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[1]._cell_temp_1=(signed char)(RXBUFF[6]);
	lakb[1]._cell_temp_2=(signed char)(RXBUFF[7]);
	
	}

if(RXBUFF[1]==PUT_ZTT_TM4)
    {
	lakb[1]._communication2lvlErrorStat=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[1]._s_o_c=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[1]._s_o_h=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[1]._cell_temp_3=(signed char)(RXBUFF[6]);
	lakb[1]._cell_temp_4=(signed char)(RXBUFF[7]);
	
	}	

if(RXBUFF[1]==PUT_ZTT_TM5)
    {
	lakb[2]._communication2lvlErrorCnt=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[2]._ch_curr=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[2]._tot_bat_volt=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[2]._cell_temp_1=(signed char)(RXBUFF[6]);
	lakb[2]._cell_temp_2=(signed char)(RXBUFF[7]);
	
	}

if(RXBUFF[1]==PUT_ZTT_TM6)
    {
	lakb[2]._communication2lvlErrorStat=(signed short)(*((signed char*)&RXBUFF[0]));
	lakb[2]._s_o_c=(signed short)(*((signed short*)&RXBUFF[2]));
	lakb[2]._s_o_h=(signed short)(*((signed short*)&RXBUFF[4]));
	lakb[2]._cell_temp_3=(signed char)(RXBUFF[6]);
	lakb[2]._cell_temp_3=(signed char)(RXBUFF[7]);	
	}	

if(RXBUFF[1]==PUT_ZTT_TM7)
    {
	lakb[0]._cell_temp_ambient=(signed char)(RXBUFF[0]);
	lakb[0]._cell_temp_power=(signed char)(RXBUFF[2]);
	lakb[1]._cell_temp_ambient=(signed char)(RXBUFF[3]);
	lakb[1]._cell_temp_power=(signed char)(RXBUFF[4]);
	lakb[2]._cell_temp_ambient=(signed char)(RXBUFF[5]);
	lakb[2]._cell_temp_power=(signed char)(RXBUFF[6]);	
	//lakb[0]._cell_temp_ambient=41;
	//lakb[0]._cell_temp_power=42;
	}	
	
CAN_IN_AN1_end:
bIN2=0;
}





  
/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
void CAN_ISR_Rx1( void )
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;
//can_cnt++;

rotor_can[0]++;

  if (!(LPC_CAN1->RFS & 0xC0000400L))
  { // 11-bit ID, no RTR, matched a filter

rotor_can[1]++;
    // initialize destination pointer
    // filter number is in lower 10 bits of C1RFS
    pDest = (unsigned int *) &(gFullCANList[(LPC_CAN1->RFS & 0x000003FFL)].Dat1);
    
    // calculate contents for first entry into FullCAN list
    buf = LPC_CAN1->RFS & 0xC00F0000L; // mask FF, RTR and DLC
    buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
    buf |= LPC_CAN1->RID & 0x000007FFL; // get CAN message ID

    // now copy entire message to FullCAN list
    *pDest = buf; 
    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
    *pDest = LPC_CAN1->RDA; 
    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
    *pDest = LPC_CAN1->RDB; 

    // now set the sempahore to complete
    buf |= 0x03000000L; // set semaphore to 11b
    pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
    *pDest = buf; 
    
	temp=(char)gFullCANList[0].DatA;
	if(temp==0x30) bR=0;
	else bR++;
	
	temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     ptr=(char*)(&gFullCANList[0].DatA);
	
	for(j=0;j<temp;j++)
		{
		RXBUFF[j]=*ptr;
		ptr++;
		}
	can_in_an1();
	    
    
  }

  LPC_CAN1->CMR = 0x04; // release receive buffer
}



/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
void CAN_ISR_Rx2( void ) 
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;
//can_cnt++;

//rotor_can[0]++;
//can_debug_plazma[0][0]++;
//if(C1ICR & 0x00000001L)
//	{
//	can_debug_plazma[0][0]++;
	if (!(LPC_CAN2->RFS & 0xC0000400L))
    		{ // 11-bit ID, no RTR, matched a filter
			
    		//rotor_can[1]++;
    		// initialize destination pointer
    		// filter number is in lower 10 bits of C1RFS
			//plazma_can4=(char)((LPC_CAN2->RFS>>16) & 0x000000FFL);
    		pDest = (unsigned int *) &(gFullCANList[(LPC_CAN2->RFS & 0x000003FFL)].Dat1);
    
			plazma_can_pal[plazma_can_pal_index]=(char)(LPC_CAN2->RDA);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((LPC_CAN2->RDA)>>8);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((LPC_CAN2->RDA)>>16);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((LPC_CAN2->RDA)>>24);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)(LPC_CAN2->RDB);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((LPC_CAN2->RDB)>>8);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((LPC_CAN2->RDB)>>16);
			plazma_can_pal_index++;
			plazma_can_pal[plazma_can_pal_index]=(char)((LPC_CAN2->RDB)>>24);
			plazma_can_pal_index++;

    		// calculate contents for first entry into FullCAN list
    		buf = LPC_CAN2->RFS & 0xC00F0000L; // mask FF, RTR and DLC
    		buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
    		buf |= LPC_CAN2->RID & 0x000007FFL; // get CAN message ID

    		// now copy entire message to FullCAN list
    		*pDest = buf; 
    		pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
    		*pDest = LPC_CAN2->RDA;
			//plazma_can4=(char)LPC_CAN2->RDA; 
    		pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
    		*pDest = LPC_CAN2->RDB; 

    		// now set the sempahore to complete
    		buf |= 0x03000000L; // set semaphore to 11b
    		pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
    		*pDest = buf; 
    
		//temp=(char)gFullCANList[0].DatA;
		temp=(char)(LPC_CAN2->RDA);
		if(temp==0x30)
			{
			 bR=0;
			 }
		else bR++;
	
		//temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     	//ptr=(char*)(&gFullCANList[0].DatA);
	
		if(!bR)
			{
			/*for(j=0;j<temp;j++)
				{
				RXBUFF[j]=*ptr;
				ptr++;
				}*/
			RXBUFF[0]=(char)(LPC_CAN2->RDA);
			RXBUFF[1]=(char)((LPC_CAN2->RDA)>>8);
			RXBUFF[2]=(char)((LPC_CAN2->RDA)>>16);
			RXBUFF[3]=(char)((LPC_CAN2->RDA)>>24);
			RXBUFF[4]=(char)(LPC_CAN2->RDB);
			RXBUFF[5]=(char)((LPC_CAN2->RDB)>>8);
			RXBUFF[6]=(char)((LPC_CAN2->RDB)>>16);
			RXBUFF[7]=(char)((LPC_CAN2->RDB)>>24);
			
			}
		else if(bR==1)
			{
			RXBUFF[8]=(char)(LPC_CAN2->RDA);
			RXBUFF[9]=(char)((LPC_CAN2->RDA)>>8);
			RXBUFF[10]=(char)((LPC_CAN2->RDA)>>16);
			RXBUFF[11]=(char)((LPC_CAN2->RDA)>>24);
			RXBUFF[12]=(char)(LPC_CAN2->RDB);
			RXBUFF[13]=(char)((LPC_CAN2->RDB)>>8);
			RXBUFF[14]=(char)((LPC_CAN2->RDB)>>16);
			RXBUFF[15]=(char)((LPC_CAN2->RDB)>>24);
			} 		
	
	
	
		
		temp=((RXBUFF[1]&0x1f)+4);
    		//rotor_can[2]++;
		if((CRC1_in()==RXBUFF[temp+1])&&(CRC2_in()==RXBUFF[temp+2])&&bR)
			{
  
			bIN=1;
  			//rotor_can[3]++;
  			can_in_an2();
			
			}    
    
  		}

LPC_CAN2->CMR = 0x04; // release receive buffer
}
/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 

void can_isr_tx1 (void) 
{
//unsigned int buf;
//unsigned int *pDest;
char temp;
//char *ptr,j;

//plazma_can2++;

can_tx_cnt++;

rotor_can[5]++;

if(ptr_can1_tx_wr!=ptr_can1_tx_rd)
	{
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
	}
else bOUT_FREE=1;
temp=LPC_CAN1->ICR;

}

/***************************************************************************/
void can_isr_tx2 (void) 
{
char temp;
can2_tx_cnt++;

//=ptr_can2_tx_wr;

if(ptr_can2_tx_wr!=ptr_can2_tx_rd)
	{
	LPC_CAN2->TFI1=can2_info[ptr_can2_tx_rd];
     LPC_CAN2->TID1=can2_id[ptr_can2_tx_rd];
     LPC_CAN2->TDA1=can2_data[ptr_can2_tx_rd];
     LPC_CAN2->TDB1=can2_datb[ptr_can2_tx_rd];
     LPC_CAN2->CMR=0x00000021;
     ptr_can2_tx_rd++;
     if(ptr_can2_tx_rd>=8)ptr_can2_tx_rd=0;
	}
else bOUT_FREE2=1;
temp=LPC_CAN2->ICR;
}

/**************************************************************************
Initialization of a CAN interface
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short can1_init (unsigned int can_btr)
{
LPC_SC->PCONP |= (1<<13);  /* Enable CAN1 and CAN2 clock */

LPC_PINCON->PINSEL0 &= ~0x0000000F;  /* CAN1 is p0.0 and p0.1	*/
LPC_PINCON->PINSEL0 |= 0x00000005;

gCANFilter = 0; // Reset and disable all message filters

LPC_CANAF->AFMR = 0x00000001L; // Acceptance Filter Mode Register = off !

LPC_CAN1->MOD = 1; // Go into Reset mode

LPC_CAN1->IER = 0;// Disable All Interrupts

LPC_CAN1->GSR = 0; // Clear Status register

LPC_CAN1->BTR = can_btr; // Set bit timing

//LPC_CAN1->IER |=(1<<0)|(1<<1)|(1<<9)|(1<<10); // Enable Receive & Transmit Interrupt

LPC_CAN1->MOD = 0; // Enter Normal Operating Mode



NVIC_EnableIRQ(CAN_IRQn);
LPC_CAN1->IER =0x0003;
return 1;
}

/**************************************************************************
Initialization of a CAN interface
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short can2_init (unsigned int can_btr)
{
LPC_SC->PCONP |= (1<<14);  /* Enable CAN1 and CAN2 clock */

LPC_PINCON->PINSEL2 &= ~0x0003c000;  /* CAN1 is p0.0 and p0.1	*/
LPC_PINCON->PINSEL4 |= 0x00014000;

gCANFilter = 0; // Reset and disable all message filters

LPC_CANAF->AFMR = 0x00000001L; // Acceptance Filter Mode Register = off !

LPC_CAN2->MOD = 1; // Go into Reset mode

LPC_CAN2->IER = 0;// Disable All Interrupts

LPC_CAN2->GSR = 0; // Clear Status register

LPC_CAN2->BTR = can_btr; // Set bit timing

//LPC_CAN1->IER |=(1<<0)|(1<<1)|(1<<9)|(1<<10); // Enable Receive & Transmit Interrupt

LPC_CAN2->MOD = 0; // Enter Normal Operating Mode



NVIC_EnableIRQ(CAN_IRQn);
LPC_CAN2->IER =0x0003;
return 1;
}

/**************************************************************************
Setting a CAN receive filter
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short FullCAN_SetFilter  (
                         unsigned short can_port, // CAN interface number
                         unsigned int CANID // 11-bit CAN ID
                         )
{
unsigned int p, n;
unsigned int buf0, buf1;
unsigned int ID_lower, ID_upper;
unsigned int candata;
unsigned int *pAddr;

 

// Acceptance Filter Mode Register = off !
LPC_CANAF->AFMR = 0x00000001L;

if (gCANFilter == 0)
     {    
     // First call, init entry zero
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
LPC_CANAF->SFF_sa = p;

pAddr = (unsigned int *) LPC_CANAF_RAM_BASE;
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
LPC_CANAF->SFF_GRP_sa = p;

// Set pointer for Extended Frame Individual
// Extended Frame Start Address Register
LPC_CANAF->EFF_sa = p;

// Set pointer for Extended Frame Groups
// Extended Frame Group Start Address Register
LPC_CANAF->EFF_GRP_sa = p;

// Set ENDofTable 
// End of AF Tables Register
LPC_CANAF->ENDofTable = p;

// Acceptance Filter Mode Register, start using filter
LPC_CANAF->AFMR = 0;
  
return 1;

/*
  // Acceptance Filter Mode Register = off !
LPC_CANAF->AFMR = 0x00000001L;

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
LPC_CANAF->SFF_sa = p;

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
LPC_CANAF->SFF_GRP_sa = p;

  // Set pointer for Extended Frame Individual
  // Extended Frame Start Address Register
LPC_CANAF->EFF_sa = p;

  // Set pointer for Extended Frame Groups
  // Extended Frame Group Start Address Register
LPC_CANAF->EFF_GRP_sa = p;

  // Set ENDofTable 
  // End of AF Tables Register
LPC_CANAF->ENDofTable = p;

  // Acceptance Filter Mode Register, start using filter
LPC_CANAF->AFMR = 0;
  
  return 1;	 */
}

//-----------------------------------------------
void CAN_IRQHandler(void)  
{
//can_rotor[0]++;
CANStatus = LPC_CAN1->ICR;
//new_rotor[3]=CANStatus;
//new_rotor[4]=CANStatus>>16;
//
//rotor_rotor_rotor[0]++;
		
if ( CANStatus & (1 << 0) )
     {
	CAN_ISR_Rx1();
	plazma_can1++;
     }

if ( CANStatus & (1 << 1) )
     {
	can_isr_tx1();
	plazma_can2++;
	
     }

CANStatus = LPC_CAN2->ICR;
//new_rotor[3]=CANStatus;
//new_rotor[4]=CANStatus>>16;
//
//rotor_rotor_rotor[0]++;
plazma_can++;		
if ( CANStatus & (1 << 0) )
     {
	CAN_ISR_Rx2();
	plazma_can3++;
	cnt_can_pal=0;

     }

if ( CANStatus & (1 << 1) )
     {
	can_isr_tx2();
	 plazma_can4++;
	
     }

return;
}










