
#include <stdio.h>
#include <stdbool.h>
#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


#define DELAY_time 40
static delay_t delay;

//////////////////////////////
//
#define LED1_DURATION 100
#define LED2_DURATION 500
#define LED3_DURATION 1000



static delay_t delayLed1;
static delay_t delayLed2;
static delay_t delayLed3;

//////////////////////////////


void debounceInit(void){
debounceState = button_up;

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	}
	void timeLed_1(void){
		    BSP_LED_Init(LED1);
			BSP_LED_Init(LED2);
			BSP_LED_Init(LED3);
		    delayInit(&delay, DELAY_time);
			delayInit(&delayLed1,LED1_DURATION);
			delayInit(&delayLed2,LED2_DURATION);
			delayInit(&delayLed3,LED3_DURATION);
			in=1;
			in1=0;
	}

	void timeLed_2(void){
		    BSP_LED_Init(LED1);
			BSP_LED_Init(LED2);
			BSP_LED_Init(LED3);
     		delayInit(&delay, DELAY_time);
		    delayInit(&delayLed1,LED2_DURATION);
			delayInit(&delayLed2,LED2_DURATION);
			delayInit(&delayLed3,LED2_DURATION);
	        in=0;
	        in1=1;
	}




void debounceUpdate(void){

	switch(debounceState){

	case button_up:
		if(delayRead(&delay)){
			if(BSP_PB_GetState(BUTTON_USER)){
				debounceState= button_falling;
				if(in1==0){
					timeLed_2();}
				else{
				    buttonPressed();}}
			else {
				debounceState = button_up;
				if(in==0){
					timeLed_1();}
				else{
				buttonReleased();}}
				}
	    break;
	case button_falling:
		if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					debounceState= button_down;
					if(in1==0){
						timeLed_2();}
						else{
						     buttonPressed();}}
				else {
					debounceState = button_up;
					if(in==0){
						timeLed_1();}
						else{
							buttonReleased();}}
					}
		break;
	case button_down:
		if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					debounceState= button_down;
					if(in1==0){
							timeLed_2();}
							else{
						    buttonPressed();}}
				else {
					debounceState = button_raising;
					if(in==0){
							timeLed_1();}
							else{
							buttonReleased();}}
					}

		break;
	case button_raising:
		if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					debounceState= button_down;
					if(in1==0){
						timeLed_2();}
						else{
						    buttonPressed();}}
				else {
					debounceState = button_up;
					if(in==0){
						timeLed_1();}
						else{
							buttonReleased();}}
					}


		break;

	}
}
void buttonPressed(void){

		if(delayRead(&delayLed1)){
			           BSP_LED_Toggle(LED1);
					}
					if(delayRead(&delayLed2)){
				           BSP_LED_Toggle(LED2);
					}
					if(delayRead(&delayLed3)){
					       BSP_LED_Toggle(LED3);
					}

}

void buttonReleased(void){
	if(delayRead(&delayLed1)){
	           BSP_LED_Toggle(LED1);
			}
			if(delayRead(&delayLed2)){
		           BSP_LED_Toggle(LED2);
			}
			if(delayRead(&delayLed3)){
			       BSP_LED_Toggle(LED3);
			}
}
