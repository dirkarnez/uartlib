#define F_CPU 1600000000UL
#include <stdio.h>

#define USART_BAUDRATE 9600
#define UBRR0L_VALUE ((unsigned char)(F_CPU/(USART_BAUDRATE*16UL)-1UL))
#define UBRR0H_VALUE ((F_CPU/(USART_BAUDRATE*16UL)-1UL) >> 8UL)
// 103
int main(void) {
    printf("%d",  (unsigned char)((F_CPU/16UL/9600)-1UL));
}
