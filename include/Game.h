#ifndef __GAME__
#define __GAME__

#include <SDL.h>
#include <memory>
#include "GameObject.h"
#include "GameState.h"
#include "Helper.h"

// Class with the main game logic
class Game
{
public:
  // === CONFIGURATION

  // Defines the maximum frames per second
  static const int frameRate = 30;

  // Defines the resolution width
  static const int screenWidth = 1024;
  // Defines the resolution height
  static const int screenHeight = 600;

  // === FUNCTIONS

  // Gets the game instance if it exists or creates one if it doesn't
  static Game &GetInstance();

  // Gets the current game state
  GameState &GetState() const { return *state; }

  // Gets the renderer
  SDL_Renderer *GetRenderer() const { return renderer.get(); }

  // Starts the game
  void Run();

  // Explicit destructor
  ~Game();

private:
  // Game instance
  static std::unique_ptr<Game> gameInstance;

  // Current state
  std::unique_ptr<GameState> state;

  // The window we'll be rendering to (with destructor function)
  Helper::auto_ptr<SDL_Window> window;

  // Renderer for the window (with destructor function)
  Helper::auto_ptr<SDL_Renderer> renderer;

  // Singleton constructor
  Game(std::string title, int width, int height);
};

#endif