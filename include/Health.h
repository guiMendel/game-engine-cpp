#ifndef __HEALTH__
#define __HEALTH__

#include "GameObject.h"
#include "Component.h"
#include "Event.h"

class Health : public Component
{
public:
  // Death event
  Event OnDeath;

  void TakeDamage(float damage);

  Health(GameObject& associatedObject) : Component(associatedObject) {}

  void Start() override {}
  void Update([[maybe_unused]] float deltaTime) override {}
  void Render() override {}

private:
  // Current health status
  float healthPoints;

  // Whether has already triggered death
  bool deathTriggered;
};

#endif