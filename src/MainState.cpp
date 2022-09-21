#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "MainState.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "Movement.h"
#include "Health.h"
#include "Collider.h"
#include "Minion.h"
#include "SpriteAnimator.h"
#include "Projectile.h"
#include <iostream>

using namespace std;

void MainState::PenguinBodyRecipe(shared_ptr<GameObject> penguin)
{
  // Get sprite
  auto sprite = penguin->AddComponent<Sprite>("./assets/image/penguin.png", RenderLayer::Player);

  // Get collider
  penguin->AddComponent<Collider>(sprite);

  // Add movement
  auto movement = penguin->AddComponent<Movement>(PenguinBody::acceleration, PenguinBody::maxSpeed);

  // Add behavior
  penguin->AddComponent<PenguinBody>(movement);

  // Add health
  penguin->AddComponent<Health>(PenguinBody::totalHealth);
}

void MainState::PenguinCannonRecipe(shared_ptr<GameObject> penguin)
{
  // Get sprite (put it on render order 1 to show ahead)
  auto sprite = penguin->AddComponent<Sprite>("./assets/image/cubngun.png", RenderLayer::Player, 1);

  // Get collider
  penguin->AddComponent<Collider>(sprite);

  // Add behavior
  penguin->AddComponent<PenguinCannon>();
}

void MainState::BackgroundRecipe(shared_ptr<GameObject> background)
{
  // Get a background sprite
  background->AddComponent<Sprite>("./assets/image/ocean.jpg", RenderLayer::Background, 0, false);

  // Make it follow the camera
  background->AddComponent<CameraFollower>(true);
}

void MainState::TilemapRecipe(shared_ptr<GameObject> tilemap)
{
  // Get the Tileset
  auto tileset = make_shared<TileSet>(64, 64, "./assets/image/tileset.png");

  // Render first tilemap layer below
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset, 0, RenderLayer::Tilemap);

  // Render second layer above
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset, 1, RenderLayer::Foreground);
}

void MainState::AlienRecipe(shared_ptr<GameObject> alien)
{
  // Get alien sprite
  auto sprite = alien->AddComponent<Sprite>("./assets/image/alien.png", RenderLayer::Enemies);

  // Get collider
  alien->AddComponent<Collider>(sprite);

  // Get alien behavior
  alien->AddComponent<Alien>(Alien::totalMinions);

  // Get movement
  alien->AddComponent<Movement>(Alien::acceleration, Alien::maxSpeed);

  // Get health
  alien->AddComponent<Health>(Alien::healthPoints);
}

auto MainState::MinionRecipe(shared_ptr<Alien> alien, float startingArc) -> function<void(shared_ptr<GameObject>)>
{
  return [alien, startingArc](shared_ptr<GameObject> minion)
  {
    // Give it a sprite
    auto sprite = minion->AddComponent<Sprite>("./assets/image/minion.png", RenderLayer::Enemies);

    // Get collider
    minion->AddComponent<Collider>(sprite);

    // Give it minion behavior
    minion->AddComponent<Minion>(alien->gameObject.GetShared(), startingArc);

    // Add to minions
    alien->minions.emplace_back(minion);
  };
}

auto ProjectileRecipe(string spritePath, Vector2 animationFrame, float animationSpeed,
                      float startingAngle,
                      float speed,
                      float timeToLive,
                      float damage,
                      weak_ptr<GameObject> target,
                      float chaseSteering)
    -> function<void(shared_ptr<GameObject>)>
{
  return [spritePath, animationFrame, animationSpeed, startingAngle, speed, timeToLive, damage, target, chaseSteering](shared_ptr<GameObject> projectile)
  {
    // Add sprite
    auto sprite = projectile->AddComponent<Sprite>(spritePath, RenderLayer::Projectiles);

    // Get collider
    projectile->AddComponent<Collider>(sprite);

    // Add animation
    projectile->AddComponent<SpriteAnimator>(sprite, animationFrame, animationSpeed);

    // Add projectile behavior
    projectile->AddComponent<Projectile>(
        startingAngle, speed, timeToLive, damage, target, chaseSteering);
  };
}

void MainState::InitializeObjects()
{
  // Add a background
  CreateObject(BackgroundRecipe);

  // Add a tilemap
  CreateObject(TilemapRecipe);

  // Add an alien
  CreateObject(AlienRecipe, Vector2(512, 300));

  // Add penguins
  auto penguin = CreateObject(PenguinBodyRecipe);

  // Add cannon as child
  CreateObject(PenguinCannonRecipe, penguin->GetPosition(), penguin->GetRotation(), penguin);

  // Make camera follow penguin
  Camera::GetInstance().Follow(penguin);

  // Play music
  // music.Play("./assets/music/main.mp3");
}