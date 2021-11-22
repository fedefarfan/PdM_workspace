
#include <stdio.h>
#include <stdbool.h>
#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


#define DELAY_time 40
static delay_t delay;

void debounceInit(void){
debounceState = button_up;

	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&delay, DELAY_time);

	//BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
}


void debounceUpdate(void){

	switch(debounceState){

	case button_up:
		if(delayRead(&delay)){
			if(BSP_PB_GetState(BUTTON_USER)){
				debounceState= button_falling;
				BSP_LED_Off(LED1);
				BSP_LED_On(LED2);
				BSP_LED_Off(LED3);}
			else {
				debounceState = button_up;
				BSP_LED_On(LED1);
				BSP_LED_Off(LED2);
				BSP_LED_Off(LED3);
				 }
				}
	    break;
	case button_falling:
		if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					debounceState= button_down;
					BSP_LED_On(LED1);
					BSP_LED_On(LED2);
					BSP_LED_Off(LED3);}
				else {
					debounceState = button_up;
					BSP_LED_On(LED1);
					BSP_LED_Off(LED2);
					BSP_LED_Off(LED3);}
					}
		break;
	case button_down:
		if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					debounceState= button_down;
					BSP_LED_On(LED1);
					BSP_LED_On(LED2);
					BSP_LED_Off(LED3);}
				else {
					debounceState = button_raising;
					BSP_LED_Off(LED1);
					BSP_LED_Off(LED2);
					BSP_LED_On(LED3);}
					}

		break;
	case button_raising:
		if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					debounceState= button_down;
					BSP_LED_On(LED1);
					BSP_LED_On(LED2);
					BSP_LED_Off(LED3);}
				else {
					debounceState = button_up;
					BSP_LED_On(LED1);
					BSP_LED_Off(LED2);
					BSP_LED_Off(LED3);
					 }
					}


		break;

	}
}
