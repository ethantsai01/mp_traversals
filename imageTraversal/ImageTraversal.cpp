#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
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
ImageTraversal::Iterator::Iterator() : traversal_(), done(true) {

}

ImageTraversal::Iterator::Iterator(ImageTraversal *traversal, Point point) : done(false) {
  /** @todo [Part 1] */
  traversal_ = traversal;
  point_ = point;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  point_ = traversal_ -> pop();
  traversal_ -> visited[point_.x][point_.y] = true;

  Point right(point_.x + 1, point_.y);
  Point above(point_.x, point_.y - 1);
  Point left(point_.x - 1, point_.y);
  Point below(point_.x, point_.y + 1);
  HSLAPixel startCompare = traversal_ -> getPNG() -> getPixel(traversal_ -> start_.x, traversal_ -> start_.y);

   if(right.x < traversal_ -> getPNG() -> width()){
     if(traversal_ -> visited[right.x][right.y] == false){
       double delta = calculateDelta(startCompare, traversal_ -> getPNG() -> getPixel(right.x, right.y));

       if(delta <= traversal_ -> getTolerance()){
         traversal_ -> add(right);
       }
     }
   }

   if(below.y < traversal_ -> getPNG() -> height()){
     if(traversal_ -> visited[below.x][below.y] == false){
       double delta = calculateDelta(startCompare, traversal_ -> getPNG() -> getPixel(below.x, below.y));

       if(delta <= traversal_ -> getTolerance()){
         traversal_ -> add(below);
       }
     }
   }

   if(point_.x > 0) {
     if(traversal_ -> visited[left.x][left.y] == false){
       double delta = calculateDelta(startCompare, traversal_ -> getPNG() -> getPixel(left.x, left.y));

       if(delta <= traversal_ -> getTolerance()){
         traversal_ -> add(left);
       }
     }
   }

   if(point_.y > 0){
     if(traversal_ -> visited[above.x][above.y] == false){
       double delta = calculateDelta(startCompare, traversal_->getPNG() -> getPixel(above.x, above.y));

       if(delta <= traversal_ -> getTolerance()){
         traversal_ -> add(above);
       }
     }
   }

   while (!(traversal_ -> empty()) && (traversal_ -> visited[traversal_ -> peek().x][traversal_ -> peek().y])) {
     traversal_ -> pop();
   }

   if (traversal_ -> empty() == true) {
     done = true;
     return *this;
   }

   point_ = traversal_ -> peek();
   return *this;
}
/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return point_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(done && other.done);
}
