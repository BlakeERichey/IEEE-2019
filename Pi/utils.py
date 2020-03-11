#Utils library for functions used brain.py
import cv2, time
from detect import detector
from brain import ACTION_SPACE

#encodes a character into a byte
#core = instance of the state
#dev_id = device we are sending data to (0, 1, 2...)
#data = a string we want to send
def send_data(core, dev_id, data):
  msg = str(data)
  print('Sending:', msg)
  core.nodes[dev_id].write(msg.encode('utf-8'))

#recieves data
def receive_data(core, dev_id):
  print('Listening to ' + dev_id + '...')
  read_serial=core.nodes[dev_id].readline()
  if(read_serial):
      msg = read_serial.decode('utf-8')

      print('Received:', msg) #decode data and print
      return msg

def send_act(core, string):
  '''
    Sends an action to ard0
  '''
  if string in ACTION_SPACE.keys():
    action = ACTION_SPACE[string]
    send_data(core, '0', action)

def take_image():
  ''' 
    returns image from pi-camera. Returns None if error occured.
  '''
  # initialize the camera
  cam = cv2.VideoCapture(0)   # 0 -> index of camera
  no_errors, img = cam.read()
  if no_errors: # frame captured without any errors
    #rotate img
    h, w, _ = img.shape
    scale = 1
    angle = 90
    center = (w/2,h/2)
    M = cv2.getRotationMatrix2D(center, angle, scale)
    img = cv2.warpAffine(img, M, (w, h))
    return img[:, 170:480] #crop out claw

def save_image(filename, img):
  cv2.imwrite(filename, img)

def load_image(filename, mode='color'):
  
  mode = ['gray','color'].index(mode)
  return cv2.imread(filename, mode)

def downscale(img, scale=.1):
  """
    img: BGR color scale image
    scale: ratio of new size to original
  """

  return cv2.resize(img, None, fx=scale, fy=scale, interpolation=cv2.INTER_AREA)

def movement(core):
  '''
    Test all movement options for arduino
  '''

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
  print("Movement complete")

def collect_images(core, num_images):
  '''
    Rotates and saves images.
  '''
  for i in range(num_images):
    while True: #primary loop
      send_act(core, 'TURN_RIGHT')
      time.sleep(.4)
      send_act(core, 'STOP')
      time.sleep(.01)

      img = take_image()
      if img is not None:
        obj_detected, obj_img = detector(img)
        save_image('images/image'+str(i)+'.jpg', img)
        if obj_detected:
          save_image('images/detected'+str(i)+'.jpg', obj_img)
        i+=1
        time.sleep(.01)