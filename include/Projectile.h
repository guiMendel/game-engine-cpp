#ifndef __BULLET__
#define __BULLET__

#include "GameObject.h"
#include "Component.h"
#include "Vector2.h"
#include <memory>

class Projectile : public Component
{
public:
  Projectile(
      GameObject &associatedObject,
      float startingAngle,
      float speed,
      float timeToLive,
      float damage,
      std::weak_ptr<GameObject> target = std::weak_ptr<GameObject>(),
      float chaseSteering = 0.5);

  RenderLayer GetRenderLayer() override { return RenderLayer::None; }
  
  void Update(float deltaTime) override;

  float GetDamage() { return damage; }

private:
  // Current speed
  Vector2 speed;

  // Current angle
  float angle;

  // How much tim it still has to live
  float timeToLive;

  // How much damage it will do
  float damage;

  // A target to chase (if empty, goes straight)
  std::weak_ptr<GameObject> targetWeak;

  // Chase steering power, in radians
  float chaseSteering;

  void Chase();
};

#endif