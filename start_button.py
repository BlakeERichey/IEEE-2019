import RPi.GPIO as GPIO
import time
import os

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(25,GPIO.IN)

while True:
    #if button is pushed
    if GPIO.input(25):
        os.system('python /home/pi/desktop/IEEE-2019/brain.py')