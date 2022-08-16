#ifndef __SPRITE__
#define __SPRITE__

#include <memory>
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
  Sprite(GameObject &associatedObject, RenderLayer renderLayer = RenderLayer::Default)
      : Component(associatedObject), renderLayer(renderLayer) {}

  // Constructor with image file name
  Sprite(GameObject &associatedObject, const std::string fileName, RenderLayer renderLayer = RenderLayer::Default, bool centerObject = true) : Sprite(associatedObject, renderLayer)
  {
    Load(fileName, centerObject);
  }

  // Loads the file image to the sprite
  void Load(const std::string fileName, bool center = true);

  // Sets which rectangle of the image to be displayed
  void SetClip(int x, int y, int width, int height, bool center = true);

  int GetWidth() const { return width; }

  int GetHeight() const { return height; }

  bool IsLoaded() const { return texture != nullptr; }

  // Renders the sprite using the associated object's position
  void Render() override { Render(gameObject.position + offset); }

  // Renders the sprite to the provided position, ignoring the associated object's position
  void Render(Vector2 position);

  void Update([[maybe_unused]] float deltaTime) override {}

  // Shifts offset so that the game object's position is centered on the sprite
  void CenterObject();

  // Offset when rendering based on game object's position
  Vector2 offset{0, 0};

  RenderLayer GetRenderLayer() override { return renderLayer; }

private:
  // The loaded texture
  SDL_Texture *texture{nullptr};

  // Dimensions
  int width{0}, height{0};

  // The clipped rectangle of the image to be rendered
  SDL_Rect clipRect;

  // The sprite's layer
  RenderLayer renderLayer{RenderLayer::Default};
};

#endif