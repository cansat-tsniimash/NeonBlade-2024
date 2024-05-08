import struct
import datetime
import socket
import sys
import argparse
import time

from RF24 import RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
from RF24 import RF24_1MBPS, RF24_250KBPS, RF24_2MBPS
from RF24 import RF24_CRC_16, RF24_CRC_8, RF24_CRC_DISABLED
from RF24 import RF24 as RF24_CLASS
from RF24 import RF24_CRC_DISABLED
from RF24 import RF24_CRC_8
from RF24 import RF24_CRC_16

radio2=RF24_CLASS(22, 0)



UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.setblocking(False)
UDPServerSocket.settimeout(0)
UDPServerSocket.bind(("0.0.0.0", 6041))
addresses = []



if __name__ == '__main__':
    static_payload_size = None

    radio2.begin()
    radio2.openReadingPipe(1, b'\xac\xac\xac\xac\xac')
    radio2.setAddressWidth(5)
    radio2.channel = 110
    radio2.setDataRate(RF24_250KBPS)
    radio2.setCRCLength(RF24_CRC_8)
    radio2.setAutoAck(False)

    if static_payload_size is not None:
        radio2.disableDynamicPayloads()
        radio2.payloadSize = static_payload_size
    else:
        radio2.enableDynamicPayloads()

    radio2.startListening()
    radio2.printDetails()

    while True:

        try:
            bytesAddressPair = UDPServerSocket.recvfrom(2)
            flag = True
            for i in range(len(addresses)):
                if addresses[i][0] == bytesAddressPair[1][0]:
                    addresses[i] = bytesAddressPair[1]
                    flag = False
                    break
            if flag:
                addresses.append(bytesAddressPair[1])        
            clientIP  = "Client IP Address:{}".format(bytesAddressPair[1])
            print(clientIP)
        except BlockingIOError as e:
            pass
        except Exception as e:
            print(str(e))

        has_payload, pipe_number = radio2.available_pipe()
        if has_payload:
            payload_size = static_payload_size
            if payload_size is None:
                payload_size = radio2.getDynamicPayloadSize()
            data = radio2.read(payload_size)

            for address in addresses:
                UDPServerSocket.sendto(data, address)

            if data[0] == 0xFF:
                if len(data) == 32:
                    print("словил 11 пакет МА")
                    pack = struct.unpack("<BHLdfdBH2B", data[:32])
                    print("Pack Num:", pack[1])
                    print("Time", pack[2])
                    print("Pressure", pack[3])
                    print("Temperature", pack[4])
                    print("Heught bme", pack[5])
                    print("State", pack[6])
            if data[0] == 0xFA:
                if len(data) == 32:
                    print("словил 12 пакет МА")
                    pack = struct.unpack("<BHL3fBH10B", data[:32])
                    print("Pack Num:", pack[1])
                    print("Time", pack[2])
                    print("latitude", pack[3])
                    print("Longitude", pack[4])
                    print("Heught gps", pack[5])
                    print("Fix", pack[6])
            if data[0] == 0xAA:
                if len(data) == 32:
                    print("словил 2 пакет МА")
                    print(len(data))
                    pack = struct.unpack("<BHL9h2H3B", data[:32])
                    print("Pack Num:", pack[1])
                    print("Time", pack[2])
                    print("Axel X", pack[3])
                    print("Axel Y", pack[4])
                    print("Axel Z", pack[5])
                    print("Giro X", pack[6])
                    print("Giro Y", pack[7])
                    print("Giro Z", pack[8])
                    print("Magnet X", pack[9])
                    print("Magnet Y", pack[10])
                    print("Magnet Z", pack[11])

                    print("Lidar", pack[12])
                
