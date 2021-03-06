import os

#State class containing active arduinos and active running components
class StateManager():

  #Determine OS
  OS="linux"
  if os.name == "nt":
    OS = 'windows'

  def __init__(self):
    self.nodes = {}			#an arduino
    self.active = 'pi'		#
    self.added_devices = {} #
  
  def add_node(self, arduino, device_name, baudrate=9600):
    _id = None
    while _id not in ['0', '1']:
      _id = self.getId(arduino)
    self.added_devices.update({_id:device_name})
    
    #add new node
    arduino.baudrate=baudrate
    newNode = {str(_id):arduino}
    self.nodes.update(newNode)
    return _id

  def getId(self, arduino):
    '''gets message from arduino serial.Serial() input stream. interprets the message as an _id'''
    # print("Attempting to read line")
    read_serial=arduino.readline()
    # print("read serial",read_serial)
    _id = read_serial.decode('utf-8') #returns initial message from arduino

    if StateManager.OS == "windows":
      _id = _id[:-2]
    else:
      _id = _id[:-2]

    # print(_id, type(_id))
    return _id
  
  def __str__(self):
    return str(self.added_devices)