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
