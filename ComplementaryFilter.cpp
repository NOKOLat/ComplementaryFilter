/*
 * ComplementaryFilter.cpp
 *
 *  Created on: May 3, 2025
 *      Author: Sezakiaoi
 */

#include <ComplementaryFilter.h>
#include <cmath>

ComplementaryFilter::ComplementaryFilter(float gain, float time) {

	this->gain = gain;
	this->time = time;
}

void ComplementaryFilter::SetData(float accel[3], float gyro[3], float time){

	//実行時間が入力された場合は更新
	if(time != 0){

		this->time = time;
	}

	//センサーデータを取り込む
	for(uint8_t i=0; i<3; i++){

		this->accel[i] = accel[i];
		this->gyro[i] = gyro[i];
	}
}

void ComplementaryFilter::Calc(){

	//現在の角度に角速度を足す（積分）
	float gyro_angle[3] = {};

	for(uint8_t i=0; i<3; i++){

		gyro_angle[i] = angle[i] + (gyro[i] + pre_gyro[i]) / 2 * time;
	}

	//加速度のノルムを計算
	float accel_norm = sqrt(accel[0] * accel[0] + accel[1] * accel[1] + accel[2] * accel[2]);

	//加速度のノルムが9.8に近い（重力加速度のみ検出している）時のみ相補フィルターの演算をする
	if((accel_norm > G - epsilon) && (accel_norm < G + epsilon)){

		float accel_angle[3] = {};

		//加速度から角度を計算
		accel_angle[0] = atan2f(accel[1], accel[2]) * 180.0 / PI;
		accel_angle[1] = atan2f(-accel[0], sqrtf(accel[1]*accel[1] + accel[2]*accel[2])) * 180.0 / PI;

		//加速度と角速度から求めた角度を合成
		angle[0] = gyro_angle[0] * gain + accel_angle[0] * (1.0 - gain);
		angle[1] = gyro_angle[1] * gain + accel_angle[1] * (1.0 - gain);
		//angle[2] = gyro_angle[2]; //yaw軸は加速度から求められないので積分値を使用
	}
	else{

		//加速度を使わない場合は、角速度の値をそのまま使う
		angle[0] = gyro_angle[0];
		angle[1] = gyro_angle[1];
		//angle[2] = gyro_angle[2];
	}

	//値を保存する
	for(uint8_t i=0; i<3; i++){

		pre_accel[i] = accel[i];
		pre_gyro[i] = gyro[i];
	}
}

void ComplementaryFilter::GetAngle(float angle[3]){

	for(uint8_t i=0; i<3; i++){

		angle[i] = this->angle[i];
	}
}
