// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h> 
#include "../../../Quaternion-master/Quaternion.h"
#include "../../../Quaternion-master/Quaternion.c"

using namespace std;
/*
gps[0] - lat
gps[1] - lon
gps[2] - height
*/
void kakashka(float q[4], float gps[3], float gps_start[3], double height, double l, int time, double vector[3], double out[3])
{
	double vec[3];//вектор, полученный после поворота
	Quaternion quat;
	quat.w = q[0];
	quat.v[0] = q[1];
	quat.v[1] = q[2];
	quat.v[2] = q[3];

	Quaternion_rotate(&quat, vector, vec);
	gps[0] = gps[0] / 57.2958;
	gps[1] = gps[1] / 57.2958;
	gps[2] = gps[2] / 57.2958;
	gps_start[0] = gps_start[0] / 57.2958;
	gps_start[1] = gps_start[1] / 57.2958;
	gps_start[2] = gps_start[2] / 57.2958;
	double rx = (gps[0] - gps_start[0]) * 6371100;
	double ry = (gps[1] - gps_start[1]) * 6371100 * cos(gps[0]);
	double rz = height;
	vec[0] = vec[0] * l;
	vec[1] = vec[1] * l;
	vec[2] = vec[2] * l;
	vec[0] += rx;
	vec[1] += ry;
	vec[2] += rz;
	out[0] = vec[0];
	out[1] = vec[1];
	out[2] = vec[2];
}

int main()
{
	float q[4] = { sqrt(3) / 2, 0, 0.5, 0 };
	float gps[3] = { 55.91781256008479, 37.77228484174793, 0 };
	float gps_start[3] = { 55.91788020961239, 37.77433244850823, 0 };
	double height = 100, l = 500;
	int time = 1000;
	double vector[3] = { sqrt(3) / 2, 0, -0.5 };
	double outt[3];
	kakashka(q, gps, gps_start, height, l, time, vector, outt);
	cout << 1LL * outt[0] << " " << 1LL * outt[1] << " " << 1LL * outt[2] << endl;
	cout << sqrt(pow(outt[0], 2) + pow(outt[1], 2));
	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
