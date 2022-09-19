#ifndef __PENGUIN_CANNON__
#define __PENGUIN_CANNON__

#include "GameObject.h"
#include "Component.h"
#include <memory>

class PenguinCannon : public Component
{
public:
  // Projectile speed
  static const float projectileSpeed;

  // Projectile time to live, in seconds
  static const float projectileTimeToLive;

  // Damage of projectile
  static const float projectileDamage;

  PenguinCannon(GameObject &associatedObject) : Component(associatedObject) {}

  void Update([[maybe_unused]] float deltaTime) override;

  void Shoot();

  // Get gun point position
  Vector2 GunPointPosition();
};

#endif