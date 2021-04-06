class Dial
{
  int radius = 25;
  int col = 0;
  int posX = 25, posY = 25;
  int val = 0;
  int [] vals;
  PFont f, f2;
  String face;

  Dial (int iSize, int iPosX, int iPosY, int rangeLow, int rangeHigh, String iFace)
  {
    vals = new int[11];
    face = iFace;
    f = createFont("Arial", iSize/15);
    f2 = createFont("Arial", iSize/15);
    textFont(f);
    textAlign(CENTER, CENTER);
    radius =iSize/2;
    posX = iPosX;
    posY = iPosY;
    for (int i = 0 ; i <= 10 ; i++)
      vals [i] = rangeLow + (rangeHigh - rangeLow) * i / 10;
  }

  void display (float iVal)
  {
    val = int(iVal);
    float radians = (map(val, 0, 254, 0, 3 * HALF_PI) + QUARTER_PI * 3);
    fill(255);
    strokeWeight(3);
    stroke (0);
    ellipse(posX, posY, radius*1.5, radius*1.5);
    fill (80);
    ellipse(posX, posY, radius*1.3, radius*1.3);
    fill(200, 0, 0);
    textFont(f2);
    text(face, posX, posY - radius/4);
    textFont(f);
    for (int i = 0 ; i <= 10 ; i++) {
      stroke (0);
      strokeWeight(2);
      line(posX + cos(QUARTER_PI * 3 + (i * 3 * PI / 20)) * radius*0.65, posY + sin(QUARTER_PI * 3 + (i * 3 * PI / 20)) * radius*0.65, posX + cos(QUARTER_PI * 3 + (i * 3 * PI / 20)) * radius * 0.75, posY + sin(QUARTER_PI * 3 + (i * 3 * PI / 20)) * radius * 0.75);
      fill(0, 0, 255);
      text(vals[i], posX + cos(QUARTER_PI * 3 + (i * 3 * PI / 20)) * radius * .9, posY + sin(QUARTER_PI * 3 + (i * 3 * PI / 20)) * radius * .9);
    }
    stroke(0);
    strokeWeight(5);
    line(posX, posY, posX + cos(radians) * radius * 0.7, posY + sin(radians) * radius * 0.7);
    fill(255, 0, 0);
    strokeWeight(2);
    ellipse(posX, posY, radius*0.1, radius*0.1);
    stroke(255, 0, 0);
    line(posX, posY, posX + cos(radians) * radius * 0.7, posY + sin(radians) * radius * 0.7);
  }
}
