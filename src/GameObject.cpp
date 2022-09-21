#include <algorithm>
#include "GameObject.h"
#include "Sound.h"
#include "Game.h"
#include <iostream>

using namespace std;

// Private constructor
GameObject::GameObject(GameState &gameState) : gameState(gameState), id(gameState.SupplyObjectId()) {}

// With dimensions
GameObject::GameObject(Vector2 coordinates, double rotation, shared_ptr<GameObject> parent)
    : GameObject(Game::GetInstance().GetState())
{
  // Only add a parent if not the root object
  if (IsRoot() == false)
  {
    // If no parent, add root as parent
    if (parent == nullptr)
      parent = Game::GetInstance().GetState().GetRootObject();

    // Add reference to parent
    this->weakParent = parent;

    // Give parent a reference to self
    parent->children[id] = GetShared();
  }

  SetPosition(coordinates);
  SetRotation(rotation);
}

void GameObject::Start()
{
  if (started)
    return;

  started = true;

  for (auto component : components)
    component->StartAndRegisterLayer();
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

shared_ptr<GameObject> GameObject::GetShared() const
{
  return Game::GetInstance().GetState().GetPointer(this).lock();
}

auto GameObject::GetComponent(const Component *componentPointer) const -> shared_ptr<Component>
{
  auto componentIterator = find_if(
      components.begin(), components.end(),
      [componentPointer](shared_ptr<Component> component)
      { return component.get() == componentPointer; });

  if (componentIterator == components.end())
    return shared_ptr<Component>();

  return *componentIterator;
}

shared_ptr<GameObject> GameObject::InternalGetParent() const
{
  // Ensure not root
  Assert(IsRoot() == false, "Getting parent is forbidden on root object");

  if (IsRoot())
    return nullptr;

  // Ensure the parent is there
  Assert(weakParent.expired() == false, "GameObject unexpectedly failed to retrieve parent object");

  return weakParent.lock();
}

shared_ptr<GameObject> GameObject::GetParent() const
{
  auto parent = InternalGetParent();

  return parent->id == 0 ? nullptr : parent;
}

void GameObject::UnlinkParent()
{
  if (IsRoot())
    return;

  InternalGetParent()->children.erase(id);
  weakParent.reset();
}

void GameObject::SetParent(shared_ptr<GameObject> newParent)
{
  Assert(IsRoot() == false, "SetParent is forbidden on root object");

  // Delete current parent
  UnlinkParent();

  // Set new parent
  weakParent = newParent;
}

// Where this object exists in game space, in absolute coordinates
Vector2 GameObject::GetPosition() const
{
  if (IsRoot())
    return localPosition;
  return InternalGetParent()->GetPosition() + localPosition;
}
void GameObject::SetPosition(const Vector2 newPosition)
{
  if (IsRoot())
    localPosition = newPosition;
  localPosition = newPosition - InternalGetParent()->GetPosition();
}

// Absolute scale of the object
Vector2 GameObject::GetScale() const
{
  if (IsRoot())
    return localScale;
  return InternalGetParent()->GetScale() + localScale;
}
void GameObject::SetScale(const Vector2 newScale)
{
  if (IsRoot())
    localScale = newScale;
  localScale = newScale - InternalGetParent()->GetScale();
}

// Absolute rotation in radians
double GameObject::GetRotation() const
{
  if (IsRoot())
    return localRotation;
  return InternalGetParent()->GetRotation() + localRotation;
}
void GameObject::SetRotation(const double newRotation)
{
  if (IsRoot())
    localRotation = newRotation;
  localRotation = newRotation - InternalGetParent()->GetRotation();
}

void GameObject::InternalDestroy()
{
  // Remove all children
  for (auto pairIterator = children.begin(); pairIterator != children.end(); ++pairIterator)
  {
    LOCK(pairIterator->second, child);

    child->InternalDestroy();
  }

  // Remove this object's reference from it's parent
  UnlinkParent();

  // Delete self from state's list
  gameState.RemoveObject(id);
}

void GameObject::RegisterCollider(shared_ptr<Collider> collider) { colliders.emplace_back(collider); }

vector<shared_ptr<Collider>> GameObject::GetColliders()
{
  vector<shared_ptr<Collider>> verifiedColliders;

  auto colliderIterator = colliders.begin();
  while (colliderIterator != colliders.end())
  {
    // Remove it if it's expired
    if (colliderIterator->expired())
    {
      colliderIterator = colliders.erase(colliderIterator);
      continue;
    }

    // Otherwise lock it and add it
    verifiedColliders.push_back(colliderIterator->lock());
  }

  return verifiedColliders;
}
