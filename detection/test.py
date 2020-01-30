import cv2, os
from detect import detection

img = cv2.imread('wb.jpg', cv2.IMREAD_COLOR)
obj_found, obj = detection(img)
if obj_found:
  cv2.imshow("Image", img)
  cv2.imshow("Object", obj)
  cv2.waitKey(0)
  cv2.destroyAllWindows()
else:
  print('No object found')