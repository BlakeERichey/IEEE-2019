import serial
import time
import os, cv2
from utils import *
from pathing import *
from state import StateManager

OS="linux"
if os.name == "nt":
  OS = 'windows'

ACTION_SPACE = {
  'STOP' : 0,
  'MOVE_FORWARD' : 1, 
  'MOVE_BACKWARD' : 2,
  'TURN_RIGHT' : 3,
  'TURN_LEFT' : 4,
  'CLOSE': 5, #Close flippers
  'GRAB': 6, #Close Claw
  'STORE': 7, #pick up and ...
}

#========== MAIN ==================================================
if __name__ == '__main__': 
  '''
    Logic for RasbPi goes here
  '''
  #========== Connect Arduinos ============================== 
  #Initialize State
  core = StateManager()
  num_devices = 2
  
  path = "/dev/"
  devices = ['ttyACM0', 'ttyACM1', 'ttyACM2'] #potential device names

  if os.name == "nt":	#If os is windows path is empty
    path = "" 
    devices = ["COM3","COM4"] 

  #Initialize Serial Information//Attach Arduinos
  while len(core.added_devices) < num_devices: #until all devices are loaded
    time.sleep(.25)
    for device_name in devices:
      if device_name not in core.added_devices.values():
        print('Attemping to connect to ' + device_name + '...')
        try:
          arduino = serial.Serial(path + device_name,9600) #ls /dev/tty*
          print('Connected!')
          _id = core.add_node(arduino, device_name)
          send_data(core, _id, 0) #job completed without error
        except Exception as e:
          print('Error occured', e)
  
  print('Resulting State:', core)
  print('Nodes', core.nodes)
  time.sleep(1)
  
  #========== Pathing ======================================== 
  movement(core)
