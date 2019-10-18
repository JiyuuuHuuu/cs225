#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;


MyColorPicker::MyColorPicker(double increment)
  : luminence(0), increment(increment) { }
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(12, 1, luminence);
  luminence += increment;
  if (luminence >= 1) { luminence -= 1; }
  return pixel;
}
