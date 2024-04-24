#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h> 
#include "../Quaternion-master/Quaternion.h"
#include "../Quaternion-master/Quaternion.c"



void kakashka(float q[4], float gps[3], double height, double l, int time, double vector[3], double out[3])
{	
	double vec[3];//вектор, полученный после поворота
	Quaternion quat;
	quat.w = q[0];
	quat.v[0] = q[1];
	quat.v[1] = q[2];
	quat.v[2] = q[3];

	Quaternion_rotate(&quat, vector, vec);
	*out[0] = vec[0];
	out[1] = vec[1];
	out[2] = vec[2];
}

/*int main()
{
	float q[4] = { sqrt(1) / 2, 0, 0, sqrt(1) / 2 };
	float gps[4] = 0;
	double height = 10.0, l = 1230;
	int time = 1000;
	double vector[3] = { 0, 0, 1 };
	kakashka(q, gps, height, l, time, vector);
	return 0;
}*/

int main() 
{
	cout >> "hello world";
	return 0;
}