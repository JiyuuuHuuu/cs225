// valgrinded
/* Your code here! */
#include <vector>
#include <queue>
#include "cs225/PNG.h"
#include "dsets.h"

using namespace std;
using namespace cs225;

class SquareMaze
{
  public:
    SquareMaze(){}; // default constructor that do nothing
    void makeCreativeMaze(int dim);
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze();
    PNG* drawMazeWithSolution();
    ~SquareMaze();

  private:
    int width_;
    int height_;
    /*
      ptr to a 1-D array that stores wall info
      ( 0 - no right nor down wall
        1 - right wall but no down wall
        2 - down wall but no right wall
        3 - both right and down wall
      )
    */
    int* mazeData;
    DisjointSets mazeConnection; // stores connection between nodes

    // helper funtion that converts 2-D index to linear index
    int convert(int x, int y) const;
    // helper function that gets the path from start to specified block
    vector<int> getPath(int x, int y, int* mazeDistance);
    // helper funtion that get each block's distance from start
    void getDistance(int* takenPath);
    // helper function that reverse a vector
    vector<int> reverse(vector<int> input);
};
