// Projekt: Odczyt temperatury i cisnienia z BMP280 na AVR
// Mikrokontroler: ATmega328P / Arduino Uno
// Komunikacja: I2C (TWI), UART do wysylania danych
// Autor: Kamil
// Data: 24.09.2025
// Opis: Program odczytuje temperature i cisnienie z BMP280,
// przetwarza je i wysyla przez UART.

#include "bmp280.h"
#include "config.h"
#include "uart.h"
#include "twi.h"

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{	
	uart_init(); //UART sterujacy BLE
	TWI_init(); // barometr na i2c
	
	BMP280_check_error();
	BMP280_reset();
	BMP280_config_control(); // ustawienie config oraz control
	BMP280_calibration_data(); // nie jest to potrzebne do odczytu temperatury
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
