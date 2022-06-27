#ifndef __VECTOR2__
#define __VECTOR2__

#include <initializer_list>
#include <cmath>

class Vector2
{
public:
  // X coordinate
  float x;

  // Y coordinate
  float y;

  // Initialize constructor
  Vector2(float x, float y) : x(x), y(y) {}

  // Base constructor
  Vector2() : Vector2(0, 0) {}

  // With initializer_list
  Vector2(std::initializer_list<float> list) : x(*list.begin()), y(*(list.begin() + 1)) {}

  // Copy constructor
  Vector2(const Vector2 &other) : x(other.x), y(other.y) {}

  // Move constructor
  Vector2(const Vector2 &&other) : x(other.x), y(other.y) {}

  // === ALGEBRAIC OPERATIONS

  Vector2 operator+(const Vector2 &other) const { return Vector2(x + other.x, y + other.y); }

  Vector2 operator-(const Vector2 &other) const { return Vector2(x - other.x, y - other.y); }

  Vector2 operator*(const Vector2 &other) const { return Vector2(x * other.x, y * other.y); }

  Vector2 operator/(const Vector2 &other) const { return Vector2(x / other.x, y / other.y); }

  Vector2 operator*(float value) const { return Vector2(x * value, y * value); }

  Vector2 operator/(float value) const { return Vector2(x / value, y / value); }

  // === OTHER OPERATIONS

  float SqrMagnitude() const { return x * x + y * y; }

  float Magnitude() const { return sqrt(SqrMagnitude()); }

  Vector2 Normalized() const { return Vector2(*this) / Magnitude(); }

  float Angle() const { return atan2(y, x); }

  // Returns a vector rotated by the given angle, in radians
  Vector2 Rotated(float angle) const
  {
    return Vector2(x * cos(angle) - y * sin(angle), y * cos(angle) - x * sin(angle));
  }

  // === OPERATORS BETWEEN 2 VEC2S

  static float Distance(const Vector2 &v1, const Vector2 &v2) { return (v1 - v2).Magnitude(); }
};

#endif