#ifndef __FACE__
#define __FACE__

#include "GameObject.h"
#include "Component.h"
#include <string>
#include <iostream>

class Face : public Component
{
public:
  Face(GameObject &associatedObject) : Component(associatedObject) {}

  // Subtracts this damage from the current hitPoints
  void Damage(int damage);

  // === OVERRIDES

  void Update(float deltaTime) override;
  void Render([[maybe_unused]] Vector2 offset) override {}

private:
  // How many hitPoints it has left
  int hitPoints{30};
};

#endif