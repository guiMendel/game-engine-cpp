#ifndef __SPRITE__
#define __SPRITE__

#include <memory.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Helper.h"
#include "GameObject.h"
#include "Component.h"

class Sprite : public Component
{
public:
  // Since we are using unique ptrs, no need to define destructor

  // Default constructor
  Sprite(GameObject &associatedObject)
      : Component(associatedObject), texture(nullptr) {}

  // Constructor with image file name
  Sprite(GameObject &associatedObject, const std::string fileName) : Sprite(associatedObject)
  {
    Load(fileName);
  }

  // Loads the file image to the sprite
  void Load(const std::string fileName);

  // Sets which rectangle of the image to be displayed
  void SetClip(int x, int y, int width, int height);

  int GetWidth() const { return width; }

  int GetHeight() const { return height; }

  bool IsLoaded() const { return texture != nullptr; }

  // Renders the sprite using the associated object's position
  void Render(Vector2 offset) override { Render(offset, associatedObject.box.Coordinates()); }

  // Renders the sprite to the provided position, ignoring the associated object's position
  void Render(Vector2 offset, Vector2 position);

  void Update([[maybe_unused]] float deltaTime) override {}

private:
  // The loaded texture
  SDL_Texture *texture;

  // Dimensions
  int width, height;

  // The clipped rectangle of the image to be rendered
  SDL_Rect clipRect;
};

#endif