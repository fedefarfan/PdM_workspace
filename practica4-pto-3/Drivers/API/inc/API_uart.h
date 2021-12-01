#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal_msp.c"



uint8_t pstring;//=0x61;
UART_HandleTypeDef UartHandle;
int entrada;
void uartInit(void);
static void SystemClock_Config(void);
static void Error_Handler(void);
void uartSendString(uint8_t pstring);
void uartmMEF(char pstring[50],int entrada1,int entrada2,int entrada3);
