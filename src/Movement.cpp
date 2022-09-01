#include "Movement.h"

using namespace std;

void Movement::Update(float deltaTime)
{
  // Adjust speed
  Accelerate(deltaTime);

  // Follow a target if it exists
  if (followTarget)
    FollowTarget(deltaTime);

  // Move based on speed
  if (!velocity)
    return;

  gameObject.position += velocity * deltaTime;
}

void Movement::Accelerate(float deltaTime)
{
  // Target velocity
  Vector2 targetVelocity = targetDirection * targetSpeed;

  float frameAcceleration = deltaTime * acceleration;

  // New velocity
  velocity = targetVelocity * frameAcceleration + velocity * max(1.0f - frameAcceleration, 0.0f);
}

void Movement::Move(Vector2 direction, bool cancelFollow)
{
  targetDirection = direction;
  followTarget = followTarget && !cancelFollow;
}

void Movement::MoveTo(Vector2 position, std::function<void()> callback)
{
  targetPosition = position;
  followTarget = true;
  targetReachCallback = callback;
}

void Movement::FollowTarget(float deltaTime)
{
  if (followTarget == false)
    return;

  // Check if arrived
  if (Vector2::SqrDistance(gameObject.position, targetPosition) < deltaTime * deltaTime * velocity.SqrMagnitude())
  {
    followTarget = false;
    gameObject.position = targetPosition;
    velocity = Vector2::Zero();

    if (targetReachCallback != nullptr)
      targetReachCallback();

    return;
  }

  // Get target angle
  float targetAngle = Vector2::AngleBetween(gameObject.position, targetPosition);

  Move(Vector2::Right().Rotated(targetAngle));
}
