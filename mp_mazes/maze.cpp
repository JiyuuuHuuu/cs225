/* Your code here! */
#include <iostream>
#include "maze.h"

using namespace std;
using namespace cs225;

/*
  SquareMaze::canTravel
    DESCRIPTION: determine can travle towards the direction or not
    INPUT: int (x, y): current position in the maze
           int dir: direction (0 - right
                               1 - down
                               2 - left
                               3 - up)
    OUTUT: true: can go towards the direction
           false : cannot fo towards the direction
    SIDEEFFECTS: NONE
*/
bool SquareMaze::canTravel(int x, int y, int dir) const
{
  switch (dir)
  {
    case 0: // right
    {
      if (x == width_ - 1)
        return false;
      if (mazeData[convert(x, y)] % 2)
        return false;
      if (mazeData[convert(x+1, y)] < 0)
        return false;
      return true;
    }
    case 1: // down
    {
      if (y == height_ - 1)
        return false;
      if (mazeData[convert(x, y)] >= 2)
        return false;
      if (mazeData[convert(x, y+1)] < 0)
        return false;
      return true;
    }
    case 2: // left
    {
      if (x == 0)
        return false;
      if (mazeData[convert(x-1, y)] % 2)
        return false;
      if (mazeData[convert(x-1, y)] < 0)
        return false;
      return true;
    }
    case 3: // up
    {
      if (y == 0)
        return false;
      if (mazeData[convert(x, y-1)] >= 2)
        return false;
      if (mazeData[convert(x, y-1)] < 0)
        return false;
      return true;
    }
    default:
      return false;
  }
}

/*
  SquareMaze::makeCreativeMaze
    DESCRIPTION: make the (200*200)maze with acyclic path to every block in
                 maze, and an I shaped hole in the middle
    INPUT: int dim: size of I
    OUTUT: NONE
    SIDEEFFECTS: build up the creative maze
*/
void SquareMaze::makeCreativeMaze(int dim)
{
  width_ = 200;
  height_ = 200;

  // sanity check
  if (dim >= 50)
    return;

  // initialize all nodes to be disconnected
  mazeConnection.addelements(width_*height_);

  mazeData = new int[width_*height_];
  // initialize all nodes with all walls
  for (int i = 0; i < width_*height_; i++)
  {
    mazeData[i] = 3;
  }
  int negSize = 0;
  // initialize the hole with -1 (form a shape I)
  for (int x = 100 - dim*1.2; x < 100 + dim*1.2; x++)
  {
    for (int y = 100 - dim*2; y < 100 - dim; y++)
    {
      mazeData[convert(x, y)] = -1;
      negSize++;
    }
    for (int y = 100 + dim; y < 100 + dim*2; y++)
    {
      mazeData[convert(x, y)] = -1;
      negSize++;
    }
  }
  for (int x = 100 - dim/2; x < 100 + dim/2; x++)
  {
    for (int y = 100 - dim; y < 100 + dim; y++)
    {
      mazeData[convert(x, y)] = -1;
      negSize++;
    }
  }
  // delete walls until no walls can be removed
  while (mazeConnection.size(0) != height_*width_ - negSize)
  {
    // cout<<mazeConnection.size(0)<<endl;
    int tarwidth = rand() % width_;
    int tarheight = rand() % height_;
    // check the position of the target block
    if (mazeData[convert(tarwidth, tarheight)] < 0)
      continue;
    int removeRight = rand() % 2;     // 1 - remove
    int removeDown = !(removeRight);  // 0 - not remove

    // check if right wall can be removed
    if (tarwidth == width_ - 1)
      removeRight = 0;
    else if (mazeData[convert(tarwidth + 1, tarheight)] < 0)
      removeRight = 0;
    else if (mazeConnection.find(convert(tarwidth, tarheight)) == mazeConnection.find(convert(tarwidth + 1, tarheight)))
      removeRight = 0;

    // check if down wall can be removed
    if (tarheight == height_ - 1)
      removeDown = 0;
    else if (mazeData[convert(tarwidth, tarheight + 1)] < 0)
      removeDown = 0;
    else if (mazeConnection.find(convert(tarwidth, tarheight)) == mazeConnection.find(convert(tarwidth, tarheight + 1)))
      removeDown = 0;

    // remove the walls
    if (removeRight)
    {
      setWall(tarwidth, tarheight, 0, false);
      mazeConnection.setunion(convert(tarwidth, tarheight), convert(tarwidth + 1, tarheight));
    }
    else if (removeDown)
    {
      setWall(tarwidth, tarheight, 1, false);
      mazeConnection.setunion(convert(tarwidth, tarheight), convert(tarwidth, tarheight + 1));
    }
  }
}

/*
  SquareMaze::makeMaze
    DESCRIPTION: make the maze with acyclic path to every block in maze
    INPUT: int (width, height): dimention of the maze
    OUTUT: NONE
    SIDEEFFECTS: build up the maze
*/
void SquareMaze::makeMaze(int width, int height)
{
  width_ = width;
  height_ = height;
  mazeData = new int[width*height];
  // initialize all nodes to be disconnected
  mazeConnection.addelements(width*height);

  // initialize all nodes with all walls
  for (int i = 0; i < width*height; i++)
  {
    mazeData[i] = 3;
  }

  // delete walls until no walls can be removed
  while (mazeConnection.size(0) != height_*width_)
  {
    int tarwidth = rand() % width_;
    int tarheight = rand() % height_;
    int removeRight = rand() % 2;     // 1 - remove
    int removeDown = !(removeRight);  // 0 - not remove

    // check if right wall can be removed
    if (tarwidth == width_ - 1)
      removeRight = 0;
    else if (mazeConnection.find(convert(tarwidth, tarheight)) == mazeConnection.find(convert(tarwidth + 1, tarheight)))
      removeRight = 0;

    // check if down wall can be removed
    if (tarheight == height_ - 1)
      removeDown = 0;
    else if (mazeConnection.find(convert(tarwidth, tarheight)) == mazeConnection.find(convert(tarwidth, tarheight + 1)))
      removeDown = 0;

    // remove the walls
    if (removeRight)
    {
      setWall(tarwidth, tarheight, 0, false);
      mazeConnection.setunion(convert(tarwidth, tarheight), convert(tarwidth + 1, tarheight));
    }
    else if (removeDown)
    {
      setWall(tarwidth, tarheight, 1, false);
      mazeConnection.setunion(convert(tarwidth, tarheight), convert(tarwidth, tarheight + 1));
    }
  }
}

/*
  SquareMaze::setWall
    DESCRIPTION: build or remove wall on desired direction
    INPUT: int (x, y): current location in the maze
           int dir: location of the wall regarding location (0 - right 1 - down)
           bool exists: true: build the wall
                        false: remove the wall
    OUTUT: NONE
    SIDEEFFECTS: build or remove a wall
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  // sanity check
  if (mazeData[convert(x, y)] < 0 || mazeData[convert(x, y)] > 4)
    return;

  if (exists) // set the wall
  {
    if (dir) //set down wall
    {
      // cases down wall can not be set
      if (y == height_ - 1 || mazeData[convert(x, y)] >= 2)
        return;
      mazeData[convert(x, y)] += 2; // set the down wall
    }
    else //set right wall
    {
      // cases right wall can not be set
      if (x == width_ - 1 || mazeData[convert(x, y)] % 2)
        return;
      mazeData[convert(x, y)] += 1; // set the right wall
    }
  }
  else // remove the wall
  {
    if (dir) //remove down wall
    {
      // cases down wall can not be removed
      if (y == height_ - 1 || mazeData[convert(x, y)] < 2)
        return;
      mazeData[convert(x, y)] -= 2; // remove the down wall
    }
    else //remove right wall
    {
      // cases right wall can not be removed
      if (x == width_ - 1 || !(mazeData[convert(x, y)] % 2))
        return;
      mazeData[convert(x, y)] -= 1; // remove the right wall
    }
  }
}

/*
  SquareMaze::solveMaze
    DESCRIPTION: solve the maze with path to the farest block
    INPUT: NONE
    OUTUT: vector with path direction to the end (direction same as canTravel)
    SIDEEFFECTS: NONE
*/
vector<int> SquareMaze::solveMaze()
{
  vector<int> retVec;
  int * mazeDistance = new int[width_*height_];
  getDistance(mazeDistance);
  int temp = 0;
  int des_x;
  for (int i = 0; i < width_; i++)
  {
    if (temp < mazeDistance[convert(i, height_ - 1)])
    {
      temp = mazeDistance[convert(i, height_ - 1)];
      des_x = i;
    }
  }
  retVec = getPath(des_x, width_ - 1, mazeDistance);

  delete[] mazeDistance;
  return retVec;
}

/*
  SquareMaze::drawMaze
    DESCRIPTION: save the unsolved maze as a PNG
    INPUT: NONE
    OUTUT: pointer to the generated PNG
    SIDEEFFECTS: NONE
*/
PNG* SquareMaze::drawMaze()
{
  PNG* myMaze = new PNG(width_*10 + 1,height_*10 + 1);

  // draw upper bound with the entrance
  for (int i  = 10; i < width_*10 + 1; i++)
  {
    HSLAPixel& temp = myMaze->getPixel(i, 0);
    temp.l = 0; // set black
  }
  // draw the left bound
  for (int i  = 0; i < height_*10 + 1; i++)
  {
    HSLAPixel& temp = myMaze->getPixel(0, i);
    temp.l = 0; // set black
  }

  // draw inner walls
  for (int y = 0; y < height_; y++)
  {
    for (int x = 0; x < width_; x++)
    {
      // draw lower bound
      if (mazeData[convert(x, y)] == 2 || mazeData[convert(x, y)] == 3)
      {
        for (int k = 0; k <= 10; k++)
        {
          HSLAPixel& temp = myMaze->getPixel(x*10+k, (y+1)*10);
          temp.l = 0;
        }
      }
      // draw right bound
      if (mazeData[convert(x, y)] == 1 || mazeData[convert(x, y)] == 3)
      {
        for (int k = 0; k <= 10; k++)
        {
          HSLAPixel& temp = myMaze->getPixel((x+1)*10,y*10+k);
          temp.l = 0;
        }
      }
      // hole cases
      if (mazeData[convert(x, y)] < 0)
      {
        if (mazeData[convert(x + 1, y)] >= 0) // draw right wall
        {
          for (int k = 0; k <= 10; k++)
          {
            HSLAPixel& temp = myMaze->getPixel((x+1)*10,y*10+k);
            temp.l = 0;
          }
        }
        if (mazeData[convert(x, y + 1)] >= 0) // draw down wall
        {
          for (int k = 0; k <= 10; k++)
          {
            HSLAPixel& temp = myMaze->getPixel(x*10+k, (y+1)*10);
            temp.l = 0;
          }
        }
      }
    }
  }

  return myMaze;
}

/*
  SquareMaze::drawMazeWithSolution
    DESCRIPTION: save the solved maze as a PNG
    INPUT: NONE
    OUTUT: pointer to the generated PNG
    SIDEEFFECTS: NONE
*/
PNG* SquareMaze::drawMazeWithSolution()
{
  PNG* myPic = drawMaze();
  vector<int> sol = solveMaze();
  int curr_x = 0;
  int curr_y = 0;
  for (int i : sol)
  {
    switch (i)
    {
      case 0: // right
      {
        for (int k = 0; k <= 10; k++)
        {
          HSLAPixel& temp = myPic->getPixel(curr_x*10+5+k, curr_y*10+5);
          temp.h = 0;
          temp.s = 1;
          temp.l = 0.5;
          temp.a = 1;
        }
        curr_x++;
        break;
      }
      case 1: // down
      {
        for (int k = 0; k <= 10; k++)
        {
          HSLAPixel& temp = myPic->getPixel(curr_x*10+5, curr_y*10+5 + k);
          temp.h = 0;
          temp.s = 1;
          temp.l = 0.5;
          temp.a = 1;
        }
        curr_y++;
        break;
      }
      case 2: // left
      {
        for (int k = 0; k <= 10; k++)
        {
          HSLAPixel& temp = myPic->getPixel(curr_x*10+5-k, curr_y*10+5);
          temp.h = 0;
          temp.s = 1;
          temp.l = 0.5;
          temp.a = 1;
        }
        curr_x--;
        break;
      }
      case 3: // up
      {
        for (int k = 0; k <= 10; k++)
        {
          HSLAPixel& temp = myPic->getPixel(curr_x*10+5, curr_y*10+5 - k);
          temp.h = 0;
          temp.s = 1;
          temp.l = 0.5;
          temp.a = 1;
        }
        curr_y--;
        break;
      }
    }
  }

  // draw exist
  for (int k = 1; k < 10; k++)
  {
    HSLAPixel& temp = myPic->getPixel(curr_x*10+k, (curr_y+1)*10);
    temp.l = 1;
  }

  return myPic;
}

/*
  SquareMaze::~SquareMaze
    DESCRIPTION: destructor cleaning memory
    INPUT: NONE
    OUTUT: NONE
    SIDEEFFECTS: clear up memory
*/
SquareMaze::~SquareMaze()
{
  delete[] mazeData;
}

/******************************************************************************/
/* private helper functions */
/*
  SquareMaze::convert
    DESCRIPTION: convert 2-D location to linear offset
    INPUT: int (x, y): location in the maze
    OUTUT: linear offset
    SIDEEFFECTS: NONE
*/
int SquareMaze::convert(int x, int y) const
{
  return x + y*width_;
}

/*
  SquareMaze::getPath
    DESCRIPTION: get a path from start to end
    INPUT: int (x, y): maze end location
           int* mazeDistance: array with distance info for every block
                              (distance is the step taken from start)
    OUTUT: vector of steps
    SIDEEFFECTS: NONE
*/
vector<int> SquareMaze::getPath(int x, int y, int* mazeDistance)
{
  vector<int> retVec;
  while (x != 0 || y != 0) // back trace the route
  {
    if (canTravel(x, y, 0)) // travel from right
    {
      if (mazeDistance[convert(x+1, y)] == mazeDistance[convert(x, y)] - 1)
      {
        x++;
        retVec.push_back(2);
        continue;
      }
    }
    if (canTravel(x, y, 1)) // travel from down
    {
      if (mazeDistance[convert(x, y+1)] == mazeDistance[convert(x, y)] - 1)
      {
        y++;
        retVec.push_back(3);
        continue;
      }
    }
    if (canTravel(x, y, 2)) // travel from left
    {
      if (mazeDistance[convert(x-1, y)] == mazeDistance[convert(x, y)] - 1)
      {
        x--;
        retVec.push_back(0);
        continue;
      }
    }
    if (canTravel(x, y, 3)) // travel from up
    {
      if (mazeDistance[convert(x, y-1)] == mazeDistance[convert(x, y)] - 1)
      {
        y--;
        retVec.push_back(1);
      }
    }
  }
  return reverse(retVec);
}

/*
  SquareMaze::getDistance
    DESCRIPTION: get the distance from start to every block
    INPUT: int* takenPath: pointer to an array to store the distance info
    OUTUT: NONE
    SIDEEFFECTS: modify the array to store distance info
*/
void SquareMaze::getDistance(int* takenPath)
{
  for (int i = 0; i < width_*height_; i++) // initialize with all negative
  {
    takenPath[i] = -1;
  }
  queue<pair<int, int>> bfsBlock;
  pair<int, int> temp(0, 0);
  bfsBlock.push(temp);
  takenPath[0] = 0;

  while (!bfsBlock.empty())
  {
    pair<int, int> temp = bfsBlock.front();
    bfsBlock.pop();
    int x = temp.first;
    int y = temp.second;
    if (canTravel(x, y, 0)) // travel right
    {
      if (takenPath[convert(x+1, y)] < 0)
      {
        temp.first = x + 1;
        temp.second = y;
        takenPath[convert(x+1, y)] = takenPath[convert(x, y)] + 1;
        bfsBlock.push(temp);
      }
    }
    if (canTravel(x, y, 1)) // travel down
    {
      if (takenPath[convert(x, y+1)] < 0)
      {
        temp.first = x;
        temp.second = y + 1;
        takenPath[convert(x, y+1)] = takenPath[convert(x, y)] + 1;
        bfsBlock.push(temp);
      }
    }
    if (canTravel(x, y, 2)) // travel left
    {
      if (takenPath[convert(x-1, y)] < 0)
      {
        temp.first = x - 1;
        temp.second = y;
        takenPath[convert(x-1, y)] = takenPath[convert(x, y)] + 1;
        bfsBlock.push(temp);
      }
    }
    if (canTravel(x, y, 3)) // travel up
    {
      if (takenPath[convert(x, y-1)] < 0)
      {
        temp.first = x;
        temp.second = y - 1;
        takenPath[convert(x, y-1)] = takenPath[convert(x, y)] + 1;
        bfsBlock.push(temp);
      }
    }
  }
}

/*
  SquareMaze::reverse
    DESCRIPTION: reverse a vector
    INPUT: vector<int> retVec: the vector want to be reversed
    OUTUT: reversed vector
    SIDEEFFECTS: NONE
*/
vector<int> SquareMaze::reverse(vector<int> retVec)
{
  vector<int> temp;
  for (int i = retVec.size() - 1; i >= 0; i--)
    temp.push_back(retVec[i]);
  return temp;
}
