#include <algorithm>
#include "GameObject.h"

using namespace std;

void GameObject::RemoveComponent(Component *component)
{
  // Find it's position
  auto componentPosition = find(components.begin(), components.end(), component);

  // Detect if not present
  if (componentPosition == components.end())
    return;

  // Remove it
  components.erase(componentPosition);
}

auto GameObject::GetComponent(std::string type) -> Component *
{
  // Find the position of the component that is of the requested type
  auto componentPosition = find_if(
      components.begin(), components.end(), [type](unique_ptr<Component> component)
      { return component->Is(type); });

  // Detect if not present
  if (componentPosition == components.end())
    return nullptr;

  return componentPosition->get();
}

// template <class T>
// auto GameObject::GetComponent() -> Component *
// {
//   // Find the position of the component that is of the requested type
//   auto componentPosition = find_if(
//       components.begin(), components.end(), [T](unique_ptr<Component> component)
//       { return dynamic_cast<T *>(component.get()) != nullptr });

//   // Detect if not present
//   if (componentPosition == components.end())
//     return nullptr;

//   return componentPosition->get();
// }