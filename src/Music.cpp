#include "Music.h"
#include "Helper.h"

using namespace Helper;

void Music::Play(const int times = -1)
{
  // Catch no music loaded
  Assert(IsLoaded(), "Tried playing a music track that was never loaded");

  auto encounteredError = Mix_PlayMusic(music.get(), times);

  // Catch weird errors
  Assert(!encounteredError, "Failed to play a music track");
}

void Music::Load(const std::string filename)
{
  // Try to load the file
  Mix_Music *loadedMusicPointer = Mix_LoadMUS(filename.c_str());

  // Ensure it loaded correctly
  Assert(loadedMusicPointer != nullptr, "Failed to load music file at " + filename);

  // Store music
  music.reset(loadedMusicPointer);
}

Music::~Music()
{
  // Stops any music being played
  FadeOut();

  // No need to free unique_ptr here
}