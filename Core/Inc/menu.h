#ifndef __MENU_H__
#define __MENU_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "MCP9808.h"


/* Variables ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/




/* Function Decleration ------------------------------------------------------------------*/

int buttons(void);
void main_page(void);
void init_page(void);
void screen(void);
int button_state(void);
void SummaryPage(void);
void summary(void);


void NotConnected(void);
void ConnectedReady(void);
void Charging(void);
void Error(void);






#endif //__MENU_H__