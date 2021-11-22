/*
 * MEF.h
 *
 *  Created on: 9 nov. 2021
 *      Author: Guillermo
 */

#ifndef MEF_H_
#define MEF_H_

//#include "API_delay.h"
//#include "stm32f4xx_hal.h"
//#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define DELAY_ 40
// Nuevo tipo de datos enumerado llamado estadoMEF_t
typedef enum{
    button_up,
    button_raising,
    button_down,
    button_falling
} debounce_t;

// Variable de estado (global)
static debounce_t debounceState;

// Prototipos de funciones
void debounceInit(void);
void debounceUpdate(void);
void buttonPressed(void);
void buttonReleased(void);

#endif /* MEF_H_ */
