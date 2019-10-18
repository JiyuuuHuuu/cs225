#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <math.h>
#include <stdlib.h>

using cs225::HSLAPixel;
using cs225::PNG;


void rotate(std::string inputFile, std::string outputFile)
{
  // TODO: Part 2
  cs225::PNG png; //create a new png variable

  png.readFromFile(inputFile); //get the inputFile

  unsigned y;
  for (unsigned x = 0; x < png.width(); x++)
  {
    for (y = 0; y < png.height()/2; y++)
    {
      HSLAPixel & pixel = png.getPixel(x, y);
      HSLAPixel & mirror = png.getPixel(png.width() - 1 - x, png.height() - 1 - y);

      double h, s, l, a;
      h = pixel.h;
      s = pixel.s;
      l = pixel.l;
      a = pixel.a;

      pixel.h = mirror.h;
      pixel.s = mirror.s;
      pixel.l = mirror.l;
      pixel.a = mirror.a;

      mirror.h = h;
      mirror.s = s;
      mirror.l = l;
      mirror.a = a;
    }
  }

  if(png.height() % 2 != 0) //check for special case (height is an odd number)
  {
    for (unsigned x = 0; x < png.width()/2; x++)
    {
      HSLAPixel & pixel = png.getPixel(x, y);
      HSLAPixel & mirror = png.getPixel(png.width() - 1 - x, png.height() - 1 - y);

      double h, s, l, a;
      h = pixel.h;
      s = pixel.s;
      l = pixel.l;
      a = pixel.a;

      pixel.h = mirror.h;
      pixel.s = mirror.s;
      pixel.l = mirror.l;
      pixel.a = mirror.a;

      mirror.h = h;
      mirror.s = s;
      mirror.l = l;
      mirror.a = a;
    }
  }

  png.writeToFile(outputFile);
}


cs225::PNG myArt(unsigned int width, unsigned int height)
{
  cs225::PNG png(width, height);
  // TODO: Part 3

  for (unsigned x = 0; x < png.width(); x++)
  {
    for (unsigned y = 0; y < png.height(); y++)
    {
      HSLAPixel & pixel = png.getPixel(x, y);
      if(x*y != 0)
      {
        HSLAPixel & a = png.getPixel(x - 1, y);
        HSLAPixel & b = png.getPixel(x, y - 1);
        pixel.h = (a.h + b.h)/2.0 + rand()%5 - 2;
      }
      else if(x != 0)
      {
        HSLAPixel & a = png.getPixel(x - 1, y);
        pixel.h = a.h + rand()%5 - 2;
      }
      else if(y != 0)
      {
        HSLAPixel & b = png.getPixel(x, y - 1);
        pixel.h = b.h + rand()%5 - 2;
      }
      else
      {
        pixel.h = 180;
      }
      pixel.s = 1;
      pixel.l = 0.5;
      pixel.a = 1;
    }
  }

  return png;
}
