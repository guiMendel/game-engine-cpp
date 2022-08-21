#ifndef __PENGUIN_CANNON__
#define __PENGUIN_CANNON__

#include "GameObject.h"
#include "Component.h"
#include <memory>

class PenguinCannon : public Component
{
public:
  PenguinCannon(GameObject &associatedObject) : Component(associatedObject) {}

  RenderLayer GetRenderLayer() override { return RenderLayer::None; }

  void Shoot();

private:
  // Access facilitator
  std::weak_ptr<GameObject> bodyWeak;
};

#endif