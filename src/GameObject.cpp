#include <algorithm>
#include "GameObject.h"
#include "Sound.h"
#include "Game.h"

using namespace std;

void GameObject::Start()
{
  for (auto component : components)
    component->Start();

  started = true;
}

void GameObject::RemoveComponent(Component *component)
{
  // Find it's position
  auto componentPosition = find_if(
      components.begin(), components.end(), [component](shared_ptr<Component> otherComponent)
      { return otherComponent.get() == component; });

  // Detect if not present
  if (componentPosition == components.end())
    return;

  // Remove it
  components.erase(componentPosition);
}

void GameObject::DestroyAfterSoundPlay()
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
      components.begin(), components.end(), [](shared_ptr<Component> component)
      { return dynamic_cast<Sound *>(component.get()) != nullptr; });

  // Remove up until sound
  components.erase(components.begin(), soundIterator);

  // See if there's more
  if (components.size() <= 1)
    return;

  // Remove from sound on
  components.erase(components.begin() + 1, components.end());
}

std::shared_ptr<GameObject> GameObject::GetShared() const
{
  auto &gameState = Game::GetInstance().GetState();

  return gameState.GetPointer(this).lock();
}
