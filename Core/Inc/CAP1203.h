#ifndef __CAP1203_H__
#define __CAP1203_H__


/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "CAP1203_Registers.h"

extern I2C_HandleTypeDef hi2c1;
/* Variables ------------------------------------------------------------------*/


// Declare I2C Address
#define CAP1203_I2C_ADDR 0x50		//CAP1203 base address 0x28<<1


// ID Registers (Register addresses)
#define Product_ID          0xFD
#define Manufacturer_ID			0xFE
#define Revision						0xFF


// Product ID - always the same (pg. 22)
#define PROD_ID_VALUE 0x6D

// Capacitive sensor input (pg. 23)
#define OFF 0x00 // No touch detecetd
#define ON  0x01  // Check capacitive sensor input (pg. 23)

// Pads to be power buttion (pg. 43)
#define PWR_CS1 0x00 // Pad 1 (Left)
#define PWR_CS2 0x01 // Pad 2 (Middle)
#define PWR_CS3 0x02 // Pad 3 (Right)

#define PAD_LEFT 		PWR_CS1
#define PAD_MIDDLE  PWR_CS2
#define PAD_RIGHT 	PWR_CS3

// Power button hold time to generate interrupt (pg. 44)
#define PWR_TIME_280_MS  0x00  // 280 ms
#define PWR_TIME_560_MS  0x01  // 560 ms
#define PWR_TIME_1120_MS 0x02 // 1.12 sec
#define PWR_TIME_2240_MS 0x03 // 2.24 sec

// Sensitivity for touch detection (pg. 25)
#define SENSITIVITY_128X 0x00 // Most sensitive
#define SENSITIVITY_64X  0x01
#define SENSITIVITY_32X  0x02
#define SENSITIVITY_16X  0x03
#define SENSITIVITY_8X   0x04
#define SENSITIVITY_4X   0x05
#define SENSITIVITY_2X   0x06
#define SENSITIVITY_1X    0x07 // Least sensitive



/* Private define ------------------------------------------------------------*/
/* Function Decleration ------------------------------------------------------------------*/
char readRegisterSingle(enum CAP1203_Register reg); //okay
void writeRegisterSingle(enum CAP1203_Register reg, uint8_t data); //okay

void readRegister(enum CAP1203_Register reg, char *buffer, char len);
void writeRegisters(enum CAP1203_Register reg, char *buffer, char len);

void clearInterrupt();

bool isLeftTouched();				//okay
bool isMiddleTouched();
bool isRightTouched();				//okay

bool isDownSwipePulled();
bool isUpSwipePulled();

void setSensitivity(uint8_t sensitivity);
void setInterruptEnabled();
void clearInterrupt();
char begin(uint8_t deviceAddress);

bool checkDevices();

bool isCAP1203Ready();

void millis_init();
void Systick_Handler(void);
uint32_t millis();





/* Typedef ------------------------------------------------------------------*/

// Sensitivity Control Reg (pg. 25)
typedef union{
	struct
	{
		uint8_t BASE_SHIFT  : 4;
    uint8_t DELTA_SENSE : 3;
    uint8_t EMPTY_1     : 1;
	}SENSITIVITY_CONTROL_FIELDS;
	uint8_t SENSITIVITY_CONTROL_COMBINED;
}SENSITIVITY_CONTROL_REG;

// General Status Reg (pg. 23)
typedef union{
	struct
	{
		uint8_t TOUCH     : 1;
		uint8_t MTP       : 1;
		uint8_t MULT      : 1;
		uint8_t EMPTY_1   : 1;
		uint8_t PWR1       : 1;
		uint8_t ACAL_FAIL : 1;
	}GENERAL_STATUS_FIELDS;
	uint8_t GENERAL_STATUS_COMBINED;
}	GENERAL_STATUS_REG;


// Sensor Input Status Reg (pg. 23)
typedef union {
  struct
  {
    uint8_t CS1 : 1;
    uint8_t CS2 : 1;
    uint8_t CS3 : 1;
    uint8_t EMPTY_1 : 5;
  } SENSOR_INPUT_STATUS_FIELDS;
  uint8_t SENSOR_INPUT_STATUS_COMBINED;
} SENSOR_INPUT_STATUS_REG;

// Main Control Register (pg. 22)
typedef union {
  struct
  {
    uint8_t INT : 1;
    uint8_t EMPTY_1 : 3;
    uint8_t DSLEEP : 1;
    uint8_t STBY : 1;
    uint8_t EMPTY_2 : 2;
  } MAIN_CONTROL_FIELDS;
  uint8_t MAIN_CONTROL_COMBINED;
} MAIN_CONTROL_REG;


// Power Button Register (pg. 43)
typedef union {
  struct
  {
    uint8_t PWR_BTN : 3;
    uint8_t EMPTY_1 : 5;
  } POWER_BUTTON_FIELDS;
  uint8_t POWER_BUTTON_COMBINED;
} POWER_BUTTON_REG;

// Power Button Configuration Register (pg. 43)
typedef union {
  struct
  {
    uint8_t PWR_TIME : 2;
    uint8_t PWR_EN : 1;
    uint8_t EMPTY_1 : 1;
    uint8_t STBY_PWR_TIME : 2;
    uint8_t STBY_PWR_EN : 1;
    uint8_t EMPTY_2 : 1;
  } POWER_BUTTON_CONFIG_FIELDS;
  uint8_t POWER_BUTTON_CONFIG_COMBINED;
} POWER_BUTTON_CONFIG_REG;

// Interrupt Enable Register (pg. 33)
typedef union {
  struct
  {
    uint8_t CS1_INT_EN : 1;
    uint8_t CS2_INT_EN : 1;
    uint8_t CS3_INT_EN : 1;
    uint8_t EMPTY_1 : 5;
  } INTERRUPT_ENABLE_FIELDS;
  uint8_t INTERRUPT_ENABLE_COMBINED;
} INTERRUPT_ENABLE_REG;












#endif /* __CAP1203_H__ */