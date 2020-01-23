import cv2
import os
import numpy as np
import matplotlib.pyplot as plt
import skimage.segmentation as seg
import skimage.color as colorseg

img = cv2.imread('empty2.jpg', cv2.IMREAD_COLOR)
y, x, _ = img.shape
print(img.shape)
print('X, Y', (x,y))
pixel = img[int(y//2), 0]
src = np.expand_dims(np.array([pixel]), axis=0)
print(src, src.shape)
color = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)
print("Color", color[0, 0])
h, s, v = color[0, 0]
lower = np.array([max(0, h-10), max(0, s-50), max(0, v-50)])
upper = np.array([min(179, h+10), min(255, s+50), min(255, v+50)])
print('Lower', lower)
print('Upper', upper)
e1 = cv2.getTickCount()
img = cv2.resize(img, None, fx=.2, fy=.2, interpolation=cv2.INTER_AREA)
image_slic = seg.slic(img,n_segments=150)
segmented = colorseg.label2rgb(image_slic, img, kind='avg')
hsv = cv2.cvtColor(segmented, cv2.COLOR_BGR2HSV)
mask = cv2.inRange(hsv, lower, upper)
# mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=1)
edges = cv2.Canny(mask, 150, 250)
contours, hierarchy = cv2.findContours(edges.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

for c in contours:
    x,y,w,h = cv2.boundingRect(c) #get bounding box
    print("wh", w*h)
    if w*h > 1000:
      img = cv2.rectangle(img,(x,y),(x+w,y+h),(255,255,255),2)
print("Contours", len(contours))

e2 = cv2.getTickCount()
time = (e2 - e1)/ cv2.getTickFrequency()
print("Time taken:", time)
cv2.imshow("Image", img)
cv2.imshow("Mask", mask)
cv2.imshow("Segmented", segmented)
cv2.imshow("Edges", edges)
cv2.waitKey(0)
cv2.destroyAllWindows()