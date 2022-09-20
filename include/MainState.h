#ifndef __MAIN_STATE__
#define __MAIN_STATE__

#include "GameState.h"
#include "GameObject.h"
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
  static auto MinionRecipe(Alien &alien, float startingArc) -> std::function<void(std::shared_ptr<GameObject>)>;

  // Projectile
  static void ProjectileRecipe(std::shared_ptr<GameObject> projectile);
};

#endif