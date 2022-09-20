#ifndef __COLLIDER__
#define __COLLIDER__

#include "GameObject.h"
#include "Component.h"
#include "Vector2.h"
#include "Rectangle.h"

class Collider : public Component
{
public:
  // Explicitly initialize box
  Collider(GameObject &associatedObject, Rectangle box);

  // Use sprite's box
  Collider(GameObject &associatedObject, std::shared_ptr<Sprite> sprite, Vector2 scale = Vector2::One());

  // Collision detection area
  Rectangle box;

  void Update(float deltaTime) override;

private:
};

#endif