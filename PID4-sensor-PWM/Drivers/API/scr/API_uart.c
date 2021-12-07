#include "./../Drivers/API/inc/API_uart.h"
#include "stm32f4xx_hal_msp.c"



int cuenta=0;
char buffer[1024];

char pp[100]="Parity ODD";

int numero;

char texto[6];// ="      ";

/* Private function prototypes -----------------------------------------------*/
//////////#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
///////////#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
///////////#else
//////////#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//////////#endif /* __GNUC__ */
//static void SystemClock_Config(void);
//static void Error_Handler(void);

void uartInit(void){
	 HAL_Init();

	  /* Configure the system clock to 180 MHz */
	  SystemClock_Config();
	  BSP_LED_Init(LED2);

	  UartHandle.Instance        = USARTx;
	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;


	  UartHandle2.Instance        = USARTx2;
	  UartHandle2.Init.BaudRate   = 9600;
	  UartHandle2.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle2.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle2.Init.Parity     = UART_PARITY_NONE;//UART_PARITY_ODD;
	  UartHandle2.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle2.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle2.Init.OverSampling = UART_OVERSAMPLING_16;

	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	   {
	     // Initialization Error
		  	     Error_Handler();
	   }
	  if (HAL_UART_Init(&UartHandle2) != HAL_OK)
	 	   {
	 	     // Initialization Error
	 		  	     Error_Handler();
	 	   }
/*
	  if (HAL_UART_Init(&USART6) != HAL_OK)
	 	   {
	 	     // Initialization Error
	 		  	     Error_Handler();
	 	   }*/
	  printf("\n\r INICIAMOS UART \n\r");
	  numero=UartHandle.Init.BaudRate ;
	  sprintf(buffer,"\n\r Configuracion 1; Baud Rate  %d  \n\r",numero);
	  HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);


	  sprintf(buffer,"\n\r Configuracion 2; %s  \n\r",pp);
	  HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);

	  numero=1;

	  sprintf(buffer," %d\n",numero);
  	  HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);
	  //	UART2
	  sprintf(buffer," %d\n",numero);
	  HAL_UART_Transmit(&UartHandle2,(uint8_t *) buffer, strlen(buffer), 5000);

}


void lectura(void){


	int t0,temp,i;




	HAL_UART_Receive(&UartHandle, texto, 1, 10000);




	      t0=texto[0]-'0';
	 	  //t1=texto[1]-'0';
	 	  //t2=texto[2]-'0';
	 	  //t3=texto[3]-'0';
	 	 // t4=texto[4]-'0';
	 	 // t5=texto[5]-'0';

//    sprintf(buffer,"%d",t0);
	//  HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);

    if(i==0)
    {
	  if(t0==0)
	  {
	    i=1;
	  }
    }else{
		  if(i==1){
	  		  temp=t0*1000;
	              }
		  if(i==2){
		  	  temp=temp+t0*100;
		  	  	  }
		  if(i==3){
		  	  temp=temp+t0*10;
		  	  	  }
		  if(i==4){
	  		  temp=temp+t0;
		  	  	  }
	        i++;
   	  if(i==5){
	        	 i=0;
	        	 sprintf(buffer,"%d",temp);
	        	 HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);
	  	  	  	  }
	  }

}


void uartSendString(uint8_t pstring)
{
//         uint8_t pstring=0x61;
	      sprintf(buffer,"\n\r Caracteres ASCII 0x61 = %c  \n\r",pstring);
		  HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);

		  sprintf(buffer," cuenta %d  \n\r",++cuenta);
		  HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);


}

void uartmMEF(char pstring[50],int entrada1,int entrada2,int entrada3)
{

	      sprintf(buffer,"\n\r %s  LED1=%d LED2=%d LED3=%d\n\r",pstring,entrada1,entrada2,entrada3);
		  HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);


}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;


  //##-1- Enable peripherals and GPIO Clocks #################################
  // Enable GPIO TX/RX clock
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();


  // Enable USARTx clock
  USARTx_CLK_ENABLE();

  ///////////////////////////////
  //YO
  //////////////////////////////
  USARTx_TX_GPIO_CLK_ENABLE2();
  USARTx_RX_GPIO_CLK_ENABLE2();


  // Enable USARTx clock
  USARTx_CLK_ENABLE2();
  ////////////////////////



  //##-2- Configure peripheral GPIO ##########################################
  // UART TX GPIO pin configuration
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /////////////////////////////////////////
  //
  ////////////////////////////////////////
  GPIO_InitStruct.Pin       = USARTx_TX_PIN2;
   GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Pull      = GPIO_PULLUP;
   GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.Alternate = USARTx_TX_AF;

   HAL_GPIO_Init(USARTx_TX_GPIO_PORT2, &GPIO_InitStruct);
  /////////////////////////////////////////////




  // UART RX GPIO pin configuration
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);



  ////////////////////////
  //yo
  ////////////////////////
  GPIO_InitStruct.Pin = USARTx_RX_PIN2;
   GPIO_InitStruct.Alternate = USARTx_RX_AF2;

   HAL_GPIO_Init(USARTx_RX_GPIO_PORT2, &GPIO_InitStruct);


}


void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  //##-1- Reset peripherals ##################################################
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  //##-2- Disable peripherals and GPIO Clocks #################################
  // Configure UART Tx as alternate function
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  // Configure UART Rx as alternate function
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);


  ///////////
  //YO
  /////////
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  //##-2- Disable peripherals and GPIO Clocks #################################
  // Configure UART Tx as alternate function
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT2, USARTx_TX_PIN2);
  // Configure UART Rx as alternate function
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT2, USARTx_RX_PIN2);


}


static void Error_Handler(void)
{
// Turn LED2 on
  BSP_LED_On(LED2);
  while (1)
  {
  }
}


static void SystemClock_Config(void)
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
    /* Initialization Error */
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
}

