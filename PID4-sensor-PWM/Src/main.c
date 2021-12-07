#include "main.h"
#include <stdio.h>
#include <stdbool.h>
#include "./../Drivers/API/inc/API_uart.h"
#include "API_delay.h"
#include "API_PWM.h"
#include "PID.h"
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */
char texto[6];// ="      ";
float errorp=0,errord=0,errori=0;
int temperatura;
/** @addtogroup UART_Printf
  * @{
  */

/*void HAL_UART_RcCpltCollback(UART_HandleTypeDef UartHandle;)
{
	HAL_UART_Receive_IT(&UartHandle, texto, 6);

}*/


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
//////////////UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
//static void SystemClock_Config(void);
//static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	int ciclo=0,salida=0;
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
 // HAL_Init();

  /* Configure the system clock to 180 MHz */
//  SystemClock_Config();

	uartInit();
  /* Initialize BSP Led for LED2 */
  //BSP_LED_Init(LED2);

  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits (7 data bit + 1 parity bit) : 
	                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
      - Stop Bit    = One Stop bit
      - Parity      = ODD parity
      - BaudRate    = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
/*  UartHandle.Instance        = USARTx;

  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;*/

	PWMInit();

	//HAL_UART_Receive_IT(&UartHandle, texto, 1000);
  /* Output a message on Hyperterminal using printf function */
  printf("\n\r Control PID - UART - sensor DS18B20 Arduino UNO \n\r");
  printf("** INICIO ** \n\r");
  pstring=0x61;
  /* Infinite loop */
  while (1)
  {


	  // uartSendString(pstring);
	  // HAL_Delay(500);
	  //debounceUpdate();
	 // HAL_UART_Receive(&UartHandle, texto, 1, 10000);
	 // HAL_UART_Transmit(&UartHandle, texto, 1, 10000);


	  //lectura();

	  ciclo=tomadato(ciclo);


	 // ciclo=cambioDUTY(salida);
	  //salida=ciclo;
	  //if(salida>=255){
	  //       salida=0;}
	  DUTY(ciclo);

	  //HAL_UART_Receive(&UartHandle, texto, 1, 10000);
	  //HAL_UART_Transmit(&UartHandle, texto, 1, 10000);
	  //HAL_UART_Transmit_IT(&UartHandle, texto, 70);
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
/*static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  // Enable Power Control clock
  __HAL_RCC_PWR_CLK_ENABLE();
  
  // The voltage scaling allows optimizing the power consumption when the device is
  //   clocked below the maximum system frequency, to update the voltage scaling value
  //   regarding system frequency refer to product datasheet.
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  // Enable HSE Oscillator and activate PLL with HSE as source
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    // Initialization Error
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    // Initialization Error
    Error_Handler();
  }
  
  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  //   clocks dividers
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    // Initialization Error
    Error_Handler();
  }
}*/
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
/*static void Error_Handler(void)
{
// Turn LED2 on
  BSP_LED_On(LED2);
  while (1)
  {
  }
}*/

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
