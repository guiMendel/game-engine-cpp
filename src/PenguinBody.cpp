#include "PenguinBody.h"
#include "InputManager.h"

using namespace std;

// INITIALIZATION
const float PenguinBody::acceleration{0.2f};
const float PenguinBody::maxSpeed{20.0f};

// In radians per second
const float PenguinBody::rotationSpeed{35.0f};

void PenguinBody::Update(float deltaTime)
{
  // Detect acceleration
  Accelerate(deltaTime);

  // Detect rotation
  Rotate(deltaTime);
}

void PenguinBody::Accelerate(float deltaTime)
{
  InputManager inputManager = InputManager::GetInstance();

  auto SetSpeedProportion = [this](float speed)
  {
    LOCK(movementWeak, movement);

    this->speedProportion = speed;
    movement->Move(Vector2::Angled(gameObject.rotation, speed));
  };

  // Gain speed with W
  if (inputManager.IsKeyDown(SDLK_w))
    SetSpeedProportion(min(1.0f, speedProportion + deltaTime * acceleration));

  // Lose speed with S
  else if (inputManager.IsKeyDown(SDLK_s))
    SetSpeedProportion(max(0.0f, speedProportion - deltaTime * acceleration));
}

void PenguinBody::Rotate(float deltaTime)
{
  InputManager inputManager = InputManager::GetInstance();

  // Rotate left with A
  if (inputManager.IsKeyDown(SDLK_a))
  {
    LOCK(movementWeak, movement);

    gameObject.rotation += deltaTime * rotationSpeed;
    movement->Move(Vector2::Angled(gameObject.rotation, speedProportion));
  }

  // Rotate right with D
  if (inputManager.IsKeyDown(SDLK_d))
  {
    LOCK(movementWeak, movement);

    gameObject.rotation -= deltaTime * rotationSpeed;
    movement->Move(Vector2::Angled(gameObject.rotation, speedProportion));
  }
}
