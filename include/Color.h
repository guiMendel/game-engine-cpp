#ifndef __COLOR__
#define __COLOR__

#include "SDL.h"

struct Color
{
  // With each channel
  Color(int red, int green, int blue, int alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

  // With only colors
  Color(int red, int green, int blue) : Color(red, green, blue, 255) {}

  // Copy constructor
  Color(const Color &other) : Color(other.red, other.green, other.blue, other.alpha) {}

  // Default to white
  Color() : Color(White()) {}

  // === PREFAB COLORS

  static Color White() { return Color(255, 255, 255); }
  static Color Black() { return Color(0, 0, 0); }
  static Color Red() { return Color(255, 0, 0); }
  static Color Green() { return Color(0, 255, 0); }
  static Color Blue() { return Color(0, 255, 255); }

  // === SDL INTEGRATION

  operator SDL_Color() const { return SDL_Color{(Uint8)red, (Uint8)green, (Uint8)blue, (Uint8)alpha}; }

  // === FIELDS

  int red;
  int green;
  int blue;
  int alpha;
};

#endif