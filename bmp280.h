#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <stdint.h>

#define BMP280_ADDR 0x76 // Adres I2C BMP280
#define BMP280_CHIP_ADDRESS 0x58 // Wartoœæ ID chipu

#define ID 0xD0 // Rejestr identyfikacyjny BMP280
#define RESET 0xE0 // Rejestr resetu
#define STATUS 0xF3 // Rejestr statusu
#define CTRL_MEAS 0xF4 // Rejestr konfiguracji pomiaru
#define CONFIG 0xF5 // Rejestr konfiguracji
#define PRESS_MSB 0xF7 // Rejestr MSB ciœnienia
#define PRESS_LSB 0xF8 // Rejestr LSB ciœnienia
#define PRESS_XLSB 0xF9 // Rejestr XLSB ciœnienia
#define TEMP_MSB 0xFA // Rejestr MSB temperatury
#define TEMP_LSB 0xFB // Rejestr LSB temperatury
#define TEMP_XLSB 0xFC // Rejestr XLSB temperatury

#define BMP280_REG_DIG_T1_LSB  0x88
#define BMP280_REG_DIG_T1_MSB  0x89
#define BMP280_REG_DIG_T2_LSB  0x8A
#define BMP280_REG_DIG_T2_MSB  0x8B
#define BMP280_REG_DIG_T3_LSB  0x8C
#define BMP280_REG_DIG_T3_MSB  0x8D

#define BMP280_REG_DIG_P1_LSB  0x8E
#define BMP280_REG_DIG_P1_MSB  0x8F
#define BMP280_REG_DIG_P2_LSB  0x90
#define BMP280_REG_DIG_P2_MSB  0x91
#define BMP280_REG_DIG_P3_LSB  0x92
#define BMP280_REG_DIG_P3_MSB  0x93
#define BMP280_REG_DIG_P4_LSB  0x94
#define BMP280_REG_DIG_P4_MSB  0x95
#define BMP280_REG_DIG_P5_LSB  0x96
#define BMP280_REG_DIG_P5_MSB  0x97
#define BMP280_REG_DIG_P6_LSB  0x98
#define BMP280_REG_DIG_P6_MSB  0x99
#define BMP280_REG_DIG_P7_LSB  0x9A
#define BMP280_REG_DIG_P7_MSB  0x9B
#define BMP280_REG_DIG_P8_LSB  0x9C
#define BMP280_REG_DIG_P8_MSB  0x9D
#define BMP280_REG_DIG_P9_LSB  0x9E
#define BMP280_REG_DIG_P9_MSB  0x9F

typedef int32_t BMP280_S32_t;
typedef uint32_t BMP280_U32_t;
typedef int64_t BMP280_S64_t;

extern BMP280_S32_t t_fine;
extern float temperature;
extern float pressure;
extern unsigned short dig_T1, dig_P1;
extern signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

void BMP280_check_error(void);
void BMP280_reset(void);
void BMP280_config_control(void);
void BMP280_calibration_data(void);
int32_t BMP280_read_temperature(void);
int32_t BMP280_read_pressure(void);
BMP280_S32_t bmp280_calculations_temperature(BMP280_S32_t adc_T);
BMP280_U32_t bmp280_calculations_pressure(BMP280_S32_t adc_P);
void read_temperature_pressure(void);

#endif
