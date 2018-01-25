#ifndef _RET_H_

#define _RET_H_

extern char retind,retsub,retindsec;
extern int retcnt,retcntsec;
extern unsigned char f0,fc0,f1,fc1;
extern short ret_duty;

void ret_ind(char r_i,char r_s,int r_c);
void ret_ind_hndl(void);
void ret_ind_sec(char r_i,int r_c);
void ret_ind_sec_hndl(void);
void ret(short duty);
void ret_hndl(void);

#endif


//



 

     
