/*
 * ComplementaryFilter.h
 *
 *  Created on: May 3, 2025
 *      Author: Sezakiaoi
 */

#ifndef INC_COMPLEMENTARYFILTER_H_
#define INC_COMPLEMENTARYFILTER_H_

#include <cstdint>

class ComplementaryFilter {

	public:

		ComplementaryFilter(float gain, float time);

		void SetData(float accel[3], float gyro[3], float time = 0);
		void Calc();
		void GetAngle(float angle[3]);

	private:


		//Sensor Data
		float accel[3] = {};
		float gyro[3] = {};
		float pre_accel[3] = {};
		float pre_gyro[3] = {};
		float angle[3] = {};

		//Coff
		float gain = 0;
		float time = 0;

		//const
		float G = 9.806;
		float PI = 3.1415926;
		float epsilon = 0.10;
};

#endif /* INC_COMPLEMENTARYFILTER_H_ */
