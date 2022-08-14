#include "Minion.h"

Minion::Minion(GameObject &associatedObject, std::weak_ptr<GameObject> hostPointer, float startingArc)
    : Component(associatedObject), hostPointer(hostPointer)
{
  // Initialize arc
  arc = startingArc;
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

  // Get radial position vector
  Vector2 radialPosition = Vector2::Right(orbitRadius).Rotated(arc);

  // Update position
  gameObject.box.SetCenter((Vector2)hostLocked->box.GetCenter() + radialPosition);
}