//ERROR:
//1 - контрольная сумма не сходится
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "main.h"
#include <math.h> 

//КАЛИБРОВКА ГИРО АКСЕЛЬ МАГНЕТ
#define kalib_gyro_0 -0,48461538;
#define kalib_gyro_1 3,45999986923;
#define kalib_gyro_2 2,561433749;

#define kalib_acc_0 0;
#define kalib_acc_1 0;
#define kalib_acc_2 0;

#define kalib_magn_0 0;
#define kalib_magn_1 0;
#define kalib_magn_2 0;

static float invSqrt(float x) {

	/*float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;*/

	return 1 / sqrt(x);
}


unsigned short Crc16(unsigned char* buf, unsigned short len) {
	unsigned short crc = 0xFFFF;
	unsigned char i;
	while (len--) {
		crc ^= *buf++ << 8;
		for (i = 0; i < 8; i++)
			crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
	}
	return crc;
}
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
   

void MadgwickAHRSupdateIMU(float* quaternion, float gx, float gy, float gz, float ax, float ay, float az, float dt, float beta)
{
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2, _8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	float sampleFreq = 1 / dt;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * (1.0f / sampleFreq);
	q1 += qDot2 * (1.0f / sampleFreq);
	q2 += qDot3 * (1.0f / sampleFreq);
	q3 += qDot4 * (1.0f / sampleFreq);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;

	quaternion[0] = q0;
	quaternion[1] = q1;
	quaternion[2] = q2;
	quaternion[3] = q3;
}

float lsm6ds3_from_fs16g_to_mg(int16_t lsb)
{
	return ((float)lsb * 488.0f / 1000.0f);
}

float lsm6ds3_from_fs2000dps_to_mdps(int16_t lsb)
{
	return ((float)lsb * 70.0f);
}

float lis3mdl_from_fs16_to_gauss(int16_t lsb)
{
	return ((float)lsb / 1711.0f);
}

int pars_p11(packet_ma_type_11_t* packet_ma_type_11_in, packet_ma_type_11_t*packet_new)
{
	if (Crc16((uint8_t*)&packet_ma_type_11_in, sizeof(packet_ma_type_11_in) - 2) != packet_ma_type_11_in->sum) return 1;
	(*packet_new).BME280_pressure = (*packet_ma_type_11_in).BME280_pressure;
	(*packet_new).BME280_temperature = (*packet_ma_type_11_in).BME280_temperature;
	(*packet_new).state = (*packet_ma_type_11_in).state;
	(*packet_new).height_bme = (*packet_ma_type_11_in).height_bme;
	(*packet_new).num = (*packet_ma_type_11_in).num;
	(*packet_new).time = (*packet_ma_type_11_in).time;

	return 0;
}

int pars_p12(packet_ma_type_12_t* packet_ma_type_12_in, new_packet_ma_type_12_t*packet_new)
{
	if (Crc16((uint8_t*)&packet_ma_type_12_in, sizeof(packet_ma_type_12_in) - 2) != packet_ma_type_12_in->sum) return 1;
	(*packet_new).altitude = (*packet_ma_type_12_in).altitude;
	(*packet_new).latitude = (*packet_ma_type_12_in).latitude;
	(*packet_new).longitude = (*packet_ma_type_12_in).longitude;
	(*packet_new).fix = (*packet_ma_type_12_in).fix;
	(*packet_new).time = (*packet_ma_type_12_in).time;
	(*packet_new).num = (*packet_ma_type_12_in).num;
	return 0;
}

int pars_2(packet_ma_type_2_t* packet_ma_type_2_in, new_packet_ma_type_2_t*new_pack)
{
	if (Crc16((uint8_t*)&packet_ma_type_2_in, sizeof(packet_ma_type_2_in) - 2) != packet_ma_type_2_in->sum) return 1;
	(*new_pack).acc_mg[0] = lsm6ds3_from_fs16g_to_mg((*packet_ma_type_2_in).acc_mg[0] /1000) + kalib_acc_0;
	(*new_pack).acc_mg[1] = lsm6ds3_from_fs16g_to_mg((*packet_ma_type_2_in).acc_mg[1] / 1000) + kalib_acc_1;
	(*new_pack).acc_mg[2] = lsm6ds3_from_fs16g_to_mg((*packet_ma_type_2_in).acc_mg[2] / 1000) + kalib_acc_2;
	(*new_pack).gyro_mdps[0] = lsm6ds3_from_fs2000dps_to_mdps((*packet_ma_type_2_in).gyro_mdps[0] / 1000) + kalib_gyro_0;
	(*new_pack).gyro_mdps[1] = lsm6ds3_from_fs2000dps_to_mdps((*packet_ma_type_2_in).gyro_mdps[1] / 1000) + kalib_gyro_1;
	(*new_pack).gyro_mdps[2] = lsm6ds3_from_fs2000dps_to_mdps((*packet_ma_type_2_in).gyro_mdps[2] / 1000) + kalib_gyro_2;
	(*new_pack).LIS3MDL_magnetometer[0] = lis3mdl_from_fs16_to_gauss((*packet_ma_type_2_in).LIS3MDL_magnetometer[0]) + kalib_magn_0;
	(*new_pack).LIS3MDL_magnetometer[1] = lis3mdl_from_fs16_to_gauss((*packet_ma_type_2_in).LIS3MDL_magnetometer[1]) + kalib_magn_1;
	(*new_pack).LIS3MDL_magnetometer[2] = lis3mdl_from_fs16_to_gauss((*packet_ma_type_2_in).LIS3MDL_magnetometer[2]) + kalib_magn_2;
	(*new_pack).lidar = (*packet_ma_type_2_in).lidar * 299792458 * 45 * pow(10, -12);//ответ в метрах. 45* = 90(пикосек)/2(путь туда-обратно)
	(*new_pack).num = (*packet_ma_type_2_in).num;
	(*new_pack).time = (*packet_ma_type_2_in).time;

}

int main()
{

    return 0;
}
