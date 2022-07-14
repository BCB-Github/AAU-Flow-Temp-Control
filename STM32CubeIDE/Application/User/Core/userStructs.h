/*
 * userStructs.h
 *
 *  Created on: Jul 8, 2022
 *      Author: barlo
 */

#ifndef APPLICATION_USER_CORE_USERSTRUCTS_H_
#define APPLICATION_USER_CORE_USERSTRUCTS_H_
#define STORED_DATA_MEAS 200

typedef struct PassDataSV {
	float flowSV;
	float tempSV;
	float volumeSV;
	int systemFlowStatusSV;
	int systemTempStatusSV;
	int systemVolLimitStatus;

}PassDataSV;

typedef struct PassDataMeas{
	float time[STORED_DATA_MEAS];
	float flowMeas[STORED_DATA_MEAS];
	float tempMeas[STORED_DATA_MEAS];
	float presMeas[STORED_DATA_MEAS];
	float motorRPMMeas[STORED_DATA_MEAS];
	float volumeMeas[STORED_DATA_MEAS];

	uint8_t newestMeasIndex;


}PassDataMeas;

typedef PassDataMeas* PassDataMeas_Handle;



#endif /* APPLICATION_USER_CORE_USERSTRUCTS_H_ */
