#include <algorithm>
#include "Camera.h"
#include "InputManager.h"

using namespace std;

#define LENGTH(array) sizeof(array) / sizeof(array[0])
#define CLAMP(value, minValue, maxValue) min(max(value, minValue), maxValue)

Vector2 GetInputDisplacement();

void Camera::Update(float deltaTime)
{
  // Get displacement from input, taking delta time in consideration
  auto frameDisplacement = GetInputDisplacement() * deltaTime;

  // If it's null and speed isn't, set it to the gravity
  if (speed && !frameDisplacement)
  {
    // Set the displacement to the opposite direction of current speed
    frameDisplacement = Vector2::Right().Rotated(-speed.Angle()) * gravity;

    // Cap to the current speed value
    frameDisplacement.CapMagnitude(speed.Magnitude());
  }

  // Add to the camera speed
  speed += frameDisplacement;

  // Check that it does not exceed the limits
  speed.CapMagnitude(maxSpeed);

  // Move
  Move(deltaTime);
}

void Camera::Move(float deltaTime)
{
  position += speed * deltaTime;
}

// Gets the displacement directions from input
Vector2 GetInputDisplacement()
{
  // Get input reference
  auto inputManager = InputManager::GetInstance();

  // Will hold camera displacement values
  Vector2 frameDisplacement;

  // Map each key direction to an index
  typedef decltype(UP_ARROW_KEY) KeyType;

  KeyType keyDirectionMap[] =
      {UP_ARROW_KEY, LEFT_ARROW_KEY, DOWN_ARROW_KEY, RIGHT_ARROW_KEY};

  // Map each displacement direction to an index, corresponding to the key direction map
  // Directions need to be the inverse of the key direction, to create the camera movement illusion
  Vector2 displacementMap[LENGTH(keyDirectionMap)] =
      {Vector2::Down(), Vector2::Right(), Vector2::Up(), Vector2::Left()};

  // Catch button presses
  for (size_t i = 0; i < LENGTH(keyDirectionMap); ++i)
  {
    // Check if this direction is pressed
    if (inputManager.IsKeyDown(keyDirectionMap[i]))
    {
      // If so, add this displacement to the sum
      frameDisplacement += displacementMap[i];
    }
  }

  return frameDisplacement;
}