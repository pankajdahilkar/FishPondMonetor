# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy
from time import sleep
import smtplib
import time
from datetime import datetime
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import RPi.GPIO as GPIO
import time
import requests as req

def Face_detect():
        #Load a cascade file for detecting faces
        faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
        # initialize the camera and grab a reference to the raw camera capture
        camera = PiCamera()
        camera.resolution = (640, 480)
        camera.framerate = 32
        rawCapture = PiRGBArray(camera, size=(640, 480))
        # allow the camera to warmup
        time.sleep(0.1)
        # capture frames from the camera
        for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
                # grab the raw NumPy array representing the image, then initialize the timestamp
                # and occupied/unoccupied text
                image = frame.array
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
                        # show the frame
                cv2.imshow("Frame", image)
                key = cv2.waitKey(1) & 0xFF
                # clear the stream in preparation for the next frame
                rawCapture.truncate(0)
                # if the `q` key was pressed, break from the loop
                if key == ord("q"):
                        break

def read_iot_cmd():
    resp = req.get("https://world4.tech/fsecure/machinetate.txt")
    print(resp.text)
    cmd = int(resp.text)
    return cmd


def send_email():
    toaddr = 'smitagawade1234@gmail.com'
    me = 'smitagawade1234@gmail.com'
    Subject='security alert'
    subject='Security allert!!'
    msg = MIMEMultipart()
    msg['Subject'] = subject
    msg['From'] = me
    msg['To'] = toaddr
    fp= open('GPIO.png','rb')
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

#print("Sending Email")
#send_email()
def Run_motor_control():
    MAIN_MOTOR = 40 # pin40
    DRAIN_MOTOR = 38
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD) # We are accessing GPIOs according to their physical location
    GPIO.setup(MAIN_MOTOR, GPIO.OUT) # We have set our MAIN_MOTOR pin mode to output
    GPIO.output(MAIN_MOTOR, GPIO.LOW) # When it will start then MAIN_MOTOR will be OFF \
    GPIO.setup(DRAIN_MOTOR, GPIO.OUT) # We have set our MAIN_MOTOR pin mode to output
    GPIO.output(DRAIN_MOTOR, GPIO.LOW) # When it will start then MAIN_MOTOR will be OFF 
    while(True):
        cmd_c = read_iot_cmd()
        if(cmd_c == 1):
            #GPIO.output(MAIN_MOTOR, GPIO.HIGH) # led on
            print("MAin Motor ON")
            resp =req.get("https://world4.tech/fsecure/pumpdata.php?val=MAIN%20Motor%20ON")
            print(resp.text)
        elif(cmd_c == 0):
            #GPIO.output(MAIN_MOTOR, GPIO.LOW)
            print("Main Motor OFF")
            resp =req.get("https://world4.tech/fsecure/pumpdata.php?val=MAIN%20Motor%20OFF")
            print(resp.text)
        elif(cmd_c == 3):
            #GPIO.output(DRAIN_MOTOR, GPIO.HIGH)
            print("DRAIN Motor ON")
            resp =req.get("https://world4.tech/fsecure/pumpdata.php?val=DRAIN%20Motor%20ON")
            print(resp.text)
        elif(cmd_c == 4):
            #GPIO.output(DRAIN_MOTOR, GPIO.LOW)
            print("DRAIN Motor OFF")
            resp =req.get("https://world4.tech/fsecure/pumpdata.php?val=DRAIN%20Motor%20OFF")
            print(resp.text)
        sleep(2)

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

#Face_detect()
