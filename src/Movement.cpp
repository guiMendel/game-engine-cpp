#include "Movement.h"

void Movement::Update(float deltaTime)
{
  FollowTarget(deltaTime);

  // Move based on speed
  if (!speed)
    return;

  gameObject.box += speed * deltaTime;
}

void Movement::MoveTo(Vector2 position, std::function<void()> callback, bool recenterCoordinates)
{
  if (recenterCoordinates)
  {
    position = Vector2(position.x - gameObject.box.width / 2, position.y - gameObject.box.height / 2);
  }

  targetPosition = position;
  followTarget = true;
  targetReachCallback = callback;
}

void Movement::FollowTarget(float deltaTime)
{
  if (followTarget == false)
    return;

  // Check if arrived
  if (Vector2::SqrDistance((Vector2)gameObject.box, targetPosition) < deltaTime * deltaTime * speed.SqrMagnitude())
  {
    followTarget = false;
    gameObject.box = targetPosition;
    speed = Vector2::Zero();

    if (targetReachCallback != nullptr)
      targetReachCallback();

    return;
  }

  // If not arrived, apply speed
  // Get target angle
  float targetAngle = Vector2::AngleBetween((Vector2)gameObject.box, targetPosition);

  speed = Vector2::Right().Rotated(targetAngle) * moveSpeed;
}
