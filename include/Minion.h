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
  const float angularSpeed{0.5};

  // Speed at which the radius changes
  const float radiusFloatSpeed{1};

  // Limits to radius floating
  const float radiusLimits[2]{90, 160};

  // Projectile speed
  const float projectileSpeed{300};

  // Projectile time to live, in seconds
  const float projectileTimeToLive{5};

  // Damage of projectile
  const float projectileDamage{50};

  Minion(GameObject &associatedObject, std::weak_ptr<GameObject> hostPointer, float startingArc = 0);

  void Update(float deltaTime) override;
  void Render() override {}
  void Start() override {}

  void Shoot(Vector2 target);

private:
  // Alien object around which to orbit
  std::weak_ptr<GameObject> hostPointer;

  // Where in the orbit's circumference the minion currently is
  float arc;

  // Distance from the orbit center
  float orbitRadius;

  // Whether to float away or towards the center (1 or -1)
  float floatDirection{1};
};

#endif