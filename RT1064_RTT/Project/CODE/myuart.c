#include "myuart.h"

void my_usart_init()
{
	uart_init(USART_8,115200,UART8_TX_D16,UART8_RX_D17);

}