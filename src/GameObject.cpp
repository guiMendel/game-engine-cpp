#include <algorithm>
#include "GameObject.h"
#include "Sound.h"

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

void GameObject::DestroyInMs(int milliseconds)
{
  // If there is sound to play, play it
  auto soundComponent = GetComponent<Sound>();

  // If no sound to play, destroy immediately
  if (soundComponent == nullptr)
  {
    RequestDestroy();
    return;
  }

  // Otherwise, play sound
  soundComponent->Play(
      [this]()
      { RequestDestroy(); },
      1);

  // Remove all components except Sound
  auto soundIterator = find_if(
      components.begin(), components.end(), [](unique_ptr<Component> &component)
      { return dynamic_cast<Sound *>(component.get()) != nullptr; });

  components.erase(components.begin(), soundIterator);

  if (components.size() <= 1)
    return;
  components.erase(components.begin() + 1, components.end());
}