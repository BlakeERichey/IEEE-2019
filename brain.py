#receives and sends data to the arduino
#manages localstate for pi
import serial
import time
import json, os

#state class containing active arduinos and active running component
class StateManager():

  def __init__(self):
    self.nodes = {}
    self.active = 'pi'
    self.added_devices = {}
  
  def add_node(self, arduino, device_name, baudrate=9600):
    _id = self.getId(arduino) #may throw error
    self.added_devices.update({_id:device_name})
    
    #add new node
    arduino.baudrate=baudrate
    newNode = {_id:arduino}
    self.nodes.update(newNode)
    return _id

  def getId(self, arduino):
    '''gets message from arduino serial.Serial() input stream. interprets the message as an _id'''
    read_serial=arduino.readline()
    _id = read_serial.decode('utf-8') #returns initial message from arduino
    return _id
  
  def __str__(self):
    return self.added_devices

def sendData(core, dev_id, data):
    msg = str(data)
    print('Sending:', msg)
    core.nodes[dev_id].write(msg.encode('utf-8'))
    # time.sleep(1)
    
def receiveData(core, dev_id):
    print('Listening to ' + dev_id + '...')
    read_serial=core.nodes[dev_id].readline()
    if(read_serial):
        msg = read_serial.decode('utf-8')
        print('Received:', msg) #decode data and print
        if msg == '-1': #job done
          core.val = 'pi' #set pi as active
    # time.sleep(1)

if __name__ == '__main__': 
  '''logic for rasbpi goes here'''
  #Initialize State
  core = StateManager()
  num_devices = 1

  #initialize Serial Information//Attach Arduinos
  devices = ['ttyACM0', 'ttyACM1'] #potential device names
  while len(core.added_devices) < num_devices: #until all devices are loaded
    time.sleep(.25)
    for device_name in devices:
      if device_name not in core.added_devices.values():
        print('Attemping to connect to ' + device_name + '...')
        try:
          arduino = serial.Serial('/dev/' + device_name,9600) #ls /dev/tty*
          print('Connected!')
          _id = core.add_node(arduino, device_name)
          sendData(core, _id, 0) #job completed without error
        except Exception as e:
          print('Error occured', e)
  
  print('Resulting State:', core)
