// Need G4P library
import g4p_controls.*;
// You can remove the PeasyCam import if you are not using
// the GViewPeasyCam control or the PeasyCam library.
PImage BinImg1;
PImage BinImg2;
long LastMillis =0;
long NowMIlls =0;
long timdiff =1000;
import peasy.*;
String MyImg = "0.jpg";
String MyImg1 = "0.jpg";

String ButtonPAth[] ={MyImg};
int level_counter =0;
int level_counter1 =0;

String data;
String data1;

public void setup() {
  size(820, 520, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here  70, 93, 240, 320,
  //355, 93, 240, 320
  BinImg1 = loadImage(MyImg); 
  BinImg2 = loadImage(MyImg1);
}

public void draw() {
  background(249);
  BinImg1 = loadImage(MyImg); 
  BinImg2 = loadImage(MyImg1); 
  image(BinImg1, 80, 93, 240, 320);
  image(BinImg2, 500, 93, 240, 320);
  textSize(26); 
  fill(0, 200, 0);
  text("Smart Waste Management Viewer", 230, 20); 
  fill(190, 0, 0);
  text(" Bin_1 "+data+"%", 120, 70);
  text("Bin_2 "+data1+"%", 560, 70);
  text("Location 1", 100, 470);
  text("Location 2", 520, 470);
  NowMIlls = millis();
  if (NowMIlls - LastMillis > timdiff)
  {
    //println(NowMIlls);
    LastMillis = NowMIlls;
    thread("Request_Bin1");
    thread("Request_Bin2");
  }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI() {
}

void Request_Bin1()
{
  try {
    check_bin_1();
  } 
  catch(Exception e) {
    println(e.toString());
  }
}

void Request_Bin2()
{
  try {
    check_bin_2();
  } 
  catch(Exception e) {
    println(e.toString());
  }
}


void check_bin_1()
{
  String[] lines = loadStrings("http://192.168.43.184/");
  String str = lines[0];
  int p1 = str.indexOf("<h4>");
  int p2 = str.indexOf("</h4>");
  //println("index of <h4>  "+ p1 +"  index of </h4>  "+ p2 );
  data = str.substring(p1+4, p2);
  println("data =" + data + " int val = "+ int(data)); 
  level_counter = int(data)/10 ;
  switch(level_counter)
  {
  case 0:
    MyImg = "0.jpg";
    break;
  case 1:
    MyImg = "0.jpg";
    break;
  case 2:
    MyImg = "20.jpg";
    break;
  case 3:
    MyImg = "30.jpg";
    break;
  case 4:
    MyImg = "30.jpg";
    break;
  case 5:
    MyImg = "50.jpg";
    break;
  case 6:
    MyImg = "60.jpg";
    break;
  case 7:
    MyImg = "70.jpg";
    break;
  case 8:
    MyImg = "70.jpg";
    break;
  case 9:
    MyImg = "90.jpg";
    break;
  case 10:
    MyImg = "100.jpg";
    break;
  };
}
void check_bin_2()
{
  String[] lines = loadStrings("http://192.168.43.186/");
  String str = lines[0];
  int p1 = str.indexOf("<h4>");
  int p2 = str.indexOf("</h4>");
  //println("index of <h4>  "+ p1 +"  index of </h4>  "+ p2 );
  data1 = str.substring(p1+4, p2);
  println("data =" + data1 + " int val = "+ int(data1)); 
  level_counter1 = int(data1)/10 ;
  switch(level_counter1)
  {
  case 0:
    MyImg1 = "0.jpg";
    break;
  case 1:
    MyImg1 = "0.jpg";
    break;
  case 2:
    MyImg1 = "20.jpg";
    break;
  case 3:
    MyImg1 = "30.jpg";
    break;
  case 4:
    MyImg1 = "30.jpg";
    break;
  case 5:
    MyImg1 = "50.jpg";
    break;
  case 6:
    MyImg1 = "60.jpg";
    break;
  case 7:
    MyImg1 = "70.jpg";
    break;
  case 8:
    MyImg1 = "70.jpg";
    break;
  case 9:
    MyImg1 = "90.jpg";
    break;
  case 10:
    MyImg1 = "100.jpg";
    break;
  };
}
