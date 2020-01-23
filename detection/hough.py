import cv2
import numpy as np
import skimage.segmentation as seg
import skimage.color as color


img = cv2.imread('coke.jpg')
img = img[135:720, :880]
img = cv2.resize(img, None, fx=.5, fy=.5, interpolation=cv2.INTER_AREA)
# image_slic = seg.slic(img,n_segments=155)
# img = color.label2rgb(image_slic, img, kind='avg')
edges = cv2.Canny(img,50,150, apertureSize=3)
edges = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8))
minLineLength = 10
maxLineGap = 1000
lines = cv2.HoughLinesP(edges,rho = 1,theta = 3*np.pi/180,threshold = 10,minLineLength = minLineLength,maxLineGap = maxLineGap)
if lines is not None:
  print('lines', len(lines))
  for i in range(len(lines)):
    for x1,y1,x2,y2 in lines[i]:
      cv2.line(img,(x1,y1),(x2,y2),(0,255,0),2)

cv2.imshow("Img", img)
cv2.imshow("Edges", edges)
cv2.waitKey(0)
cv2.destroyAllWindows()