#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Component.h"
#include "Rectangle.h"

class GameObject
{
public:
  // Base constructor
  GameObject() : isDead(false) {}

  // Base destructor
  // Components are smart pointers, they free themselves
  ~GameObject() { components.clear(); }

  // Called once per frame
  void Update(float deltaTime)
  {
    for (const auto &component : components)
      component->Update(deltaTime);
  }

  // Renders to the screen every frame
  void Render()
  {
    for (const auto &component : components)
      component->Render();
  }

  // Whether is dead
  bool IsDead() const { return isDead; }

  // Destroys the object
  void RequestDestroy() { isDead = true; }

  // Adds a new component
  void AddComponent(Component *component) { components.emplace_back(component); }

  // Removes an existing component
  void RemoveComponent(Component *component);

  // Gets pointer to a component of the given type
  auto GetComponent(std::string type) -> Component *;

  // Gets pointer to a component of the given type
  template <class T>
  auto GetComponent() -> Component *;

  // The rectangle that specifies where this object exists in game space
  Rectangle box;

private:
  // Vector with all components of this object
  std::vector<std::unique_ptr<Component>> components;

  // Whether is dead
  bool isDead;
};

#endif