#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "MainState.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "Movement.h"
#include "Health.h"
#include <iostream>

using namespace std;

void PenguinBodyRecipe(shared_ptr<GameObject> penguin)
{
  // Get sprite
  penguin->AddComponent<Sprite>("./assets/image/penguin.png", RenderLayer::Player);

  // Add movement
  auto movement = penguin->AddComponent<Movement>(PenguinBody::acceleration, PenguinBody::maxSpeed);

  // Add behavior
  penguin->AddComponent<PenguinBody>(movement);

  // Add health
  penguin->AddComponent<Health>(PenguinBody::totalHealth);
}

void PenguinCannonRecipe(shared_ptr<GameObject> penguin)
{
  // Get sprite (put it on render order 1 to show ahead)
  penguin->AddComponent<Sprite>("./assets/image/cubngun.png", RenderLayer::Player, 1);

  // Add behavior
  penguin->AddComponent<PenguinCannon>();
}

void BackgroundRecipe(shared_ptr<GameObject> background)
{
  // Get a background sprite
  background->AddComponent<Sprite>("./assets/image/ocean.jpg", RenderLayer::Background, 0, false);

  // Make it follow the camera
  background->AddComponent<CameraFollower>();
}

void TilemapRecipe(shared_ptr<GameObject> tilemap)
{
  // Get the Tileset
  auto tileset = make_shared<TileSet>(64, 64, "./assets/image/tileset.png");

  // Render first tilemap layer below
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset, 0, RenderLayer::Tilemap);

  // Render second layer above
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset, 1, RenderLayer::Foreground);
}

// void AlienRecipe(shared_ptr<GameObject> alien)
// {
//   // Get alien sprite
//   alien->AddComponent<Sprite>("./assets/image/alien.png", RenderLayer::Enemies);

//   // Get alien behavior
//   alien->AddComponent<Alien>(6);

//   // Get movement
//   alien->AddComponent<Movement>(175);

//   // Get health
//   alien->AddComponent<Health>();
// }

void MainState::InitializeObjects()
{
  // Add a background
  CreateObject(BackgroundRecipe);

  // Add a tilemap
  CreateObject(TilemapRecipe);

  // Add an alien
  // CreateObject(AlienRecipe, Vector2(512, 300));

  // Add penguins
  auto penguin = CreateObject(PenguinBodyRecipe);

  // Add cannon as child
  CreateObject(PenguinCannonRecipe, penguin->GetPosition(), penguin->GetRotation(), penguin);

  // Play music
  music.Play("./assets/music/main.mp3");
}