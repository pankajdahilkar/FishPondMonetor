import time
import requests as req
max_water_level = 18
min_water_level = 5

for distance in range(19):
    distance = round(distance+1.15, 2)
    distance_actual = distance - 5
    level_water = 13 - distance_actual;
    percenatge_water_level = level_water *10
    if  percenatge_water_level < 0:
       percenatge_water_level =0
    print("distance = ",distance," water level= ",percenatge_water_level," %")
    url = "https://world4.tech/fsecure/upload.php?val="+str(int(percenatge_water_level))+" %"
    resp =req.get(url)
    print(resp.text)
    time.sleep(10)
    
