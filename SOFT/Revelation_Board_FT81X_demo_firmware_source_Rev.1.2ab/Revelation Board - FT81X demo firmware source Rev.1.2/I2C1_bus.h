#ifndef I2C1_BUS_H_
#define I2C1_BUS_H_

#include "stm32f0xx.h"
#include "stm32f0xx_i2c.h"

void init_I2C1(void);
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
void I2C_stop(I2C_TypeDef* I2Cx);
void I2C_WriteDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t RegisterValue);
uint8_t I2C_ReadDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr);
uint8_t I2C_AMT_ReadDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr);

#endif /* I2C1_BUS_H_ */
