
#define UBRR_VALUE(UART_BAUDRATE) ((unsigned char)(((F_CPU)/((UART_BAUDRATE) * (16UL)))-((double)(1UL))))
