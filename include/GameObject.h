#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <typeinfo>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <utility>
#include "GameObject.h"
#include "Component.h"
#include "Rectangle.h"
#include "Vector2.h"

using namespace std;

class GameObject
{
public:
  // Base constructor
  GameObject() : destroyRequested(false) {}

  // With dimensions
  GameObject(Vector2 coordinates) : box(coordinates, 0, 0) {}

  GameObject(Rectangle box) : box(box) {}

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
  bool DestroyRequested() const { return destroyRequested; }

  // Destroys the object
  void RequestDestroy() { destroyRequested = true; }

  // Adds a new component
  template <class T, typename... Args>
  T &AddComponent(Args &&...args)
  {
    auto component = make_shared<T>(*this, std::forward<Args>(args)...);

    components.push_back(component);

    // Start it
    if (started)
      component->Start();

    return dynamic_cast<T &>(*components.back());
  }

  // Removes an existing component
  void RemoveComponent(Component *component);

  // Gets pointer to a component of the given type
  // Needs to be in header file so the compiler knows how to build the necessary methods
  template <class T>
  auto GetComponent() -> T *
  {
    // Find the position of the component that is of the requested type
    auto componentIterator = std::find_if(
        components.begin(), components.end(), [](std::shared_ptr<Component> component)
        { return dynamic_cast<T *>(component.get()) != nullptr; });

    // Detect if not present
    if (componentIterator == components.end())
      return nullptr;

    return dynamic_cast<T *>(componentIterator->get());
  }

  // Like GetComponent, but raises if it's not present
  template <class T>
  auto RequireComponent() -> T *
  {
    auto component = GetComponent<T>();

    if (component == nullptr)
    {
      throw std::runtime_error("Required component was not found.\nRequired component typeid name: "s + typeid(T).name());
    }

    return component;
  }

  // The rectangle that specifies where this object exists in game space
  Rectangle box;

  // Temporary method to play sound & destroy after done playing
  void DestroyAfterSoundPlay();

  // Initialize
  void Start();

  // Returns this object's shared pointer
  std::shared_ptr<GameObject> GetShared() const;

private:
  // Vector with all components of this object
  std::vector<std::shared_ptr<Component>> components;

  // Whether is dead
  bool destroyRequested{false};

  // Whether has already run started
  bool started{false};
};

#endif