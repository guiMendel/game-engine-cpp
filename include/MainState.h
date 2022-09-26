#ifndef __MAIN_STATE__
#define __MAIN_STATE__

#include "GameState.h"
#include "GameObject.h"
#include "Alien.h"
#include <functional>
#include <memory>

class MainState : public GameState
{
public:
  // How many aliens to start with
  static const int totalAliens;

  void InitializeObjects() override;

  void Update(float deltaTime) override;

  void AdvanceState(bool victory);

private:
  Music music;

  // How many aliens there still are
  int alienCount{totalAliens};
};

#endif