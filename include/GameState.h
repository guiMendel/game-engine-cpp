#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <memory>
#include <vector>
#include <iostream>
#include <SDL.h>
#include "GameObject.h"
#include "TileMap.h"
#include "Sprite.h"
#include "Music.h"
#include "InputManager.h"
#include "Vector2.h"

// Class that defines a state of the game
class GameState
{
public:
  GameState();

  // Clear objects on destroy
  ~GameState() { gameObjects.clear(); }

  // Whether the game should exit
  bool QuitRequested() { return quitRequested; }

  // Preloads all the assets so that they are ready when required
  void LoadAssets();

  void Update(float deltaTime);

  void Render();

  // Adds a new game object
  std::weak_ptr<GameObject> AddObject(GameObject *gameObject);

  std::weak_ptr<GameObject> GetPointer(GameObject *gameObject);

  void Start();
  
private:

  // Reference to input manager
  InputManager &inputManager;

  Music music;

  // Indicates that the game must exit
  bool quitRequested;

  // Array with all of the state's objects
  std::vector<std::shared_ptr<GameObject>> gameObjects;

  // Whether the state has executed the start method
  bool started;
};

#endif