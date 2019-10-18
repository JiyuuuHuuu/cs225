#include "Image.h"
#include "StickerSheet.h"
#include <stdlib.h>
#include <math.h>

int main()
{
  Image base;
  base.readFromFile("base.png");
  Image sticker1;
  sticker1.readFromFile("sticker1.png");
  sticker1.scale(0.1);
  Image sticker2;
  sticker2.readFromFile("sticker2.png");
  sticker2.scale(0.22);
  Image sticker3;
  sticker3.readFromFile("sticker3.png");
  sticker3.scale(0.1);
  Image sticker4;
  sticker4.readFromFile("sticker4.png");
  sticker4.scale(0.22);

  StickerSheet s1(base, 30);

  for (int i = 0; i < 30; i++)
  {
    int num = rand() % 4;
    int two = rand() % 2;
    unsigned a, b;
    if (two == 0)
    {
      a = (rand() % 1000 + 1236)/2;
      b = (rand() % 360 + 860)/2;
    }
    else
    {
      a = (rand() % 1000)/2;
      b = (rand() % 360 + 860)/2;
    }
    switch(num)
    {
      case 0:
        s1.addSticker(sticker1, a, b);
        break;
      case 1:
        s1.addSticker(sticker2, a, b);
        break;
      case 2:
        s1.addSticker(sticker3, a, b);
        break;
      default:
        s1.addSticker(sticker4, a, b);
    }
  }

  Image final = s1.render();
  final.writeToFile("myImage.png");

  /*
  Image test;
  test.readFromFile("base.png");
  test.scale(1280,400);
  test.writeToFile("testscale.png");
  return 0;
  */
}
