#ifndef __BULLET__
#define __BULLET__

#include "GameObject.h"
#include "Component.h"

class Bullet : public Component
{
public:
  Bullet(
      GameObject &associatedObject,
      float startingAngle,
      float speed,
      float maxDistance,
      float damage);

  void Start() override;
  void Update(float deltaTime) override;
  void Render() override;

private:
};

#endif