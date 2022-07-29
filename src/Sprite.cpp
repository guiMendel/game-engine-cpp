#include "Sprite.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"
#include <string>

using namespace std;
using namespace Helper;

void Sprite::Load(const string fileName)
{
  // Get texture from resource manager
  texture = &Resources::GetTexture(fileName);

  // Get it's dimensions
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  // Set the clip to the full image
  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int width, int height)
{
  clipRect = {x, y, width, height};

  // Also set the object dimensions
  associatedObject.box.width = width;
  associatedObject.box.height = height;
}

void Sprite::Render(Vector2 position, bool ignoreCameraPosition)
{
  // Get the real position
  Vector2 offsetPosition =
      ignoreCameraPosition
          ? position
          : Camera::GetInstance().WorldToScreen(position);

  // Get destination rectangle
  SDL_Rect destinationRect{
      (int)offsetPosition.x, (int)offsetPosition.y, clipRect.w, clipRect.h};

  // Put the texture in the renderer
  SDL_RenderCopy(
      Game::GetInstance().GetRenderer(),
      texture,
      &clipRect,
      &destinationRect);
}
