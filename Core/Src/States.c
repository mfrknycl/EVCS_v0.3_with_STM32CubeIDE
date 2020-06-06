#include "States.h"
#include <stdint.h>

extern uint32_t analog_value;
extern TIM_HandleTypeDef htim3;

/**
 *	  @brief  get states for the pilot line
 *    @return EVSE_StatusTypeDef
 */
EVSE_StatusTypeDef getState(){
	  if ((analog_value >= 240) && (analog_value <= 255)){
		  htim3.Instance->CCR1 = 1000;
		  return State_A;
	  }
	  HAL_Delay(200);

	  if ((analog_value >= 117) && (analog_value <= 125)){
		  htim3.Instance->CCR1 = 1000;
		  return State_A;
	  }

	  if ((analog_value >= 210) && (analog_value <= 220)){
	  	  htim3.Instance->CCR1 = 500;
	  	  return State_B;

	  }

	  if ((analog_value >= 100) && (analog_value <= 108)){
		  htim3.Instance->CCR1 = 500;
		  return State_B;
	  	}


	  if((analog_value >= 80) && (analog_value <= 89)){
		  htim3.Instance->CCR1 = 500;
		  return State_C;
	  }

	  if((analog_value >= 68) && (analog_value <= 75)){
		  htim3.Instance->CCR1 = 500;
		  return State_D;
	  }
	  /*
	  if((analog_value >= 0) && (analog_value <= 0)){
		  htim3.Instance->CCR1 = 500;
		  return State_E;
	  }
	   */
	  if((analog_value >= 45) && (analog_value <= 53)){
		  htim3.Instance->CCR1 = 500;
		  return State_F;
	  }
}
