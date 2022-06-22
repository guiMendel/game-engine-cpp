#ifndef __GAME__
#define __GAME__

#include <SDL.h>
#include <memory>
#include "GameState.h"

// Class with the main game logic
class Game
{
  // Game instance
  static std::unique_ptr<Game> gameInstance;

  // Current state
  std::unique_ptr<GameState> state;

  // Game window
  std::unique_ptr<SDL_Window> window;

  // Game window renderer
  std::unique_ptr<SDL_Renderer> renderer;

  // Singleton constructor
  Game(std::string title, int width, int height);

public:
  // Gets the game instance if it exists or creates one if it doesn't
  static int GetInstance();

  // Gets the current game state
  GameState &GetState() const;

  // Gets the renderer
  SDL_Renderer &GetRenderer() const;

  // Starts the game
  void Run();
};

#endif