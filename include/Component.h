#ifndef __COMPONENT__
#define __COMPONENT__

#include "GameObject.h"
#include "InputManager.h"
#include <string>

class GameObject;

class Component
{
public:
  // Called once per frame
  virtual void Update(float deltaTime) = 0;

  // Called once per frame to render to the screen
  virtual void Render() = 0;

  Component(GameObject &associatedObject)
      : associatedObject(associatedObject), inputManager(InputManager::GetInstance()) {}

  // Destructor to be overriden
  virtual ~Component() {}

protected:
  // The associated game object
  GameObject &associatedObject;

  // Reference to input manager
  InputManager &inputManager;
};

#endif