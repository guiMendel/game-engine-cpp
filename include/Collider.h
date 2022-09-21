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

  void Update(float deltaTime) override;

  TODO: COLOCAR UM START QUE ANUNCIA ESTE COLLIDER PAR AO GAMEOBJECT OU GAMESTATE SLA

  void SetBox(const Rectangle &box);
  Rectangle GetBox() const;

private:
  // Collision detection area
  Rectangle box;

  // Maximum distance of a vertex from the rectangle's center
  float maxVertexDistanceSquared;
};

#endif