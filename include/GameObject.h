#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include "GameObject.h"
#include "Component.h"
#include "Rectangle.h"

class GameObject
{
public:
  // Base constructor
  GameObject() : isDead(false) {}

  // With dimensions
  GameObject(int x, int y, int width = 0, int height = 0) : box(x, y, width, height), isDead(false) {}

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
  template <class T, typename... Args>
  T &AddComponent(Args &&...args)
  {
    components.emplace_back(new T(*this, std::forward<Args>(args)...));
    return dynamic_cast<T &>(*components.back());
  }

  // Removes an existing component
  void RemoveComponent(Component *component);

  // Gets pointer to a component of the given type (non dynamic way)
  auto GetComponent(std::string type) -> Component *;

  // Gets pointer to a component of the given type
  // Needs to be in header file so the compiler knows how to build the necessary methods
  template <class T>
  auto GetComponent() -> T *
  {
    // Find the position of the component that is of the requested type
    auto componentPosition = std::find_if(
        components.begin(), components.end(), [](std::unique_ptr<Component> &component)
        { return dynamic_cast<T *>(component.get()) != nullptr; });

    // Detect if not present
    if (componentPosition == components.end())
      return nullptr;

    return dynamic_cast<T *>(componentPosition->get());
  }

  // The rectangle that specifies where this object exists in game space
  Rectangle box;

  // Temporary method to play sound & destroy in some ms
  void DestroyInMs(int milliseconds);

private:
  // Temporary: check if channel is done
  int checkChannel{-1};

  // Vector with all components of this object
  std::vector<std::unique_ptr<Component>> components;

  // Whether is dead
  bool isDead;
};

#endif