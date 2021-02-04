# Python program for Detection of a 
# specific color(blue here) using OpenCV with Python 
import cv2 
import numpy as np 

# Webcamera no 0 is used to capture the frames 
#cap = cv2.VideoCapture(0) 
#204,134,160 rgb
#220,144,164
# This drives the program into an infinite loop.  
# Captures the live stream frame-by-frame 
# Converts images from BGR to HSV
frame = cv2.imread("image1.jpeg")

hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) 
lower_red = np.array([160,130,200]) 
upper_red = np.array([170,160,220]) 

# Here we are defining range of bluecolor in HSV 
# This creates a mask of blue coloured 
# objects found in the frame. 
mask1 = cv2.inRange(hsv, lower_red, upper_red) 

# Range for upper range
#lower_red = np.array([100,130,170])
#upper_red = np.array([200,255,255])
#mask2 = cv2.inRange(hsv,lower_red,upper_red)
mask = mask1#+mask2

# The bitwise and of the frame and mask is done so 
# that only the blue coloured objects are highlighted 
# and stored in res 
res = cv2.bitwise_and(frame,frame, mask= mask) 
cv2.imshow('frame',frame) 
cv2.imshow('mask',mask) 
cv2.imshow('res',res) 

# This displays the frame, mask 
# and res which we created in 3 separate windows. 

