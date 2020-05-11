#include "MCP9808.h"
#include <stdint.h>
#include <stdbool.h>


uint8_t buff8[8];
uint8_t buff16[2]; //[0] --> MSB, [1] --> LSB


/**
 *    @brief  init function
 *    @return True if initialization was successful, otherwise false.
 */
bool init() {

  if (read16(MCP9808_REG_MANUF_ID) != 0x0054)
    return false;
  if (read16(MCP9808_REG_DEVICE_ID) != 0x0400)
    return false;
  write16(MCP9808_REG_CONFIG, 0x0);
  return true;
}

/**
 *   @brief  Reads the 16-bit temperature register and returns the Centigrade
 *           temperature as a float.
 *   @return Temperature in Centigrade.
 */
float readTempC(){
  uint16_t t = read16(MCP9808_REG_AMBIENT_TEMP);

  float temp = t & 0x0FFF;
  temp /= 16.0;
  if (t & 0x1000)
    temp -= 256;

  return temp;
}

/**
 *   @brief  Set Sensor to Shutdown-State or wake up (Conf_Register BIT8)
 *   @param  sw true = shutdown / false = wakeup
 */
void shutdown_wake(bool sw){
  uint8_t conf_shutdown;
  uint16_t conf_register = read16(MCP9808_REG_CONFIG);
  if (sw == true){
    conf_shutdown = conf_register | MCP9808_REG_CONFIG_SHUTDOWN;
    write16(MCP9808_REG_CONFIG, &conf_shutdown);
  }
  if (sw == false){
    conf_shutdown = conf_register & ~MCP9808_REG_CONFIG_SHUTDOWN;
    write16(MCP9808_REG_CONFIG, &conf_shutdown);
  }
}

/**
 *   @brief  Shutdown MCP9808
 */
void shutdown(){ 
	shutdown_wake(true); 
}

/**
 *   @brief  Wake up MCP9808
 */
void wake(){
  shutdown_wake(false);
  HAL_Delay(250);
}

/**
 *   @brief  Get Resolution Value
 *   @return Resolution value
 */
uint8_t getResolution(){
  return read8(MCP9808_REG_RESOLUTION);
}

/**
 *   @brief  Set Resolution Value
 *   @param  value
 */
void setResolution(uint8_t value){
  write8(MCP9808_REG_RESOLUTION, value & 0x03); //why & 0x03
}

/*************************8-bit***************************************/
/**
 *    @brief  Low level 8 bit write procedure
 *    @param  reg
 *    @param  value
 */
void write8(uint8_t reg, uint8_t value){
	HAL_I2C_Mem_Write(&hi2c1, MCP9808_I2CADDR_DEFAULT, reg, 1, &value, 1, 10);
}

/**
 *    @brief  Low level 8 bit read procedure
 *    @param  reg
 *    @return value
 */
uint8_t read8(uint8_t reg){
		if(HAL_I2C_Mem_Read(&hi2c1, MCP9808_I2CADDR_DEFAULT, reg, 1, buff8, 1, 10) == HAL_OK){
			return *buff8;
		}
		else{
			return 0;
		}
}

/*************************16-bit***************************************/
/**
 *    @brief  Low level 16 bit write procedure
 *    @param  reg
 *    @param  data
 */
void write16(uint8_t reg, uint8_t *data){
	HAL_I2C_Mem_Write(&hi2c1, MCP9808_I2CADDR_DEFAULT, reg, 1, data, 2, 10);
}

/**
 *    @brief  Low level 16 bit read procedure
 *    @param  reg
 *    @return result
 */
uint16_t read16(uint8_t reg){	
		uint16_t result;
		if(HAL_I2C_Mem_Read(&hi2c1, MCP9808_I2CADDR_DEFAULT, reg, 1, buff16, 2, 10) == HAL_OK){
			result = (buff16[0]<<8) | buff16[1];
			return result;
		}
		else{
			return 0;
		}
}

/**
 *	@brief	Check it if the device is ready
 *	@return true
 */
bool isMCP98083Ready(){
	if(HAL_I2C_IsDeviceReady(&hi2c1, MCP9808_I2CADDR_DEFAULT, 2, 10) != HAL_OK){
		return false;
	}
	return true;
}