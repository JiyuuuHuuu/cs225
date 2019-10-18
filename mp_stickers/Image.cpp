#include "Image.h"

void Image::darken()
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.l -= 0.1;
      if (pixel.l < 0) //set luminence in range [0,1]
      {
        pixel.l = 0;
      }
    }
  }
}


void Image::darken(double amount)
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.l -= amount;
      if (pixel.l < 0) //set luminence in range [0,1]
      {
        pixel.l = 0;
      }
    }
  }
}


void Image::desaturate()
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.s -= 0.1;
      if (pixel.s < 0) //set luminence in range [0,1]
      {
        pixel.s = 0;
      }
    }
  }
}


void Image::desaturate(double amount)
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.s -= amount;
      if (pixel.s < 0) //set luminence in range [0,1]
      {
        pixel.s = 0;
      }
    }
  }
}

void Image::grayscale()
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.s = 0;
    }
  }
}

void Image::illinify()
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      if(pixel.h >= 288 || pixel.h <= 108)
      {
        pixel.h = 11;
      }
      else
      {
        pixel.h = 216;
      }
    }
  }
}


void Image::lighten()
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.l += 0.1;
      if (pixel.l > 1) //set luminence in range [0,1]
      {
        pixel.l = 1;
      }
    }
  }
}


void Image::lighten(double amount)
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.l += amount;
      if (pixel.l > 1) //set luminence in range [0,1]
      {
        pixel.l = 1;
      }
    }
  }
}


void Image::rotateColor(double degrees)
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.h += degrees;
      if (pixel.h > 360) //set hue in range [0,360]
      {
        pixel.h -= 360;
      }
      else if(pixel.h < 0)
      {
        pixel.h += 360;
      }
    }
  }
}


void Image::saturate()
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.s += 0.1;
      if (pixel.s > 1) //set luminence in range [0,1]
      {
        pixel.s = 1;
      }
    }
  }
}


void Image::saturate(double amount)
{
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.s += amount;
      if (pixel.s > 1) //set luminence in range [0,1]
      {
        pixel.s = 1;
      }
    }
  }
}


void Image::scale(double factor)
{
  PNG copy = *this;
  resize(width() * factor, height() * factor);
  for (unsigned x = 0; x < width(); x++)
  {
    for (unsigned y = 0; y < height(); y++)
    {
      int i = x/factor;
      int j = y/factor;
      cs225::HSLAPixel & pixcopy = copy.getPixel(i, j);
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel = pixcopy;
    }
  }
}


void Image::scale(unsigned w, unsigned h)
{
  PNG copy = *this;
  double facx = (double)w/(double)width();
  double facy = (double)h/(double)height();
  double factor;
  if(facx >= facy)
  {
    factor = facy;
  }
  else
  {
    factor = facx;
  }
  scale(factor);
}
