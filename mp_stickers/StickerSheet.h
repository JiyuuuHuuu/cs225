/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet
{
  private:
    Image base;
    Image * stickers;
    unsigned * xCoordinate;
    unsigned * yCoordinate;
    unsigned count;
    unsigned maxStickers;
    void destroy();
    void copy(StickerSheet const & other);

  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    unsigned addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);
    Image render() const;
};
