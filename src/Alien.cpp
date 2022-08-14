#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include <iostream>

using namespace std;

Alien::Alien(GameObject &associatedObject, int minionCount) : Component(associatedObject)
{
}

void Alien::Start()
{
  gameObject.RequireComponent<Movement>();
  auto health = gameObject.RequireComponent<Health>();

  // Remove on death
  health->OnDeath.AddListener(
      "deathRemove", [this]()
      { gameObject.RequestDestroy(); });
}

void Alien::Update([[maybe_unused]] float deltaTime)
{
  auto checkButtonLinkedToAction = [this](int button, Action::Type actionType)
  {
    auto inputManager = InputManager::GetInstance();

    // On left mouse button, shoot
    if (inputManager.MousePress(button))
      AddAction(actionType);
  };

  // Link mouse buttons to actions
  checkButtonLinkedToAction(LEFT_MOUSE_BUTTON, Action::Type::shoot);
  checkButtonLinkedToAction(RIGHT_MOUSE_BUTTON, Action::Type::move);
}

void Alien::AddAction(Action::Type actionType)
{
  bool wasEmpty = actionQueue.empty();

  actionQueue.emplace(actionType, inputManager.GetMouseWorldCoordinates());

  // Execute them
  if (wasEmpty)
    ExecuteActions();
}

void Alien::AdvanceActionQueue()
{
  actionQueue.pop();

  ExecuteActions();
}

void Alien::ExecuteActions()
{
  if (actionQueue.empty())
    return;

  // Next action in queue
  auto currentAction = actionQueue.front();

  // If move action
  if (currentAction.type == Action::Type::move)
  {
    gameObject.GetComponent<Movement>()->MoveTo(
        // Upon arrival, pop this action
        currentAction.position, [this]()
        { AdvanceActionQueue(); });
  }

  // If shoot action
  else if (currentAction.type == Action::Type::shoot)
  {
    AdvanceActionQueue();
  }
}
