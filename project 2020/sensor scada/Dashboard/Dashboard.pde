import processing.serial.*;

Serial myPort;           // Create object from Serial class
char [] inVal = new char[4];      // Data received from the serial port
PFont f;
Dial dialA, dialB, dialC,dialD;
Bar barA;
Map mapA;
int i = 0;
String[] q={"", "", "", "0", "100", "88","","","","",""};
int temp;
int moisture,humidity,CO2;
int Fan_stat;
PImage FanImg;
String MyImg = "FAN_OFF.png";

void setup ()
{
 frameRate(100);
  size (1000, 700);
 clock_init();
 // println (Serial.list());
  //String portName = Serial.list()[1];
  //myPort = new Serial(this, portName, 57600);
 println(Serial.list());
  try {
  myPort = new Serial(this, Serial.list()[4], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
    } catch(Exception e) {
    println(e.toString());
  }
  dialA = new Dial (300, 180, 180, 0, 100, "CO2 Value");
  dialB = new Dial (300, 540, 180, 0, 180, "Temp C");
  dialC = new Dial (300, 180, 480, 0, 100, "Moisture");
  dialD = new Dial (300, 540, 480, 0, 100, "Humidity");
  // mapA = new Map (100, 400, 300);
}

void draw()
{
  background(220);
  textSize(26); 
  fill(0, 0, 250);
  text("Food storage  monitor system", 500, 20); 
  fill(190, 0, 0);
  fill(255, 0, 0);
  noStroke();
  dialA.display(CO2*2.5);
  dialB.display(temp*1.34);
  // barA.display (inVal[2]);
  dialC.display(moisture*2.5);
  dialD.display(humidity*2.5);

textSize(19); 
  text("CO2 Value = "+CO2+"%", 180, 310);
  text("Temeperature = "+temp+" Degree", 540, 310);
  text("Humidity = "+humidity+"%", 540, 620);
  text("Moisture Level ="+moisture+"%", 180, 620);
  // mapA.display (20, 150);
  
   if(Fan_stat == 1)
   {
   MyImg = "FAN_ON.png";  
    fill(0, 200, 0);
   text("FAN ON", 850, 620);
   }else
   {
   MyImg = "FAN_OFF.png"; 
    text("FAN OFF", 850, 620);
   }
    FanImg = loadImage(MyImg);
   image(FanImg, 740, 366, 230, 230);

 clock_dis();
  Display_time();

}




void serialEvent(Serial port) {
  try {
    String inData = port.readStringUntil('\n');
    inData = trim(inData);                 // cut off white space (carriage return)
    if (inData.charAt(0) == 'P') {           // leading 'S' means Pulse Sensor data packet
      q[4] = inData.substring(1);        // cut off the leading 'S'
      // convert the string to usable int
    }
    if (inData.charAt(0) == 'A') {          // leading 'B' for BPM data
      q[1] = inData.substring(1);        // cut off the leading 'B'
    Fan_stat =int(   q[1]);  // begin heart image 'swell' timer
    }
    if (inData.charAt(0) == 'B') {            // leading 'Q' means IBI data
      q[2] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
    }
    if (inData.charAt(0) == 'C') {            // leading 'Q' means IBI data
      q[3] = inData.substring(1);        // cut off the leading 'Q'
      CO2 =int(q[3]);
      // convert the string to usable int
    }
     if (inData.charAt(0) == 'D') {            // leading 'Q' means IBI data
      q[5] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
    }
    if (inData.charAt(0) == 'T') {            // leading 'Q' means IBI data
      q[6] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
      temp = int(q[6]);
    }
    if (inData.charAt(0) == 'H') {            // leading 'Q' means IBI data
      q[7] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
            humidity = int(q[7]);

    }
  
     if (inData.charAt(0) == 'M') {            // leading 'Q' means IBI data
      q[9] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
      moisture =int(q[9]);
    }
  } 
  catch(Exception e) {
    println(e.toString());
  }
}// 
