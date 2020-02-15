#Library for performing robot pathing
from utils import *
from detect import detector

def find_obj(core):
  '''
    Rotates right until an object is detected by obj detector
  '''
  obj_detected = False
  while not obj_detected: 
    send_act(core, 'TURN_RIGHT')
    time.sleep(.4)
    send_act(core, 'STOP')
    time.sleep(.01) #stop briefly to stablize camera image

    #Obj detected?
    img = take_image()
    if img is not None:
      #find if object is detected
      obj_detected, obj_img = detector(img)
  
  return obj_img

def find_and_retrieve(core):
  '''
    Finds obj than goes to it and picks it up
  '''

  obj = find_obj(core)
  pass