#ifndef __COMPONENT__
#define __COMPONENT__

#include "InputManager.h"
#include "Vector2.h"
#include "RenderLayer.h"
#include <string>
#include <memory>

class GameObject;

class Component
{
public:
  // Called once per frame
  virtual void Update([[maybe_unused]] float deltaTime) {}

  // Called once per frame to render to the screen
  virtual void Render() {}

  Component(GameObject &associatedObject)
      : gameObject(associatedObject), inputManager(InputManager::GetInstance()) {}

  // In which render layer this component is
  // If None, then it's Render method will never be called
  virtual RenderLayer GetRenderLayer() = 0;

  void StartAndRegisterLayer();

  // Returns this component's shared pointer
  std::shared_ptr<Component> GetShared() const;

  bool IsEnabled() const { return enabled; }

protected:
  virtual void Start() {}

  // The associated game object
  GameObject &gameObject;

  // Reference to input manager
  InputManager &inputManager;

  // Whether the component is active
  bool enabled{true};
};

#include "GameObject.h"
#include "Helper.h"

// We don't care it's recommended against doing this — we only want our lives to be easier
using namespace Helper;

#endif