import cv2
import numpy as np
import matplotlib.pyplot as plt

def detection(img):
  '''
    returns if an object was found and then returns the closest obj to the camera
  '''
  e1 = cv2.getTickCount()
  img = cv2.resize(img, None, fx=.2, fy=.2, interpolation=cv2.INTER_AREA)
  thresh = 0.03*img.size #minimum size for object to be detected
  blur = cv2.medianBlur(img, 3)
  edges = cv2.Canny(blur, 150, 200)

  edges = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=1)
  image, contours, hierarchy = cv2.findContours(edges.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

  objs = [] #cropped images
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
  return res is not None, res

img = cv2.imread('empty.jpg', cv2.IMREAD_COLOR)
obj_found, obj = detection(img)
if obj_found:
  cv2.imshow("Object", obj)
  cv2.waitKey(0)
  cv2.destroyAllWindows()
else:
  print('No object found')
