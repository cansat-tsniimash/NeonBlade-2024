import ctypes

import socket
import struct

if __name__ == '__main__':

    #localIP = "192.168.0.188"
    localIP = "127.0.0.1"
    localPort = 6040
    bufferSize = 32
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    class packet_ma_type_11_t(ctypes.Structure):
        _fields_ = [('flag', ctypes.c_uint8),
                    ('num', ctypes.c_uint16),
                    ('time', ctypes.c_uint32),
                    ('BME280_pressure', ctypes.c_double),
                    ('BME280_temperature', ctypes.c_float),
                    ('height_bme', ctypes.c_double),
                    ('state', ctypes.c_uint8), 
                    ('sum', ctypes.c_uint16)]

    class packet_ma_type_12_t(ctypes.Structure):
        _fields_ = [('flag', ctypes.c_uint8),
                    ('num', ctypes.c_uint16),
                    ('time', ctypes.c_uint32),
                    ('latitude', ctypes.c_float),
                    ('longitude', ctypes.c_float),
                    ('altitude', ctypes.c_float),
                    ('fix', ctypes.c_uint8), 
                    ('sum', ctypes.c_uint16)]

    class packet_ma_type_2_t(ctypes.Structure):
        _fields_ = [('flag', ctypes.c_uint8),
                    ('num', ctypes.c_uint16),
                    ('time', ctypes.c_uint32),
                    ('acc_mg', ctypes.c_int16 * 3),
                    ('gyro_mdps', ctypes.c_int16 * 3),
                    ('LIS3MDL_magnetometer', ctypes.c_int16 * 3),
                    ('lidar', ctypes.c_uint16), 
                    ('sum', ctypes.c_uint16)]
    ##################################NEW
    class new_packet_ma_type_11_t(ctypes.Structure):
        _fields_ = [('num', ctypes.c_uint16),
                    ('time', ctypes.c_uint32),
                    ('BME280_pressure', ctypes.c_double),
                    ('BME280_temperature', ctypes.c_float),
                    ('height_bme', ctypes.c_double),
                    ('state', ctypes.c_uint8)]
                    

    class new_packet_ma_type_12_t(ctypes.Structure):
        _fields_ = [('num', ctypes.c_uint16),
                    ('time', ctypes.c_uint32),
                    ('latitude', ctypes.c_float),
                    ('longitude', ctypes.c_float),
                    ('altitude', ctypes.c_float),
                    ('fix', ctypes.c_uint8)]
                    

    class new_packet_ma_type_2_t(ctypes.Structure):
        _fields_ = [('num', ctypes.c_uint16),
                    ('time', ctypes.c_uint32),
                    ('acc_mg', ctypes.c_float * 3),
                    ('gyro_mdps', ctypes.c_float * 3),
                    ('LIS3MDL_magnetometer', ctypes.c_float * 3),
                    ('lidar', ctypes.c_double),
                    ('q', ctypes.c_float * 4)]
                    

    lib1 = ctypes.CDLL("../func_de_la_function/func_de_la_function/libtest.dll")

    lib1.MadgwickAHRSupdateIMU.argtypes = (ctypes.POINTER(ctypes.c_float), ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float,)
    lib1.MadgwickAHRSupdateIMU.restype = ctypes.c_void_p

    lib1.lsm6ds3_from_fs16g_to_mg.argtypes = [ctypes.c_int16]
    lib1.lsm6ds3_from_fs16g_to_mg.restype = ctypes.c_float

    lib1.lsm6ds3_from_fs2000dps_to_mdps.argtypes = [ctypes.c_int16]
    lib1.lsm6ds3_from_fs2000dps_to_mdps.restype = ctypes.c_float

    lib1.lis3mdl_from_fs16_to_gauss.argtypes = [ctypes.c_int16]
    lib1.lis3mdl_from_fs16_to_gauss.restype = ctypes.c_float

    lib1.pars_p11.argtypes = [ctypes.POINTER(packet_ma_type_11_t), ctypes.POINTER(new_packet_ma_type_11_t)]
    lib1.pars_p12.argtypes = [ctypes.POINTER(packet_ma_type_12_t), ctypes.POINTER(new_packet_ma_type_12_t)]
    lib1.pars_2.argtypes = [ctypes.POINTER(packet_ma_type_2_t), ctypes.POINTER(new_packet_ma_type_2_t)]

    UDPServerSocket.bind((localIP, localPort))
    UDPServerSocket.setblocking(0)
    UDPServerSocket.settimeout(1)
    print("UDP server up and listening")
    while(True):    
        # Bind to address and ip
        try:
            data = UDPServerSocket.recvfrom(bufferSize)
        except TimeoutError:
            continue
        #print(data[0])
        if data[0][0] == 0xff:
            print(1111111111111111111111111111111111111111111111111111111111111111)
            pack = struct.unpack("<BHLdfdBHBB", data[0])
            #print(data[0])
            packet_ma_type_11 = packet_ma_type_11_t(pack[0], pack[1], pack[2], pack[3], pack[4], pack[5], pack[6], pack[7])
            new_packet_ma_type_11 = new_packet_ma_type_11_t()
            lib1.pars_p11(ctypes.pointer(packet_ma_type_11), ctypes.pointer(new_packet_ma_type_11))
            print("num:", new_packet_ma_type_11.num)
            print(new_packet_ma_type_11)
            print("time:", new_packet_ma_type_11.time)
            print("bme_press:", new_packet_ma_type_11.BME280_pressure)
            print("bme_temperature:", new_packet_ma_type_11.BME280_temperature)
            print("bme_height:", new_packet_ma_type_11.height_bme)
            #print("state:", new_ma_packet_11.state)

        if data[0][0] == 0xfa:
            print(11111111111111111111111111112222222222222222222222222222222222)
            pack = struct.unpack("<BHL3fBH10B", data[0])
            packet_ma_type_12 = packet_ma_type_12_t(pack[0], pack[1], pack[2], pack[3], pack[4], pack[5], pack[6], pack[7])
            new_packet_ma_type_12 = new_packet_ma_type_12_t()
            lib1.pars_p12(ctypes.pointer(packet_ma_type_12), ctypes.pointer(new_packet_ma_type_12))
            print("num:", new_packet_ma_type_12.num)
            print("time:", new_packet_ma_type_12.time)
            print("latitude:", new_packet_ma_type_12.latitude)
            print("longitude:", new_packet_ma_type_12.longitude)
            print("altitude:", new_packet_ma_type_12.altitude)
            print("fix:", new_packet_ma_type_12.fix)


        if data[0][0] == 0xaa:
            print(2222222222222222222222222222222222222222222222222222222222222222222)
            pack = struct.unpack("<BHL9h2H3B", data[0])
            packet_ma_type_2 = packet_ma_type_2_t()
            packet_ma_type_2.flag = pack[0]
            packet_ma_type_2.num = pack[1]
            packet_ma_type_2.time = pack[2]
            packet_ma_type_2.acc_mg[0] = pack[3]
            packet_ma_type_2.acc_mg[1] = pack[4]
            packet_ma_type_2.acc_mg[2] = pack[5]
            packet_ma_type_2.gyro_mdps[0] = pack[6]
            packet_ma_type_2.gyro_mdps[1] = pack[7]
            packet_ma_type_2.gyro_mdps[2] = pack[8]
            packet_ma_type_2.LIS3MDL_magnetometer[0] = pack[9]
            packet_ma_type_2.LIS3MDL_magnetometer[1] = pack[10]
            packet_ma_type_2.LIS3MDL_magnetometer[2] = pack[11]
            packet_ma_type_2.lidar = pack[12]
            packet_ma_type_2.sum = pack[13]
            new_packet_ma_type_2 = new_packet_ma_type_2_t()
            lib1.pars_2(ctypes.pointer(packet_ma_type_2), ctypes.pointer(new_packet_ma_type_2))
            print("num:", new_packet_ma_type_2.num)
            print("time:", new_packet_ma_type_2.time)
            print("acc1:", new_packet_ma_type_2.acc_mg[0])
            print("acc2:", new_packet_ma_type_2.acc_mg[1])
            print("acc3:", new_packet_ma_type_2.acc_mg[2])
            print("gyro_mdps1:", new_packet_ma_type_2.gyro_mdps[0])
            print("gyro_mdps2:", new_packet_ma_type_2.gyro_mdps[1])
            print("gyro_mdps3:", new_packet_ma_type_2.gyro_mdps[2])
            print("LIS3MDL_magnetometer1:", new_packet_ma_type_2.LIS3MDL_magnetometer[0])
            print("LIS3MDL_magnetometer2:", new_packet_ma_type_2.LIS3MDL_magnetometer[1])
            print("LIS3MDL_magnetometer3:", new_packet_ma_type_2.LIS3MDL_magnetometer[2])
            print("lidar:", new_packet_ma_type_2.lidar)
            print("q0", new_packet_ma_type_2.q[0])
            print("q1", new_packet_ma_type_2.q[1])
            print("q2", new_packet_ma_type_2.q[2])
            print("q3", new_packet_ma_type_2.q[3])
    