#define SDA__  3
#define SCL__  2
 
#define I2C_TM_BUS_FREE		5
#define	I2C_TM_START_SU		5
#define I2C_TM_START_HD		4
#define I2C_TM_SCL_LOW		5
#define	I2C_TM_SCL_HIGH		4
#define I2C_TM_DATA_SU		1
#define I2C_TM_DATA_HD          0
#define I2C_TM_SCL_TO_DATA	4	/* SCL low to data valid */
#define	I2C_TM_STOP_SU		4
#define I2C_TM_SCL_TMO		10	/* clock time out */


//#define i2c_Start()		i2c_Restart()
#define i2c_WriteTo(address)	i2c_Open((address), I2C_WRITE)
#define i2c_ReadFrom(address)	i2c_Open((address), I2C_READ)

void i2c_Start(void);
void i2c_Restart(void);
unsigned char i2c_SendByte(unsigned char byte);
unsigned char i2c_SendAddress(unsigned char address, unsigned char rw);
signed char i2c_ReadAcknowledge(void);
char i2c_ReadByte(void);
void i2c_SendAcknowledge(unsigned char status);
void i2c_Stop(void);
