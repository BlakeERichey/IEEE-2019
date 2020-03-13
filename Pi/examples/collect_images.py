import time
from victor.cv import detector
from victor.utils import take_image, save_image
from victor import Brain

brain = Brain(1)

num_images = 250

def collect_images(brain, num_images):
  '''
    Rotates and saves images.
  '''
  for i in range(num_images):
    while True: #primary loop
      brain.send_act('TURN_RIGHT')
      time.sleep(.4)
      brain.send_act('STOP')
      time.sleep(.01)

      img = take_image()
      if img is not None:
        obj_detected, obj_img, _ = detector(img)
        save_image('images/image'+str(i)+'.jpg', img)
        if obj_detected:
          save_image('images/detected'+str(i)+'.jpg', obj_img)
        i+=1
        time.sleep(.01)

collect_images(brain, num_images)