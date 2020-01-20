import cv2
import numpy as np
import matplotlib.pyplot as plt

def detection(img):
  e1 = cv2.getTickCount()
  img = cv2.resize(img, None, fx=.2, fy=.2, interpolation=cv2.INTER_AREA)
  print("Size:", img.size)
  thresh = 0.03*img.size
  kernel = np.ones((5,5), np.uint8)
  blur = cv2.medianBlur(img, 3)
  edges = cv2.Canny(blur, 50, 200)

  # laplacian = cv2.Laplacian(img,cv2.CV_64F)
  # abs_sobel64f = np.absolute(laplacian)
  # laplacian_8u = np.uint8(abs_sobel64f)
  edges = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=1)
  edges = cv2.medianBlur(edges, 3)
  # edges = cv2.morphologyEx(edges, cv2.MORPH_OPEN, np.ones((3,3), np.uint8), iterations=1)
  edges = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=5)
  image, contours, hierarchy = cv2.findContours(edges.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

  for c in contours:
    rect = cv2.minAreaRect(c)
    w, h = rect[1]
    print("W, H", w, h, w*h)
    if w*h > thresh:
      box = cv2.boxPoints(rect)
      box = np.int0(box)
      img = cv2.drawContours(img,[box],0,(255,255,255),2)


  e2 = cv2.getTickCount()
  time = (e2 - e1)/ cv2.getTickFrequency()
  print("Time taken:", time)

  cv2.imshow("Image", img)
  cv2.imshow("edges", edges)
  cv2.waitKey(0)
  cv2.destroyAllWindows()

img = cv2.imread('coke.jpg', cv2.IMREAD_COLOR)
detection(img)
