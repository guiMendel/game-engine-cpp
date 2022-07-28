#include <iostream>
#include "TileSet.h"
#include "Sprite.h"
#include "Helper.h"

using namespace std;
using namespace Helper;

TileSet::TileSet(int tileWidth, int tileHeight, std::string filename) : tileWidth(tileWidth), tileHeight(tileHeight)
{
  // Add the sprite component
  tileSet = &tileSetObject.AddComponent<Sprite>(filename);

  // Avoid awkward situations
  Assert(tileWidth > 0 && tileHeight > 0, "Tile dimensions must be greater than zero");
  Assert(tileSet->GetHeight() > 0 && tileSet->GetWidth() > 0, "Tileset sprite is invalid (dimensions not greater than 0)");

  // Get the rows & columns
  rows = tileSet->GetHeight() / tileHeight;
  columns = tileSet->GetWidth() / tileWidth;
}

void TileSet::RenderTile(unsigned index, int x, int y)
{
  // Ensure valid index
  Assert(index >= 0 && index < rows * columns, "Invalid index");

  // Get to which row this tile belongs
  int tileRow = index / columns;

  // Get tile row position
  int tileColumn = index % columns;

  // Set the sprite's clip to the tile
  tileSet->SetClip(tileColumn * tileWidth, tileRow * tileHeight, tileWidth, tileHeight);

  // Render it to the correct position
  tileSet->Render(x, y);
}