#ifndef __HELPER__
#define __HELPER__

#include <string>
#include <SDL.h>

namespace Helper
{
  // Alias for unique pointer with destructor function
  template <class T>
  using auto_ptr = std::unique_ptr<T, void (*)(T *)>;

  // Throws exception if condition is false
  static void Assert(bool condition, std::string message, std::string explanation)
  {
    if (condition == false)
    {
      throw std::runtime_error(message + ". Reported error: " + explanation);
    }
  }

  // Throws exception if condition is false
  static void Assert(bool condition, std::string message)
  {
    Assert(condition, message, SDL_GetError());
  }
}

#endif