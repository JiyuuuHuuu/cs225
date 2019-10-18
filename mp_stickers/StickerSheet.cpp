#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
  //std::cout<<max<<std::endl;
  base = picture;
  //std::cout<<"3 lines"<<std::endl;
  count = 0;
  maxStickers = max;
  stickers = new Image[max];
  xCoordinate = new unsigned[max];
  yCoordinate = new unsigned[max];
}

void StickerSheet::destroy()
{
  //std::cout<<maxStickers<<std::endl;
  //std::cout<<"3"<<std::endl;
  if(maxStickers != 0)
  {
    delete[] stickers;
    delete[] xCoordinate;
    delete[] yCoordinate;
    count = 0;
    maxStickers = 0;
  }
}

StickerSheet::~StickerSheet()
{

  destroy();
}

void StickerSheet::copy(StickerSheet const & other)
{
  maxStickers = 0;
  //std::cout<<"1"<<std::endl;
  destroy();
  //std::cout<<"2"<<std::endl;
  base = other.base;
  count = other.count;
  maxStickers = other.maxStickers;
  stickers = new Image[maxStickers];
  xCoordinate = new unsigned[maxStickers];
  yCoordinate = new unsigned[maxStickers];
  for (unsigned i = 0; i < maxStickers; i++)
  {
    xCoordinate[i] = other.xCoordinate[i];
    yCoordinate[i] = other.yCoordinate[i];
    stickers[i] = other.stickers[i];
  }
}

StickerSheet::StickerSheet(const StickerSheet &other)
{
  copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other)
{
  if (this != &other)
  {
    copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
  //std::cout<<"1"<<std::endl;
  if(max == maxStickers)
  {
    return;
  }
  Image * copier = new Image[max];
  unsigned * xCopy = new unsigned[max];
  unsigned * yCopy = new unsigned[max];
  //std::cout<<"1"<<std::endl;
  unsigned end;
  if(max > maxStickers)
  {
    end = maxStickers;
  }
  else
  {
    end = max;
    count = max;
  }
  for (unsigned i = 0; i < end; i++)
  {
    xCopy[i] = xCoordinate[i];
    yCopy[i] = yCoordinate[i];
    copier[i] = stickers[i];
  }

  delete[] stickers;
  delete[] xCoordinate;
  delete[] yCoordinate;
  maxStickers = max;

  stickers = copier;
  xCoordinate = xCopy;
  yCoordinate = yCopy;
  //std::cout<<maxStickers<<std::endl;
}

unsigned StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
  if(count >= maxStickers)
  {
    return -1;
  }
  //std::cout<<x<<std::endl;
  stickers[count] = sticker;
  xCoordinate[count] = x;
  yCoordinate[count] = y;
  count++;
  //std::cout<<maxStickers<<std::endl;
  return 0;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
  if (index >= count)
  {
    return false;
  }
  if(x > base.width() || y > base.height())
  {
    return false;
  }
  xCoordinate[index] = x;
  yCoordinate[index] = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index)
{
  if (index == 0)
  {
    Image * copy = new Image[maxStickers];
    unsigned * xCopy = new unsigned[maxStickers];
    unsigned * yCopy = new unsigned[maxStickers];
    for (unsigned i = 0; i < count - 1; i++)
    {
      copy[i] = stickers[i + 1];
      xCopy[i] = xCoordinate[i + 1];
      yCopy[i] = yCoordinate[i + 1];
      delete[] stickers;
      delete[] xCoordinate;
      delete[] yCoordinate;
      stickers = copy;
      xCoordinate = xCopy;
      yCoordinate = yCopy;
    }
  }
  else if (index < count - 1)
  {
    for (unsigned i = index; i < count - 1; i++)
    {
      stickers[i] = stickers[i + 1];
      xCoordinate[i] = xCoordinate[i + 1];
      yCoordinate[i] = yCoordinate[i + 1];
    }
  }
  count--;
  //writeToFile("output.png");
}

Image * StickerSheet::getSticker(unsigned index)
{
  if (index >= count)
  {
    return NULL;
  }
  return &(stickers[index]);
}

Image StickerSheet::render() const
{
  Image final = base;
  for (unsigned i = 0; i < count; i++)
  {
    unsigned xOffset = xCoordinate[i];
    unsigned yOffset = yCoordinate[i];
    unsigned xEnd = base.width();
    if (xEnd > xOffset + stickers[i].width())
    {
      xEnd = xOffset + stickers[i].width();
    }
    unsigned yEnd = base.height();
    if (yEnd > yOffset + stickers[i].height())
    {
      yEnd = yOffset + stickers[i].height();
    }
    for (unsigned x = xOffset; x < xEnd; x++)
    {
      for (unsigned y = yOffset; y < yEnd; y++)
      {
        cs225::HSLAPixel & pixel = final.getPixel(x, y);
        cs225::HSLAPixel & cover = stickers[i].getPixel(x - xOffset,y - yOffset);
        if(cover.a == 0)
        {
          continue;
        }
        pixel = cover;
      }
    }
  }
  //final.writeToFile("output.png");
  return final;
}
