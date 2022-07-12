#include "Game.h"
#include "Resources.h"
#include "Helper.h"
#include <utility>
#include <tuple>

using namespace std;
using namespace Helper;

unordered_map<string, Helper::auto_ptr<SDL_Texture>> Resources::textureTable;

unordered_map<string, Helper::auto_ptr<Mix_Music>> Resources::musicTable;

unordered_map<string, Helper::auto_ptr<Mix_Chunk>> Resources::soundTable;

SDL_Texture &Resources::GetTexture(string filename)
{

  // Check if it's already loaded
  auto textureIterator = textureTable.find(filename);

  // If so, return the loaded asset
  if (textureIterator != textureTable.end())
    return *textureIterator->second;

  // At this point, we know the asset isn't loaded yet

  // Get the game renderer
  SDL_Renderer *renderer = Game::GetInstance().GetRenderer();

  // Gets the texture pointer
  SDL_Texture *texturePointer = IMG_LoadTexture(renderer, filename.c_str());

  // Catch any errors
  Assert(texturePointer != nullptr, "Failed to load texture at " + filename);

  // Store the texture (create the pointer with the destructor)
  textureTable.emplace(
      piecewise_construct,
      forward_as_tuple(filename),
      forward_as_tuple(texturePointer, SDL_DestroyTexture));

  // Now that it's loaded, return it
  return *texturePointer;
}
