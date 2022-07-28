#ifndef __SOUND__
#define __SOUND__

#include <SDL_mixer.h>
#include <iostream>
#include <functional>
#include "GameObject.h"
#include "Component.h"
#include "Helper.h"

class Sound : public Component
{
public:
  // Default constructor
  Sound(GameObject &associatedObject)
      : Component(associatedObject), chunk(nullptr, Mix_FreeChunk) {}

  // Constructor with sound file name
  Sound(GameObject &associatedObject, const std::string fileName) : Sound(associatedObject)
  {
    Load(fileName);
  }

  // Ensure sound stops if destroyed
  ~Sound() { Stop(); }

  // Loads the file sound
  void Load(const std::string fileName);

  // Plays audio
  void Play(const int times = 1);
  void Play(std::function<void()> callback, const int times = 1);

  // Stops playing
  void Stop();

  bool IsLoaded() const { return chunk != nullptr; }

  // === COMPONENT OVERRIDES

  void Update([[maybe_unused]] float deltaTime) override
  {
    // TEMPORARY
    // Do nothing is this channel is playing
    if (Mix_Playing(channel) || !finishCallback)
      return;

    // Otherwise, call the callback
    finishCallback();

    finishCallback = nullptr;
  }

  void Render() override {}

private:
  // Callback to execute when sound stops playing
  std::function<void()> finishCallback;

  // The loaded audio chunk
  // No need for destructor to free it!
  Helper::auto_ptr<Mix_Chunk> chunk;

  // The channel where to play
  int channel{-1};
};

#endif