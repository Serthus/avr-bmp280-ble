#include "config.h"
#include <util/delay.h>
#include "bmp280.h"
#include "twi.h"

typedef int32_t BMP280_S32_t;
typedef uint32_t BMP280_U32_t;
typedef int64_t BMP280_S64_t;

BMP280_S32_t t_fine;
float temperature = 0;
float pressure = 0;
unsigned short dig_T1, dig_P1;
signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

void BMP280_WriteReg(uint8_t reg, uint8_t value)
{
	TWI_start();
	TWI_write(BMP280_ADDR << 1 | 0);
	
	TWI_write(reg);
	TWI_write(value);
	TWI_stop();
	
}
uint8_t BMP280_ReadReg(uint8_t reg)
{
	uint8_t data;
	TWI_start();
	TWI_write(BMP280_ADDR << 1 | 0);
	TWI_write(reg);
	TWI_start();
	TWI_write(BMP280_ADDR << 1 | 1);
	data = TWI_ReadNACK();
	TWI_stop();
	return data;
}
void BMP280_check_error(void)
{
	if(BMP280_ReadReg(ID) != 0x58)
	{
		_delay_ms(5000);
		display_text("chip_identification error");
	}
}
void BMP280_reset(void)
{
	BMP280_WriteReg(RESET, 0xB6);
	while(BMP280_ReadReg(STATUS) & (0x01));
}
void BMP280_config_control(void)
{
	BMP280_WriteReg(CTRL_MEAS, 0x29); // ustawione forced mode, low power pressure
	BMP280_WriteReg(CONFIG, 0x00);
}
void BMP280_calibration_data(void)
{
	dig_T1 = BMP280_ReadReg(BMP280_REG_DIG_T1_LSB) | ((unsigned short)BMP280_ReadReg(BMP280_REG_DIG_T1_MSB) << 8);
	dig_T2 = BMP280_ReadReg(BMP280_REG_DIG_T2_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_T2_MSB) << 8);
	dig_T3 = BMP280_ReadReg(BMP280_REG_DIG_T3_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_T3_MSB) << 8);
	
	dig_P1 = BMP280_ReadReg(BMP280_REG_DIG_P1_LSB) | ((unsigned short)BMP280_ReadReg(BMP280_REG_DIG_P1_MSB) << 8);
	dig_P2 = BMP280_ReadReg(BMP280_REG_DIG_P2_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P2_MSB) << 8);
	dig_P3 = BMP280_ReadReg(BMP280_REG_DIG_P3_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P3_MSB) << 8);
	dig_P4 = BMP280_ReadReg(BMP280_REG_DIG_P4_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P4_MSB) << 8);
	dig_P5 = BMP280_ReadReg(BMP280_REG_DIG_P5_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P5_MSB) << 8);
	dig_P6 = BMP280_ReadReg(BMP280_REG_DIG_P6_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P6_MSB) << 8);
	dig_P7 = BMP280_ReadReg(BMP280_REG_DIG_P7_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P7_MSB) << 8);
	dig_P8 = BMP280_ReadReg(BMP280_REG_DIG_P8_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P8_MSB) << 8);
	dig_P9 = BMP280_ReadReg(BMP280_REG_DIG_P9_LSB) | ((signed short)BMP280_ReadReg(BMP280_REG_DIG_P9_MSB) << 8);
}
int32_t BMP280_read_temperature(void)
{
	uint8_t MSB = BMP280_ReadReg(TEMP_MSB);
	uint8_t LSB = BMP280_ReadReg(TEMP_LSB);
	uint8_t XLSB = BMP280_ReadReg(TEMP_XLSB);
	uint32_t adc_T = ((int32_t)MSB << 12) | ((int32_t)LSB << 4) | ((int32_t)XLSB >> 4);
	return adc_T;
}
int32_t BMP280_read_pressure(void)
{
	uint8_t MSB = BMP280_ReadReg(PRESS_MSB);
	uint8_t LSB = BMP280_ReadReg(PRESS_LSB);
	uint8_t XLSB = BMP280_ReadReg(PRESS_XLSB);
	uint32_t adc_P = ((int32_t)MSB << 12) | ((int32_t)LSB << 4) | ((int32_t)XLSB >> 4);
	return adc_P;
}
BMP280_S32_t bmp280_calculations_temperature(BMP280_S32_t adc_T)
{
	BMP280_S32_t var1, var2, T;
	var1 = (((adc_T>>3) - ((BMP280_S32_t)dig_T1<<1)) * ((BMP280_S32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((BMP280_S32_t)dig_T1)) * ((adc_T>>4) - ((BMP280_S32_t)dig_T1))) >> 12) * ((BMP280_S32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}
BMP280_U32_t bmp280_calculations_pressure(BMP280_S32_t adc_P)
{
	BMP280_S64_t var1, var2, p;
	var1 = ((BMP280_S64_t)t_fine) - 128000;
	var2 = var1 * var1 * (BMP280_S64_t)dig_P6;
	var2 = var2 + ((var1*(BMP280_S64_t)dig_P5)<<17);
	var2 = var2 + (((BMP280_S64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (BMP280_S64_t)dig_P3)>>8) + ((var1 * (BMP280_S64_t)dig_P2)<<12);
	var1 = (((((BMP280_S64_t)1)<<47)+var1))*((BMP280_S64_t)dig_P1)>>33;
	if (var1 == 0)
	{
		return 0;
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((BMP280_S64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((BMP280_S64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((BMP280_S64_t)dig_P7)<<4);
	return (BMP280_U32_t)p;

}
void read_temperature_pressure(void)
{
	BMP280_WriteReg(CTRL_MEAS, 0x29);
	while(BMP280_ReadReg(STATUS) & 0x08);
	uint32_t adc_T = BMP280_read_temperature();
	uint32_t adc_P = BMP280_read_pressure();
	BMP280_U32_t T = bmp280_calculations_temperature(adc_T);
	BMP280_U32_t P = bmp280_calculations_pressure(adc_P);
	temperature = T / 100.0f;
	pressure = P / 256.0f;
	pressure = pressure / 100.0f;
}