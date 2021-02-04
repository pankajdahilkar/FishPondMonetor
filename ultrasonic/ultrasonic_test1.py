import RPi.GPIO as GPIO
import time

def get_water_level():
    TRIG = 16
    ECHO = 18
    GPIO.setup(TRIG,GPIO.OUT)
    GPIO.setup(ECHO,GPIO.IN)
    GPIO.output(TRIG, False)
    print("Calibrating.....")
    time.sleep(2)
    print ("Place the object......")
    max_water_level = 24
    min_water_level = 13
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)
    while GPIO.input(ECHO)==0:
      pulse_start = time.time()

    while GPIO.input(ECHO)==1:
      pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 17150
    distance = round(distance+1.15, 2)
    print(distance)
    distance_actual = distance - min_water_level
    level_water = 11 - distance_actual;
    percenatge_water_level = level_water *10
    if  percenatge_water_level < 0:
       percenatge_water_level =0
    print("water level= ",int(percenatge_water_level)," %")
    url = "https://world4.tech/fsecure/upload.php?val="+str(int(percenatge_water_level))+" %"
    resp =req.get(url)
    print(resp.text)
    time.sleep(2)
    return (int(percenatge_water_level))

if __name__ == "__main__":
    GPIO.setmode(GPIO.BOARD)
    while True:
        get_water_level()
        

