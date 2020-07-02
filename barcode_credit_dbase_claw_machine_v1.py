import RPi.GPIO as GPIO
import os
import sys
import time
channel = 14

def cleanAndExit():
        print ("Cleaning...")
        GPIO.cleanup()
        print ("Bye!")
        sys.exit()


GPIO.setmode(GPIO.BCM)
GPIO.setup(channel, GPIO.OUT)

def relay_off(pin):
    GPIO.output(pin, GPIO.HIGH)  # Turn motor on


def relay_on(pin):
    GPIO.output(pin, GPIO.LOW)  # Turn motor off



number = ""

relay_off(channel)
while True: 
 try:


  number = input ("Enter number:")

  maggi = "4800092113246" #cre
  combi = "4800092113253" #cho
  sandwich = "4800092113260" #stra
  sandComb = "4800092113536" #combiChoco

  if ( number == maggi):
   relay_on(channel)
   time.sleep(5)
   relay_off(channel) 
   print("maggi")

  if ( number == combi):
   relay_on(channel)
   time.sleep(5)
   relay_off(channel)
   print("combi")

  if ( number == sandwich):
   relay_on(channel)
   time.sleep(5)
   relay_off(channel)
   print("sandwich")

  if (number == sandComb):
   relan_on(channel)
   time.sleep(5)
   relay_off(channel)
   print("SandComb")

  else:
   relay_off(channel)
 except (KeyboardInterrupt, SystemExit):
    cleanAndExit()


