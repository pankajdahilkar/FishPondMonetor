// Need G4P library
import g4p_controls.*;
// You can remove the PeasyCam import if you are not using
// the GViewPeasyCam control or the PeasyCam library.
import peasy.*;
import processing.serial.*;
Serial myPort;        // The serial port


public void setup() {
  size(900, 520, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
  clock_init();
  BinImg1 = loadImage(MyImg); 
  V1_Img = loadImage(MyImg1);
  V2_Img = loadImage(MyImg2); 
  V3_Img = loadImage(MyImg3);
   println(Serial.list());
  try {
  myPort = new Serial(this, Serial.list()[4], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
    } catch(Exception e) {
    println(e.toString());
  }
  
  
}

public void draw() {
  // background(255);
  background(255);
  if(Tank<=30)MyImg="30_tank.jpg";
  if(Tank<=90 && Tank>30)MyImg="60_tank.jpg";
  if( Tank>90)MyImg="90_tank.jpg";
  
  BinImg1 = loadImage(MyImg); 
  image(BinImg1, 0, 25, 720, 480);

  animate_valves();
  clock_dis();
  Display_time();
check_timing_valve();
  textSize(19); 
  if (V1_flag ==1) {
    fill(0, 255, 0);
    text("VALVE ON", 380, 200);
  } else 
  {
    fill(255, 0, 0);
    text("VALVE OFF", 380, 200);
  }
  if (V2_flag ==1) {
    fill(0, 255, 0);
     text("VALVE ON", 380, 450); 
  } else 
  {
    fill(255, 0, 0);
     text("VALVE OFF", 380, 450); 
  }
   if (V3_flag ==1) {
    fill(0, 255, 0);
  text("VALVE ON", 600, 380);
  } else 
  {
    fill(255, 0, 0);
  text("VALVE OFF", 600, 380);
  }
   if (Pump_flag ==1) {
    fill(0, 255, 0);
  text("PUMP ON", 20, 270);
  } else 
  {
    fill(255, 0, 0);
  text("PUMP OFF", 20, 270);
  }
 
 fill(190, 0, 0);
  text("Water Level = "+Tank+"%", 20, 400);
  text("Temeperature = "+temp+"Degree", 20, 425);
  text("Humidity = "+humidity+"%", 20, 450);
  text("Moisture Level ="+moisture+"%", 20, 475);
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI() {
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
      // begin heart image 'swell' timer
    }
    if (inData.charAt(0) == 'B') {            // leading 'Q' means IBI data
      q[2] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
    }
    if (inData.charAt(0) == 'C') {            // leading 'Q' means IBI data
      q[3] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
    }
     if (inData.charAt(0) == 'D') {            // leading 'Q' means IBI data
      q[5] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
    }
    if (inData.charAt(0) == 'T') {            // leading 'Q' means IBI data
      q[6] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
      temp = float(q[6]);
    }
    if (inData.charAt(0) == 'H') {            // leading 'Q' means IBI data
      q[7] = inData.substring(1);        // cut off the leading 'Q'
      // convert the string to usable int
            humidity = int(q[7]);

    }
    if (inData.charAt(0) == 'W') {            // leading 'Q' means IBI data
      q[8] = inData.substring(1);        // cut off the leading 'Q'
       Tank = int(q[8]);
      println("Water level = "+ Tank);
     
      // convert the string to usable int
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
}// END OF
