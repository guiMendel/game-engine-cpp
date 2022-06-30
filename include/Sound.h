#ifndef __SOUND__
#define __SOUND__

#include <SDL_mixer.h>
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

  // Stops playing
  void Stop();

  bool IsLoaded() const { return chunk != nullptr; }

  // === COMPONENT OVERRIDES

  void Update(float deltaTime) override {}

  // Renders the Sound to the screen
  void Render() override;

  // Determines if is from a certain type
  virtual bool Is(std::string type) override { return type == typeid(*this).name(); }

private:
  // The loaded audio chunk
  // No need for destructor to free it!
  Helper::auto_ptr<Mix_Chunk> chunk;

  // The channel where to play
  int channel{-1};
};

#endif