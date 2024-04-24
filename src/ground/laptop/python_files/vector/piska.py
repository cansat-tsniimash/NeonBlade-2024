import ctypes
import math 

import array as arr
if __name__ == '__main__':

	lib1 = ctypes.CDLL("qwerty/libtest.dll")
	lib1.kakashka.argtypes = [ctypes.c_float*4, ctypes.c_float*3, ctypes.c_double, ctypes.c_double, ctypes.c_int, ctypes.c_double*3, ctypes.c_double*3]
	lib1.kakashka.restype = ctypes.c_void_p



	qi = [math.sqrt(2)/2, 0, 0, math.sqrt(2)/2]
	FloatArray4 = ctypes.c_float * 4
	q = FloatArray4(*qi)

	gpsi = [123.123, 0, 0.21]
	FloatArray3 = ctypes.c_float * 3
	gps = FloatArray3(*gpsi)

	vectori = [0, 0, 1.0]
	DoubleArray3 = ctypes.c_double * 3
	vector = DoubleArray3(*vectori)

	puti = [0, 1, 2]
	put = DoubleArray3(*puti)
	
	height = 123.123
	l = 123.123
	time = 1000
	lib1.kakashka(q, gps, height, l, time, vector, put)
	print(put[0])
	print(put[1])
	print(put[2])

