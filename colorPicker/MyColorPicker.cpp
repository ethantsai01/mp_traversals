#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue_, 1, 0.5);
  hue_ += move_;

  if(hue_ >= 200) {
    hue_ -= 42;
  }

  return pixel;
  return HSLAPixel();
}
