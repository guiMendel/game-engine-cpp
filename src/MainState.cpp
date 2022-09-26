#include "MainState.h"
#include "GameData.h"
#include "EndState.h"
#include "Recipes.h"
#include "Camera.h"
#include "Tilemap.h"

using namespace std;

const int MainState::totalAliens{5};

void MainState::AdvanceState(bool victory)
{
  if (victory)
    GameData::GetInstance().playerWon = true;

  Game::GetInstance().PushState(make_unique<EndState>());
  popRequested = true;
}

void MainState::InitializeObjects()
{
  // Add a background
  CreateObject("Background", Recipes::Background("./assets/image/ocean.jpg"));

  // Add a tilemap
  auto tilemap = CreateObject("Tilemap", Recipes::Tilemap)->GetComponent<TileMap>();

  // Function to count alien death
  auto CountAlienDeath = [this]()
  {
    //  If all aliens are dead, win
    if (--alienCount == 0)
      AdvanceState(true);
  };

  // Add aliens
  for (int i = 0; i < totalAliens; i++)
  {
    // Get coordinates for it
    Vector2 alienPosition = Vector2(
        RandomRange(-tilemap->GetWidth() / 2, tilemap->GetWidth() / 2),
        RandomRange(-tilemap->GetHeight() / 2, tilemap->GetHeight() / 2));

    auto alien = CreateObject("Alien", Recipes::Alien, alienPosition);

    // When it dies, decrement counter
    alien->GetComponent<Health>()->OnDeath.AddListener("stateCounterDecrement", CountAlienDeath);
  }

  // Add penguins
  auto penguin = CreateObject("Penguin Body", Recipes::PenguinBody);

  // Add cannon as child
  CreateObject("Penguin Cannon", Recipes::PenguinCannon, penguin->GetPosition(), penguin->GetRotation(), penguin);

  // Pass on penguin death
  penguin->GetComponent<Health>()->OnDeath.AddListener(
      "stateAdvance",
      [this]()
      { AdvanceState(false); });

  // Make camera follow penguin
  Camera::GetInstance()
      .Follow(penguin);

  // Play music
  music.Play("./assets/music/main.mp3");
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