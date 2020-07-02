import cv2
import numpy as np
import RPi.GPIO as GPIO
import time
import sys
MIN_MATCH_COUNT=30

algodetect=cv2.xfeatures2d.SIFT_create()

relay = 14
relay2 = 15
intDist = 0.7 #Camera Distance Sensitivity

GPIO.setmode(GPIO.BCM)
GPIO.setup(relay, GPIO.OUT)
GPIO.setup(relay2, GPIO.OUT)

FLANN_INDEX_KDITREE=0
flannParam=dict(algorithm=FLANN_INDEX_KDITREE,tree=5)
flann=cv2.FlannBasedMatcher(flannParam,{})

logo1 ="/home/pi/maggi/maggi-logo.jpg"
trainImg2 = cv2.imread(logo1)
print(trainImg2.shape)
trainImg=cv2.cvtColor(trainImg2, cv2.COLOR_BGR2GRAY)
trainKP,trainDesc=algodetect.detectAndCompute(trainImg,None)

def relay_off(pin):
    GPIO.output(pin, GPIO.HIGH)  # Turn motor on

def relay_on(pin):
    GPIO.output(pin, GPIO.LOW)  # Turn motor off


print("relay OFF")
relay_off(relay)
time.sleep(3)



def cleanAndExit():
        print ("Cleaning...")
        cam.release()
        cv2.destroyAllWindows()
        GPIO.cleanup()
        print ("Bye!")
        sys.exit()

cam=cv2.VideoCapture(0)
cam.set(3, 480) 
cam.set(4, 320) 
while True:
 try:
    ret, QueryImgBGR=cam.read()
    QueryImgBGR = cv2.flip(QueryImgBGR, -1)
    QueryImg=cv2.cvtColor(QueryImgBGR,cv2.COLOR_BGR2GRAY)
    queryKP,queryDesc=algodetect.detectAndCompute(QueryImg,None)
    matches=flann.knnMatch(queryDesc,trainDesc,k=2)

    goodMatch=[]
    for m,n in matches:
        if(m.distance<intDist*n.distance):
            goodMatch.append(m)

    if(len(goodMatch)>MIN_MATCH_COUNT):
        print("Detected")
        relay_on(relay)
        relay_on(relay2)
    else:
        relay_off(relay)
        relay_off(relay2)
        print ("Insufficient sample match detected- %d/%d"%(len(goodMatch),MIN_MATCH_COUNT))
 except(KeyboardInterrupt, SystemExit):
        cleanAndExit()
