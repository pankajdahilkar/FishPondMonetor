#from picamera import PiCamera
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

#https://www.google.com/settings/security/lesssecureapps

def read_iot_cmd():
    resp = req.get("https://world4.tech/fsecure/machinetate.txt")
    print(resp.text)
    cmd = int(resp.text)
    return cmd


def send_email():
    toaddr = 'kishorlanjewar66@gmail.com'
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
LED = 40 # pin40
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD) # We are accessing GPIOs according to their physical location
GPIO.setup(LED, GPIO.OUT) # We have set our LED pin mode to output
GPIO.output(LED, GPIO.LOW) # When it will start then LED will be OFF
 
while(True):
    cmd_c = read_iot_cmd()
    if(cmd_c == 1):
        GPIO.output(LED, GPIO.HIGH) # led on
        print("Motor ON")
        resp =req.get("https://world4.tech/fsecure/upload.php?val=Motor%20ON")
        print(resp.text)
    elif(cmd_c == 0):
        GPIO.output(LED, GPIO.LOW)
        print("Motor OFF")
        resp =req.get("https://world4.tech/fsecure/upload.php?val=Motor%20OFF")
        print(resp.text)
    sleep(2)
    
