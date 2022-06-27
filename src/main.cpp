#include <iostream>
#include "Game.h"
// #include "test.h"

using namespace std;

int main(int argc, char **argv)
{
  // Get game instance & run
  try
  {
    Game &gameInstance = Game::GetInstance();

    gameInstance.Run();
  }
  // Catch any runtime errors
  catch (const runtime_error &error)
  {
    cerr << "=> ERROR: " << error.what() << endl;
  }

  return 0;
}