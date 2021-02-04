import cv2
import sys
import logging as log
#import datetime as dt
from time import sleep
import smtplib
import time
from datetime import datetime
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
#import RPi.GPIO as GPIO
import time
import threading
import requests as req
#https://www.google.com/settings/security/lesssecureapps

def send_email():
    toaddr = 'pankajmdahilkar@gmail.com'
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


def Face_detect():
    cascPath = "haarcascade_frontalface_default.xml"
    faceCascade = cv2.CascadeClassifier(cascPath)
    log.basicConfig(filename='webcam.log',level=log.INFO)

    video_capture = cv2.VideoCapture(0)
    anterior = 0
    flag_detect =0
    prev_minute =0
    min_now =0;
    while True:
        if not video_capture.isOpened():
            print('Unable to load camera.')
            sleep(5)
            pass

        # Capture frame-by-frame
        ret, frame = video_capture.read()
        #frame = cv2.imread("pankaj.jpg")
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        min_now = datetime.now().minute
        print(min_now)
        if(int(min_now) - int(prev_minute)) >= 1:
           print("minutes over reseting security")
           flag_detect =0
           prev_minute = min_now

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
                send_email()
                print("Sending Email")
                flag_detect=1
        if anterior != len(faces):
            anterior = len(faces)
            log.info("faces: "+str(len(faces))+" at "+str(datetime.now()))


        # Display the resulting frame
        cv2.imshow('Video', frame)


        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        # Display the resulting frame
        cv2.imshow('Video', frame)
    video_capture.release()
    cv2.destroyAllWindows()
def read_iot_cmd():
    resp = req.get("https://world4.tech/fsecure/machinetate.txt")
    print(resp.text)
    cmd = int(resp.text)
    return cmd

#print("Sending Email")
#send_email()
def Run_motor_control():
    #MAIN_MOTOR = 40 # pin40
    #DRAIN_MOTOR = 38
    #GPIO.setwarnings(False)
    #GPIO.setmode(GPIO.BOARD) # We are accessing GPIOs according to their physical location
    #GPIO.setup(LED, GPIO.OUT) # We have set our LED pin mode to output
    #GPIO.output(LED, GPIO.LOW) # When it will start then LED will be OFF 
    while(True):
        cmd_c = read_iot_cmd()
        if(cmd_c == 1):
            #GPIO.output(MAIN_MOTOR, GPIO.HIGH) # led on
            print("MAin Motor ON")
            resp =req.get("https://world4.tech/fsecure/upload.php?val=MAIN%20Motor%20ON")
            print(resp.text)
        elif(cmd_c == 0):
            #GPIO.output(MAIN_MOTOR, GPIO.LOW)
            print("Main Motor OFF")
            resp =req.get("https://world4.tech/fsecure/upload.php?val=MAIN%20Motor%20OFF")
            print(resp.text)
        elif(cmd_c == 3):
            #GPIO.output(DRAIN_MOTOR, GPIO.HIGH)
            print("DRAIN Motor ON")
            resp =req.get("https://world4.tech/fsecure/upload.php?val=DRAIN%20Motor%20ON")
            print(resp.text)
        elif(cmd_c == 4):
            #GPIO.output(DRAIN_MOTOR, GPIO.LOW)
            print("DRAIN Motor OFF")
            resp =req.get("https://world4.tech/fsecure/upload.php?val=DRAIN%20Motor%20OFF")
            print(resp.text)
        sleep(2)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

if __name__ == "__main__":
    #Run_motor_control()
    #Face_detect()
    t1 = threading.Thread(target=Run_motor_control, name='t1') 
    t2 = threading.Thread(target=Face_detect, name='t2')
    # starting threads 
    t1.start() 
    t2.start() 
    # wait until all threads finish 
    t1.join() 
    t2.join() 
# When everything is done, release the capture

