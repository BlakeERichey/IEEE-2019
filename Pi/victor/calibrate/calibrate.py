import cv2
import json
import numpy as np
from victor.utils import take_image, load_image

def squeeze(color):
  '''squeezes an arr into hsv color space'''
  h, s, v = color

  for i, value in enumerate([h,s,v]):
    if i == 0: #hue value
      hue = value%180
      if hue < 0:
        hue = 180-hue
      
      value = hue
    else:
      value = value%256
    
    color[i] = value

def lower_upper(color, h_thresh=10, min_s=50, min_v=50, max_s=255, max_v=255):
  '''
    Takes in hsv color and returns ranges around the color
  '''
  lower, upper = color.copy(), color.copy()
  lower[0] -= h_thresh #h
  lower[1] = min(lower[1], min_s) #s
  lower[2] = min(lower[2], min_v) #v
  upper[0] += h_thresh
  upper[1] = max_s
  upper[2] = max_v
  squeeze(lower), squeeze(upper)

  if lower[0] > upper[0]: #if hue is centered around 180, returns list now
    lower = [lower, np.array([0, min_s, min_v])]
    upper = [np.array([179,max_s,max_v]), upper]

  return lower, upper

def get_thresh(string):
  '''
    Takes string of a color name and returns lower and upper thresholds
  '''
  string = string.lower()
  assert string in ['red','black','green']

  color_dict = {
    'red':    np.array([0,   150, 100]), 
    'pink':   np.array([0,   125, 230]),  #does not work
    'yellow': np.array([35,  150, 100]),  #does not work
    'purple': np.array([150, 150, 100]),  #does not work
    'blue':   np.array([120, 150, 100]),  #does not work
    'green':  np.array([60,  150, 100]), 
  }

  if string in ['pink']:
    color = color_dict[string]
    lower, upper = lower_upper(color, 10, 15, 230, 125, 255)
  elif string in ['black', 'white']:
    if string == 'black':
      lower, upper = np.array([0,0,0]), np.array([179,255,100])
    else:
      lower, upper = np.array([0,140,235]), np.array([179,140,255]) #does not work
  else:
    color = color_dict[string]
    lower, upper = lower_upper(color, h_thresh=20, min_s=10)
  
  return lower, upper

def get_mask(hsv, string):
  '''
    Returns mask of img that contains color `string`

    hsv: hsv image
    string: color to threshold ('pink', 'blue'...)
  '''
  color = string.lower()
  lower, upper = get_thresh(color)
  # print(color, lower, upper)

  if isinstance(lower, list):
    mask = cv2.inRange(hsv, lower[0], upper[0])
    mask2 = cv2.inRange(hsv, lower[1], upper[1])

    mask = cv2.bitwise_or(mask, mask2)
  else:
    mask = cv2.inRange(hsv, lower, upper)
  
  return mask

def calibrate_distance(colors, img=None, scale=1, display=False):
  '''
    Finds pixels that correspond to key distances.
    if img is not provided, then function takes a picture from camera.

    Expects BGR image.
    Colors: list of color strings expect from bottom to top of image
  '''
  if img is None:
    img = take_image()

  img = cv2.resize(img, None, fx=scale, fy=scale, interpolation=cv2.INTER_AREA)
  
  original = img
  
  top_pixels = []
  if img is not None:
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    for color in colors:
      img = original.copy()
      mask = get_mask(hsv, color)

      #find area of color
      # mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=3)
      contours, hierarchy = cv2.findContours(mask.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
      cntsSorted = sorted(contours, key=lambda x: cv2.contourArea(x), reverse=True)
      
      #get bounding box of largest area
      try:
        largest_contour = cntsSorted[0]
        x,y,w,h = cv2.boundingRect(largest_contour) #get bounding box
        img = cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
        print(len(cntsSorted), 'Color:', color, 'Top Pixel:', y)
        
        top_pixels.append(y)
      except IndexError as e:
        print('Error occured detecting', color, e)
        top_pixels.append(-1)

      
      if display:
        cv2.imshow("Image", img)
        cv2.imshow(color, mask)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

  return top_pixels