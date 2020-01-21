import cv2
import numpy as np
import matplotlib.pyplot as plt

def detection(img):
  '''
    returns number of objects found and their images
  '''
  e1 = cv2.getTickCount()
  img = cv2.resize(img, None, fx=.2, fy=.2, interpolation=cv2.INTER_AREA)
  # print("Size:", img.size)
  thresh = 0.03*img.size
  kernel = np.ones((5,5), np.uint8)
  blur = cv2.medianBlur(img, 3)
  edges = cv2.Canny(blur, 150, 200)

  edges = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=1)
  contours, hierarchy = cv2.findContours(edges.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

  objs = []
  border_id = None
  for i, c in enumerate(contours):
    x,y,w,h = cv2.boundingRect(c) #get bounding box
    if w*h >= thresh: #if bounding box big enough
      parent = hierarchy[0][i][3]
      # print('heir', hierarchy[0][i], parent)
      # if border_id == None:
      #   border_id = i
      # if parent == border_id:
      # print("W, H", w, h, w*h)
      # print('X, Y', (x, y), '\n\n')
      objs.append(img[y:y+h, x:x+w])
      # img = cv2.rectangle(img,(x,y),(x+w,y+h),(255,255,255),2)
  
  return len(objs), objs


  e2 = cv2.getTickCount()
  time = (e2 - e1)/ cv2.getTickFrequency()
  print("Time taken:", time)

  # cv2.imshow("Image", img)
  # cv2.imshow("edges", edges)
  # cv2.waitKey(0)
  # cv2.destroyAllWindows()

img = cv2.imread('wb.jpg', cv2.IMREAD_COLOR)
num, imgs = detection(img)
for i, image in enumerate(imgs):
  cv2.imshow(str(i), image)
cv2.waitKey(0)
cv2.destroyAllWindows()
