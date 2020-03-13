from victor.utils import load_image
from victor.calibrate import calibrate_distance

img = load_image("calibrate.jpg")
pixels = calibrate_distance(["red", "black", "green"], img, scale=.1, display=True)

print(pixels)