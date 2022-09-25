#ifndef __TITLE_STATE__
#define __TITLE_STATE__

#include "GameState.h"

class TitleState : public GameState
{
public:
  void InitializeObjects() override;

  void Update(float deltaTime) override;
};

#endif
