import cv2
import sys
import logging as log
import datetime as dt
from time import sleep
import smtplib
import time
from datetime import datetime
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
#import RPi.GPIO as GPIO
import time
#https://www.google.com/settings/security/lesssecureapps

def send_email():
    toaddr = 'kishorlanjewar66@gmail.com'
    me = 'smitagawade1234@gmail.com'
    Subject='security alert'
    subject='Security allert!!'
    msg = MIMEMultipart()
    msg['Subject'] = subject
    msg['From'] = me
    msg['To'] = toaddr
    fp= open('saved_img.jpg','rb')
    img = MIMEImage(fp.read())
    fp.close()
    msg.attach(img)
    now = datetime.now() 
    print("now =", now)
    # dd/mm/YY H:M:S
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    print("date and time =", dt_string)
    body = 'Intruder is detected at your fish area ' + dt_string
    body1 = MIMEText(body) # convert the body to a MIME compatible string
    msg.attach(body1) # attach it to your main message
    server = smtplib.SMTP('smtp.gmail.com',587)
    server.starttls()
    server.login(user = 'smitagawade1234@gmail.com',password='Smita@123')
    server.send_message(msg)
    server.quit()
    print("Email sent")


cascPath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascPath)
log.basicConfig(filename='webcam.log',level=log.INFO)

video_capture = cv2.VideoCapture(0)
anterior = 0
flag_detect =0
while True:
    if not video_capture.isOpened():
        print('Unable to load camera.')
        sleep(5)
        pass

    # Capture frame-by-frame
 #   ret, frame = video_capture.read()
    frame = cv2.imread("pankaj.jpg")
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30)
    )

    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        cv2.imwrite(filename='saved_img.jpg', img=frame)
        print("face detected")
        if(flag_detect == 0):
            #send_email()
            flag_detect=1
    if anterior != len(faces):
        anterior = len(faces)
        log.info("faces: "+str(len(faces))+" at "+str(dt.datetime.now()))


    # Display the resulting frame
    cv2.imshow('Video', frame)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

    # Display the resulting frame
    cv2.imshow('Video', frame)

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
