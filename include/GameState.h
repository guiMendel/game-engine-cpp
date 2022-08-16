#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <SDL.h>
#include "GameObject.h"
#include "TileMap.h"
#include "Sprite.h"
#include "Music.h"
#include "InputManager.h"
#include "Vector2.h"

class Component;

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
  std::shared_ptr<GameObject> AddObject(std::shared_ptr<GameObject> gameObject);

  // Creates a new game object
  template <typename... Args>
  std::shared_ptr<GameObject> CreateObject(
      std::function<void(std::shared_ptr<GameObject>)> initializer, Args &&...args)
  {
    std::shared_ptr<GameObject> object = make_shared<GameObject>(std::forward<Args>(args)...);

    gameObjects[object->id] = object;

    // Initialize it
    if (initializer)
      initializer(object);

    // Call it's start method
    if (started)
      object->Start();

    return object;
  }

  std::weak_ptr<GameObject> GetPointer(const GameObject *gameObject);

  void Start();

  // Supplies a valid unique identifier for a game object
  int SupplyObjectId() { return nextObjectId++; }

  void RegisterLayerRenderer(std::shared_ptr<Component> component);

private:
  // Reference to input manager
  InputManager &inputManager;

  Music music;

  // Indicates that the game must exit
  bool quitRequested{false};

  // Array with all of the state's objects
  std::unordered_map<int, std::shared_ptr<GameObject>> gameObjects;

  // Whether the state has executed the start method
  bool started{false};

  // ID counter for game objects
  int nextObjectId{0};

  // Structure that maps each component that renders to it's corresponding render layer
  std::unordered_map<RenderLayer, std::vector<std::weak_ptr<Component>>>
      layerStructure;
};

#include "Component.h"

#endif