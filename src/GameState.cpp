#include <algorithm>
#include <math.h>
#include "GameState.h"
#include "Vector2.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"
#include <iostream>
using namespace std;

GameState::GameState() : inputManager(InputManager::GetInstance())
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
        if (component->IsEnabled())
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

  // Load any assets
  LoadAssets();

  // Create the initial objects
  InitializeObjects();

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
