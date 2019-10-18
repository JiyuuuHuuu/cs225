// valginded
#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
  SquareMaze m;
  m.makeCreativeMaze(45);
  std::cout << "MakeCreativeMaze complete" << std::endl;

  cs225::PNG* unsolved = m.drawMaze();
  unsolved->writeToFile("unsolved_creative.png");
  delete unsolved;
  std::cout << "drawMaze complete" << std::endl;

  // std::vector<int> sol = m.solveMaze();
  // std::cout << "solveMaze complete" << std::endl;
  // for (int i : sol)
  //   std::cout<<i<<" ";
  // std::cout<<std::endl;
  //
  cs225::PNG* solved = m.drawMazeWithSolution();
  solved->writeToFile("creative.png");
  delete solved;
  std::cout << "drawMazeWithSolution complete" << std::endl;

  return 0;
}
