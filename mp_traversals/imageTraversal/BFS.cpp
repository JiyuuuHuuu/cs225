#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance): myImage(png), startPoint(start), tolerance_(tolerance)
{
  /** @todo [Part 1] */
  bfsQueue.push(start);
  vector<vector<int>> temp(myImage.width(), vector<int>(myImage.height(), 0));
  visited = temp;
  visited[start.x][start.y] = 1;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
 ImageTraversal::Iterator BFS::begin()
 {
   /** @todo [Part 1] */
   // BFS *temp = new BFS(myImage, startPoint, tolerance_);
   return ImageTraversal::Iterator(*this, startPoint, &myImage, tolerance_);
 }

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point)
{
  /** @todo [Part 1] */
  if (visited[point.x][point.y] == 0)
  {
    visited[point.x][point.y] = 1;
    bfsQueue.push(point);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop()
{
  /** @todo [Part 1] */
  if (!empty())
  {
    Point retVal = bfsQueue.front();
    // visited.push_back(retVal);
    bfsQueue.pop();

    return retVal;
  }

  return Point(0, 0);
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const
{
  /** @todo [Part 1] */
  if (!empty())
    return bfsQueue.front();

  return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const
{
  /** @todo [Part 1] */
  if (bfsQueue.size() == 0)
    return true;

  return false;
}

// PNG BFS::getImage()
// {
//   return myImage;
// }
