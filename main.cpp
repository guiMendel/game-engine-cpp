#include <iostream>
#include <SDL2/SDL.h>
#include <unistd.h>

using namespace std;

int main()
{
  cout << "Hello there!" << endl;
  SDL_Init(SDL_INIT_VIDEO);

  return 0;
}