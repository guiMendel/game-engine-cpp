#include "Sprite.h"
#include "Game.h"
#include <string>

using namespace std;
using namespace Helper;

void Sprite::Load(const string fileName)
{
  // No need to unload previous sprite, since we are using unique ptr, which does this for us

  // Get the game renderer
  SDL_Renderer *renderer = Game::GetInstance().GetRenderer();

  // Gets the texture pointer
  SDL_Texture *texturePointer = IMG_LoadTexture(renderer, fileName.c_str());

  // Catch any errors
  Assert(texturePointer != nullptr, "Failed to load texture at " + fileName);

  // Store the texture
  texture.reset(texturePointer);

  // Get it's dimensions
  SDL_QueryTexture(texturePointer, nullptr, nullptr, &width, &height);

  // Set the clip to the full image
  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int width, int height)
{
  clipRect = {x, y, width, height};
}

void Sprite::Render(int x, int y)
{
  // Get destination rectangle
  SDL_Rect destinationRect = {x, y, clipRect.w, clipRect.h};

  // Put the texture in the renderer
  SDL_RenderCopy(
      Game::GetInstance().GetRenderer(),
      texture.get(),
      &clipRect,
      &destinationRect);
}