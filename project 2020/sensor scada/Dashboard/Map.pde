class Map
{
  int posX, posY, size;
  float [] [] posHistory;
  int arrSize = 100;

  Map (int iposX, int iposY, int isize)
  {
    posX = iposX;
    posY = iposY;
    size = isize;
    posHistory = new float [100][2];
    for (int i = 1 ; i < (arrSize-1) ; i++)
    {
      posHistory[i-1][0] = 0;
      posHistory[i-1][1] = 0;
    }
  }

  void display (int xpos, int ypos)
  {
    rect (posX, posY, size, size);
    noFill();
    beginShape();
    if (posHistory[0][0] != map (xpos, 0, 500, 0, size) && posHistory[0][1] != map (ypos, 0, 500, 0, size))
    {
      posHistory[0][0] = map (xpos, 0, 500, 0, size);
      posHistory[0][1] = map (ypos, 0, 500, 0, size);
      for (int i = 1 ; i <= (arrSize-1) ; i++)
      {
        posHistory[arrSize-i][0] = posHistory[arrSize-i-1][0];
        posHistory[arrSize-i][1] = posHistory[arrSize-i-1][1];
      }
      for (int i = 0 ; i < (arrSize-1) ; i++)
      {
        curveVertex(posX + size * 0.1 + posHistory[i][0], posY + size * 0.1 + posHistory[i][1]);
      }
      endShape();
    }
  }
}
