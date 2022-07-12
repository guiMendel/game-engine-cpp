#ifndef __TILEMAP__
#define __TILEMAP__

#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component
{
public:
  // Default constructor
  TileMap(GameObject &associatedObject, std::string filename, TileSet *tileSet)
      : Component(associatedObject), tileSet(tileSet)
  {
    Load(filename);
  }

  // Loads a map configuration file
  void Load(std::string filename);

  // Sets the associated tileset
  void SetTileSet(TileSet *newTileSet) { tileSet.reset(newTileSet); }

  // Returns a reference to the tile at the given position
  int &At(int x, int y, int z = 0) { return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight]; }

  // Renders a given layer
  void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

  int GetWidth() const { return mapWidth; }
  int GetHeight() const { return mapHeight; }
  int GetDepth() const { return mapDepth; }

  // === OVERRIDES

  void Render() override
  {
    // Render each layer
    for (int layer = 0; layer < mapDepth; ++layer)
    {
      RenderLayer(layer);
    }
  }

  void Update(float deltaTime) override {}

private:
  std::vector<int> tileMatrix;

  // Reference to the tileset
  std::unique_ptr<TileSet> tileSet;

  int mapWidth;
  int mapHeight;
  int mapDepth;
};

#endif