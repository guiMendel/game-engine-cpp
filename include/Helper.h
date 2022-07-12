#ifndef __HELPER__
#define __HELPER__

#include <vector>
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

  // Splits the given string into an array of strings, using the given delimiter as the separator token
  static auto SplitString(std::string text, std::string delimiter) -> std::vector<std::string>
  {
    // Will hold the results
    std::vector<std::string> items;

    // Holds the position of the next delimiter found
    size_t next = 0;

    // Remember the last delimiter position
    size_t last = 0;

    // While there are delimiters to go
    while ((next = text.find(delimiter, last)) != std::string::npos)
    {
      // Push the item right before the found delimiter
      items.push_back(text.substr(last, next - last));

      // Advance the delimiter position
      last = next + delimiter.length();
    }

    // When there's an item left after the last delimiter, push it too
    if (last < text.length())
      items.push_back(text.substr(last));

    return items;
  }

}

#endif