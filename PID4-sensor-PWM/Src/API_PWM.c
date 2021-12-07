#include <stdio.h>
#include <stdbool.h>
#include "API_PWM.h"
#include "API_delay.h"
#include "./../Drivers/API/inc/API_uart.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#define Tiempo_Menor 1
#define Tiempo_cambio 10//500
#define Tiempo_Dato 2000//1000


char texto[6];// ="      ";
char buffer[1024];
static delay_t delayPWM;
static delay_t delayPWM_cambio;
static delay_t delayTD;



int tomadato(int ciclo1)
{
	float errorp1=0;
	int l,i=0,temp,t0,PWM_c,bandera,salida;

	bandera=0;

	if(delayRead(&delayTD)){
		BSP_LED_Off(LED1);
		bandera=1;
for(l=0;l<8;l++)
{
	HAL_UART_Receive(&UartHandle, texto, 1, 1000);
	//	HAL_UART_Receive_IT(&UartHandle, texto, 1000);//, 10000);
	     t0=texto[0]-'0';
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
		        if(temp>1000){
		        	 PWM_c=pid_calc(temp);
	        	 sprintf(buffer,"T=%d  muestra=%d ",temp,PWM_c);
        	     HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);
		        }else{
		        	PWM_c=ciclo1;

		        }
        	     //sprintf(buffer,"%d",temp);
		        //HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);
		  	  	  	  }
		  }

//DUTY(ciclo2);
}

	}


	if(bandera>0)
	{
		salida=PWM_c;
	}else{
		salida=ciclo1;
	}

	return salida;
	}

void PWMInit(void){
	estPWM = inicioPWM;
	cuenta_PWM=0;
	BSP_LED_Init(LED1);
delayInit(&delayPWM, Tiempo_Menor);
delayInit(&delayPWM_cambio, Tiempo_cambio);
delayInit(&delayTD, Tiempo_Dato);

BSP_LED_On(LED1);
HAL_Delay(1000);
BSP_LED_Off(LED1);
HAL_Delay(1000);
}

int cambioDUTY(int DP){
int vcambio,ii;
int i=0,temp,t0;
	if(delayRead(&delayPWM_cambio)){
	DP++;
	if(DP>255){
		DP=255;
	}
	//if(temp>3000){
	if(DP<0){
		DP=0;
	}
	vcambio=DP;
	//HAL_UART_Receive(&UartHandle, texto, 1, 10000);
	//HAL_UART_Transmit(&UartHandle, texto, 1, 10000);

	}
	else
	{
		vcambio=DP;
	}
return vcambio;
}

void DUTY(int duty_PWM){
//int duty_PWM=125;


  switch(estPWM){
  //HAL_UART_Receive(&UartHandle, texto, 1, 10000);
		case inicioPWM:
			//HAL_UART_Receive(&UartHandle, texto, 1, 10000);
			if(delayRead(&delayPWM)){
				duty_PWM_interno=duty_PWM;
				cuenta_PWM=0;

				if(duty_PWM_interno == 0){
						xPWM = 0;
						}
						else{
						cuenta_PWM=cuenta_PWM+1;
						xPWM=1;}

			if(xPWM==0){
					estPWM=inicioPWM;
					BSP_LED_Off(LED1);

				}
				else {
					estPWM=pasa_uno;
					 BSP_LED_On(LED1);
					 }
					}
		    break;

		case pasa_uno:

			if(delayRead(&delayPWM)){

			if(cuenta_PWM < duty_PWM_interno)
			{
				cuenta_PWM=cuenta_PWM+1;
				xPWM =1;
			}
				else{
				cuenta_PWM=cuenta_PWM+1;
				xPWM=0;
				}


			if(xPWM==1){
					estPWM=sigue_uno;
					BSP_LED_On(LED1);
				}
				else {
					estPWM=pasa_cero;
					BSP_LED_Off(LED1);

					 }
					}
		    break;

		case sigue_uno:

			if(delayRead(&delayPWM)){

			if(cuenta_PWM < duty_PWM_interno){
				cuenta_PWM=cuenta_PWM+1;
				xPWM=1;
			    }
				else{
				cuenta_PWM=cuenta_PWM+1;
				xPWM=0;
				}

			if(xPWM==1){
					estPWM=sigue_uno;
					BSP_LED_On(LED1);
				}
				else {
					estPWM=pasa_cero;
					BSP_LED_Off(LED1);
					}
					}
		    break;

		case pasa_cero:
			if(delayRead(&delayPWM)){

				if(cuenta_PWM < 255){
						cuenta_PWM=cuenta_PWM+1;
						xPWM=0;
				}
						else{
						xPWM=1;
								}

			if(xPWM==0){
					estPWM=sigue_cero;
					BSP_LED_Off(LED1);
					}
				else {
					estPWM=terminaPWM;
					BSP_LED_Off(LED1);
					 }
					}
		    break;


		case sigue_cero:
			if(delayRead(&delayPWM)){
				if(cuenta_PWM < 255){
						cuenta_PWM=cuenta_PWM+1;
						xPWM=0;
				}
						else{
							cuenta_PWM=cuenta_PWM+1;
						xPWM=1;
							}
			if(xPWM==0){
					estPWM=sigue_cero;
					BSP_LED_Off(LED1);
					}
				else {
					estPWM=terminaPWM;
					BSP_LED_Off(LED1);
					 }
					}
		    break;


		case terminaPWM:
			if(delayRead(&delayPWM)){
				if(duty_PWM == duty_PWM_interno)
				{
					cuenta_PWM=1;
					xPWM=1;}
					else{
					xPWM=0;
					cuenta_PWM=0;
						}

			if(xPWM==0){
					estPWM=inicioPWM;
					BSP_LED_Off(LED1);

				}
				else {
					estPWM=pasa_uno;
					BSP_LED_On(LED1);
					 }
					}
		    break;

		}

  if(cuenta_PWM>255)
  {
	  cuenta_PWM=255;

  }


}
