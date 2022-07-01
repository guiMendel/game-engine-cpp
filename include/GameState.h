#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <memory>
#include <vector>
#include <SDL.h>
#include "GameObject.h"
#include "Sprite.h"
#include "Music.h"

// Class that defines a state of the game
class GameState
{
public:
  GameState() : music("./assets/music/main.mp3")
  {
    quitRequested = false;

    // Get a background sprite
    background.AddComponent(new Sprite(background, "./assets/image/ocean.jpg"));

    // Play the music
    music.Play();
  }

  // Clear objects on destroy
  ~GameState() { gameObjects.clear(); }

  // Whether the game should exit
  bool QuitRequested() { return quitRequested; }

  // Preloads all the assets so that they are ready when required
  void LoadAssets();

  void Update(float deltaTime);

  void Render();

private:
  // Get input
  void Input();

  // Adds a new game object
  void AddObject(int mouseX, int mouseY);

  GameObject background;

  Music music;

  // Indicates that the game must exit
  bool quitRequested;

  // Array with all of the state's objects
  std::vector<std::unique_ptr<GameObject>> gameObjects;
};

#endif