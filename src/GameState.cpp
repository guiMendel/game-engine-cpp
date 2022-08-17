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
  background->AddComponent<Sprite>("./assets/image/ocean.jpg", RenderLayer::Background, false);

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
  alien->AddComponent<Sprite>("./assets/image/alien.png", RenderLayer::Enemies);

  // Get alien behavior
  alien->AddComponent<Alien>(4);

  // Get movement
  alien->AddComponent<Movement>(175);

  // Get health
  alien->AddComponent<Health>();

  return alien;
}

GameState::GameState() : inputManager(InputManager::GetInstance()), music("./assets/music/main.mp3")
{
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
  for (auto &objectPair : gameObjects)
    objectPair.second->Update(deltaTime);

  // Check for dead objects
  for (auto &objectPair : gameObjects)
  {
    if (objectPair.second->DestroyRequested() == false)
      continue;

    // If is dead, delete
    gameObjects.erase(objectPair.first);

    printf("Objects size: was %d, is now %d\n", gameObjects.size() + 1, gameObjects.size());
  }
}

void GameState::Render()
{
  // Foreach layer
  for (int layer{0}; layer != (int)RenderLayer::None; layer++)
  {
    // Get the layer's components
    auto &components = layerStructure[(RenderLayer)layer];

    // For each component in this layer
    auto componentIterator{components.begin()};

    while (componentIterator != components.end())
    {
      // Lock the component
      if (auto component = componentIterator->lock())
      {
        // Render it
        component->Render();

        // Advance
        componentIterator++;
      }
      // If lock fails, it was erased, so remove it
      else
      {
        componentIterator = components.erase(componentIterator);
      }
    }
  }
}

shared_ptr<GameObject> GameState::AddObject(shared_ptr<GameObject> gameObject)
{
  // Store it
  gameObjects[gameObject->id] = gameObject;

  // Call it's start method
  if (started)
    gameObject->Start();

  return gameObject;
}

weak_ptr<GameObject> GameState::GetPointer(const GameObject *targetObject)
{
  // Find this pointer in the list
  auto foundObjectIterator = find_if(
      gameObjects.begin(), gameObjects.end(),
      [targetObject](const auto objectPair)
      { return objectPair.second.get() == targetObject; });

  // Catch nonexistent
  if (foundObjectIterator == gameObjects.end())
  {
    // Return empty pointer
    return weak_ptr<GameObject>();
  }

  return weak_ptr<GameObject>(foundObjectIterator->second);
}

void GameState::Start()
{
  started = true;

  LoadAssets();

  // Add a background
  auto background = CreateBackgroundObject();
  gameObjects[background->id] = background;

  // Add a tilemap
  auto tilemap = CreateTilemapObject();
  gameObjects[tilemap->id] = tilemap;

  // Play the music
  music.Play();

  // Add an alien
  auto alien = CreateAlienObject();
  gameObjects[alien->id] = alien;

  for (auto &objectPair : gameObjects)
    objectPair.second->Start();
}

void GameState::RegisterLayerRenderer(shared_ptr<Component> component)
{
  // Simply ignore invalid requests
  if (!component)
    return;

  // Add it's entry
  layerStructure[component->GetRenderLayer()].emplace_back(component);
}
