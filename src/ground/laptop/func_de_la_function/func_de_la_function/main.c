

//ERROR:
//1 - контрольная сумма не сходится
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include <math.h>
#include "Quaternion-master/Quaternion.h"
#include "Quaternion-master/Quaternion.c"

//#include "sofa\sofam.h"

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

float Kalib_acc_A[3][3] = { 1.052050,	-0.042355,	-0.023001,
							-0.042355,	1.046937,	0.027873,
							-0.023001,	0.027873,	1.005446 };
float Kalib_acc_B[3] = { 0.207685, -0.010756, 0.034427 };


float Kalib_gyro_B[3] = {0.42, -3.5, -3.08};


float Kalib_magn_A[3][3] = { 2.394741,	-0.312813,	0.162253,
							-0.312813,	2.531681,	0.454779,
							0.162253,	0.454779,	2.271241 };
float Kalib_magn_B[3] = { -0.047637, -0.371532, 0.684505 };





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

coordinate_t coordinate[10] = { 0 };
float time_p12_pr = 0;
float time_p11_pr = 0;
float time_p2_pr = 0;
int incriment = 0;
float x_lat_pr = 0;
float y_lon_pr = 0;
float z_bme_pr = 0;
double L0[3] = { 0.866, 0, -0.5 };

int GetCoordinates(new_packet_ma_type_11_t*packet11_new, new_packet_ma_type_12_t*packet12_new, new_packet_ma_type_2_t*packet2_new, pointArray_t*pointArray, int point_len) {
	if ((packet12_new->time > time_p12_pr) && (packet11_new->time > time_p11_pr)) {
		for (int i = 0; i < incriment; i++) {
			coordinate[i].x_lat = x_lat_pr + (coordinate[i].time - time_p12_pr) * (packet12_new->latitude - x_lat_pr) / (packet12_new->time - time_p12_pr);
			coordinate[i].y_lon = y_lon_pr + (coordinate[i].time - time_p12_pr) * (packet12_new->longitude - y_lon_pr) / (packet12_new->time - time_p12_pr);
			coordinate[i].z_bme = z_bme_pr + (coordinate[i].time - time_p11_pr) * (packet11_new->height_bme - z_bme_pr) / (packet11_new->time - time_p11_pr);
			
			double L[3] = { coordinate[i].lidar * L0[0], coordinate[i].lidar * L0[1], coordinate[i].lidar * L0[2] };

			Quaternion quat;
			quat.w = packet2_new->q[0];
			quat.v[0] = packet2_new->q[1];
			quat.v[1] = packet2_new->q[2];
			quat.v[2] = packet2_new->q[3];
			double vec[3] = { 0 };

			Quaternion_rotate(&quat, L, vec);
			pointArray->pointArray[i].x = vec[0] + coordinate[i].x_lat;
			pointArray->pointArray[i].y = vec[1] + coordinate[i].y_lon;
			pointArray->pointArray[i].z = vec[2] + coordinate[i].z_bme;
			printf("New_Packet_number %d:\t", i);
			printf("%f\t%f\t%f\t%f\n", pointArray->pointArray[i].time, pointArray->pointArray[i].x, pointArray->pointArray[i].y, pointArray->pointArray[i].z);


			printf("Old_Packet_number %d:\t", i);
			printf("%f\t%f\t%f\t%f\n", coordinate[i].time, coordinate[i].x_lat, coordinate[i].y_lon, coordinate[i].z_bme);
		}
		int n = incriment;
		printf("%d\n", n);
		incriment = 0;
		time_p12_pr = packet12_new->time;
		time_p11_pr = packet11_new->time;
		x_lat_pr = packet12_new->latitude;
		y_lon_pr = packet12_new->longitude;
		z_bme_pr = packet11_new->height_bme;

		/*printf(" GPS BME:\n");
		for (int i = 0; i < incriment; i++) {
		printf("%f\t%f\t%f\t%f\n", coordinate[i].time, coordinate[i].x_lat, coordinate[i].y_lon, coordinate[i].z_bme);
		}*/

		return n;
	}

	if (packet2_new->time > time_p2_pr) {
	
		time_p2_pr = packet2_new->time;
		coordinate[incriment].time = packet2_new->time;
		coordinate[incriment].lidar = packet2_new->lidar;
		coordinate[incriment].q[0] = packet2_new->q[0];
		coordinate[incriment].q[1] = packet2_new->q[1];
		coordinate[incriment].q[2] = packet2_new->q[2];
		coordinate[incriment].q[3] = packet2_new->q[3];
		printf("Quaternion: \t");
		printf("%f\t%f\t%f\t%f\n", coordinate[incriment].q[0], coordinate[incriment].q[1], coordinate[incriment].q[2], coordinate[incriment].q[3]);
		if (incriment < point_len) incriment++;
		else incriment = 0;
	}
	

	return 0;
}

	
	









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











void MadgwickAHRSupdate(float* quaternion, float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float dt, float beta) {
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float hx, hy;

#	pragma GCC diagnostic push
	// warning: variable '_2q2q3' set but not used [-Wunused-but-set-variable]
	// warning: variable '_2q0q2' set but not used [-Wunused-but-set-variable]
	// Мы доверяем этому коду
#	pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	float _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz, _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
#	pragma GCC diagnostic pop

	// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
	if ((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) {
		MadgwickAHRSupdateIMU(quaternion, gx, gy, gz, ax, ay, az, dt, beta);
		return;
	}

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

		// Normalise magnetometer measurement
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0mx = 2.0f * q0 * mx;
		_2q0my = 2.0f * q0 * my;
		_2q0mz = 2.0f * q0 * mz;
		_2q1mx = 2.0f * q1 * mx;
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_2q0q2 = 2.0f * q0 * q2;
		_2q2q3 = 2.0f * q2 * q3;
		q0q0 = q0 * q0;
		q0q1 = q0 * q1;
		q0q2 = q0 * q2;
		q0q3 = q0 * q3;
		q1q1 = q1 * q1;
		q1q2 = q1 * q2;
		q1q3 = q1 * q3;
		q2q2 = q2 * q2;
		q2q3 = q2 * q3;
		q3q3 = q3 * q3;

		// Reference direction of Earth's magnetic field
		hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1 + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
		hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2 - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
		_2bx = sqrt(hx * hx + hy * hy);
		_2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3 - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
		_4bx = 2.0f * _2bx;
		_4bz = 2.0f * _2bz;
		float _8bx = 2.0f * _4bx;
		float _8bz = 2.0f * _4bz;

		// Gradient decent algorithm corrective step
		s0 = -_2q2 * (2 * (q1q3 - q0q2) - ax) + _2q1 * (2 * (q0q1 + q2q3) - ay) + -_4bz * q2*(_4bx*(0.5 - q2q2 - q3q3) + _4bz * (q1q3 - q0q2) - mx) + (-_4bx * q3 + _4bz * q1)*(_4bx*(q1q2 - q0q3) + _4bz * (q0q1 + q2q3) - my) + _4bx * q2*(_4bx*(q0q2 + q1q3) + _4bz * (0.5 - q1q1 - q2q2) - mz);
		s1 = _2q3 * (2 * (q1q3 - q0q2) - ax) + _2q0 * (2 * (q0q1 + q2q3) - ay) + -4 * q1*(2 * (0.5 - q1q1 - q2q2) - az) + _4bz * q3*(_4bx*(0.5 - q2q2 - q3q3) + _4bz * (q1q3 - q0q2) - mx) + (_4bx*q2 + _4bz * q0)*(_4bx*(q1q2 - q0q3) + _4bz * (q0q1 + q2q3) - my) + (_4bx*q3 - _8bz * q1)*(_4bx*(q0q2 + q1q3) + _4bz * (0.5 - q1q1 - q2q2) - mz);
		s2 = -_2q0 * (2 * (q1q3 - q0q2) - ax) + _2q3 * (2 * (q0q1 + q2q3) - ay) + (-4 * q2)*(2 * (0.5 - q1q1 - q2q2) - az) + (-_8bx * q2 - _4bz * q0)*(_4bx*(0.5 - q2q2 - q3q3) + _4bz * (q1q3 - q0q2) - mx) + (_4bx*q1 + _4bz * q3)*(_4bx*(q1q2 - q0q3) + _4bz * (q0q1 + q2q3) - my) + (_4bx*q0 - _8bz * q2)*(_4bx*(q0q2 + q1q3) + _4bz * (0.5 - q1q1 - q2q2) - mz);
		s3 = _2q1 * (2 * (q1q3 - q0q2) - ax) + _2q2 * (2 * (q0q1 + q2q3) - ay) + (-_8bx * q3 + _4bz * q1)*(_4bx*(0.5 - q2q2 - q3q3) + _4bz * (q1q3 - q0q2) - mx) + (-_4bx * q0 + _4bz * q2)*(_4bx*(q1q2 - q0q3) + _4bz * (q0q1 + q2q3) - my) + (_4bx*q1)*(_4bx*(q0q2 + q1q3) + _4bz * (0.5 - q1q1 - q2q2) - mz);
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




   



float lsm6ds3_from_fs16g_to_mpss(int16_t lsb)
{
	return ((float)lsb * 0.488f / 1000.0f * 9.81);
}

float lsm6ds3_from_fs2000dps_to_degps(int16_t lsb)
{
	return ((float)lsb * 70.0f / 1000.0f);
}

float lis3mdl_from_fs16_to_gauss(int16_t lsb)
{
	return ((float)lsb / 1711.0f);
}

int pars_p11(packet_ma_type_11_t* packet_ma_type_11_in, new_packet_ma_type_11_t*packet_new)
{
	//if (Crc16((uint8_t*)&packet_ma_type_11_in, sizeof(packet_ma_type_11_in) - 2) != packet_ma_type_11_in->sum) return 1;
	(*packet_new).BME280_pressure = (*packet_ma_type_11_in).BME280_pressure;
	(*packet_new).BME280_temperature = (*packet_ma_type_11_in).BME280_temperature;
	(*packet_new).state = (*packet_ma_type_11_in).state;
	(*packet_new).height_bme = (*packet_ma_type_11_in).height_bme;
	(*packet_new).num = (*packet_ma_type_11_in).num;
	(*packet_new).time = (*packet_ma_type_11_in).time / 1000.0f;

	return 0;
}


float start_lat = 0;
float start_lon = 0;

int pars_p12(packet_ma_type_12_t*packet_ma_type_12_in, new_packet_ma_type_12_t*packet_new)
{
	//if (Crc16((uint8_t*)&packet_ma_type_12_in, sizeof(packet_ma_type_12_in) - 2) != packet_ma_type_12_in->sum) return 1;
	(*packet_new).fix = (*packet_ma_type_12_in).fix;
	(*packet_new).time = (*packet_ma_type_12_in).time / 1000.0f;
	(*packet_new).num = (*packet_ma_type_12_in).num;
	(*packet_new).volts = (*packet_ma_type_12_in).volts;
	(*packet_new).lux = (*packet_ma_type_12_in).lux;
	//printf("volts and lux:");
	//printf("\t%f\t%f\n", (*packet_new).volts, (*packet_new).lux);
	//printf("\t%f\t%f\n", (*packet_ma_type_12_in).volts, (*packet_ma_type_12_in).lux);

	if ((*packet_ma_type_12_in).fix) {
		if (!start_lat) {

			start_lat = (*packet_ma_type_12_in).latitude / 57.2958;
			start_lon = (*packet_ma_type_12_in).longitude / 57.2958;
		}
		(*packet_new).altitude = (*packet_ma_type_12_in).altitude;
		(*packet_new).latitude = (*packet_ma_type_12_in).latitude / 57.2958;
		(*packet_new).longitude = (*packet_ma_type_12_in).longitude / 57.2958;
		
		double rx = ((*packet_new).latitude - start_lat) * 6371100;
		double ry = ((*packet_new).longitude - start_lon) * 6371100 * cos((*packet_new).latitude);
		//(*packet_new).latitude = (*packet_new).latitude * 500;
		//(*packet_new).longitude = (*packet_new).longitude * 500;
		(*packet_new).latitude = rx; // В метрах
		(*packet_new).longitude = ry; // В метрах


		
		

		return 0;
	}
	
}


static float prev_time = 0;


int pars_2(packet_ma_type_2_t* packet_ma_type_2_in, new_packet_ma_type_2_t*new_pack, float time_pr)
{
	//if (Crc16((uint8_t*)&packet_ma_type_2_in, sizeof(packet_ma_type_2_in) - 2) != packet_ma_type_2_in->sum) return 1;
	float quat[4];
	(*new_pack).acc_mg[0] = lsm6ds3_from_fs16g_to_mpss((*packet_ma_type_2_in).acc_mg[0] );
	(*new_pack).acc_mg[1] = lsm6ds3_from_fs16g_to_mpss((*packet_ma_type_2_in).acc_mg[1] );
	(*new_pack).acc_mg[2] = lsm6ds3_from_fs16g_to_mpss((*packet_ma_type_2_in).acc_mg[2] );
	
	//float acc_amb[3];
	//iauPmp((*new_pack).acc_mg, Kalib_acc_B, acc_amb);
	//iauRxp(Kalib_acc_A, acc_amb, (*new_pack).acc_mg);

	/*
	printf(
		"%6d %6d %6d\n",
		(int)packet_ma_type_2_in->LIS3MDL_magnetometer[0],
		(int)packet_ma_type_2_in->LIS3MDL_magnetometer[1],
		(int)packet_ma_type_2_in->LIS3MDL_magnetometer[2]
	); */

	new_pack->gyro_mdps[0] = lsm6ds3_from_fs2000dps_to_degps((*packet_ma_type_2_in).gyro_mdps[0]);// -Kalib_gyro_B[0];
	new_pack->gyro_mdps[1] = lsm6ds3_from_fs2000dps_to_degps((*packet_ma_type_2_in).gyro_mdps[1]);// -Kalib_gyro_B[1];
	new_pack->gyro_mdps[2] = lsm6ds3_from_fs2000dps_to_degps((*packet_ma_type_2_in).gyro_mdps[2]);// -Kalib_gyro_B[2];

	new_pack->LIS3MDL_magnetometer[0] = lis3mdl_from_fs16_to_gauss((*packet_ma_type_2_in).LIS3MDL_magnetometer[0]);
	new_pack->LIS3MDL_magnetometer[1] = lis3mdl_from_fs16_to_gauss((*packet_ma_type_2_in).LIS3MDL_magnetometer[1]);
	new_pack->LIS3MDL_magnetometer[2] = lis3mdl_from_fs16_to_gauss((*packet_ma_type_2_in).LIS3MDL_magnetometer[2]);
	new_pack->lidar = (*packet_ma_type_2_in).lidar * 299792458 * 45 * pow(10, -12);//ответ в метрах. 45* = 90(пикосек)/2(путь туда-обратно)
	new_pack->num = (*packet_ma_type_2_in).num;
	new_pack->time = packet_ma_type_2_in->time / 1000.0f;
	const float dt = new_pack->time - prev_time;
	//MadgwickAHRSupdate(
	MadgwickAHRSupdateIMU(
		quat,
		(*new_pack).gyro_mdps[0] / 180.0f*M_PI,
		(*new_pack).gyro_mdps[1] / 180.0f*M_PI,
		(*new_pack).gyro_mdps[2] / 180.0f*M_PI,
		(*new_pack).acc_mg[0],
		(*new_pack).acc_mg[1],
		(*new_pack).acc_mg[2],
		//(*new_pack).LIS3MDL_magnetometer[0], 
		//(*new_pack).LIS3MDL_magnetometer[1], 
		//(*new_pack).LIS3MDL_magnetometer[2], 
		dt, //(*new_pack).time - time_pr,
		0.3
	);
	prev_time = new_pack->time;
	new_pack->q[0] = quat[0];
	new_pack->q[1] = quat[1];
	new_pack->q[2] = quat[2];
	new_pack->q[3] = quat[3];
	
	/*
	printf(
		"%+14f %+14f %+14f ... %+14f %+14f %+14f ... %+14f %+14f %+14f ... %+14f\n",
		(*new_pack).gyro_mdps[0],
		(*new_pack).gyro_mdps[1],
		(*new_pack).gyro_mdps[2],
		(*new_pack).acc_mg[0],
		(*new_pack).acc_mg[1],
		(*new_pack).acc_mg[2],
		(*new_pack).LIS3MDL_magnetometer[0],
		(*new_pack).LIS3MDL_magnetometer[1],
		(*new_pack).LIS3MDL_magnetometer[2],
		dt
	);
	*/

	return 0;
}

//L = (0, 8660254; 0; -0.5)
void GetPoint(float quat[4]) {


}




int main()
{

    return 0;
}
