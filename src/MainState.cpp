#include "MainState.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "Movement.h"
#include "Health.h"

using namespace std;

void BackgroundRecipe(shared_ptr<GameObject> background)
{
  // Get a background sprite
  background->AddComponent<Sprite>("./assets/image/ocean.jpg", RenderLayer::Background, false);

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

void AlienRecipe(shared_ptr<GameObject> alien)
{
  // Get alien sprite
  alien->AddComponent<Sprite>("./assets/image/alien.png", RenderLayer::Enemies);

  // Get alien behavior
  alien->AddComponent<Alien>(6);

  // Get movement
  alien->AddComponent<Movement>(175);

  // Get health
  alien->AddComponent<Health>();
}

void MainState::InitializeObjects()
{
  // Add a background
  CreateObject(BackgroundRecipe);

  // Add a tilemap
  CreateObject(TilemapRecipe);

  // Add an alien
  CreateObject(AlienRecipe, Vector2(512, 300));

  // Play music
  music.Play("./assets/music/main.mp3");
}