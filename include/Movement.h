#ifndef __MOVEMENT__
#define __MOVEMENT__

#include <functional>
#include "GameObject.h"
#include "Component.h"
#include "Vector2.h"

class Movement : public Component
{
public:
  // Current speed
  Vector2 speed{0, 0};

  Movement(GameObject &associatedObject, float moveSpeed)
      : Component(associatedObject), moveSpeed(moveSpeed) {}

  void Update(float deltaTime) override;
  void Start() override {}
  void Render() override {}

  // Start moving towards this target
  // recenterCoordinates adjusts the given coordinates so that they are relative to the object's center, and not top left
  void MoveTo(Vector2 position, std::function<void()> callback = nullptr, bool recenterCoordinates = true);

private:
  // A target to move towards each frame (if followTarget is true)
  Vector2 targetPosition;

  // Whether to follow current target
  bool followTarget{false};

  // Speed applied to the movement direction
  float moveSpeed;

  // Callback to execute on target reach
  std::function<void()> targetReachCallback;

  void FollowTarget(float deltaTime);
};

#endif