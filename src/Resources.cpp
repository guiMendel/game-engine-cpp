#include "Game.h"
#include "Resources.h"
#include "Helper.h"
#include <utility>
#include <tuple>
#include <memory>

using namespace std;
using namespace Helper;

unordered_map<string, std::shared_ptr<SDL_Texture>> Resources::textureTable;

unordered_map<string, std::shared_ptr<Mix_Music>> Resources::musicTable;

unordered_map<string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;

std::shared_ptr<SDL_Texture> Resources::GetTexture(string filename)
{
  function<SDL_Texture *(string)> textureLoader = [](string filename)
  {
    // Get the game renderer
    SDL_Renderer *renderer = Game::GetInstance().GetRenderer();

    // Gets the texture pointer
    return IMG_LoadTexture(renderer, filename.c_str());
  };

  return GetResource<SDL_Texture>("texture", filename, textureTable, textureLoader, SDL_DestroyTexture);
}

std::shared_ptr<Mix_Music> Resources::GetMusic(string filename)
{
  function<Mix_Music *(string)> musicLoader = [](string filename)
  {
    return Mix_LoadMUS(filename.c_str());
  };

  return GetResource<Mix_Music>("music", filename, musicTable, musicLoader, Mix_FreeMusic);
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string filename)
{
  function<Mix_Chunk *(string)> chunkLoader = [](string filename)
  {
    return Mix_LoadWAV(filename.c_str());
  };

  return GetResource<Mix_Chunk>("sound chunk", filename, soundTable, chunkLoader, Mix_FreeChunk);
}