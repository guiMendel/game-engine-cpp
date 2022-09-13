#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "Minion.h"
#include "Debug.h"
#include <iostream>

using namespace std;

// Helper functions
shared_ptr<GameObject> NearestMinion(vector<weak_ptr<GameObject>> &minions, Vector2 position);

void Alien::Start()
{
  gameObject.RequireComponent<Movement>();
  auto health = gameObject.RequireComponent<Health>();

  // Remove on death
  health->OnDeath.AddListener(
      "deathRemove", [this]()
      { gameObject.RequestDestroy(); });

  // Get game state reference
  auto &gameState = Game::GetInstance().GetState();

  // Add minions
  for (int i = 0; i < minionCount; i++)
    gameState.CreateObject([this, i](shared_ptr<GameObject> minionObject)
                           {
      // Give it a sprite
      minionObject->AddComponent<Sprite>("./assets/image/minion.png", RenderLayer::Enemies);

      // Give it minion behavior
      minionObject->AddComponent<Minion>(gameObject.GetShared(), 2 * M_PI * i / minionCount);
      
      // Add to minions
      minions.emplace_back(minionObject); });
}

void Alien::Update([[maybe_unused]] float deltaTime)
{
  auto checkButtonLinkedToAction = [this](int button, Action::Type actionType)
  {
    auto inputManager = InputManager::GetInstance();

    if (inputManager.MousePress(button))
      AddAction(actionType);
  };

  // Link mouse buttons to actions
  checkButtonLinkedToAction(LEFT_MOUSE_BUTTON, Action::Type::shoot);
  checkButtonLinkedToAction(RIGHT_MOUSE_BUTTON, Action::Type::move);

  // Rotate slowly
  gameObject.localRotation += rotationSpeed * deltaTime;
}

void Alien::Render()
{
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
    // Ignore if no minions
    if (!minions.empty())
    {
      // Pick nearest minion
      auto minion = NearestMinion(minions, currentAction.position);

      // Check that it's valid
      if (minion)
      {
        // Tell it to shoot at the target
        minion->GetComponent<Minion>()->Shoot(currentAction.position);
      }
    }

    AdvanceActionQueue();
  }
}

shared_ptr<GameObject> NearestMinion(vector<weak_ptr<GameObject>> &minions, Vector2 position)
{
  // Best distance so far
  float bestDistance = -1;

  shared_ptr<GameObject> bestMinion;

  // For each minion
  auto minionIterator = minions.begin();

  while (minionIterator != minions.end())
  {
    // Try to lock it
    if (auto minion = minionIterator->lock())
    {
      // Get it's distance
      float distance = Vector2::Distance(minion->GetPosition(), position);

      // If it's better
      if (bestDistance == -1 || distance < bestDistance)
      {
        bestDistance = distance;
        bestMinion = minion;
      }

      minionIterator++;
    }
    // If failed, it's gone, so forget it
    else
      minionIterator = minions.erase(minionIterator);
  }

  return bestMinion;
}
