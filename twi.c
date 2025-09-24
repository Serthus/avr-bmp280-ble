#include "twi.h"
#include <avr/io.h>

void TWI_init(void)
{
	TWSR = 0;
	TWBR = 72;
}
uint8_t TWI_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT)));
	return (TWSR & 0xF8);
}
void TWI_stop(void)
{
	TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
}
uint8_t TWI_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	return (TWSR & 0xF8);
}
uint8_t TWI_ReadACK(void)
{
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}
uint8_t TWI_ReadNACK(void)
{
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}