#include "Recipes.h"
#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "Movement.h"
#include "Health.h"
#include "Collider.h"
#include "Minion.h"
#include "SpriteAnimator.h"
#include "Projectile.h"
#include "Sound.h"
#include <iostream>

using namespace std;

void Recipes::PenguinBody(shared_ptr<GameObject> penguin)
{
  // Get sprite
  auto sprite = penguin->AddComponent<Sprite>("./assets/image/penguin.png", RenderLayer::Player);

  // Get collider
  penguin->AddComponent<Collider>(sprite);

  // Add movement
  auto movement = penguin->AddComponent<Movement>(PenguinBody::acceleration, PenguinBody::maxSpeed);

  // Add behavior
  penguin->AddComponent<::PenguinBody>(movement);

  // Add health
  penguin->AddComponent<Health>(PenguinBody::totalHealth);

  // Give it a player tag
  penguin->tag = Tag::Player;
}

void Recipes::PenguinCannon(shared_ptr<GameObject> penguin)
{
  // Get sprite (put it on render order 1 to show ahead)
  auto sprite = penguin->AddComponent<Sprite>("./assets/image/cubngun.png", RenderLayer::Player, 1);

  // Get collider
  penguin->AddComponent<Collider>(sprite);

  // Add behavior
  penguin->AddComponent<::PenguinCannon>();

  // Give it a player tag
  penguin->tag = Tag::Player;
}

auto Recipes::Background(string imagePath) -> function<void(shared_ptr<GameObject>)>
{
  return [imagePath](shared_ptr<GameObject> background)
  {
    // Get a background sprite
    background->AddComponent<Sprite>(imagePath, RenderLayer::Background, 0, false);

    // Make it follow the camera
    background->AddComponent<CameraFollower>(true);
  };
}

void Recipes::Tilemap(shared_ptr<GameObject> tilemap)
{
  // Get the Tileset
  auto tileset = make_shared<TileSet>(64, 64, "./assets/image/tileset.png");

  // Render first tilemap layer below
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset, 0, RenderLayer::Tilemap);

  // Render second layer above
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset, 1, RenderLayer::Foreground);
}

void Recipes::Alien(shared_ptr<GameObject> alien)
{
  // Get alien sprite
  auto sprite = alien->AddComponent<Sprite>("./assets/image/alien.png", RenderLayer::Enemies);

  // Get collider
  alien->AddComponent<Collider>(sprite);

  // Get alien behavior
  alien->AddComponent<::Alien>(Alien::totalMinions);

  // Get movement
  alien->AddComponent<Movement>(Alien::acceleration, Alien::maxSpeed);

  // Get health
  alien->AddComponent<Health>(Alien::healthPoints);

  // Give it an enemy tag
  alien->tag = Tag::Enemy;
}

auto Recipes::Minion(shared_ptr<::Alien> alien, float startingArc) -> function<void(shared_ptr<GameObject>)>
{
  return [alien, startingArc](shared_ptr<GameObject> minion)
  {
    // Give it a sprite
    auto sprite = minion->AddComponent<Sprite>("./assets/image/minion.png", RenderLayer::Enemies);

    // Get collider
    minion->AddComponent<Collider>(sprite);

    // Give it minion behavior
    minion->AddComponent<::Minion>(alien->gameObject.GetShared(), startingArc);

    // Make it mortal
    minion->AddComponent<Health>(Minion::healthPoints);

    // Add to minions
    alien->minions.emplace_back(minion);

    // Give it an enemy tag
    minion->tag = Tag::Enemy;
  };
}

auto Recipes::OneShotAnimation(string spritePath, Vector2 animationFrame, float animationSpeed)
    -> function<void(shared_ptr<GameObject>)>
{
  return [spritePath, animationFrame, animationSpeed](shared_ptr<GameObject> animation)
  {
    // Add sprite
    auto sprite = animation->AddComponent<Sprite>(spritePath, RenderLayer::VFX);

    // Add animation
    auto animator = animation->AddComponent<SpriteAnimator>(sprite, animationFrame, animationSpeed);

    // Get weak pointer to animation object
    auto animationWeak = weak_ptr(animation);

    // Play boom
    animation->AddComponent<Sound>("./assets/sound/boom.wav");

    // Delete self on animation end
    animator->OnCycleEnd.AddListener("One Shot Destructor", [animationWeak]()
                                     { if (auto animation = animationWeak.lock()) 
                                        animation->RequestDestroy(); });
  };
}

auto Recipes::Projectile(string spritePath, Vector2 animationFrame, float animationSpeed, bool loopAnimation,
                         Tag targetTag,
                         float startingAngle,
                         float speed,
                         float timeToLive,
                         float damage,
                         weak_ptr<GameObject> target,
                         float chaseSteering)
    -> function<void(shared_ptr<GameObject>)>
{
  return [targetTag, spritePath, animationFrame, animationSpeed, startingAngle, speed, timeToLive, damage, target, chaseSteering, loopAnimation](shared_ptr<GameObject> projectile)
  {
    // Add sprite
    auto sprite = projectile->AddComponent<Sprite>(spritePath, RenderLayer::Projectiles);

    // Add animation
    auto animator = projectile->AddComponent<SpriteAnimator>(sprite, animationFrame, animationSpeed, loopAnimation);

    // Get collider
    projectile->AddComponent<Collider>(animator);

    // Add projectile behavior
    projectile->AddComponent<::Projectile>(
        targetTag, startingAngle, speed, timeToLive, damage, target, chaseSteering);
  };
}
