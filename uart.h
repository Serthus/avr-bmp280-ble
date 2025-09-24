#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <stdint.h>

void uart_init(void);
unsigned char uart_receive(void);
void uart_send(uint8_t data);
void display_text(const char *text);
void display_float_number(float number);

#endif