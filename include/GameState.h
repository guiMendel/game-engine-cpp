#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <SDL.h>
#include "Sprite.h"
#include "Music.h"

// Class that defines a state of the game
class GameState
{
private:
  Sprite background;

  Music music;

  // Indicates that the game must exit
  bool quitRequested;

public:
  GameState() : background(*this, "./assets/ocean.jpg"), music("./assets/stageState.ogg")
  {
    quitRequested = false;

    // Play the music
    music.Play();
  }

  // Whether the game should exit
  bool QuitRequested() { return quitRequested; }

  // Preloads all the assets so that they are ready when required
  void LoadAssets();

  void Update(float deltaTime);

  void Render();
};

#endif