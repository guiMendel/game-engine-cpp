#include "Projectile.h"
#include <cmath>
#include <string>

using namespace std;

Projectile::Projectile(
    GameObject &associatedObject,
    float startingAngle,
    float speed,
    float timeToLive,
    float damage,
    weak_ptr<GameObject> target,
    float chaseSteering)
    : Component(associatedObject), speed(Vector2::Angled(startingAngle, speed)), angle(startingAngle), timeToLive(timeToLive), damage(damage), targetWeak(target), chaseSteering(chaseSteering)
{
  // Adjust rotation
  gameObject.rotation = this->speed.Angle();
}

void Projectile::Update(float deltaTime)
{
  // Check if timer is up
  if ((timeToLive -= deltaTime) <= 0)
  {
    gameObject.RequestDestroy();

    return;
  }

  // Chase
  Chase();

  // Move
  gameObject.position += speed * deltaTime;
}

void Projectile::Chase()
{
  // Get target
  auto target = targetWeak.lock();

  if (!target)
    return;

  // Get angle between projectile and target
  float targetSteer = Vector2::AngleBetween(gameObject.position, target->position) - angle;

  // Get angle to steer
  float steerAngle = std::abs(targetSteer) > std::abs(chaseSteering) ? chaseSteering : targetSteer;

  // Steer
  speed = speed.Rotated(steerAngle);

  // Adjust rotation
  gameObject.rotation = speed.Angle();
}