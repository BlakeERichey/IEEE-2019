import os
import cv2
import time
import serial
from victor.cv import detector
from victor.utils import StateManager, take_image
from victor.calibrate import ACTION_SPACE

class Brain:

  def __init__(self, num_devices = 1):
    """
      Intializes Arduino brain with num_devices arduinos connected.
    """
    #Initialize State
    core = StateManager()
    num_devices = num_devices
    
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
            self._send_data(_id, 0, core) #job completed without error
          except Exception as e:
            print('Error occured', e)
    
    print('Resulting State:', core)
    print('Nodes', core.nodes)
    time.sleep(1)

    self.state = core

  #========== Pathing Methods ======================================== 
  def run_competition(self,):
    """
      Performs all pathing necessary to complete IEEE challenge
    """
    pass

  def find_obj(self):
    '''
      Rotates right until an object is detected by obj detector
    '''
    state = self.state
    obj_detected = False
    while not obj_detected: 
      self.send_act(state, 'TURN_RIGHT')
      time.sleep(.4)
      self.send_act(state, 'STOP')
      time.sleep(.01) #stop briefly to stablize camera image

      #Obj detected?
      img = take_image()
      if img is not None:
        #find if object is detected
        obj_detected, obj_img, coords = detector(img)
    
    return obj_img, coords

  def find_and_retreive(self,):
    pass

  #========== Servos Methods ======================================== 

  def pickup(self):
    """
      Object is detected withing grabbing distance.
      Robot should stop and pick up the piece of trash.
    """

    time.sleep(.1) #give robot time to reach trash.
    self.send_act("STOP")
    time.sleep(1) #give flippers time to cease closing
    self.send_act("CLOSE_CLAW", "1")
    time.sleep(1) #give claw time to cease closing
    
    #NOT IMPLEMENTED
    # send_act(state, "RAISE_ARM", "1")

  def dispose(self):
    """
      Drops trash
    """
    self.send_act("OPEN_CLAW", "1")
    time.sleep(1)
    self.send_act("CLOSE_CLAW", "1")
    time.sleep(1)

  def close_flippers(self):
    """
      Object detected within flipper range. Begins closing flippers.
    """

    self.send_act("CLOSE_FLIPPERS", "1")

  #========== Communication Methods ======================================== 

  def send_act(self, string, ardId="0"):
    '''
      Sends an action to arduino
    '''
    if string in ACTION_SPACE.keys():
      action = ACTION_SPACE[string]
      self._send_data(ardId, action)

  #========== Private Utility Methods ======================================== 

  #encodes a character into a byte
  #state = instance of the StateManager class
  #dev_id = device we are sending data to (0, 1, 2...)
  #data = a string we want to send
  def _send_data(self, dev_id, data, state=None):
    state = state or self.state
    msg = str(data)
    print('Sending:', msg)
    state.nodes[dev_id].write(msg.encode('utf-8'))

  #recieves data
  def _receive_data(self, dev_id):
    state = self.state
    print('Listening to ' + dev_id + '...')
    read_serial=state.nodes[dev_id].readline()
    if(read_serial):
        msg = read_serial.decode('utf-8')

        print('Received:', msg) #decode data and print
        return msg