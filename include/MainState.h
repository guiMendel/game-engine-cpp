#ifndef __MAIN_STATE__
#define __MAIN_STATE__

#include "GameState.h"
#include "GameObject.h"
#include "Alien.h"
#include <functional>
#include <memory>

class MainState : public GameState
{
public:
  void InitializeObjects() override;

  // === RECIPES

  // Map
  static void BackgroundRecipe(std::shared_ptr<GameObject> background);
  static void TilemapRecipe(std::shared_ptr<GameObject> tilemap);

  // Penguins
  static void PenguinBodyRecipe(std::shared_ptr<GameObject> penguin);
  static void PenguinCannonRecipe(std::shared_ptr<GameObject> penguin);

  // Aliens
  static void AlienRecipe(std::shared_ptr<GameObject> alien);
  static auto MinionRecipe(std::shared_ptr<Alien> alien, float startingArc) -> std::function<void(std::shared_ptr<GameObject>)>;

  // Projectile
  static auto ProjectileRecipe(std::string spritePath, Vector2 animationFrame, float animationSpeed, bool loopAnimation,
                               Tag targetTag,
                               float startingAngle,
                               float speed = 300.0f,
                               float timeToLive = 5.0f,
                               float damage = 50.0f,
                               std::weak_ptr<GameObject> target = std::weak_ptr<GameObject>(),
                               float chaseSteering = 0.5f)
      -> std::function<void(std::shared_ptr<GameObject>)>;
};

#endif