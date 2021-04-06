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
String MyImg = "scada.jpg";
String MyImg1 = "30_tank.jpg";

String ButtonPAth[] ={MyImg};
int level_counter =0;
public void setup() {
  size(720, 480, JAVA2D);
 
  // Place your setup code here  70, 93, 240, 320,
  //355, 93, 240, 320
  BinImg1 = loadImage(MyImg); 
  BinImg2 = loadImage(MyImg1);
}

public void draw() {
  background(249);
  BinImg1 = loadImage(MyImg); 
  BinImg2 = loadImage(MyImg1); 
  image(BinImg1, 0, 0, 720, 480);
  image(BinImg2, 0, 0, 310, 480);

}
