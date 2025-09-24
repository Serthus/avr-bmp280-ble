#include "uart.h"
#include <avr/io.h>
#include <stdlib.h>

void uart_init(void)
{
	unsigned int ubrr = 103;
	UBRR0H = (ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
unsigned char uart_receive(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}
void uart_send(uint8_t data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}
void display_text(const char *text)
{
	while(*text)
	{
		uart_send(*text);
		text++;
	}
}
void display_float_number(float number)
{
	char bufor[20];
	dtostrf(number, 4, 2, bufor);
	for(int i = 0; bufor[i] != '\0'; i++)
	{
		uart_send(bufor[i]);
	}
}