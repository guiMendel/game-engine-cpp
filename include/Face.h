#ifndef __FACE__
#define __FACE__

#include "GameObject.h"
#include "Component.h"
#include <string>

class Face : public Component
{
public:
  Face(GameObject &associatedObject) : Component(associatedObject) {}

  // Subtracts this damage from the current hitPoints
  void Damage(int damage);

  // === OVERRIDES

  void Update(float deltaTime) override {}
  void Render() override {}

  // Determines if is from a certain type
  virtual bool Is(std::string type) override { return type == typeid(*this).name(); }

private:
  // How many hitPoints it has left
  int hitPoints{30};
};

#endif