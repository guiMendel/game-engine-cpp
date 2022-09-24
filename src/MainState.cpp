#include "MainState.h"
#include "Recipes.h"
#include "Camera.h"

using namespace std;

void MainState::InitializeObjects()
{
  // Add a background
  CreateObject("Background", Recipes::Background);

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