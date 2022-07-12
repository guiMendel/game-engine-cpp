#include <ctype.h>
#include <algorithm>
#include <fstream>
#include "TileMap.h"
#include "Helper.h"

using namespace std;
using namespace Helper;

void TileMap::Load(std::string filename)
{
  // Flush the current loaded matrix
  tileMatrix.clear();

  // Open the file
  ifstream mapFile(filename.c_str());

  // Ensure all's good
  Assert(mapFile.is_open(), "Unable to open tilemap configuration file " + filename);

  // Will hold each line from the document
  string line;

  // Get the first line, which holds the maps dimensions
  getline(mapFile, line);

  auto mapDimensions = SplitString(line, ",");

  try
  {
    // Extract the dimensions
    mapWidth = stoi(mapDimensions[0]);
    mapHeight = stoi(mapDimensions[1]);
    mapDepth = stoi(mapDimensions[2]);

    // Loop through each item of each line
    while (getline(mapFile, line))
      for (auto item : SplitString(line, ","))
      {
        // Disregard empty or whitespace only strings
        if (item.empty() || item.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
          continue;

        // Convert from string and subtract 1 (so that empty tiles are mapped to -1)
        // Push the result to the matrix
        tileMatrix.push_back(stoi(item) - 1);
      }
  }
  // Catch stoi errors
  catch (const invalid_argument &error)
  {
    // Clean up file
    mapFile.close();

    throw runtime_error("Map file at " + filename + " has invalid syntax");
  }

  // Close file
  mapFile.close();
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
  // Offset to apply to matrix index to account for layer
  int layerOffset = layer * mapWidth * mapHeight;

  // For each tile in matrix
  for (int i = layerOffset; i < layerOffset + mapWidth * mapHeight; i++)
  {
    // Skip empty tiles
    if (tileMatrix[i] == -1)
      continue;

    // X coord where to render it
    int x = (i % mapWidth) * tileSet->GetTileWidth();

    // Y coord where to render it
    int y = (i / mapWidth) * tileSet->GetTileHeight();

    // Render it
    tileSet->RenderTile(tileMatrix[i], x - cameraX, y - cameraY);
  }
}
