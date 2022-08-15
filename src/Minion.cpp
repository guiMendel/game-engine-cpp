#include "Minion.h"
#include "Projectile.h"
#include "Game.h"
#include "Sprite.h"
#include <math.h>

Minion::Minion(GameObject &associatedObject, std::weak_ptr<GameObject> hostPointer, float startingArc)
    : Component(associatedObject), hostPointer(hostPointer), arc(startingArc)
{
  // Initialize radius
  orbitRadius = (rand() % (int)floor(radiusLimits[1] - radiusLimits[0])) + radiusLimits[0];
}

void Minion::Update(float deltaTime)
{
  auto hostLocked = hostPointer.lock();

  // If host is gone, destroy self
  if (!hostLocked)
  {
    gameObject.RequestDestroy();
    return;
  }

  // Update orbit position
  arc += angularSpeed * deltaTime;

  // Update radius position
  orbitRadius += radiusFloatSpeed * floatDirection;

  if (orbitRadius <= radiusLimits[0])
  {
    orbitRadius = radiusLimits[0];
    floatDirection = 1;
  }

  else if (orbitRadius >= radiusLimits[1])
  {
    orbitRadius = radiusLimits[1];
    floatDirection = -1;
  }

  // Get radial position vector
  Vector2 radialPosition = Vector2::Right(orbitRadius).Rotated(arc);

  // Update position
  gameObject.box.SetCenter((Vector2)hostLocked->box.GetCenter() + radialPosition);
}

void Minion::Shoot(Vector2 target)
{
  // Get angle to target
  float targetAngle = Vector2::AngleBetween((Vector2)gameObject.box, target);

  // Create the projectile
  Game::GetInstance()
      .GetState()
      .CreateObject(
          [this, targetAngle](std::shared_ptr<GameObject> projectile)
          {
    // Add sprite
    projectile->AddComponent<Sprite>("./assets/image/minionbullet1.png");
    
    // Add projectile behavior
    projectile->AddComponent<Projectile>(
      targetAngle, projectileSpeed, projectileTimeToLive, projectileDamage); },
          gameObject.box.GetCenter());
}