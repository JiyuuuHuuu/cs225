#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance): myImage(png), startPoint(start), tolerance_(tolerance)
{
  /** @todo [Part 1] */
  dfsStack.push_back(start);
  vector<vector<int>> temp(myImage.width(), vector<int>(myImage.height(), 0));
  visited = temp;
  checkStack = temp;
  checkStack[start.x][start.y] = 1;
  // visited.push_back(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
 ImageTraversal::Iterator DFS::begin()
 {
   /** @todo [Part 1] */
   // ImageTraversal *temp = new DFS(myImage, startPoint, tolerance_);
   return ImageTraversal::Iterator(*this, startPoint, &myImage, tolerance_);
 }

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point)
{
  /** @todo [Part 1] */
  if (visited[point.x][point.y] == 0)
  {
    if (checkStack[point.x][point.y] == 1)
    {
      auto it = find(dfsStack.begin(), dfsStack.end(), point);
      dfsStack.erase(it);
      checkStack[point.x][point.y] = 0;
    }
    dfsStack.push_back(point);
    checkStack[point.x][point.y] = 1;
    // visited.push_back(point);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if (!empty())
  {
    Point retVal = dfsStack.back();
    visited[retVal.x][retVal.y] = 1;
    dfsStack.pop_back();

    return retVal;
  }

  return Point(0, 0);
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const
{
  /** @todo [Part 1] */
  if (!empty())
    return dfsStack.back();

  return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const
{
  /** @todo [Part 1] */
  if (dfsStack.size() == 0)
    return true;

  return false;
}

// PNG DFS::getImage()
// {
//   return myImage;
// }
