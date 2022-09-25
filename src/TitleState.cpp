#include "TitleState.h"
#include "Recipes.h"
#include "Game.h"
#include "MainState.h"

using namespace std;

void TitleState::InitializeObjects()
{
  // Add a background
  CreateObject("Background", Recipes::Background("./assets/image/title.jpg"));
}

void TitleState::Update(float deltaTime)
{
  // Call base
  GameState::Update(deltaTime);

  // Quit on esc key
  if (inputManager.KeyRelease(ESCAPE_KEY))
  {
    quitRequested = true;
  }

  // Start main state on space key
  else if (inputManager.KeyPress(SPACE_KEY))
  {
    Game::GetInstance().PushState(make_unique<MainState>());
  }
}
