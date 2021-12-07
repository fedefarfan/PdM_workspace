#include <stdio.h>
#include <stdbool.h>
#include "API_PWM.h"
#include "API_delay.h"
#include "./../Drivers/API/inc/API_uart.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"


char texto[6];// ="      ";
char buffer[3000];//[1024];

float error=0.0,errSum=0.0,Setpoint=40.0,lastErr=0;
int Output;






int pid_calc(int temp3){
int   lastTime,muestra;
float Ajuste=0.0012;//0.0015;
float Kp=Ajuste*3.35;//Ajuste*Kp2;//Probamos 10,5,20 y ahora 10... acomodamos salida PID con PWM
float Ki=Kp/8.0;//Kp/Ti;
//float Ki=0.1*Kp/8.0;//Kp/Ti;
//float Kd=Kp*2.0;
float Kd=Kp*2.0;
float timeChange=1000,dErr,temperatura,error,pot1;//Kp*Td;
	//if(delayRead(&delayTD_M)){



    temperatura=(float) (temp3/100.0);

    error = Setpoint - temperatura;//Setpoint - Input;
    errSum += (error * timeChange);
    dErr = (error - lastErr) / timeChange;

    /* Calculamos la función de salida del PID. */

    Output = Kp * error + Ki * errSum + Kd * dErr;

    /* Guardamos el valor de algunas variables para el próximo ciclo de cálculo. */

    lastErr = error;
    lastTime = 1000;


    pot1=Output;
    if(pot1>255)
    {
    	pot1=255.0;
    }
    if(pot1<0)
    {
    	pot1=0.0;
    }
   // analogWrite(9 , pot1);
   // Serial.println(temp);
muestra=(int) (pot1);

   // sprintf(buffer,"T=%d  muestra=%d ",temp3,muestra);
   // HAL_UART_Transmit(&UartHandle,(uint8_t *) buffer, strlen(buffer), 5000);


    return muestra;
}

