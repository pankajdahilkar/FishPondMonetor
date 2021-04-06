int V1_On_time_hr=0;
int V1_On_time_min=0;
int V1_Off_time_hr=0;
int V1_Off_time_min=0;

int V2_On_time_hr=0;
int V2_On_time_min=0;
int V2_Off_time_hr=0;
int V2_Off_time_min=0;

int V3_On_time_hr=0;
int V3_On_time_min=0;
int V3_Off_time_hr=0;
int V3_Off_time_min=0;
long new_time_diff=1000;
long LastMillis_1;
int cx, cy;
float secondsRadius;
float minutesRadius;
float hoursRadius;
float clockDiameter;
PImage BinImg1;
PImage V1_Img;
PImage V2_Img;
PImage V3_Img;
long LastMillis =0;
long NowMIlls =0;
long timdiff =1000;
String MyImg1 = "30_tank.jpg";
String MyImg2 = "V1_ON.png";
String MyImg3 = "V1_OFF.png";
int imgx_V1=499, imgy_V1=140;
int imgx_V2=499, imgy_V2=420;
int imgx_V3=650, imgy_V3=280;
int toggle =0;
int V1_flag=0;
int V2_flag=0;
int V3_flag=0;
int Pump_flag=0;

void clock_init()
{

  int radius = 120;
  secondsRadius = radius * 0.72;
  minutesRadius = radius * 0.60;
  hoursRadius = radius * 0.50;
  clockDiameter = radius * 1.8;

  cx = 850;
  cy = 180;
}
void clock_dis()
{
  // background(0);

  // Draw the clock background
  fill(80);
  noStroke();
  ellipse(cx, cy, clockDiameter, clockDiameter);

  // Angles for sin() and cos() start at 3 o'clock;
  // subtract HALF_PI to make them start at the top
  float s = map(second(), 0, 60, 0, TWO_PI) - HALF_PI;
  float m = map(minute() + norm(second(), 0, 60), 0, 60, 0, TWO_PI) - HALF_PI; 
  float h = map(hour() + norm(minute(), 0, 60), 0, 24, 0, TWO_PI * 2) - HALF_PI;

  // Draw the hands of the clock
   stroke (0);
   strokeWeight(2);
  stroke(255,0,0);
  
  //strokeWeight(1);
  line(cx, cy, cx + cos(s) * secondsRadius, cy + sin(s) * secondsRadius);
  strokeWeight(2);
  line(cx, cy, cx + cos(m) * minutesRadius, cy + sin(m) * minutesRadius);
  strokeWeight(4);
  line(cx, cy, cx + cos(h) * hoursRadius, cy + sin(h) * hoursRadius);

  // Draw the minute ticks
  strokeWeight(2);
  beginShape(POINTS);
  for (int a = 0; a < 360; a+=6) {
    float angle = radians(a);
    float x = cx + cos(angle) * secondsRadius;
    float y = cy + sin(angle) * secondsRadius;
    vertex(x, y);
  }
  endShape();
}




void Display_time()
{
  int time_x = 850;
  int time_y = 310;

  int d = day();    // Values from 1 - 31
  int mo = month();  // Values from 1 - 12
  int y = year();   // 2003, 2004, 2005, etc.
  int s = second();  // Values from 0 - 59
  int m = minute();  // Values from 0 - 59
  int h = hour();    // Values from 0 - 23
  textSize(26); 
 // text("Smart Irrigation system scada", 250, 20); 
  if (m<10 && s<10)
  {
    text(h + ":0"+ m+":0"+s, time_x, time_y);
  } else if (m<10) {  
    text(h + ":0"+ m+":"+s, time_x, time_y);
  } else if (s<10) {  
    text(h + ":"+ m+":0"+s, time_x, time_y);
  } else text(h + ":"+ m+":"+s, time_x, time_y);
  textSize(15);
}
