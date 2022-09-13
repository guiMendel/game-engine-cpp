#ifndef __CAMERA_FOLLOWER__
#define __CAMERA_FOLLOWER__

#include "Component.h"
#include "Camera.h"
#include <iostream>

using namespace std;

class CameraFollower : public Component
{
public:
  CameraFollower(GameObject &associatedObject) : Component(associatedObject) {}

  void Update([[maybe_unused]] float deltaTime) override
  {
    gameObject.SetPosition(-Camera::GetInstance().position);
  }

  RenderLayer GetRenderLayer() override { return RenderLayer::None; }
};

#endif