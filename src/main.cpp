#include <iostream>
#include "Game.h"
// #include "test.h"

using namespace std;

int main()
{

  // cout << "Hello there! " << Test::getAbo() << endl;
  cout << "Hello there! " << endl;

  // Get game instance & run
  Game::GetInstance().Run();

  return 0;
}