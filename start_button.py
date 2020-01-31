import RPi.GPIO as GPIO
import time
import os

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(25,GPIO.IN)

run = False
while True:
    #if button is pushed
    if not GPIO.input(25) and not run:
        run = True
        print('Button pressed')
        os.system('python /home/pi/Desktop/IEEE-2019/brain.py')
    elif GPIO.input(25):
        print('Button not pressed')
        run = False
    time.sleep(.2)