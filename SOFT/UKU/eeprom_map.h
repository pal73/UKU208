
#define EE_CAN_RESET_CNT	0x06
#define RESET_CNT	0x08

#define SECTOR_KOEF 0x10

#define EE_KUBAT1		SECTOR_KOEF
#define EE_KUBAT2		SECTOR_KOEF+2
#define EE_KI0BAT1		SECTOR_KOEF+4
#define EE_KI0BAT2		SECTOR_KOEF+6
#define EE_KI1BAT1		SECTOR_KOEF+8
#define EE_KI1BAT2		SECTOR_KOEF+10
#define EE_KTBAT1		SECTOR_KOEF+12
#define EE_KTBAT2		SECTOR_KOEF+14
#define EE_KUNET       	SECTOR_KOEF+16
#define EE_KFNET       	SECTOR_KOEF+18
#define EE_KULOAD       	SECTOR_KOEF+20
#define  EE_KUNET_EXT0   SECTOR_KOEF+22
#define  EE_KUNET_EXT1   SECTOR_KOEF+24
#define  EE_KUNET_EXT2   SECTOR_KOEF+26
#define EE_KUBATM1		SECTOR_KOEF+28
#define EE_KUBATM2		SECTOR_KOEF+30
#define EE_KVV0_EB2		SECTOR_KOEF+32
#define EE_KVV1_EB2		SECTOR_KOEF+34
#define EE_KVV2_EB2		SECTOR_KOEF+36
#define EE_KPES0_EB2	SECTOR_KOEF+38
#define EE_KPES1_EB2	SECTOR_KOEF+40
#define EE_KPES2_EB2	SECTOR_KOEF+42
#define EE_KUNETA      	SECTOR_KOEF+44
#define EE_KUNETB      	SECTOR_KOEF+46
#define EE_KUNETC      	SECTOR_KOEF+48
#define EE_KUBPS      	SECTOR_KOEF+50
#define EE_KUOUT      	SECTOR_KOEF+52

#define SECTOR_SETS 	SECTOR_KOEF+100

#define EE_MAIN_IST 	SECTOR_SETS+2
#define EE_UMAX    		SECTOR_SETS+4
#define EE_UB0    		SECTOR_SETS+6
#define EE_UB20    		SECTOR_SETS+8
#define EE_TMAX		SECTOR_SETS+10
#define EE_AV_OFF_AVT    SECTOR_SETS+12
#define EE_USIGN		SECTOR_SETS+14
#define EE_UMN			SECTOR_SETS+16
#define EE_ZV_ON		SECTOR_SETS+18
#define EE_IKB			SECTOR_SETS+20
#define EE_KVZ			SECTOR_SETS+22
#define EE_IMAX		SECTOR_SETS+24
#define EE_IMIN		SECTOR_SETS+26
#define EE_APV_ON		SECTOR_SETS+28
#define EE_IZMAX		SECTOR_SETS+30
#define EE_U0B			SECTOR_SETS+32
#define EE_TZAS		SECTOR_SETS+34
#define EE_NUMIST  		SECTOR_SETS+36
#define EE_NUMINV  		SECTOR_SETS+38
#define KI0SRC1     	SECTOR_SETS+40
#define KI0SRC2     	SECTOR_SETS+42
#define EE_APV_ON1  	SECTOR_SETS+44
#define EE_APV_ON2  	SECTOR_SETS+46
#define EE_APV_ON2_TIME  SECTOR_SETS+48
#define KT_EXT0		SECTOR_SETS+50
#define KT_EXT1		SECTOR_SETS+52
#define KT_EXT2		SECTOR_SETS+54
#define EE_AVZ_TIME		SECTOR_SETS+56
#define EE_HOUR_AVZ		SECTOR_SETS+58	
#define EE_MIN_AVZ  	SECTOR_SETS+60
#define EE_SEC_AVZ  	SECTOR_SETS+62
#define EE_DATE_AVZ 	SECTOR_SETS+64
#define EE_MONTH_AVZ	SECTOR_SETS+66
#define EE_YEAR_AVZ 	SECTOR_SETS+68
#define EE_AVZ			SECTOR_SETS+70
#define EE_MNEMO_ON 	SECTOR_SETS+72
#define EE_MNEMO_TIME 	SECTOR_SETS+74
#define EE_VZ_HR		SECTOR_SETS+76
#define EE_TBAT          SECTOR_SETS+78
#define EE_U_AVT         SECTOR_SETS+80
#define EE_TSIGN		SECTOR_SETS+82
#define EE_DU			SECTOR_SETS+84
#define EE_PAR			SECTOR_SETS+86
#define EE_TBATMAX		SECTOR_SETS+88
#define EE_TBATSIGN		SECTOR_SETS+90
#define EE_TBOXMAX		SECTOR_SETS+92
#define EE_TBOXREG		SECTOR_SETS+94
#define EE_TBOXVENTMAX	SECTOR_SETS+96
#define EE_TLOADDISABLE	SECTOR_SETS+98
#define EE_TLOADENABLE	SECTOR_SETS+100
#define EE_TBATDISABLE	SECTOR_SETS+102
#define EE_TBATENABLE	SECTOR_SETS+104
#define EE_UVZ			SECTOR_SETS+106
#define EE_RELE_VENT_LOGIC	SECTOR_SETS+108
#define EE_TVENTON		SECTOR_SETS+110
#define EE_TVENTOFF	SECTOR_SETS+112	
#define EE_RELEVENTSIGN	 SECTOR_SETS+114
#define EE_NPN_OUT	 SECTOR_SETS+116
#define EE_NPN_SIGN	 SECTOR_SETS+118
#define EE_UONPN	 SECTOR_SETS+120
#define EE_UVNPN	 SECTOR_SETS+122
#define EE_TZNPN	 SECTOR_SETS+124
#define EE_TERMOKOMP	 	SECTOR_SETS+126
#define EE_TBOXVENTON	 	SECTOR_SETS+128
#define EE_TBOXVENTOFF	 	SECTOR_SETS+130
#define EE_TBOXWARMON	 	SECTOR_SETS+132 
#define EE_TBOXWARMOFF	 	SECTOR_SETS+134
#define EE_NUMBYPASS	 	SECTOR_SETS+136
#define EE_TWARMON			SECTOR_SETS+138
#define EE_TWARMOFF			SECTOR_SETS+140
#define EE_BAT_TYPE			SECTOR_SETS+142
#define EE_LI_UNECC			SECTOR_SETS+144
#define EE_LI_Q				SECTOR_SETS+146
#define EE_LI_IZMAX1		SECTOR_SETS+148
#define EE_LI_IZMAX2		SECTOR_SETS+150
#define EE_LI_K1			SECTOR_SETS+152
#define EE_LI_K2			SECTOR_SETS+154
#define EE_LI_K3			SECTOR_SETS+156
#define EE_LI_T4			SECTOR_SETS+158
#define EE_TELECORE2015_KLIMAT_VENT_SIGNAL	SECTOR_SETS+160
#define EE_SPEED_CHRG_CURR		 		SECTOR_SETS+162
#define EE_SPEED_CHRG_VOLT		 		SECTOR_SETS+164
#define EE_SPEED_CHRG_TIME				SECTOR_SETS+166
#define EE_SPEED_CHRG_AVT_EN				SECTOR_SETS+168	
#define EE_SPEED_CHRG_D_U				SECTOR_SETS+170
#define EE_SPEED_CHRG_BLOCK_SRC			SECTOR_SETS+172
#define EE_SPEED_CHRG_BLOCK_LOG			SECTOR_SETS+174
#define EE_DU_LI_BAT					SECTOR_SETS+176
#define EE_FORVARDBPSCHHOUR				SECTOR_SETS+178
#define EE_FORVBPSHOURCNT				SECTOR_SETS+180
#define EE_U_OUT_KONTR_MAX				SECTOR_SETS+182
#define EE_U_OUT_KONTR_MIN				SECTOR_SETS+184
#define EE_U_OUT_KONTR_DELAY			SECTOR_SETS+186
#define EE_DOP_RELE_FUNC				SECTOR_SETS+188
#define EE_IPS_BLOCK_SRC			   	SECTOR_SETS+190
#define EE_IPS_BLOCK_LOG				SECTOR_SETS+192
#define EE_NUMBAT_IP55					SECTOR_SETS+194

#define SECTOR_AUSW  		SECTOR_KOEF+300

#define EE_AUSW_MAIN 		SECTOR_AUSW
#define EE_AUSW_MAIN_NUMBER 	SECTOR_AUSW+2 
#define EE_AUSW_UKU 		SECTOR_AUSW+4 
#define EE_AUSW_UKU_SUB 		SECTOR_AUSW+6
#define EE_AUSW_UKU_NUMBER	SECTOR_AUSW+8
#define EE_AUSW_DAY			SECTOR_AUSW+10
#define EE_AUSW_MONTH		SECTOR_AUSW+12
#define EE_AUSW_YEAR		SECTOR_AUSW+14
#define EE_AUSW_BPS1_NUMBER	SECTOR_AUSW+16		
#define EE_AUSW_BPS2_NUMBER	SECTOR_AUSW+18
#define EE_AUSW_RS232		SECTOR_AUSW+20
#define EE_AUSW_PDH			SECTOR_AUSW+22
#define EE_AUSW_SDH			SECTOR_AUSW+24
#define EE_AUSW_ETH			SECTOR_AUSW+26

#define SECTOR_BAT  		SECTOR_KOEF+400

#define EE_BAT1_IS_ON         SECTOR_BAT
#define EE_BAT1_DAY_OF_ON     SECTOR_BAT+2
#define EE_BAT1_MONTH_OF_ON   SECTOR_BAT+4
#define EE_BAT1_YEAR_OF_ON    SECTOR_BAT+6
#define EE_BAT1_C_REAL        SECTOR_BAT+8
#define EE_BAT1_RESURS        SECTOR_BAT+10
#define EE_BAT1_ZAR_CNT      	SECTOR_BAT+12
#define EE_BAT1_ZAR_CNT_KE   	SECTOR_BAT+14
#define EE_BAT1_C_NOM         SECTOR_BAT+16


#define EE_BAT2_IS_ON         SECTOR_BAT+30
#define EE_BAT2_DAY_OF_ON     SECTOR_BAT+32
#define EE_BAT2_MONTH_OF_ON   SECTOR_BAT+34
#define EE_BAT2_YEAR_OF_ON    SECTOR_BAT+36
#define EE_BAT2_C_REAL        SECTOR_BAT+38
#define EE_BAT2_RESURS        SECTOR_BAT+40
#define EE_BAT2_ZAR_CNT       SECTOR_BAT+42
#define EE_BAT2_ZAR_CNT_KE    SECTOR_BAT+44
#define EE_BAT2_C_NOM         SECTOR_BAT+48



#define SECTOR_SPC	  		SECTOR_KOEF+480
#define EE_SPC_STAT			SECTOR_SPC
#define EE_VZ_CNT			SECTOR_SPC+2
#define EE_SPC_BAT			SECTOR_SPC+4
#define EE_SPC_PHASE		SECTOR_SPC+6
#define EE_SPC_KE_DATE0		SECTOR_SPC+8
#define EE_SPC_KE_DATE1		SECTOR_SPC+12
#define EE_SPC_VZ_LENGT		SECTOR_SPC+14

//#define KOEF_LONG	30

#define SECTOR_EXT  		SECTOR_KOEF+500
#define EE_TMAX_EXT_EN0		SECTOR_EXT
#define EE_TMAX_EXT0		SECTOR_EXT+2
#define EE_TMIN_EXT_EN0		SECTOR_EXT+4
#define EE_TMIN_EXT0		SECTOR_EXT+6
#define EE_T_EXT_REL_EN0		SECTOR_EXT+8
#define EE_T_EXT_ZVUK_EN0	SECTOR_EXT+10
#define EE_T_EXT_LCD_EN0		SECTOR_EXT+12
#define EE_T_EXT_RS_EN0		SECTOR_EXT+14
#define EE_TMAX_EXT_EN1		SECTOR_EXT+16
#define EE_TMAX_EXT1		SECTOR_EXT+18
#define EE_TMIN_EXT_EN1		SECTOR_EXT+20
#define EE_TMIN_EXT1		SECTOR_EXT+22
#define EE_T_EXT_REL_EN1		SECTOR_EXT+24
#define EE_T_EXT_ZVUK_EN1	SECTOR_EXT+26
#define EE_T_EXT_LCD_EN1		SECTOR_EXT+28
#define EE_T_EXT_RS_EN1		SECTOR_EXT+30
#define EE_TMAX_EXT_EN2		SECTOR_EXT+32
#define EE_TMAX_EXT2		SECTOR_EXT+34
#define EE_TMIN_EXT_EN2		SECTOR_EXT+36
#define EE_TMIN_EXT2		SECTOR_EXT+38
#define EE_T_EXT_REL_EN2		SECTOR_EXT+40
#define EE_T_EXT_ZVUK_EN2	SECTOR_EXT+42
#define EE_T_EXT_LCD_EN2		SECTOR_EXT+44
#define EE_T_EXT_RS_EN2		SECTOR_EXT+46
#define EE_SK_SIGN0			SECTOR_EXT+48
#define EE_SK_REL_EN0		SECTOR_EXT+50
#define EE_SK_ZVUK_EN0		SECTOR_EXT+52
#define EE_SK_LCD_EN0		SECTOR_EXT+54
#define EE_SK_RS_EN0		SECTOR_EXT+56
#define EE_SK_SIGN1			SECTOR_EXT+58
#define EE_SK_REL_EN1		SECTOR_EXT+60
#define EE_SK_ZVUK_EN1		SECTOR_EXT+62
#define EE_SK_LCD_EN1		SECTOR_EXT+64
#define EE_SK_RS_EN1		SECTOR_EXT+66
#define EE_SK_SIGN2			SECTOR_EXT+68
#define EE_SK_REL_EN2		SECTOR_EXT+70
#define EE_SK_ZVUK_EN2		SECTOR_EXT+72
#define EE_SK_LCD_EN2		SECTOR_EXT+74
#define EE_SK_RS_EN2		SECTOR_EXT+76
#define EE_SK_SIGN3			SECTOR_EXT+78
#define EE_SK_REL_EN3		SECTOR_EXT+80
#define EE_SK_ZVUK_EN3		SECTOR_EXT+82
#define EE_SK_LCD_EN3		SECTOR_EXT+84
#define EE_SK_RS_EN3		SECTOR_EXT+86
#define EE_NUMSK			SECTOR_EXT+88
#define EE_NUMDT			SECTOR_EXT+90
#define EE_POS_VENT			SECTOR_EXT+92
#define EE_POWER_CNT_ADRESS   SECTOR_EXT+94
#define EE_UBM_AV             SECTOR_EXT+96
#define EE_NUMAVT			SECTOR_EXT+98
#define EE_NUMMAKB			SECTOR_EXT+100
#define EE_RELE_LOG			SECTOR_EXT+102


#define SECTOR_ETH  		SECTOR_EXT+200
#define EE_ETH_IS_ON		SECTOR_ETH
#define EE_ETH_DHCP_ON		SECTOR_ETH+2
#define EE_ETH_IP_1			SECTOR_ETH+4
#define EE_ETH_IP_2			SECTOR_ETH+6
#define EE_ETH_IP_3			SECTOR_ETH+8
#define EE_ETH_IP_4			SECTOR_ETH+10
#define EE_ETH_MASK_1		SECTOR_ETH+12
#define EE_ETH_MASK_2		SECTOR_ETH+14
#define EE_ETH_MASK_3		SECTOR_ETH+16
#define EE_ETH_MASK_4		SECTOR_ETH+18
#define EE_ETH_TRAP1_IP_1	SECTOR_ETH+20
#define EE_ETH_TRAP1_IP_2	SECTOR_ETH+22
#define EE_ETH_TRAP1_IP_3	SECTOR_ETH+24
#define EE_ETH_TRAP1_IP_4	SECTOR_ETH+26
#define EE_ETH_TRAP2_IP_1	SECTOR_ETH+28
#define EE_ETH_TRAP2_IP_2	SECTOR_ETH+30
#define EE_ETH_TRAP2_IP_3	SECTOR_ETH+32
#define EE_ETH_TRAP2_IP_4	SECTOR_ETH+34
#define EE_ETH_TRAP3_IP_1	SECTOR_ETH+36
#define EE_ETH_TRAP3_IP_2	SECTOR_ETH+38
#define EE_ETH_TRAP3_IP_3	SECTOR_ETH+40
#define EE_ETH_TRAP3_IP_4	SECTOR_ETH+42
#define EE_ETH_TRAP4_IP_1	SECTOR_ETH+44
#define EE_ETH_TRAP4_IP_2	SECTOR_ETH+46
#define EE_ETH_TRAP4_IP_3	SECTOR_ETH+48
#define EE_ETH_TRAP4_IP_4	SECTOR_ETH+50
#define EE_ETH_TRAP5_IP_1	SECTOR_ETH+52
#define EE_ETH_TRAP5_IP_2	SECTOR_ETH+54
#define EE_ETH_TRAP5_IP_3	SECTOR_ETH+56
#define EE_ETH_TRAP5_IP_4	SECTOR_ETH+58
#define EE_ETH_SNMP_PORT_READ	SECTOR_ETH+60
#define EE_ETH_SNMP_PORT_WRITE	SECTOR_ETH+62
#define EE_ETH_GW_1			SECTOR_ETH+64
#define EE_ETH_GW_2			SECTOR_ETH+66
#define EE_ETH_GW_3			SECTOR_ETH+68
#define EE_ETH_GW_4			SECTOR_ETH+70
#define EE_MODBUS_ADRESS		SECTOR_ETH+72
#define EE_MODBUS_BAUDRATE	SECTOR_ETH+74
#define EE_BAT_LINK			SECTOR_ETH+76


#define SECTOR_LOCATION  	SECTOR_ETH+200
#define EE_LOCATION			SECTOR_LOCATION
#define SECTOR_COMMUNITY  	SECTOR_ETH+270
#define EE_COMMUNITY		SECTOR_COMMUNITY


#define KE_PTR			996
#define KE_CNT			998
#define UNET_AVAR_PTR	1000
#define UNET_AVAR_CNT	1002
#define SRC1_AVAR_PTR	1004
#define SRC1_AVAR_CNT	1006
#define SRC2_AVAR_PTR	1008
#define SRC2_AVAR_CNT	1010
#define BAT_AVAR_PTR	1012
#define BAT_AVAR_CNT	1014
#define VZ_PTR			1016
#define VZ_CNT			1018
#define WRK_PTR		1020
#define WRK_CNT		1022


#define EVENT_LOG	1024 
//массив данных журнала событий 32*64=2048
// Структура данных журнала событий:
// Байт 0 - род устройства:
//					'B' - батарея
//					'S' - бпсы
//					'P' - питающая сеть
//					'I' - инверторы
//					'U' - УКУ
//					'T' - Внешний датчик температуры
//					'L' - Внешний логический вход
// Байт 1 - порядковый номер устройства(начинается с нуля)
// Байт 2 - род события:
//					'A' - авария (для питающей сети) 
//					'L' - авария связи (для БПСов и инверторов)
//					'C' - авария отсутствия(для батареи и БПСов) 
//					'U' - авария завышенного напряжения (для БПСов и инверторов) 
//					'u' - авария заниженного напряжения (для БПСов и инверторов) 
//					'T' - авария по температуре (для БПСов и инверторов) 
//					'R' - перезагрузка или включение, только для УКУ
// Байт 3 - год возникновения события
// Байт 4 - месяц возникновения события
// Байт 5 - день возникновения события
// Байт 6 - час возникновения события
// Байт 7 - минута возникновения события
// Байт 8 - секунда возникновения события

#define PTR_EVENT_LOG	EVENT_LOG+1024+512+1024 
// указатель на события(показывает на последнее записанное) 
#define CNT_EVENT_LOG	PTR_EVENT_LOG+2 
// колличество событий (не более 64) 
// массив данных аварий сети {(8*64)+(2*64)}
// Структура данных аварий сети:
// при возникновении аварии записывается 
// первые 4 байта с полным временем возникновения аварии
// другие 4 байта полностью обнуляются, при пропадании аварии  в них записывается
// полное время устранения и в 2 байта данных записывается минимальное напряжение 
// во время аварии.

#define SRC1_AVAR	1664
#define SRC1_AVAR_DAT	2176  
// массив данных аварий источника №1 {(8*64)+(4*64)}
// Структура данных аварий источника №1:
// при возникновении аварии записывается 
// первые 4 байта с полным временем возникновения аварии
// другие 4 байта полностью обнуляются, при пропадании аварии  в них записывается
// полное время устранения и в 4 байта данных записывается : 
// 1 байт - вид аварии(0x55 - занижено напряжение,
//                     0x66 - завышено напряжение,
//                     0x77 - перегрев источника)

#define SRC2_AVAR	2432
#define SRC2_AVAR_DAT	2944  
// массив данных аварий источника №1 {(8*64)+(4*64)}
// Структура данных аварий источника №1:
// при возникновении аварии записывается 
// первые 4 байта с полным временем возникновения аварии
// другие 4 байта полностью обнуляются, при пропадании аварии  в них записывается
// полное время устранения и в 4 байта данных записывается : 
// 1 байт - вид аварии(0x55 - занижено напряжение,
//                     0x66 - завышено напряжение,
//                     0x77 - перегрев источника)

#define BAT_AVAR	3200
#define BAT_AVAR_DAT	3712  
// массив данных аварий батареи {(8*64)+(4*64)}
// Структура данных аварий источника №1:
// при возникновении аварии записывается 
// первые 4 байта с полным временем возникновения аварии
// другие 4 байта полностью обнуляются, при пропадании аварии  в них записывается
// полное время устранения и в 4 байта данных записывается : 
// 1 байт - вид аварии(0x55 - занижено напряжение,
//                     0x66 - завышено напряжение,
//                     0x77 - перегрев источника)

#define VZ	3968
#define VZ_L	4224  
// массив данных выравнивающих зарядов {(4*64)+(2*64)}
// Структура данных ыравнивающих зарядов:
// при завершении процесса записывается 
// первые 4 байта с полным временем завершения процесса
// и в 2 байта данных записывается длительность процесса в часах 

#define WRK	4352
#define WRK_AH	5376  
// массив данных разрядов батареи {(8*128)+(2*128)}
// Структура данных разрядов батареи:
// при завершении процесса записывается 
// первые 4 байта с полным временем начала процесса
// затем 4 байта с полным временем завершения процесса
// и в 2 байта данных записывается колличество отданных амперчасов 

#define KE	5632
#define KE_AH	6144  
// массив данных разрядов батареи {(8*64)+(2*64)}
// Структура данных разрядов батареи:
// при завершении процесса записывается 
// первые 4 байта с полным временем начала процесса
// затем 4 байта с полным временем завершения процесса
// и в 2 байта данных записывается колличество отданных амперчасов 

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

