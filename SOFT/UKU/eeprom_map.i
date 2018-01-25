#line 1 "eeprom_map.c"
#line 1 "eeprom_map.h"






#line 34 "eeprom_map.h"



#line 134 "eeprom_map.h"



#line 151 "eeprom_map.h"



#line 163 "eeprom_map.h"


#line 174 "eeprom_map.h"



#line 185 "eeprom_map.h"



#line 241 "eeprom_map.h"


#line 283 "eeprom_map.h"








#line 305 "eeprom_map.h"







































































































extern const unsigned short ADR_EE_BAT_ZAR_CNT[2];
extern const unsigned short ADR_EE_BAT_ZAR_CNT_KE[2];
extern const unsigned short ADR_EE_BAT_C_NOM[2];
extern const unsigned short ADR_EE_BAT_YEAR_OF_ON[2];
extern const unsigned short ADR_EE_BAT_IS_ON[2];
extern const unsigned short ADR_EE_BAT_DAY_OF_ON[2];
extern const unsigned short ADR_EE_BAT_MONTH_OF_ON[2];
extern const unsigned short ADR_EE_BAT_RESURS[2];
extern const unsigned short ADR_EE_BAT_C_REAL[2];
extern const unsigned short ADR_EE_BAT_TYPE[2];
extern const unsigned short ADR_KUBAT[2];
extern const unsigned short ADR_KUBATM[2];
extern const unsigned short ADR_KI0BAT[2];
extern const unsigned short ADR_KI1BAT[2];
extern const unsigned short ADR_KTBAT[2];
extern const unsigned short ADR_EE_BAT_TYPE[2];


extern const unsigned short ADR_TMAX_EXT_EN[3];
extern const unsigned short ADR_TMAX_EXT[3];
extern const unsigned short ADR_TMIN_EXT_EN[3];
extern const unsigned short ADR_TMIN_EXT[3];
extern const unsigned short ADR_T_EXT_REL_EN[3];
extern const unsigned short ADR_T_EXT_ZVUK_EN[3];
extern const unsigned short ADR_T_EXT_LCD_EN[3];
extern const unsigned short ADR_T_EXT_RS_EN[3];

extern const unsigned short ADR_SK_SIGN[4];
extern const unsigned short ADR_SK_REL_EN[4];
extern const unsigned short ADR_SK_ZVUK_EN[4];
extern const unsigned short ADR_SK_LCD_EN[4];
extern const unsigned short ADR_SK_RS_EN[4];

#line 2 "eeprom_map.c"


const unsigned short ADR_EE_BAT_ZAR_CNT[2]={0x10+400+12,0x10+400+42};
const unsigned short ADR_EE_BAT_ZAR_CNT_KE[2]={0x10+400+14,0x10+400+44};
const unsigned short ADR_EE_BAT_C_NOM[2]={0x10+400+16,0x10+400+48};
const unsigned short ADR_EE_BAT_YEAR_OF_ON[2]={0x10+400+6,0x10+400+36};
const unsigned short ADR_EE_BAT_IS_ON[2]={0x10+400,0x10+400+30};
const unsigned short ADR_EE_BAT_DAY_OF_ON[2]={0x10+400+2,0x10+400+32};
const unsigned short ADR_EE_BAT_MONTH_OF_ON[2]={0x10+400+4,0x10+400+34};
const unsigned short ADR_EE_BAT_RESURS[2]={0x10+400+10,0x10+400+40};
const unsigned short ADR_EE_BAT_C_REAL[2]={0x10+400+8,0x10+400+38};

const unsigned short ADR_KUBAT[2]={0x10,0x10+2};
const unsigned short ADR_KUBATM[2]={0x10+28,0x10+30};
const unsigned short ADR_KI0BAT[2]={0x10+4,0x10+6};
const unsigned short ADR_KI1BAT[2]={0x10+8,0x10+10};
const unsigned short ADR_KTBAT[2]={0x10+12,0x10+14};


const unsigned short ADR_TMAX_EXT_EN[3]={0x10+500,0x10+500+16,0x10+500+32};
const unsigned short ADR_TMAX_EXT[3]={0x10+500+2,0x10+500+18,0x10+500+34};
const unsigned short ADR_TMIN_EXT_EN[3]={0x10+500+4,0x10+500+20,0x10+500+36};
const unsigned short ADR_TMIN_EXT[3]={0x10+500+6,0x10+500+22,0x10+500+38};
const unsigned short ADR_T_EXT_REL_EN[3]={0x10+500+8,0x10+500+24,0x10+500+40};
const unsigned short ADR_T_EXT_ZVUK_EN[3]={0x10+500+10,0x10+500+26,0x10+500+42};
const unsigned short ADR_T_EXT_LCD_EN[3]={0x10+500+12,0x10+500+28,0x10+500+44};
const unsigned short ADR_T_EXT_RS_EN[3]={0x10+500+14,0x10+500+30,0x10+500+46};

const unsigned short ADR_SK_SIGN[4]={0x10+500+48,0x10+500+58,0x10+500+68,0x10+500+78};
const unsigned short ADR_SK_REL_EN[4]={0x10+500+50,0x10+500+60,0x10+500+70,0x10+500+80};
const unsigned short ADR_SK_ZVUK_EN[4]={0x10+500+52,0x10+500+62,0x10+500+72,0x10+500+82};
const unsigned short ADR_SK_LCD_EN[4]={0x10+500+54,0x10+500+64,0x10+500+74,0x10+500+84};
const unsigned short ADR_SK_RS_EN[4]={0x10+500+56,0x10+500+66,0x10+500+76,0x10+500+86};
