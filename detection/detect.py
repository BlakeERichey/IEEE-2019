import cv2
import os
import numpy as np
import matplotlib.pyplot as plt
import skimage.segmentation as seg
import skimage.color as color

def foreground_obstructed(img):
  '''
    segments image and determines if the foreground is broken up by an object.
  '''
  #segment image to isolate colors
  image_slic = seg.slic(img,n_segments=150)
  segmented = color.label2rgb(image_slic, img, kind='avg')

  #determine color threshold
  y, x, _ = img.shape
  pixel = img[int(y//2), 0] #take pixel halfway down y axis at x=0
  src = np.expand_dims(np.array([pixel]), axis=0)
  foreground_color = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)

  #color threshold with foreground color
  hsv = cv2.cvtColor(segmented, cv2.COLOR_BGR2HSV)
  h, s, v = foreground_color[0, 0]
  lower = np.array([max(0, h-10), max(0, s-50), max(0, v-50)])
  upper = np.array([min(179, h+10), min(255, s+50), min(255, v+50)])
  mask = cv2.inRange(hsv, lower, upper)

  #find strong edges
  edges = cv2.Canny(mask, 150, 250)
  contours, hierarchy = cv2.findContours(edges.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

  return (False, len(contours) > 1)[contours is not None]

def detection(img):
  '''
    returns if an object was found and then returns the closest obj to the camera
  '''
  e1 = cv2.getTickCount()
  img = cv2.resize(img, None, fx=.2, fy=.2, interpolation=cv2.INTER_AREA)
  obj_in_fg = foreground_obstructed(img)
  
  objs = [] #cropped images of objs
  if obj_in_fg:
    thresh = 0.03*img.size #minimum size for object to be detected
    blur = cv2.medianBlur(img, 3)
    edges = cv2.Canny(blur, 150, 200)

    edges = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=1)
    contours, hierarchy = cv2.findContours(edges.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    coords = [] #x,y,w,h locations
    border_id = None #will be used for primary parent identifier
    for i, c in enumerate(contours):
      x,y,w,h = cv2.boundingRect(c) #get bounding box
      if w*h >= thresh: #if bounding box big enough
        parent = hierarchy[0][i][3]
        #INSERT LOGIC TO REMOVE PRIMARY PARENT HERE
        objs.append(img[y:y+h, x:x+w])
        coords.append((len(coords),x,y,w,h))
    coords = sorted(coords, key=lambda x: x[1]) #sort by x location (closest box to left is closest obj)
  
  res = None
  if len(objs) > 1:
    res = objs[coords[1][0]] #ignore primary parent, so coords[1]. [0] gets index number

  e2 = cv2.getTickCount()
  time = (e2 - e1)/ cv2.getTickFrequency()
  print("Time taken:", time)
  
  if res is not None:
    cv2.imshow("Image", img)
    cv2.imshow("Edges", edges)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
  return res is not None, res

# path = './images/coke/'
# cokes = [name for name in os.listdir('./images/coke/')]

# for i in range(100):
#   print('Loading:', path+cokes[i])
#   img = cv2.imread(path+cokes[i], cv2.IMREAD_COLOR)
#   obj_found, obj = detection(img)
#   if obj_found:
#     cv2.imshow("Object", obj)
#     cv2.waitKey(0)
#     cv2.destroyAllWindows()
#   else:
#     print('No object found')

img = cv2.imread('nacho.jpg', cv2.IMREAD_COLOR)
obj_found, obj = detection(img)
if obj_found:
  cv2.imshow("Object", obj)
  cv2.waitKey(0)
  cv2.destroyAllWindows()
else:
  print('No object found')

