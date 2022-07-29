#include <algorithm>
#include <iostream>
#include "Camera.h"
#include "InputManager.h"

using namespace std;

#define LENGTH(array) sizeof(array) / sizeof(array[0])
#define CLAMP(value, minValue, maxValue) min(max(value, minValue), maxValue)

Vector2 GetInputSpeedChange();

void Camera::Update(float deltaTime)
{
  // Get displacement from input, taking delta time in consideration
  auto frameSpeedChange = GetInputSpeedChange() * acceleration * deltaTime;

  // cout << (string)speed << endl;

  // If it's null and speed isn't, set it to the gravity
  if (speed && !frameSpeedChange)
  {
    // Set the displacement to the opposite direction of current speed
    frameSpeedChange = Vector2(speed).Normalized() * -gravity;

    // Cap to the current speed value
    frameSpeedChange.CapMagnitude(speed.Magnitude());
  }

  // if (frameSpeedChange)
  //   cout << (string)frameSpeedChange << endl;

  // Move
  Move(frameSpeedChange, deltaTime);
}

void Camera::Move(Vector2 speedModification, float deltaTime)
{
  // Add to the camera speed
  speed += speedModification;

  // Check that it does not exceed the limits
  speed.CapMagnitude(maxSpeed);

  // Displace it
  position += speed * deltaTime;
}

// Gets the displacement directions from input
Vector2 GetInputSpeedChange()
{
  // Get input reference
  auto inputManager = InputManager::GetInstance();

  // Will hold camera displacement values
  Vector2 frameSpeedChange;

  // Map each key direction to an index
  typedef decltype(UP_ARROW_KEY) KeyType;

  KeyType keyDirectionMap[] =
      {UP_ARROW_KEY, LEFT_ARROW_KEY, DOWN_ARROW_KEY, RIGHT_ARROW_KEY};

  // Map each displacement direction to an index, corresponding to the key direction map
  Vector2 displacementMap[LENGTH(keyDirectionMap)] =
      {Vector2::Up(), Vector2::Right(), Vector2::Down(), Vector2::Left()};

  // Catch button presses
  for (size_t i = 0; i < LENGTH(keyDirectionMap); ++i)
  {

    // Check if this direction is pressed
    if (inputManager.IsKeyDown(keyDirectionMap[i]))
    {
      // string direction;

      // if (i == 0)
      //   direction = "up";
      // else if (i == 1)
      //   direction = "left";
      // else if (i == 2)
      //   direction = "down";
      // else if (i == 3)
      //   direction = "right";

      // If so, add this displacement to the sum
      frameSpeedChange += displacementMap[i];

      // cout << "Pressed " << direction << ", new speed: " << (string)frameSpeedChange << endl;
    }
  }

  // if (frameSpeedChange)
  //   cout << "Speed change: " << (string)frameSpeedChange << endl;

  return frameSpeedChange;
}