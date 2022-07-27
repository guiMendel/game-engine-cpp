#include "Face.h"
#include "Sound.h"

void Face::Damage(int damage)
{
  hitPoints -= damage;

  // Detect death
  if (hitPoints > 0)
    return;

  // associatedObject.RequestDestroy();
  associatedObject.DestroyInMs(3000);
}

void Face::Update(float deltaTime)
{
  // Disregard if it was not clicked
  if (
      inputManager.MouseRelease(LEFT_MOUSE_BUTTON) == false ||
      associatedObject.box.Contains(
          {(float)inputManager.GetMouseX(), (float)inputManager.GetMouseY()}) == false)
    return;

  // Apply damage
  Damage(std::rand() % 10 + 10);
}
