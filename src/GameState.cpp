#include "GameState.h"

void GameState::LoadAssets()
{
}

void GameState::Update(float deltaTime)
{
  // === QUIT REQUESTS

  if (SDL_QuitRequested())
    quitRequested = true;
}

void GameState::Render()
{
  background.Render(0, 0);
}
