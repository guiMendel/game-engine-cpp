#include "Projectile.h"
#include "Health.h"
#include <cmath>
#include <string>

using namespace std;

Projectile::Projectile(
    GameObject &associatedObject,
    Tag targetTag,
    float startingAngle,
    float speed,
    float timeToLive,
    float damage,
    weak_ptr<GameObject> target,
    float chaseSteering)
    : Component(associatedObject), speed(Vector2::Angled(startingAngle, speed)), angle(startingAngle), timeToLive(timeToLive), damage(damage), targetWeak(target), chaseSteering(chaseSteering), targetTag(targetTag)
{
  // Adjust rotation
  gameObject.SetRotation(this->speed.Angle());
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
  gameObject.localPosition += speed * deltaTime;
}

void Projectile::Chase()
{
  // Get target
  auto target = targetWeak.lock();

  if (!target)
    return;

  // Get angle between projectile and target
  float targetSteer = Vector2::AngleBetween(gameObject.GetPosition(), target->GetPosition()) - angle;

  // Get angle to steer
  float steerAngle = std::abs(targetSteer) > std::abs(chaseSteering) ? chaseSteering : targetSteer;

  // Steer
  speed = speed.Rotated(steerAngle);

  // Adjust rotation
  gameObject.SetRotation(speed.Angle());
}

void Projectile::OnCollision(GameObject &other)
{
  // Ignore if other isn't of target tag
  if (other.tag != targetTag)
    return;

  // Get other's health component
  auto health = other.GetComponent<Health>();

  // If it has none, stop
  if (!health)
    return;

  // Deal damage
  health->TakeDamage(damage);

  // Die
  gameObject.RequestDestroy();
}
