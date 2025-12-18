// Project: Read temperature and pressure from BMP280 on AVR
// Microcontroller: ATmega328P / Arduino Uno
// Communication: I2C (TWI), UART for data transmission
// Author: Kamil Kupis
// Date: 2025-09-24
// Description: Reads temperature and pressure from BMP280,
// processes data and sends it over UART.

#include "bmp280.h"
#include "config.h"
#include "uart.h"
#include "twi.h"

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{	
	uart_init();
	TWI_init();
	
	BMP280_check_error();
	BMP280_reset();
	BMP280_config_control();
	BMP280_calibration_data();
	while (1)
	{
		read_temperature_pressure();
		
		display_text("Temperatura: ");
		display_float_number(temperature);
		uart_send(32);
		uart_send('C');
		uart_send('\n');
		
		display_text("Cisnienie: ");
		display_float_number(pressure);
		uart_send(32);
		display_text("hPa");
		uart_send('\n');
		uart_send('\n');
		_delay_ms(5000);
	}
}
