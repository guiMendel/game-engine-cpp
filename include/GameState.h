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

private:
  // Adds a new game object
  void AddObject(Vector2 coordinates);

  // Object with background image
  GameObject background;

  Sprite* backgroundSprite;

  // Object with tilemap
  GameObject tilemapObject;

  // Tilemap reference
  TileMap *tilemap;

  // Reference to input manager
  InputManager &inputManager;

  Music music;

  // Indicates that the game must exit
  bool quitRequested;

  // Array with all of the state's objects
  std::vector<std::shared_ptr<GameObject>> gameObjects;
};

#endif