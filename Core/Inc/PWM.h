#ifndef __PWM_H__
#define __PWM_H__

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* Private define ------------------------------------------------------------*/
#define RelayClosed  (1)
#define RelayON 		 (0)

/*
#define current_6A     	(100) //10% Duty Cycle
#define current_12A			(200)	//20% Duty Cycle
#define current_18A			(300)	//30% Duty Cycle
#define current_24A			(400)	//40% Duty Cycle
#define current_30A			(500)	//50% Duty Cycle
*/

/* Typedef ------------------------------------------------------------------*/

typedef enum {
current_6A  = 100, 	//10% Duty Cycle
current_12A	= 200,	//20% Duty Cycle
current_18A = 300,	//30% Duty Cycle
current_24A = 400,	//40% Duty Cycle
current_30A = 500		//50% Duty Cycle
}CurrentStates_t;

//CurrentStates_t power = {.c6A=100, .c12A=200, .c18A=300, .c24A=400, .c30A=500};


/** 
  * @brief  Pilot Signal status structures definition  
  */ 
typedef enum {
	stateA = 972, 	//Not Connected						 --> 972 == 12V
	stateB = 849,	  //EV Connected (Ready)     --> 849 == 9V
	stateC = 730, 	//EV Charge								 --> 730 == 6V
	stateE = 0,			//Error
	stateF = 1			//Unknown/Error
}States_t;

/* Function Decleration ------------------------------------------------------------------*/
void relay(uint8_t relayState);
CurrentStates_t generatePWM(uint16_t dutycycle);
void readFeedback(); // for deneme
void generateCurrent(uint16_t current);





#endif /* __PWM_H__ */