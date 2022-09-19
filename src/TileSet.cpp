#include <iostream>
#include "TileSet.h"
#include "Sprite.h"
#include "Helper.h"

using namespace std;
using namespace Helper;

TileSet::TileSet(int tileWidth, int tileHeight, std::string filename) : tileWidth(tileWidth), tileHeight(tileHeight)
{
  // Add the sprite component
  // Don't give it a render layer. It must only be directly rendered by the tilemap method
  auto tileSprite = tileSetObject.AddComponent<Sprite>(filename, RenderLayer::None);

  tileSpriteWeak = tileSprite;

  // Avoid awkward situations
  Assert(tileWidth > 0 && tileHeight > 0, "Tile dimensions must be greater than zero");
  Assert(tileSprite->GetUnscaledHeight() > 0 && tileSprite->GetUnscaledWidth() > 0, "Tileset sprite is invalid (dimensions not greater than 0)");

  // Get the rows & columns
  rows = tileSprite->GetUnscaledHeight() / tileHeight;
  columns = tileSprite->GetUnscaledWidth() / tileWidth;
}

void TileSet::RenderTile(unsigned index, Vector2 position)
{
  // Ensure valid index
  Assert((int)index < rows * columns, "Invalid index");

  auto tileSprite = tileSpriteWeak.lock();

  Assert((bool)tileSprite, "Failed to retrieve tileset sprite");

  // Get to which row this tile belongs
  int tileRow = index / columns;

  // Get tile row position
  int tileColumn = index % columns;

  // Set the sprite's clip to the tile
  tileSprite->SetClip(tileColumn * tileWidth, tileRow * tileHeight, tileWidth, tileHeight);

  // Render it to the correct position
  tileSprite->Render(position);
}
