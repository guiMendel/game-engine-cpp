#include "Minion.h"
#include <math.h>

Minion::Minion(GameObject &associatedObject, std::weak_ptr<GameObject> hostPointer, float startingArc)
    : Component(associatedObject), hostPointer(hostPointer), arc(startingArc)
{
  // Initialize radius
  orbitRadius = (rand() % (int)floor(radiusLimits[1] - radiusLimits[0])) + radiusLimits[0];
}

void Minion::Update(float deltaTime)
{
  auto hostLocked = hostPointer.lock();

  // If host is gone, destroy self
  if (!hostLocked)
  {
    gameObject.RequestDestroy();
    return;
  }

  // Update orbit position
  arc += angularSpeed * deltaTime;

  // Update radius position
  orbitRadius += radiusFloatSpeed * floatDirection;

  if (orbitRadius <= radiusLimits[0]) {
    orbitRadius = radiusLimits[0];
    floatDirection = 1;
  }

  else if (orbitRadius >= radiusLimits[1]) {
    orbitRadius = radiusLimits[1];
    floatDirection = -1;
  }

  // Get radial position vector
  Vector2 radialPosition = Vector2::Right(orbitRadius).Rotated(arc);

  // Update position
  gameObject.box.SetCenter((Vector2)hostLocked->box.GetCenter() + radialPosition);
}