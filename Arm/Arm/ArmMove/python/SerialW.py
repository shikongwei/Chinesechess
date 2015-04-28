#!/usr/bin/python
import serial #used to use serial port
import os     #used to call shell
import sys    #used to passing argument
import getopt
import string
import struct
#to send bype your data should format as /x01/xa0/xff
serNum=os.popen("ls /dev/ttyUSB*")
sern=serNum.read()[:-1]
os.system("echo nao |sudo -S sudo chmod 777 "+sern)#need to input password again
ser = serial.Serial(sern,9600)  #open serial
def send(para):
	senddata=para
	data = senddata.split(' ')      #change input into list
	print data
	dataB = []
	for i in range(len(data)):      #change list into hex
		z=int(data[i],10)
		zh=z>>8			#high 8 bit
		zl=z&255		#low  8 bit
		dataB.insert(2*i,zh)     
		dataB.insert(2*i+1,zl)    
	print dataB
	stri=""
	stri=stri.join(chr(i) for i in dataB)   #change into string to send
	print stri
	a=ser.write(stri) 						#send the first argument 
	print "the bype of data sended" 
	print a
def rece(num):
	recedata=ser.read(num)
	#recedataD=int(recedata,16)
	return recedata
