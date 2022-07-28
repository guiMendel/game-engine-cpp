#ifndef __RECTANGLE__
#define __RECTANGLE__

#include <initializer_list>
#include <SDL.h>
#include "Vector2.h"

class Rectangle
{
public:
  // X coordinate
  float x;

  // Y coordinate
  float y;

  // Width
  float width;

  // Height
  float height;

  // === CONSTRUCTORS

  Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

  Rectangle() : x(0), y(0), width(0), height(0) {}

  Rectangle(std::initializer_list<float> list)
      : x(*list.begin()), y(*(list.begin() + 1)), width(*(list.begin() + 2)), height(*(list.begin() + 3)) {}

  Rectangle(const Rectangle &other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

  Rectangle(const Rectangle &&other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

  // === OPERATIONS

  Rectangle operator+(const Vector2 &vector) const
  {
    return Rectangle(x + vector.x, y + vector.y, width, height);
  }

  Rectangle operator-(const Vector2 &vector) const
  {
    return Rectangle(x - vector.x, y - vector.y, width, height);
  }

  Vector2 Coordinates() const { return Vector2(x, y); }

  Vector2 GetCenter() const { return Vector2(x + width / 2, y + height / 2); }

  // Indicates if a given coordinate is contained by the rectangle
  bool Contains(const Vector2 &vector) const
  {
    return vector.x >= x && vector.x <= x + width && vector.y >= y && vector.y <= y + height;
  }

  // Convert to sdl rect
  operator SDL_Rect() const { return SDL_Rect{(int)x, (int)y, (int)width, (int)height}; }
};

#endif