#ifndef __COLLIDER__
#define __COLLIDER__

#include "GameObject.h"
#include "Component.h"
#include "Vector2.h"
#include "Rectangle.h"

class Collider : public Component
{
public:
  Collider(GameObject &associatedObject, Rectangle box) : Component(associatedObject), box(box) {}

  // Collision detection area
  Rectangle box;

  void Update(float deltaTime) override;

private:
};

#endif