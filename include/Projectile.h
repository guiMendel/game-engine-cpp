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
      Tag targetTag,
      float startingAngle,
      float speed = 300.0f,
      float timeToLive = 5.0f,
      float damage = 50.0f,
      std::weak_ptr<GameObject> target = std::weak_ptr<GameObject>(),
      float chaseSteering = 0.5f);

  RenderLayer GetRenderLayer() override { return RenderLayer::None; }

  void Update(float deltaTime) override;

  void OnCollision(GameObject &other) override;

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

  // Which tag of object will this projectile collide with
  Tag targetTag;

  void Chase();
};

#endif