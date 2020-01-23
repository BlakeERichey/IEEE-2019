# import numpy as np
# import matplotlib.pyplot as plt
# import skimage.data as data
# import skimage.segmentation as seg
# import skimage.filters as filters
# import skimage.draw as draw
# import skimage.color as color
# from skimage import io
# import cv2

# image = io.imread('wb.jpg')
# e1 = cv2.getTickCount()
# image = cv2.resize(image, None, fx=.2, fy=.2, interpolation=cv2.INTER_AREA)
# image_slic = seg.slic(image,n_segments=100)
# # image_slic = seg.slic(image,n_segments=100)
# # image_slic = seg.slic(image_slic,n_segments=100)
# # image_slic = seg.felzenszwalb(image)
# segmented = color.label2rgb(image_slic, image, kind='avg')

# segmented = cv2.cvtColor(segmented, cv2.COLOR_RGB2BGR)
# first_segment = segmented.copy()
# # segmented = cv2.medianBlur(segmented, 3)
# edges = cv2.Canny(segmented, 150, 200)
# edges = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, np.ones((5,5), np.uint8), iterations=2)
# # edges = cv2.morphologyEx(edges, cv2.MORPH_OPEN, np.ones((3,3), np.uint8), iterations=1)
# contours, hierarchy = cv2.findContours(edges.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

# for i, c in enumerate(contours):
#   x,y,w,h = cv2.boundingRect(c) #get bounding box
#   segmented = cv2.rectangle(segmented,(x,y),(x+w,y+h),(255,255,255),2)

# e2 = cv2.getTickCount()
# time = (e2 - e1)/ cv2.getTickFrequency()
# print("Time taken:", time)
# cv2.imshow('Original', first_segment)
# cv2.imshow('segmented', segmented)
# cv2.imshow('edges', edges)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
# print('Hello')