#include "Health.h"

void Health::TakeDamage(float damage)
{
  healthPoints -= damage;

  if (healthPoints <= 0 && deathTriggered == false)
  {
    OnDeath.Invoke();
    deathTriggered = true;
  }
}