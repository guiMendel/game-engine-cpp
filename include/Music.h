#ifndef __MUSIC__
#define __MUSIC__

#include <SDL_mixer.h>
#include <string>
#include "Helper.h"

class Music
{
public:
  // Default constructor
  Music() : music(nullptr, Mix_FreeMusic) {}

  // Construct from music filename
  Music(const std::string filename) : music(nullptr, Mix_FreeMusic) { Load(filename); }

  // Plays the given music (-1 loops forever)
  void Play(const int times);

  // Fades out the currently playing music. Thw fade out window is in ms
  void FadeOut(const int fadeWindow = 1500) { Mix_FadeOutMusic(fadeWindow); }

  // Loads the music file
  void Load(const std::string filename);

  // Whether a music file is loaded
  bool IsLoaded() const { return music != nullptr; }

  // Declare custom destructor
  ~Music();

private:
  // The currently loaded music track
  Helper::auto_ptr<Mix_Music> music;
};

#endif