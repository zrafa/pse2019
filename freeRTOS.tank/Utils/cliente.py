#!/usr/bin/env python
from socket import socket, AF_INET, SOCK_STREAM
import sys
import readchar

#TCP_IP = (sys.argv[1])
TCP_IP = "192.168.4.1"
#TCP_PORT = int(sys.argv[2])
TCP_PORT = 100
BUFFER_SIZE = 1024

s = socket(AF_INET, SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
print("Ingrese los comandos")
while 1:
    comando = readchar.readchar()
    if(comando == 'q'):
        s.close()
        break  
    s.send(comando.encode())
    #data = s.recv(BUFFER_SIZE)
    #data = str(data, 'ascii')
    #print ("received data:", data)
    #print ("\n")
s.close()


