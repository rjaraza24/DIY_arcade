import RPi.GPIO as GPIO
import os
import sys
import time
channel = 14 # pouches 
channel2 = 15 # bottle
channel3 = 18 # gallon
irbot  = 17 #bot IR 
irgal  = 27 #gal IR
act_pos = 23
act_neg = 24
TimerOn = 0	 #starting position adjuster
TimeStartStop = 5 #how long to on/off the moving shaft

def cleanAndExit():
        linear_stop()
        print ("Cleaning...")
        GPIO.cleanup()
        print ("Bye!")
        sys.exit()


GPIO.setmode(GPIO.BCM)
GPIO.setup(channel, GPIO.OUT)
GPIO.setup(act_pos, GPIO.OUT)
GPIO.setup(act_neg, GPIO.OUT)
GPIO.setup(channel2, GPIO.OUT)
GPIO.setup(channel3, GPIO.OUT)


GPIO.setup(irbot, GPIO.IN)
GPIO.setup(irgal, GPIO.IN)


detectBot = False
detectGal = False
detectSmall = False
detectMed = False
detectLrg = False
acceptBot = False
acceptGal = False


def relay_off(pin):
    GPIO.output(pin, GPIO.HIGH)  # Turn motor on


def relay_on(pin):
    GPIO.output(pin, GPIO.LOW)  # Turn motor off

def linear_up():
    GPIO.output(act_pos, GPIO.LOW)
    GPIO.output(act_neg, GPIO.HIGH)

def linear_stop():
    GPIO.output(act_pos, GPIO.HIGH)
    GPIO.output(act_neg, GPIO.HIGH)
def linear_down():
    GPIO.output(act_pos, GPIO.HIGH)
    GPIO.output(act_neg, GPIO.LOW)        

number = ""
relay_off(channel)

linear_down()
time.sleep(TimerOn)
linear_stop()

frito80 = 0
frito175 = 0
frito250 = 0
bote = 0
gal = 0
while True: 
 try:


  mfrito80 = "4804880551333"
  mfrito175 = "4804880551111"
  palmfrito250 = "4804880551449"
  canola500 = "4804880553436"
  veget450 = "4804880553160"
  mfrito900 = "4804880551319"
  veget1l = "4804880555317"
  palmfrito900 = "4804880551401"
  corn1800 = "4804880552385"
  veget2l = "4804880552248"

  corn2l_bot = "4804880555225"
  veget1l_bot = "4804880553115"
  veget32l_gal = "4804880555447"

  number = input ("Enter number:")
#ChoMuch
#MilkMuch
  if (irbot):
   detectBot  = True
  if (irgal):
   detectGal  = True

################ SMALLLLL

  if ( number == mfrito80 or number ==  mfrito175 or number == palmfrito250):
   frito80 += 1
   print("Current Small Pouch:", frito80)
   relay_on(channel)
   time.sleep(5)
   relay_off(channel)

   if(frito80 >=5):
    print("5 sachet accepted...Generating 1kg of Rice")
    time.sleep(1)
    linear_up()
    time.sleep(TimeStartStop)
    linear_stop()
    time.sleep(2)
    linear_down()
    time.sleep(TimeStartStop)
    linear_stop()
    frito80 = 0 
############### MEDIUMMMMM
  if (  number == canola500 or number == veget450):
   frito175 += 1
   print("Current Medium Pouch:", frito175)
   relay_on(channel)
   time.sleep(5)
   relay_off(channel)

   if(frito175 >=2):
    print("2 sachet accepted...Generating 1kg of Rice")
    time.sleep(1)
    linear_up()
    time.sleep(TimeStartStop)
    linear_stop()
    time.sleep(2)
    linear_down()
    time.sleep(TimeStartStop)
    linear_stop()
    frito175 = 0 
################ LARGE
  if ( number == mfrito900 or number==veget1l or number==palmfrito900 or number==corn1800 or number==veget2l ):
   frito250 += 1
   relay_on(channel)
   time.sleep(5)
   relay_off(channel)
   print("Current Big Pouch:", frito250)
   if(frito250 >=1):
    frito250 = 0 
    print("5 sachet accepted...Generating 1kg of Rice")
    time.sleep(1)
    linear_up()
    time.sleep(TimeStartStop)
    linear_stop()
    time.sleep(2)
    linear_down()
    time.sleep(TimeStartStop)
    linear_stop()


######### BOTE
  if (  number ==  corn2l_bot or number == veget1l_bot ):
   bote += 1
   print("Current Bottle:", bote)
   relay_on(channel2)
   time.sleep(6)
   relay_off(channel2)

   if(bote >=2 and detectBote):
    print("2 bottles accepted...Generating 1kg of Rice")
    time.sleep(1)
    linear_up()
    time.sleep(TimeStartStop)
    linear_stop()
    time.sleep(2)
    linear_down()
    time.sleep(TimeStartStop)
    linear_stop()
    detectBote = False
    bote = 0
######## GALLON
  if (  number == veget32l_gal):
   gal += 1
   print("Current Gallon:", gal)
   relay_on(channel3)
   time.sleep(5)
   relay_off(channel3)

   if(gal >=1 and detectGal):
    print("2 sachet accepted...Generating 1kg of Rice")
    time.sleep(1)
    linear_up()
    time.sleep(TimeStartStop)
    linear_stop()
    time.sleep(2)
    linear_down()
    time.sleep(TimeStartStop)
    linear_stop()
    detectGal = False
    gal = 0




  else:
   relay_off(channel)
   linear_stop() 
 except (KeyboardInterrupt, SystemExit):
    cleanAndExit()
# finally: 
#    GPIO.cleanup()


