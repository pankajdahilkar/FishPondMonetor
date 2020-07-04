import io
#import picamera
import cv2
import numpy


image = cv2.imread("pankaj.jpg")
#Load a cascade file for detecting faces
faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

#Convert to grayscale
gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

#Look for faces in the image using the loaded cascade file
faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30)
    )
print("Found "+str(len(faces))+" face(s)")

#Draw a rectangle around every found face
for (x,y,w,h) in faces:
    cv2.rectangle(image,(x,y),(x+w,y+h),(255,255,0),2)

#Save the result image
cv2.imshow('result.jpg',image)
