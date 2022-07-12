#ifndef __RESOURCES__
#define __RESOURCES__

#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Helper.h"

class Resources
{
public:
  // Get an image texture
  static SDL_Texture &GetTexture(std::string filename);

  // Clear all textures
  static void ClearTextures() { textureTable.clear(); }

  // Get a music
  static Mix_Music &GetMusic(std::string filename);

  // Clear all music
  static void ClearMusics() { musicTable.clear(); }

  // Get an sfx
  static Mix_Chunk &GetSound(std::string filename);

  // Clear all sfx
  static void ClearSounds() { soundTable.clear(); }

  // Clear everything
  static void ClearAllResources()
  {
    ClearMusics();
    ClearTextures();
    ClearSounds();
  }

private:
  // Store textures
  static std::unordered_map<std::string, Helper::auto_ptr<SDL_Texture>> textureTable;

  // Store music
  static std::unordered_map<std::string, Helper::auto_ptr<Mix_Music>> musicTable;

  // Store sfx
  static std::unordered_map<std::string, Helper::auto_ptr<Mix_Chunk>> soundTable;
};

#endif