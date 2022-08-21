#ifndef __PENGUIN_BODY__
#define __PENGUIN_BODY__

#include "GameObject.h"
#include "Component.h"
#include <memory>

class PenguinBody : public Component
{
public:
  PenguinBody(GameObject &associatedObject) : Component(associatedObject) {}

  RenderLayer GetRenderLayer() override { return RenderLayer::None; }

private:
  // Access facilitator
  std::weak_ptr<GameObject> cannonWeak;
};

#endif