#include "MainState.h"
#include "Recipes.h"
#include "Camera.h"

using namespace std;

void MainState::InitializeObjects()
{
  // Add a background
  CreateObject("Background", Recipes::Background("./assets/image/ocean.jpg"));

  // Add a tilemap
  CreateObject("Tilemap", Recipes::Tilemap);

  // Add an alien
  CreateObject("Alien", Recipes::Alien, Vector2(512, 300));

  // Add penguins
  auto penguin = CreateObject("Penguin Body", Recipes::PenguinBody);

  // Add cannon as child
  CreateObject("Penguin Cannon", Recipes::PenguinCannon, penguin->GetPosition(), penguin->GetRotation(), penguin);

  // Make camera follow penguin
  Camera::GetInstance().Follow(penguin);

  // Play music
  // music.Play("./assets/music/main.mp3");
}

void MainState::Update(float deltaTime)
{
  // Call base
  GameState::Update(deltaTime);

  // Pop this state on esc key
  if (inputManager.KeyRelease(ESCAPE_KEY))
  {
    popRequested = true;
  }
}