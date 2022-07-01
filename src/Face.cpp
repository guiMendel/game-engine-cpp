#include "Face.h"
#include "Sound.h"

void Face::Damage(int damage)
{
  hitPoints -= damage;

  // Detect death
  if (hitPoints > 0)
    return;

  associatedObject.RequestDestroy();

  // If there is sound to play, play it
  //  associatedObject.GetComponent<Sound>();
  Sound *soundComponent = (Sound *)associatedObject.GetComponent("Sound");

  if (soundComponent == nullptr)
    return;

  soundComponent->Play();
}
