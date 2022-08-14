#ifndef __MINION__
#define __MINION__

#include "GameObject.h"
#include "Component.h"
#include "Vector2.h"

#include <memory>

class Minion : public Component
{
public:
  // Speed at which to orbit the host alien, in radians
  const float angularSpeed = 0.5;

  // Orbit radius
  const float orbitRadius = 120;

  Minion(GameObject &associatedObject, std::weak_ptr<GameObject> hostPointer, float startingArc = 0);

  void Update(float deltaTime) override;
  void Render() override {}
  void Start() override {}

  void Shoot(Vector2 target);

private:
  // Alien object around which to orbit
  std::weak_ptr<GameObject> hostPointer;

  float arc;
};

#endif