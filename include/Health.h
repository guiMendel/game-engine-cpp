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

  Health(GameObject &associatedObject, float totalHealth) : Component(associatedObject), healthPoints(totalHealth) {}

  RenderLayer GetRenderLayer() override { return RenderLayer::None; }

private:
  // Current health status
  float healthPoints;

  // Whether has already triggered death
  bool deathTriggered{false};
};

#endif