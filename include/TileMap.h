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
  // Defines the intensity of the parallax effect. 0 means no effect
  const float parallaxIntensity = 0.75;

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

  int &At(Vector2 position, int layer) { return At((int)position.x, (int)position.y, layer); }

  // Renders a given layer
  void RenderLayer(int layer);

  int GetWidth() const { return mapWidth; }
  int GetHeight() const { return mapHeight; }
  int GetDepth() const { return mapDepth; }

  // === OVERRIDES

  void Render() override;

  void Update([[maybe_unused]] float deltaTime) override {}

private:
  std::vector<int> tileMatrix;

  // Reference to the tileset
  std::unique_ptr<TileSet> tileSet;

  int mapWidth;
  int mapHeight;
  int mapDepth;
};

#endif