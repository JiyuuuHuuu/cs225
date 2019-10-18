
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;       png.readFromFile("input.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(90, 90), 0.25);
  MyColorPicker mine(0.05);
  image.addFloodFill( bfs, mine);

  DFS dfs(png, Point(149, 160), 0.25);
  HSLAPixel backgroundColor(120, 1, 0.5);
  HSLAPixel gridColor(266, 1, 0.5);
  GridColorPicker myGrid(gridColor, backgroundColor, 10);
  image.addFloodFill(dfs, myGrid);

  Animation animation = image.animate(400);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
