#include <SDL.h>
#include <memory>

// Class with the main game logic
class Game
{
  // Game instance
  static std::unique_ptr<Game> gameInstance;

  // Singleton constructor
  Game(std::string title, int width, int height);

public:
  // Gets the game instance if it exists or creates one if it doesn't
  static int GetInstance();
};
