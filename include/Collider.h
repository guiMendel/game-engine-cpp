#ifndef __COLLIDER__
#define __COLLIDER__

#include "GameObject.h"
#include "Component.h"
#include "Vector2.h"
#include "Rectangle.h"

class Sprite;

class Collider : public Component
{
public:
  // Explicitly initialize box
  Collider(GameObject &associatedObject, Rectangle box);

  // Use sprite's box
  Collider(GameObject &associatedObject, std::shared_ptr<Sprite> sprite, Vector2 scale = Vector2::One());

  void Start() override;

  void SetBox(const Rectangle &box);
  Rectangle GetBox() const;

  float GetMaxVertexDistance() const { return maxVertexDistance; }

private:
  // Collision detection area
  Rectangle box;

  // Maximum distance of a vertex from the rectangle's center
  float maxVertexDistance;
};

#include "Sprite.h"

#endif