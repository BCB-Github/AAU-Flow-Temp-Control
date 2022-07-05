/*
 * i2cUserFunctions.c
 *
 *  Created on: Jul 1, 2022
 *      Author: barlo
 *      Here we define the functions that we will use to read from the i2c protocall
 */
#include "i2cUserFunctionsHeader.h"
#include <stdint.h> /* stdint.h is used to allow for uint8_t variable type */
#include "main.h"


/*Define Variables used by I2C for SF06 Sensor
 * These are defined by the Arduino Test Example given by Sensiron
 * https://developer.sensirion.com/archive/tutorials/arduino-interface-for-sf06-liquid-flow-sensors-with-level-shifter/
 * */
static const uint8_t SLF3X_I2C_ADDRESS = 0x08;
/*
static const float   SLF3X_SCALE_FACTOR_FLOW = 500.0;
static const float   SLF3X_SCALE_FACTOR_TEMP = 200.0;
*/

static const uint8_t  CMD_START_MEASUREMENT_LENGTH = 2;
static const uint8_t  DATA_LENGTH = 9;

static const uint8_t  SOFT_RESET_I2C_ADDRESS = 0x0;
/*

static const uint8_t  INITIAL_MEASURE_DELAY = 120; // LD20: 120ms; SLF3X: 50ms
*/
//static const uint8_t SLF3X_I2C_ADDRESS = 0x08;
static const uint8_t  CMD_SOFT_RESET =  0x06 ;

extern I2C_HandleTypeDef hi2c1;
float flow, temp;




void I2CSoftReset(void){
	// We want to reset
		  //i2c_write(SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET, CMD_SOFT_RESET_LENGTH);
		  uint8_t pData[2] = {SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET};
		  //pData = {SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET};
		  HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)(SLF3X_I2C_ADDRESS<<1) , &pData, (uint16_t) 2, 1000);
		  int count = 0;
}

void I2CStartMeasurement(void) {
	  uint8_t  CMD_START_MEASUREMENT[2] = { 0x36, 0x08 };
	  HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)(SLF3X_I2C_ADDRESS<<1), &CMD_START_MEASUREMENT, CMD_START_MEASUREMENT_LENGTH, 1000);
	  //uint8_t  CMD_START_MEASUREMENT = { 0x36, 0x08 };
	  int count1 = 0;

}





void I2CInitialize(){
// We want to reset
	I2CSoftReset();
	osDelay(100);
	I2CStartMeasurement();
	osDelay(100);
	I2CRead();



	//  uint8_t count = 0;
	  //i2c_write(SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET, CMD_SOFT_RESET_LENGTH);
	 // uint8_t pData[2] = {SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET};

	  //pData = {SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET};
	 // HAL_I2C_Master_Transmit(&hi2c3, (SLF3X_I2C_ADDRESS<<1) , pData, sizeof(pData), 50);
	 // osDelay(1000);

	   // delay(CHIP_RESET_RETRY_DELAY);
}
void I2CRead(){
	    //i2c_read(uint8_t addr, uint8_t* data, uint16_t count)
		// We want to reset
		//I2CSoftReset();
		/*  uint8_t count = 0;
		  //i2c_write(SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET, CMD_SOFT_RESET_LENGTH);
		  uint8_t pData[2] = {SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET};

		  //pData = {SOFT_RESET_I2C_ADDRESS, CMD_SOFT_RESET};
		  HAL_I2C_Master_Transmit(&hi2c3, (SLF3X_I2C_ADDRESS<<1) , pData, sizeof(pData), 50);
		  osDelay(1000);
		  */
		//I2CStartMeasurement();
		//osDelay(100);
		uint8_t readData[DATA_LENGTH];


		  HAL_I2C_Master_Receive(&hi2c1, (uint16_t)	((SLF3X_I2C_ADDRESS<<1) | 0x1), readData, DATA_LENGTH, 1000);
		  flow = (uint16_t)((readData[0] << 8) | readData[1]);
		  flow = flow/10;

		  temp = (uint16_t)((readData[3] << 8) | readData[4]);
		  temp = temp/200;

		//  osDelay(100);



		  // DEFINE THE START MEASUREMENT DATA



	/*
		  int8_t SensirionLF::readSample()
		  {
		    uint8_t data[DATA_LENGTH] = { 0 };

		    if (i2c_read(, data, DATA_LENGTH) != 0) {
		      return 1;
		    }
		    if (validate_crc(data, 3) != 0) {
		      return 2;
		    }
		    mFlow = convert_and_scale(data[0], data[1], mFlowScaleFactor);
		    mTemp = convert_and_scale(data[3], data[4], mTempScaleFactor);
		    mAirInLineDetected = data[7]       & 1U;
		    mHighFlowDetected = (data[7] >> 1) & 1U;
		    return 0;
		  }
*/





	/* Function Prototypes
	HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size, Timeout);
	HAL_I2C_Master_Receive(hi2c, DevAddress, pData, Size, Timeout);
	HAL_I2C_Mem_Read(hi2c, DevAddress, pData, Size, Timeout);
	HAL_I2C_Mem_Write(hi2c, DevAddress, pData, Size, Timeout);
	*/
	//HAL_I2C_Master_Transmit(hi2c, (mI2cAddress<<1) , pData, sizeof(pData), 50);
//	HAL_I2C_Master_Receive(hi2c, (mI2cAddress<<1) | 0x1, pData, sizeof(pData, Timeout);




	/*Arduino Protoypes
	 * i2c_read(mI2cAddress, data, DATA_LENGTH) != 0);
	 *
  	  *int8_t  i2c_read(uint8_t addr, uint8_t* data, uint16_t count);
	 *
	 *i2c_write(mI2cAddress, CMD_START_MEASUREMENT, CMD_START_MEASUREMENT_LENGTH)
	 *  int8_t  i2c_write(uint8_t addr, const uint8_t* data, uint16_t count);
	 *Note - these functions either return a 1 or a 0 to signify if the function worked or not
	 *
	 **/

}
