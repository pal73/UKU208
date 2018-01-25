

extern char portForStarkBatteryIsInitiated;
extern char starkBatteryHndlPhase;
extern char starkBatteryInBuff[100];
extern short starkBatteryInBuffPtr;
extern char starkRequestPhase;
//short coslightSilentCnt;
//char bCoslightPacketIn;
//short coslightBatteryInBuffPtr_plazma;

void stark_bat_hndl(void);
short ascii2halFhex(char in);