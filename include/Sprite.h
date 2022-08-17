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
  Sprite(GameObject &associatedObject, RenderLayer renderLayer = RenderLayer::Default, bool centerObject = true)
      : Component(associatedObject), centered(centerObject), renderLayer(renderLayer) {}

  // Constructor with image file name
  Sprite(GameObject &associatedObject, const std::string fileName, RenderLayer renderLayer = RenderLayer::Default, bool centerObject = true) : Sprite(associatedObject, renderLayer, centerObject)
  {
    Load(fileName);
  }

  // Loads the file image to the sprite
  void Load(const std::string fileName);

  // Sets which rectangle of the image to be displayed
  void SetClip(int x, int y, int width, int height);

  int GetWidth() const { return width; }

  int GetHeight() const { return height; }

  int GetScaledWidth() const { return clipRect.w * gameObject.scale.x; }

  int GetScaledHeight() const { return clipRect.h * gameObject.scale.y; }

  bool IsLoaded() const { return texture != nullptr; }

  // Renders the sprite using the associated object's position
  void Render() override { Render(gameObject.position + offset); }

  // Renders the sprite to the provided position, ignoring the associated object's position
  void Render(Vector2 position);

  void Update([[maybe_unused]] float deltaTime) override {}

  // Offset when rendering based on game object's position
  Vector2 offset{0, 0};

  // Whether to center the sprite on the render coordinates
  bool centered;

  RenderLayer GetRenderLayer() override { return renderLayer; }

private:
  // The loaded texture
  SDL_Texture *texture{nullptr};

  // Real dimensions of the loaded image
  int width{0}, height{0};

  // Scaled dimensions
  int scaledWidth{0}, scaledHeight{0};

  // The clipped rectangle of the image to be rendered
  SDL_Rect clipRect;

  // The sprite's layer
  RenderLayer renderLayer{RenderLayer::Default};
};

#endif