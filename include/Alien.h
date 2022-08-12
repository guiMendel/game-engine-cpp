#ifndef __ALIEN__
#define __ALIEN__

#include "Vector2.h"
#include "GameObject.h"
#include <queue>
#include <vector>
#include <memory>

class Alien
{
public:
private:
  // Defines the alien's possible actions
  class Action
  {
  };

  // It's current speed
  Vector2 speed;

  // It's current health
  int healthPoints;

  // The actions it's currently assigned to perform
  std::queue<Action> actionQueue;

  // It's current minions
  std::vector<std::weak_ptr<GameObject>> minions;
};

#endif