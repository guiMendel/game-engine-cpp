#include "PenguinCannon.h"
#include "InputManager.h"
#include "SpriteAnimator.h"
#include "Projectile.h"
#include "MainState.h"

// Projectile speed
const float PenguinCannon::projectileSpeed{300};

// Projectile time to live, in seconds
const float PenguinCannon::projectileTimeToLive{5};

// Damage of projectile
const float PenguinCannon::projectileDamage{50};

void PenguinCannon::Update([[maybe_unused]] float deltaTime)
{
  auto &input = InputManager::GetInstance();

  // Point at mouse
  gameObject.SetRotation(
      Vector2::AngleBetween(gameObject.GetPosition(), input.GetMouseWorldCoordinates()));

  // Shoot on click
  if (input.MousePress(RIGHT_MOUSE_BUTTON))
    Shoot();
}

void PenguinCannon::Shoot()
{
  // Create the projectile
  gameObject.gameState
      .CreateObject(
          "Penguin Projectile",
          MainState::ProjectileRecipe(
              "./assets/image/penguinbullet.png", Vector2(30, 29), 0.2f,
              gameObject.GetRotation(), projectileSpeed, projectileTimeToLive, projectileDamage),
          GunPointPosition());
}

Vector2 PenguinCannon::GunPointPosition()
{
  // Get image size
  int width = gameObject.GetComponent<Sprite>()->GetWidth();

  // Gun point is on end of image
  return gameObject.GetPosition() + Vector2::Angled(gameObject.GetRotation(), width / 2);
}
