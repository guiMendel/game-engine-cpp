#include "Sound.h"

using namespace Helper;
using namespace std;

void Sound::Play(const int times)
{
  // Catch no chunk loaded
  Assert(IsLoaded(), "Tried playing a sound chunk that was never loaded");

  // Play and memorize channel
  channel = Mix_PlayChannel(-1, chunk.get(), times - 1);
}

void Sound::Play(function<void()> callback, const int times)
{
  finishCallback = callback;
  Play(times);
}

void Sound::Stop()
{
  // Catch no chunk loaded or no channel registered
  if (IsLoaded() == false || channel < 0)
    return;

  // Stop the channel that was previously used
  Mix_HaltChannel(channel);

  // Resets channel
  channel = -1;
}

void Sound::Load(const std::string fileName)
{
  // Try opening file
  Mix_Chunk *loadedChunk = Mix_LoadWAV(fileName.c_str());

  // Catch open fail
  Assert(loadedChunk != nullptr, "Failed to load audio chunk at " + fileName);

  // Store it
  chunk.reset(loadedChunk);
}
