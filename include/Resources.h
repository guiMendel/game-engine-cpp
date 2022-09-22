#ifndef __RESOURCES__
#define __RESOURCES__

#include <functional>
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
  // Get a resource
  template <class Resource>
  static Resource &GetResource(
      std::string resourceType,
      std::string filename,
      std::unordered_map<std::string, Helper::auto_ptr<Resource>> &table,
      std::function<Resource *(std::string)> resourceLoader,
      void (*resourceDestructor)(Resource *))
  {
    // Check if it's already loaded
    auto resourceIterator = table.find(filename);

    // If so, return the loaded asset
    if (resourceIterator != table.end())
      return *resourceIterator->second;

    // At this point, we know the asset isn't loaded yet

    // Load it
    Resource *resourcePointer = resourceLoader(filename);

    // Catch any errors
    Assert(resourcePointer != nullptr, "Failed to load " + resourceType + " at " + filename);

    // Store the texture (create the pointer with the destructor)
    table.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(filename),
        std::forward_as_tuple(resourcePointer, resourceDestructor));

    // Now that it's loaded, return it
    return *resourcePointer;
  }

  // Store textures
  static std::unordered_map<std::string, Helper::auto_ptr<SDL_Texture>> textureTable;

  // Store music
  static std::unordered_map<std::string, Helper::auto_ptr<Mix_Music>> musicTable;

  // Store sfx
  static std::unordered_map<std::string, Helper::auto_ptr<Mix_Chunk>> soundTable;
};

#endif