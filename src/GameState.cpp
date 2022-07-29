#include <math.h>
#include "GameState.h"
#include "Face.h"
#include "Vector2.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <iostream>
using namespace std;

shared_ptr<GameObject> CreateBackgroundObject()
{
  auto background = make_shared<GameObject>();

  // Get a background sprite
  background->AddComponent<Sprite>("./assets/image/ocean.jpg");

  // Make it follow the camera
  background->AddComponent<CameraFollower>();

  return background;
}

shared_ptr<GameObject> CreateTilemapObject()
{
  // Get the Tileset
  TileSet *tileset = new TileSet(64, 64, "./assets/image/tileset.png");

  auto tilemap = make_shared<GameObject>();

  // Get a tilemap
  tilemap->AddComponent<TileMap>("./assets/map/tileMap.txt", tileset);

  return tilemap;
}

GameState::GameState() : inputManager(InputManager::GetInstance()), music("./assets/music/main.mp3")
{
  quitRequested = false;

  // Add a background
  gameObjects.push_back(CreateBackgroundObject());

  // Add a tilemap
  gameObjects.push_back(CreateTilemapObject());

  // Play the music
  music.Play();
}

void GameState::LoadAssets()
{
}

void GameState::Update(float deltaTime)
{
  // Quit if necessary
  if (inputManager.KeyRelease(ESCAPE_KEY) || inputManager.QuitRequested())
  {
    quitRequested = true;
  }

  // On space press, create face
  if (inputManager.KeyRelease(SPACE_KEY))
  {
    // Rotate it in a range from -90 to 90 degrees
    float rotation = -M_PI + M_PI * (rand() % 1001) / 500.0;

    // Get it's position relative to mouse
    Vector2 position =
        Vector2(200, 0).Rotated(rotation) +
        inputManager.GetMouseWorldCoordinates();

    // Insert it
    AddObject(position);
  }

  // Update camera
  Camera::GetInstance().Update(deltaTime);

  // Update game objects
  for (auto &gameObject : gameObjects)
    gameObject->Update(deltaTime);

  // Check for dead objects
  for (int i = 0; i < (int)gameObjects.size(); i++)
  {
    if (gameObjects[i]->IsDead() == false)
      continue;

    // If is dead, delete
    gameObjects.erase(gameObjects.begin() + i);
  }
}

void GameState::Render()
{
  // Render objects
  for (auto &gameObject : gameObjects)
    gameObject->Render();
}

void GameState::AddObject(Vector2 coordinates)
{
  // Create new object
  auto newObject = make_unique<GameObject>(coordinates);

  // Give it a sprite
  auto &sprite = newObject->AddComponent<Sprite>("./assets/image/penguinface.png");

  // Center it with image dimensions
  newObject->box.x -= sprite.GetWidth();
  newObject->box.y -= sprite.GetHeight();

  // Give it a sound component
  newObject->AddComponent<Sound>("./assets/sound/boom.wav");

  // Give it a face component
  newObject->AddComponent<Face>();

  // Store it
  gameObjects.emplace_back(newObject.release());
}

// void GameState::Input()
// {
//   SDL_Event event;
//   int mouseX, mouseY;

//   // Get mouse coords
//   SDL_GetMouseState(&mouseX, &mouseY);

//   // If there are any input events in the SDL stack pile, this function returns 1 and sets the argument to next event
//   while (SDL_PollEvent(&event))
//   {

//     // Quit on quit event
//     if (event.type == SDL_QUIT)
//       quitRequested = true;

//     // On click event
//     if (event.type == SDL_MOUSEBUTTONDOWN)
//     {
//     }

//     // On keyboard event
//     if (event.type == SDL_KEYDOWN)
//     {
//       // Esc closes the game
//       if (event.key.keysym.sym == SDLK_ESCAPE)
//       {
//         quitRequested = true;
//       }

//       // Other keys create a new object
//       else
//       {
//         // Rotate it in a range from -90 to 90 degrees
//         float rotation = -M_PI + M_PI * (rand() % 1001) / 500.0;

//         // Get it's position relative to mouse
//         Vector2 position =
//             Vector2(200, 0).Rotated(rotation) +
//             Vector2(mouseX, mouseY);

//         // Insert it
//         AddObject((int)position.x, (int)position.y);
//       }
//     }
//   }
// }