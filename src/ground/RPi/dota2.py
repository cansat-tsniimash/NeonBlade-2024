import sys
import argparse
import time
import struct
import datetime
import socket

from RF24 import RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
from RF24 import RF24_1MBPS, RF24_250KBPS, RF24_2MBPS
from RF24 import RF24_CRC_16, RF24_CRC_8, RF24_CRC_DISABLED
from RF24 import RF24 as RF24_CLASS
from RF24 import RF24_CRC_DISABLED
from RF24 import RF24_CRC_8
from RF24 import RF24_CRC_16

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.setblocking(False)
UDPServerSocket.settimeout(0)
UDPServerSocket.bind(("0.0.0.0", 20002))
addresses = []


radio2=RF24_CLASS(24, 1)


def generate_logfile_name():
    now = datetime.datetime.utcnow().replace(microsecond=0)
    isostring = now.isoformat()  # string 2021-04-27T23:17:31
    isostring = isostring.replace("-", "")  # string 20210427T23:17:31
    isostring = isostring.replace(":", "")  # string 20210427T231731, òî ÷òî íàäî
    return "./log/neonblade_Mandarinas" + isostring + ".bin"


if __name__ == '__main__':
    static_payload_size = None

    radio2.begin()
    radio2.openReadingPipe(1, b'\xac\xac\xac\xac\xac')
    radio2.setAddressWidth(5)
    radio2.channel = 100
    radio2.setDataRate(RF24_250KBPS)
    radio2.setCRCLength(RF24_CRC_8)
    radio2.setAutoAck(True)

    if static_payload_size is not None:
        radio2.disableDynamicPayloads()
        radio2.payloadSize = static_payload_size
    else:
        radio2.enableDynamicPayloads()

    radio2.startListening()
    radio2.printDetails()

    while True:
        has_payload, pipe_number = radio2.available_pipe()
        #print(f'has_payload-{has_payload}, pipe_number={pipe_number}')

        if has_payload:
            payload_size = static_payload_size
            if payload_size is None:
                payload_size = radio2.getDynamicPayloadSize()

            data = radio2.read(payload_size)
            print('got data %s' % data)

            if data[0] == 255:
                print("словил 11 пакет МА")
                pack = struct.unpack("<BHL3dB", data)
                print("Pack Num:", pack[1])
                print("Time", pack[2])
                print("Pressure", pack[3])
                print("Temperature", pack[4])
                print("Heught bme", pack[5])
                print("State", pack[6])
                


            if data[0] == 25:
                print("словил 11 пакет МА")
                pack = struct.unpack("<BHL3fB", data)
                print("Pack Num:", pack[1])
                print("Time", pack[2])
                print("latitude", pack[3])
                print("Longitude", pack[4])
                print("Heught gps", pack[5])
                print("Fix", pack[6])


            if data[0] == 10:
                print("словил 2 пакет МА")
                pack = struct.unpack("<BHL9h2H", data)
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
                


