#ifndef __COMPONENT__
#define __COMPONENT__

#include "GameObject.h"
#include <string>

class GameObject;

class Component
{
public:
  // Called once per frame
  virtual void Update(float deltaTime) = 0;

  // Called once per frame to render to the screen
  virtual void Render() = 0;

  // Determines if is from a certain type
  virtual bool Is(std::string type) = 0;

  Component(GameObject &associatedObject) : associatedObject(associatedObject) {}

  // Destructor to be overriden
  virtual ~Component() {}

protected:
  // The associated game object
  GameObject &associatedObject;
};

#endif