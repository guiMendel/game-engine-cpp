#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

// === INITIALIZE STATIC FIELDS =================================

// Game instance
unique_ptr<Game> Game::gameInstance = nullptr;

// === PRIVATE METHODS =================================

Game::Game(string title, int width, int height)
{
  // Check for invalid existing instance
  if (Game::gameInstance)
    throw invalid_argument("Tried to instantiate another Game instance");

  // Initialize SDL & all it's necessary subsystems
  auto error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

  // Catch any errors
  if (error)
    throw runtime_error("Failed to initialize SDL. Reported error: " + string(SDL_GetError()));

  // Initialize the image module
  cout << "Initializing SDL" << endl;
}

// === PUBLIC METHODS =================================

int Game::GetInstance()
{
  // If it doesn't exist...
  if (!gameInstance)
  {
    // Create it
    gameInstance = unique_ptr<Game>(new Game("The Watch Penguins", 600, 600));
  }

  // Return the instance
  return 1;
}