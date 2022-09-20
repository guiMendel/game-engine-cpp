#ifndef __ALIEN__
#define __ALIEN__

#include "GameObject.h"
#include "Movement.h"
#include "Health.h"
#include "Vector2.h"
#include "Component.h"
#include <queue>
#include <vector>
#include <memory>

class Alien : public Component
{
public:
  // Rotation speed, in radians
  static const float rotationSpeed;

  // Movement acceleration
  static const float acceleration;
  static const float maxSpeed;

  // Total minion count
  static const int totalMinions;

  // Total health points
  static const float healthPoints;

  Alien(GameObject &associatedObject, int minionCount) : Component(associatedObject), minionCount(minionCount)
  {
  }

  void Start() override;
  void Update(float deltaTime) override;
  void Render() override;
  RenderLayer GetRenderLayer() override { return RenderLayer::None; }

private:
  // Defines the alien's possible actions
  struct Action
  {
    // Types
    enum class Type
    {
      move,
      shoot
    };

    Type type;

    Action(Type type, Vector2 position)
        : type(type), position(position) {}

    Vector2 position;
  };

  // The actions it's currently assigned to perform
  std::queue<Action> actionQueue;

  // How many minions it should start with
  int minionCount;

  // It's current minions
  std::vector<std::weak_ptr<GameObject>> minions;

  // Executes next action
  void ExecuteActions();

  // Adds new action to queue
  void AddAction(Action::Type actionType);

  // Advances thew action queue
  void AdvanceActionQueue();

  std::weak_ptr<Movement> movementPointer;
  std::weak_ptr<Health> healthPointer;
};

#endif