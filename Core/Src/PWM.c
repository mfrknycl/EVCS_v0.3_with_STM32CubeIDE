/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "PWM.h"
#include "main.h"
#include <stdint.h>


extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc;

extern int relay_statu;

/* Variables ------------------------------------------------------------------*/
uint32_t adcVal0; //to store ADC value


/* Functions ------------------------------------------------------------------*/
void relay(uint8_t relayState){
	if(relayState == RelayClosed){
		HAL_GPIO_WritePin(RLY1_GPIO_Port, RLY1_Pin, 1);
		relay_statu = 1;
	}else if(relayState == RelayON){
		relay_statu = 0;
		HAL_GPIO_WritePin(RLY1_GPIO_Port, RLY1_Pin, 0);
	}
}

CurrentStates_t generatePWM(uint16_t dutycycle){
	htim3.Instance->CCR1 = dutycycle;
	//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, dutycycle);
}
		//duty = current / 0.6;
		//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty*10);
//Duty cycle = Amps / 0.6
//Amps = Duty cycle x 0.6
void generateCurrent(uint16_t current){
	htim3.Instance->CCR1 = (current/0.6)*10;
	//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (current/0.6));
}

void readFeedback(){
		if(HAL_ADC_PollForConversion(&hadc, 5) == HAL_OK)
		{
			adcVal0 = HAL_ADC_GetValue(&hadc);
			HAL_GPIO_TogglePin(NEW_LED_GPIO_Port, NEW_LED_Pin);
			HAL_Delay(100);
		}else{
			HAL_GPIO_TogglePin(NEW_LED_GPIO_Port, NEW_LED_Pin);
			HAL_Delay(1000);
		}
		
		HAL_Delay(50);
}

States_t specifyState(States_t *pStates){
	switch (*pStates)
  {
  	case stateA: //just +12V
			HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1); //Start PWM signal generation at 1KHz with 10% Duty Cyle
			htim3.Instance->CCR1 = 1000; //put constant +12V on pilot pin
  		break;
  	case stateB:
			HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1); //Start PWM signal generation at 1KHz with 10% Duty Cyle
  		break;
  	case stateC:
  		break;
  	case stateE:
  		break;	
  	case stateF:
  		break;		
  	default:
  		break;
  }
}
//***************


























