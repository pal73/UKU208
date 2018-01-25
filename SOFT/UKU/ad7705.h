
extern unsigned short ad7705_res1,ad7705_res2;
extern unsigned short ad7705_buff[2][16],ad7705_buff_[2];
extern unsigned short ad7705_res;
extern char b7705ch,ad7705_wrk_cnt;
extern unsigned short cnt_ad7705_vis,cnt_ad7705_vis_wrk;
extern signed short ad7705_plazma;


void spi1_ad7705_config(void);
void ad7705_reset(void);
void ad7705_write(char in);
void ad7705_read(char num);
void ad7705_drv(void);



