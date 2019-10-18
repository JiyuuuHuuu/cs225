// valgrinded [part=2]
/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource, vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if (theSource.getRows() == 0 || theSource.getColumns() == 0)
      return NULL;
    if (theTiles.size() == 0)
      return NULL;

    map<Point<3>, TileImage*> tileMap;
    vector<Point<3>> tilePoints;

    for (auto & tempTile : theTiles)
    {
      LUVAPixel temp = tempTile.getAverageColor();
      Point<3> tempPoint = convertToXYZ(temp);

      // map correspoinding tile and point
      tileMap.insert(pair<Point<3>, TileImage*>(tempPoint, &tempTile));
      tilePoints.push_back(tempPoint);
    }

    // create the kdtree according to tiles
    KDTree<3> tileTree(tilePoints);
    MosaicCanvas * ret = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    // set tiles for MosaicCanvas accordingly
    for (int a = 0; a < ret->getRows(); a++)
    {
      for (int b = 0; b < ret->getColumns(); b++)
      {
        LUVAPixel temp = theSource.getRegionColor(a, b);
        Point<3> mapPoint = tileTree.findNearestNeighbor(convertToXYZ(temp));
        TileImage * mapTile = tileMap[mapPoint];
        ret->setTile(a, b, mapTile);
      }
    }

    return ret;
}
