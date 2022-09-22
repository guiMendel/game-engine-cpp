#include "Music.h"
#include "Helper.h"
#include "Resources.h"

using namespace Helper;

void Music::Play(const int times)
{
  Assert(musicPath.size() > 0, "Tried playing music without providing it's file path");

  // Get music
  Mix_Music &music = Resources::GetMusic(musicPath);

  auto encounteredError = Mix_PlayMusic(&music, times);

  // Catch weird errors
  Assert(!encounteredError, "Failed to play a music track");
}

Music::~Music()
{
  // Stops any music being played
  FadeOut();
}