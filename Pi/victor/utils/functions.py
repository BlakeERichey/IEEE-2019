#Utils library for functions used brain.py
import cv2, time
from victor.calibrate.action_space import ACTION_SPACE

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