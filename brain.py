#receives and sends data to the arduino
#manages localstate for pi
import serial
import time
import json, os, cv2
from detection import detect

OS="linux"
if os.name == "nt":
  OS = 'windows'

ACTION_SPACE = {
	'STOP' : 0,
	'MOVE_FORWARD' : 1, 
	'MOVE_BACKWARD' : 2,
	'TURN_RIGHT' : 3,
	'TURN_LEFT' : 4,
}

#state class containing active arduinos and active running component
class StateManager():

  def __init__(self):
    self.nodes = {}			#an arduino
    self.active = 'pi'		#
    self.added_devices = {} #
  
  def add_node(self, arduino, device_name, baudrate=9600):
    _id = self.getId(arduino) #may throw error
    self.added_devices.update({_id:device_name})
    
    #add new node
    arduino.baudrate=baudrate
    newNode = {str(_id):arduino}
    self.nodes.update(newNode)
    return _id

  def getId(self, arduino):
    '''gets message from arduino serial.Serial() input stream. interprets the message as an _id'''
    print("Attempting to read line")
    read_serial=arduino.readline()
    print("read serial",read_serial)
    _id = read_serial.decode('utf-8') #returns initial message from arduino

    if OS == "windows":
      _id = _id[:-2]
    else:
      _id = _id[:-2]

    print(_id, type(_id))
    return _id
  
  def __str__(self):
    return str(self.added_devices)

#encodes a character into a byte
#core = instance of the state
#dev_id = device we are sending data to 
#data = a string we want to send

def send_data(core, dev_id, data):
    msg = str(data)
    print('Sending:', msg)
    core.nodes[dev_id].write(msg.encode('utf-8'))
    # time.sleep(1)
    
#recieves data
def receive_data(core, dev_id):
    print('Listening to ' + dev_id + '...')
    read_serial=core.nodes[dev_id].readline()
    if(read_serial):
        msg = read_serial.decode('utf-8')

        if OS == "windows":
          _id = _id[:-2]
        else:
          _id = _id[:-2]


        print('Received:', msg) #decode data and print
        if msg == '-1': #job done
          core.val = 'pi' #set pi as active
    # time.sleep(1)

def movement():
	actions = [
		ACTION_SPACE['MOVE_FORWARD'],
		ACTION_SPACE['STOP'],
		ACTION_SPACE['MOVE_BACKWARD'],
		ACTION_SPACE['STOP'],
		ACTION_SPACE['TURN_LEFT'],
		ACTION_SPACE['STOP'],
		ACTION_SPACE['TURN_RIGHT'],
		ACTION_SPACE['STOP'],
	]

	for action in actions: 
		send_data(core,'0',action)
		time.sleep(3)
	print("movemnt complete")

def IMU():
	pass

def send_act(core, string):
  if string in ACTION_SPACE.keys():
    action = ACTION_SPACE[string]
    send_data(core, '0', action)

def take_image():
  '''returns image from pi-camera'''
  # initialize the camera
  cam = cv2.VideoCapture(0)   # 0 -> index of camera
  s, img = cam.read()
  if s:    # frame captured without any errors
    return img

def save_image(filename, img):
  cv2.imwrite(filename, img)

#start of program
if __name__ == '__main__': 
  '''logic for rasbpi goes here'''
  #Initialize State
  core = StateManager()
  num_devices = 1
  
  path = "/dev/"
  devices = ['ttyACM0', 'ttyACM1'] #potential device names

  if os.name == "nt":	#If os is windows path is empty
	  path = "" 
	  devices = ["COM3","COM4"] 

  #initialize Serial Information//Attach Arduinos
  
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
  
  time.sleep(2)
  i = 0
  # movement()
  while True: #primary loop

    #rotate until object found
    img = take_image()
    h, w, _ = img.shape
    scale = 1
    angle = 180
    center = (w/2,h/2)
    M = cv2.getRotationMatrix2D(center, angle, scale)
    img = cv2.warpAffine(img, M, (w, h))
    if img is not None:
      # cv2.imshow('Image', img)
      # cv2.waitKey(0)
      # cv2.destroyAllWindows()
      obj_detected, obj_img = detect.detection(img)
      if obj_detected:
        save_image('image'+str(i), img)
        i+=1
      # if not obj_detected:
      #   send_act(core, 'TURN_RIGHT')
      # else:
      #   send_act(core, 'STOP')
      #   break
