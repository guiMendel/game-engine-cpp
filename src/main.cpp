#include <iostream>
#include "Game.h"
// #include "test.h"

using namespace std;

int main()
{
  // Get game instance & run
  try
  {
    Game::GetInstance().Run();
  }
  // Catch any runtime errors
  catch (const runtime_error &error)
  {
    cerr << "=> ERROR: " << error.what() << endl;
  }

  return 0;
}