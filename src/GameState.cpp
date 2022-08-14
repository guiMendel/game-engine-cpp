#include <algorithm>
#include <math.h>
#include "GameState.h"
#include "Vector2.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "Movement.h"
#include "Health.h"
#include <iostream>
using namespace std;

shared_ptr<GameObject> CreateBackgroundObject()
{
  auto background = make_shared<GameObject>();

  // Get a background sprite
  background->AddComponent<Sprite>("./assets/image/ocean.jpg");

  // Make it follow the camera
  background->AddComponent<CameraFollower>();

  return background;
}

shared_ptr<GameObject> CreateTilemapObject()
{
  // Get the Tileset
  TileSet *tileset = new TileSet(64, 64, "./assets/image/tileset.png");

  auto tilemap = make_shared<GameObject>();

  // Get a tilemap
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset);

  return tilemap;
}

shared_ptr<GameObject> CreateAlienObject()
{
  auto alien = make_shared<GameObject>(Vector2(512, 300));

  // Get alien sprite
  auto sprite = alien->AddComponent<Sprite>("./assets/image/alien.png");

  // Get alien behavior
  alien->AddComponent<Alien>(4);

  // Get movement
  alien->AddComponent<Movement>(175);

  // Get health
  alien->AddComponent<Health>();

  // Center it
  sprite.CenterObject();

  return alien;
}

GameState::GameState() : inputManager(InputManager::GetInstance()), music("./assets/music/main.mp3")
{
  quitRequested = false;

  // Add a background
  gameObjects.push_back(CreateBackgroundObject());

  // Add a tilemap
  gameObjects.push_back(CreateTilemapObject());

  // Play the music
  music.Play();

  // Add an alien
  gameObjects.push_back(CreateAlienObject());
}

void GameState::LoadAssets()
{
}

void GameState::Update(float deltaTime)
{
  // Quit if necessary
  if (inputManager.KeyRelease(ESCAPE_KEY) || inputManager.QuitRequested())
  {
    quitRequested = true;
  }

  // Update camera
  Camera::GetInstance().Update(deltaTime);

  // Update game objects
  for (auto &gameObject : gameObjects)
    gameObject->Update(deltaTime);

  // Check for dead objects
  for (int i = 0; i < (int)gameObjects.size(); i++)
  {
    if (gameObjects[i]->DestroyRequested() == false)
      continue;

    // If is dead, delete
    gameObjects.erase(gameObjects.begin() + i);
  }
}

void GameState::Render()
{
  // Render objects
  for (auto &gameObject : gameObjects)
    gameObject->Render();
}

std::shared_ptr<GameObject> GameState::AddObject(std::shared_ptr<GameObject> gameObject)
{
  // Store it
  gameObjects.push_back(gameObject);

  // Call it's start method
  if (started)
    gameObject->Start();

  return gameObject;
}

std::weak_ptr<GameObject> GameState::GetPointer(const GameObject *targetObject)
{
  // Find this pointer in the list
  auto foundObjectIterator = find_if(
      gameObjects.begin(), gameObjects.end(),
      [targetObject](const auto gameObject)
      { return gameObject.get() == targetObject; });

  // Catch nonexistent
  if (foundObjectIterator == gameObjects.end())
  {
    // Return empty pointer
    return weak_ptr<GameObject>();
  }

  return weak_ptr(*foundObjectIterator);
}

void GameState::Start()
{
  LoadAssets();

  for (auto gameObject : gameObjects)
    gameObject->Start();

  started = true;
}