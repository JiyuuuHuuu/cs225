#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace std;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2)
{
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = NULL;
}

// ImageTraversal::Iterator::~Iterator()
// {
//   delete traversal;
//   delete myImage;
// }

ImageTraversal::Iterator::Iterator(ImageTraversal & input, const Point start, const PNG* png, double tolerance):
myImage(png), start(start), tolerance_(tolerance)
{
  traversal = &input;
  current = traversal->peek();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++()
{
  /** @todo [Part 1] */
  if (traversal != NULL)
  {
    if (!traversal->empty())
    {
      current = traversal->pop();

      int x = current.x;
      int y = current.y;

      HSLAPixel temp;
      HSLAPixel startPx;
      startPx = myImage->getPixel(start.x, start.y);

      if (x + 1 < (int)myImage->width())
      {
        temp = myImage->getPixel(x + 1, y);
        if (calculateDelta(temp, startPx) < tolerance_)
          traversal->add(Point(x + 1, y));
      }
      if (y + 1 < (int)myImage->height())
      {
        temp = myImage->getPixel(x, y + 1);
        if (calculateDelta(temp, startPx) < tolerance_)
          traversal->add(Point(x, y + 1));
      }
      if (x - 1 >= 0)
      {
        temp = myImage->getPixel(x - 1, y);
        if (calculateDelta(temp, startPx) < tolerance_)
          traversal->add(Point(x - 1, y));
      }
      if (y - 1 >= 0)
      {
        temp = myImage->getPixel(x, y - 1);
        if (calculateDelta(temp, startPx) < tolerance_)
          traversal->add(Point(x, y - 1));
      }
      if (traversal->empty())
        traversal = NULL;
    }
    else
    {
      traversal = NULL;
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  if (traversal != NULL)
    return traversal->peek();

  return Point(0, 0);
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other)
{
  /** @todo [Part 1] */
  // cout<<"1"<<endl;
  if (traversal != NULL && other.traversal != NULL)
    return (!(traversal->peek() == other.traversal->peek()));

  if (traversal == NULL && other.traversal == NULL)
    return false;

  return true;
}

// Point ImageTraversal::start
// {
//   return startPoint;
// }
