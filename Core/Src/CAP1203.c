#include "CAP1203.h"
#include "CAP1203_Registers.h"
#include <stdint.h>


uint8_t Buff[8];

static volatile uint32_t _millis;

void millis_init(){
	_millis = 0;
	if(SysTick_Config(SystemCoreClock/1000)){
		while(1);
	}
}

void Systick_Handler(void){
	_millis++;
}

uint32_t millis(){
	return millis();
}

/**
 *		@brief  Read a single byte of data from the CAP1203 register "reg"
 *    @param  CAP1203_Register reg
 *    @return *Buff
 */
char readRegisterSingle(enum CAP1203_Register reg){
		if(HAL_I2C_Mem_Read(&hi2c1, CAP1203_I2C_ADDR, reg, 1, Buff, 1, 10) == HAL_OK){
			return *Buff;
		}
		else{
			return 0;
		}
}


/**
 *		@brief	Write a single byte of data to a register in CAP1203
 *		@param  reg
 *		@param  data
 */
void writeRegisterSingle(enum CAP1203_Register reg, uint8_t data){
		HAL_I2C_Mem_Write(&hi2c1, CAP1203_I2C_ADDR, reg, 1, &data, 1, 10);
}


/**
 *		@brief	Read "len" bytes from the CAP1203, starting at register "reg."
 *		@param  reg				
 *		@param  *buffer
 *		@param  len
 */
void readRegister(enum CAP1203_Register reg, char *buffer, char len){
	HAL_I2C_Mem_Read(&hi2c1, CAP1203_I2C_ADDR, reg, 8, (uint8_t*)buffer, len, 10);
}

/**
 *		@brief	Write an array of "len" bytes ("buffer"), starting at register "reg" and auto-incementing to the next
 *		@param  reg				
 *		@param  *buffer
 *		@param  len
 */
void writeRegisters(enum CAP1203_Register reg, char *buffer, char len){
	HAL_I2C_Mem_Write(&hi2c1, CAP1203_I2C_ADDR, reg, 8, (uint8_t*)buffer, len, 10);
}

void setSensitivity(uint8_t sensitivity){
    SENSITIVITY_CONTROL_REG reg;
    reg.SENSITIVITY_CONTROL_COMBINED = readRegisterSingle(SENSITIVITY_CONTROL);
    if (sensitivity == SENSITIVITY_128X){
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_128X;
    }
    else if (sensitivity == SENSITIVITY_64X){
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_64X;
    }
    else if (sensitivity == SENSITIVITY_32X){
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_32X;
    }
    else if (sensitivity == SENSITIVITY_16X){
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_16X;
    }
    else if (sensitivity == SENSITIVITY_8X){
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_8X;
    }
    else if (sensitivity == SENSITIVITY_4X){
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_4X;
    }
    else if (sensitivity == SENSITIVITY_1X){
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_1X;
    }
    else{
        // Default case: calibrated for CAP1203 touch sensor
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_2X;
    }
    writeRegisterSingle(SENSITIVITY_CONTROL, reg.SENSITIVITY_CONTROL_COMBINED);
}

void setInterruptEnabled(){
    INTERRUPT_ENABLE_REG reg;
    reg.INTERRUPT_ENABLE_COMBINED = readRegisterSingle(INTERRUPT_ENABLE);
    reg.INTERRUPT_ENABLE_FIELDS.CS1_INT_EN = 0x01;
    reg.INTERRUPT_ENABLE_FIELDS.CS2_INT_EN = 0x01;
    reg.INTERRUPT_ENABLE_FIELDS.CS3_INT_EN = 0x01;
    writeRegisterSingle(INTERRUPT_ENABLE, reg.INTERRUPT_ENABLE_COMBINED);
}

void clearInterrupt(){
    MAIN_CONTROL_REG reg;
    reg.MAIN_CONTROL_COMBINED = readRegisterSingle(MAIN_CONTROL);
    reg.MAIN_CONTROL_FIELDS.INT = 0x00;
    writeRegisterSingle(MAIN_CONTROL, reg.MAIN_CONTROL_COMBINED);
}

char begin(uint8_t deviceAddress){
	  // Read PROD_ID register
    char prodIDValue = readRegisterSingle(PROD_ID);
	
	    // PROD_ID should always be 0x6D
    if (prodIDValue != PROD_ID_VALUE){
        return false;
    }
		
		setSensitivity(SENSITIVITY_2X); // Set sensitivity to 2x on startup - value calibrated for SparkFun CAP1203 Cap Touch Slider Board
    setInterruptEnabled();          // Enable INT and LED as default
    clearInterrupt();               // Clear interrupt on startup
    return true;
}

/**
 *		@brief	Check if CS1 is touched or not
 */
bool isLeftTouched(){
	SENSOR_INPUT_STATUS_REG reg;
	reg.SENSOR_INPUT_STATUS_COMBINED = readRegisterSingle(SENSOR_INPUT_STATUS);
	
	// Touch detected
	if(reg.SENSOR_INPUT_STATUS_FIELDS.CS1 == ON){
		clearInterrupt();
		return true;
	}
	return false;
}

bool isMiddleTouched(){
	SENSOR_INPUT_STATUS_REG reg;
	reg.SENSOR_INPUT_STATUS_COMBINED = readRegisterSingle(SENSOR_INPUT_STATUS);
	
	// Touch detected
	if(reg.SENSOR_INPUT_STATUS_FIELDS.CS2 == ON){
		clearInterrupt();
		return true;
	}
	return false;
}

bool isRightTouched(){
	SENSOR_INPUT_STATUS_REG reg;
	reg.SENSOR_INPUT_STATUS_COMBINED = readRegisterSingle(SENSOR_INPUT_STATUS);
	
	// Touch detected
	if(reg.SENSOR_INPUT_STATUS_FIELDS.CS3 == ON){
		clearInterrupt();
		return true;
	}
	return false;	
}

/**
 *		@brief	Check it if the device is ready
 *		@return true
 */
bool isCAP1203Ready(){
	if(HAL_I2C_IsDeviceReady(&hi2c1, CAP1203_I2C_ADDR, 2, 10) != HAL_OK){
		return false;
	}
	return true;
}

/* IS RIGHT SWIPE
    Checks if a right swipe occurred on the board. This method
    takes up all functionality due to implementation of
    while loop with millis().
*/
bool isDownSwipePulled()
{
    bool swipe = false; // Tracks if conditions are being met
    unsigned long startTime = HAL_GetTick();

    // LEFT TOUCH CONDITION
    while ((HAL_GetTick() - startTime) < 100)
    {
        if (isLeftTouched() == true)
        {
            swipe = true;
            while (isLeftTouched() == true)
                ;  // Wait for user to remove their finger
            break; // Break out of loop
        }
    }



    // Return if middle not touched
    if (swipe == false)
    {
        return false;
    }

    startTime = HAL_GetTick(); // Reset start time
    swipe = false;        // Reset check statement

    // RIGHT TOUCH CONDITION
    while ((HAL_GetTick() - startTime) < 100)
    {
        if (isRightTouched() == true)
        {
            return true;
        }
    }

    return false;
}

/* IS LEFT SWIPE PULLED
    Checks if a left swipe occured on the board. This method
    takes up all functionality due to implementation of
    while loop with millis().
*/
bool isUpSwipePulled()
{
    bool swipe = false; // Tracks if conditions are being met
    unsigned long startTime = HAL_GetTick();

    // RIGHT TOUCH CONDITION
    while ((HAL_GetTick() - startTime) < 100)
    {
        if (isRightTouched() == true)
        {
            swipe = true;
            while (isRightTouched() == true)
                ;  // Wait for user to remove their finger
            break; // Break out of loop
        }
    }


    // Return if middle not touched
    if (swipe == false)
        return false;

    startTime = HAL_GetTick(); // Reset start time
    swipe = false;        // Reset check statement

    // LEFT TOUCH CONDITION
    while ((HAL_GetTick() - startTime) < 100)
    {
        if (isLeftTouched() == true)
        {
            return true;
        }
    }

    return false;
}


