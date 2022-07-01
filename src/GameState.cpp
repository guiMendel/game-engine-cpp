#include <math.h>
#include "GameState.h"
#include "Face.h"
#include "Vector2.h"
#include "Sound.h"
#include <iostream>
using namespace std;

void GameState::LoadAssets()
{
}

void GameState::Update(float deltaTime)
{
  // Get input
  Input();

  // Update game objects
  for (auto &gameObject : gameObjects)
    gameObject->Update(deltaTime);

  // Check for dead objects
  for (int i = 0; i < gameObjects.size(); i++)
  {
    if (gameObjects[i]->IsDead() == false)
      continue;

    // If is dead, delete
    gameObjects.erase(gameObjects.begin() + i);
  }
}

void GameState::Render()
{
  // Render state background
  background.Render();

  // Render objects
  for (auto &gameObject : gameObjects)
    gameObject->Render();
}

void GameState::AddObject(int mouseX, int mouseY)
{
  // Create new object
  auto newObject = make_unique<GameObject>(mouseX, mouseY);

  // Give it a sprite
  auto &sprite = (Sprite &)newObject->AddComponent(new Sprite(*newObject, "./assets/image/penguinface.png"));

  // Center it on mouse coordinates
  newObject->box.x -= sprite.GetWidth();
  newObject->box.y -= sprite.GetHeight();

  // Give it a sound component
  newObject->AddComponent(new Sound(*newObject, "./assets/sound/boom.wav"));

  // Give it a face component
  newObject->AddComponent(new Face(*newObject));

  // Store it
  gameObjects.emplace_back(newObject.release());
}

void GameState::Input()
{
  SDL_Event event;
  int mouseX, mouseY;

  // Get mouse coords
  SDL_GetMouseState(&mouseX, &mouseY);

  // If there are any input events in the SDL stack pile, this function returns 1 and sets the argument to next event
  while (SDL_PollEvent(&event))
  {

    // Quit on quit event
    if (event.type == SDL_QUIT)
      quitRequested = true;

    // On click event
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      // Cycle through the game objects starting from the end, so to catch the objects on top first
      for (
          auto gameObjectIterator = gameObjects.rbegin();
          gameObjectIterator != gameObjects.rend();
          gameObjectIterator++)
      {
        // Get the game object pointer (dereference the iterator)
        auto &gameObject = *gameObjectIterator;

        cout << gameObject->box.width << " " << gameObject->box.height << endl;

        // Disregard if it was not clicked
        if (gameObject->box.Contains({(float)mouseX, (float)mouseY}) == false)
          return;

        // Try to get a Face component
        Face *face = (Face *)gameObject->GetComponent("Face");

        // Disregard if it doesn't have one
        if (face == nullptr)
          continue;

        // Apply damage
        face->Damage(std::rand() % 10 + 10);

        // Only one can be clicked at a time
        break;
      }
    }

    // On keyboard event
    if (event.type == SDL_KEYDOWN)
    {
      // Esc closes the game
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        quitRequested = true;
      }

      // Other keys create a new object
      else
      {
        // Rotate it in a range from -90 to 90 degrees
        float rotation = -M_PI + M_PI * (rand() % 1001) / 500.0;

        // Get it's position relative to mouse
        Vector2 position =
            Vector2(200, 0).Rotated(rotation) +
            Vector2(mouseX, mouseY);

        // Insert it
        AddObject((int)position.x, (int)position.y);
      }
    }
  }
}