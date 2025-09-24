#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <stdint.h>

void TWI_init(void);
uint8_t TWI_start(void);
void TWI_stop(void);
uint8_t TWI_write(uint8_t data);
uint8_t TWI_ReadACK(void);
uint8_t TWI_ReadNACK(void);
void BMP280_WriteReg(uint8_t reg, uint8_t value);
uint8_t BMP280_ReadReg(uint8_t reg);

#endif