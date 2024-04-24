import ctypes

import socket
import struct


file = open('data.bin', "rb")

#serverAddressPort   = ("192.168.0.188", 6040)
serverAddressPort   = ("127.0.0.1", 6040)


# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

while(True):
	data = file.read(32)
	print(data)
	UDPClientSocket.sendto(data, serverAddressPort)
	if len(data) == 0:
		break