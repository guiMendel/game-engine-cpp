#ifndef __SPRITE__
#define __SPRITE__

#include <memory.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Helper.h"

class Sprite
{
public:
  // Since we are using unique ptrs, no need to define destructor

  // Default constructor
  Sprite() : texture(nullptr, SDL_DestroyTexture) {}

  // Constructor with image file name
  Sprite(const std::string fileName) : texture(nullptr, SDL_DestroyTexture)
  {
    Open(fileName);
  }

  // Loads the file image to the sprite
  void Open(const std::string fileName);

  // Sets which rectangle of the image to be displayed
  void SetClip(int x, int y, int width, int height);

  // Renders the sprite to the screen
  void Render(int x, int y);

  int GetWidth() const { return width; }

  int GetHeight() const { return height; }

  bool IsOpen() const { return texture != nullptr; }

private:
  // The loaded texture
  Helper::auto_ptr<SDL_Texture> texture;

  // Dimensions
  int width, height;

  // The clipped rectangle of the image to be rendered
  SDL_Rect clipRect;
};

#endif