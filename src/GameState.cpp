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

// Initialize root object
GameState::GameState() : inputManager(InputManager::GetInstance()), rootObject(new GameObject(*this))
{
}

void GameState::UpdateObjects(float deltaTime)
{
  for (auto &objectPair : gameObjects)
    objectPair.second->Update(deltaTime);
}

void GameState::DeleteObjects()
{
  // Check for dead objects
  vector<shared_ptr<GameObject>> deadObjects;

  // Collect them
  for (auto &objectPair : gameObjects)
  {
    // If is dead, collect
    if (objectPair.second->DestroyRequested())
      deadObjects.push_back(objectPair.second);

    // Not a good idea to delete them here directly, as it would invalidate this loop's iterator
  }

  // Erase them
  for (auto &deadObject : deadObjects)
    deadObject->InternalDestroy();
}

void GameState::DetectCollisions() {
  TODO:
  GUARDAR UM MAP DOS IDS DOS OBJETOS A UM VETOR DOS SEUS COLLDIERS
  AI QUANDO O COLLIDER DER START ELE SE REGISTRA NESSE VETOR
  AI VAMOS PODER TIRAR A REFERENCIA AOS COLLIDERS Q EU COLOQUEI EM GAMEOBJECT E TIRAR O FRIEND TB

  AI AQUI TEM Q PASSAR POR ESSE MAP E GERAR UM NOVO MAP IGUAL, MAS USANDO SAHREDPTR EM VEZ DE WEAK (JA REMOVE OS WEAK EXPIRED TAMBEM)
  AI DPS PASSA UM POR UM TESTANDO COLISAO COM OS DEMAIS
  LEMBRAR D EUSAR UM ITERADOR E SO COPARAR COM OS OBJECTOS DA FRENTE, PQ OS DE TRAS JA TESTARAM COM ESTE OBJETO
  
  for (auto &objectPair : gameObjects) {
    
  }
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
  UpdateObjects(deltaTime);

  // Delete dead ones
  DeleteObjects();

  // Inform them of any collisions
  DetectCollisions();
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

void GameState::RemoveObject(int id)
{
  gameObjects.erase(id);
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
  if (started)
    return;

  // Load any assets
  LoadAssets();

  // Create the initial objects
  InitializeObjects();

  started = true;

  for (auto &objectPair : gameObjects)
    objectPair.second->Start();
}

void GameState::RegisterLayerRenderer(shared_ptr<Component> component)
{
  // Simply ignore invalid requests
  if (!component)
    return;

  // Get it's layer
  auto &layer = layerStructure[component->GetRenderLayer()];

  // Add it's entry
  layer.emplace_back(component);

  // Sort it
  sort(layer.begin(), layer.end(), [](weak_ptr<Component> comp1Weak, weak_ptr<Component> comp2Weak)
       { 
        auto comp1 = comp1Weak.lock();
        auto comp2 = comp2Weak.lock();

        // Leave as is if any of them has been erased
        if (comp1 == nullptr || comp2 == nullptr) return true;
        
        return comp1->GetRenderOrder() < comp2->GetRenderOrder(); });
}
