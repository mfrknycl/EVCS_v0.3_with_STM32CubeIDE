#ifndef __STATES_H__
#define __STATES_H__


/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ssd1306_tests.h"
#include "ssd1306.h"


/* Typedef ------------------------------------------------------------------*/
typedef enum
{
  State_A  = 0x01U, //Not Connected
  State_B  = 0x02U, //EV Connected
  State_C  = 0x03U, //EV Charging
  State_D  = 0x04U, //Vent. Required
  State_E  = 0x05U, //Error
  State_F  = 0x06U  //Unknown/Error
} EVSE_StatusTypeDef;




/* Function Decleration ------------------------------------------------------------------*/
EVSE_StatusTypeDef getState();







#endif /* __STATES_H__ */
