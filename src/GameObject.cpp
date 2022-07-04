#include <algorithm>
#include "GameObject.h"

using namespace std;

void GameObject::RemoveComponent(Component *component)
{
  // Find it's position
  auto componentPosition = find_if(
      components.begin(), components.end(), [component](unique_ptr<Component> &otherComponent)
      { return otherComponent.get() == component; });

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
      components.begin(), components.end(), [type](unique_ptr<Component> &component)
      { return component->Is(type); });

  // Detect if not present
  if (componentPosition == components.end())
    return nullptr;

  return componentPosition->get();
}
