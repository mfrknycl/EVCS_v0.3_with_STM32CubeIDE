#include "menu.h"
#include "cap1203.h"
#include "ssd1306_tests.h"
#include "ssd1306.h"
#include "States.h"

int state = 0;
int count = 0;
extern int buttonStates;
extern int time;
extern int gfci_statu;
extern int relay_statu;

extern TIM_HandleTypeDef htim3;

/**
 *   @brief  Reads the states of the buttons. There are two buttons in total.
 *           Every button has different state if they are pressed over some time.
 *   @return State of the buttons
 */
int buttons(void){
	time = 0;
  if(isLeftTouched() == true){
		while(isLeftTouched() == true){time += 1;}
	  if(time > 500){
			return 4;
		}
   return 3;
  }

  if(isRightTouched() == true){
		while(isRightTouched() == true){time += 1;}
	  if(time > 500){
			return 2;
		}
   return 1;
  }

	
		return 0;
}


void screen(void){


	if(state == 0){
		HAL_Delay(200);
		switch (buttons()){
      case 0:
    	  switch (getState()) {
    		case State_A:
    			  ssd1306_Fill(Black);
    			  ssd1306_SetCursor(2, 7);
    			  ssd1306_WriteString("MFRKNYCL", Font_11x18, White);
    			  ssd1306_UpdateScreen();
    			break;
    		case State_B:
    			  ssd1306_Fill(Black);
    			  ssd1306_SetCursor(2, 7);
    			  ssd1306_WriteString("Connected", Font_11x18, White);
    			  ssd1306_UpdateScreen();
    			break;
    		case State_C:
    			  ssd1306_Fill(Black);
    			  ssd1306_SetCursor(2, 7);
    			  ssd1306_WriteString("Charging", Font_11x18, White);
    			  ssd1306_UpdateScreen();
    			break;
    		case State_D:
    			  ssd1306_Fill(Black);
    			  ssd1306_SetCursor(2, 7);
    			  ssd1306_WriteString("Ventilation", Font_11x18, White);
    			  ssd1306_UpdateScreen();
    			break;
    		case State_E:

    			break;
    		case State_F:
    			  ssd1306_Fill(Black);
    			  ssd1306_SetCursor(2, 7);
    			  ssd1306_WriteString("Unknown/Err", Font_11x18, White);
    			  ssd1306_UpdateScreen();
    			break;
    		default:
    			break;
    	  }

        break;
			    
		}
	}

	
	if(state == 1){
		HAL_Delay(200);
		switch (buttons()){
      case 1:
		  ssd1306_Fill(Black);
		  ssd1306_SetCursor(2, 7);
		  ssd1306_WriteInteger(htim3.Instance->CCR1, Font_11x18, White);
		  ssd1306_UpdateScreen();

        break;
      case 3:
        state = 0;
        break;
		}
	}
	
	if(state == 2){
		HAL_Delay(200);
		switch (buttons()){
      case 1:
        ConnectedReady();
        break;
      case 3:
        NotConnected();
        break;
		}
	}
	
	if(state == 3){
		HAL_Delay(200);
		switch (buttons()){
      case 1:
        Charging();
        break;
      case 3:
        ConnectedReady();
        break;
		}
	}
	
	if(state == 4){
		HAL_Delay(200);
		switch (buttons()){
      case 1:
        Error();
        break;
      case 3:
        Charging();
        break;
		}
	}

}
    
//This the first page
void main_page(void){
		ssd1306_Fill(Black);
    ssd1306_SetCursor(15, 5);
		ssd1306_WriteString("MFRKNYCL", Font_11x18, White);
    ssd1306_UpdateScreen();
	  state = 2;
}

//It shows the State A
void NotConnected(void){
		ssd1306_Fill(Black);
	
    ssd1306_SetCursor(2, 7);
		ssd1306_WriteString("NotConnect.", Font_11x18, White);

    ssd1306_UpdateScreen();
	  state = 2;
}
//It shows the State B
void ConnectedReady(void){

			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 7);
			ssd1306_WriteString("Ready", Font_11x18, White);
			ssd1306_UpdateScreen();
			count ++;			

	  state = 3;
}

//It shows the State C
void Charging(void){
		ssd1306_Fill(Black);
	
    ssd1306_SetCursor(2, 7);
		ssd1306_WriteString("EV Charging", Font_11x18, White);

    ssd1306_UpdateScreen();
	  state = 4;
}

//It shows Unknonw Error
void Error(void){
		ssd1306_Fill(Black);
	
    ssd1306_SetCursor(2, 7);
		ssd1306_WriteString("Error!", Font_11x18, White);

    ssd1306_UpdateScreen();
	  state = 4;
}


void init_page(void){
		ssd1306_Fill(Black);
    ssd1306_SetCursor(2, 26);
		ssd1306_WriteString("initialization...", Font_11x18, White);
    ssd1306_UpdateScreen();
		state = 1;
}

void SummaryPage(void){
		ssd1306_Fill(Black);
	
		//Add temperature information
    ssd1306_SetCursor(1, 1);
		ssd1306_WriteString("Temp:", Font_6x8, White);
		ssd1306_SetCursor(1, 10);
		ssd1306_WriteFloat(readTempC(), Font_6x8, White);
    
		//Add GFCI information
		//0 means no Fault
		//1 mean there is a Fault
		ssd1306_SetCursor(40, 1);
		ssd1306_WriteString("GFCI:", Font_6x8, White);
	
		if(gfci_statu == 1){
			ssd1306_SetCursor(40, 10);
			ssd1306_WriteString("[X]", Font_6x8, White);
		}
		if(gfci_statu == 0){
			ssd1306_SetCursor(40, 10);
			ssd1306_WriteString("[OK]", Font_6x8, White);			
		}

	
	  //Add AC Line information
		ssd1306_SetCursor(79, 1);
		ssd1306_WriteString("AC Line:", Font_6x8, White);
		ssd1306_SetCursor(79, 10);
		ssd1306_WriteString(" [OK]", Font_6x8, White);
	
	
		//Add Relay information
		//#define RelayClosed  (1) means circuit is completed
		//#define RelayON 		 (0) means circuit is not completed
		ssd1306_SetCursor(20, 20);
		ssd1306_WriteString("Relay -->", Font_6x8, White);
		
		if(relay_statu == 1){
			ssd1306_SetCursor(60, 20);
			ssd1306_WriteString(" [Closed]", Font_6x8, White);
		}
		if(relay_statu == 0){
			ssd1306_SetCursor(60, 20);
			ssd1306_WriteString(" [ON]", Font_6x8, White);			
		}
		

	
	
		ssd1306_UpdateScreen();
}


//Font_6x8
//Font_7x10
//Font_11x18
//Font_16x26




