#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Helper.h"
#include "Resources.h"
#include "InputManager.h"

using namespace std;
using namespace Helper;

// === EXTERNAL METHODS =================================

// Initializes SDL
auto InitializeSDL(string title, int width, int height) -> pair<SDL_Window *, SDL_Renderer *>
{
  // === BASE SDL

  // Initialize SDL & all it's necessary subsystems
  auto encounteredError = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

  // Catch any errors
  Assert(!encounteredError, "Failed to initialize SDL");

  // === SDL IMAGE

  // Initialize the image module
  int requestedFlags = IMG_INIT_JPG | IMG_INIT_PNG;
  int returnedFlags = IMG_Init(requestedFlags);

  // Check if everything went alright
  Assert((returnedFlags & requestedFlags) == requestedFlags, "Failed to initialize SDL-image", IMG_GetError());

  // === SDL MIXER

  // Initialize the mixer
  Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);

  // Initialize open audio
  encounteredError = Mix_OpenAudio(
      MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

  // Catch any errors
  Assert(!encounteredError, "Failed to initialize SDL-mixer", Mix_GetError());

  // Allocate more sound channels
  Mix_AllocateChannels(32);

  // === GAME WINDOW

  auto gameWindow = SDL_CreateWindow(
      title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  // Catch any errors
  Assert(gameWindow != nullptr, "Failed to create SDL window");

  // Create renderer
  auto renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

  // Catch any errors
  Assert(renderer != nullptr, "Failed to create SDL renderer");

  return make_pair(gameWindow, renderer);
}

void ExitSDL(SDL_Window *window, SDL_Renderer *renderer)
{
  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(window);

  Mix_CloseAudio();

  Mix_Quit();

  IMG_Quit();

  SDL_Quit();
}

// === INITIALIZE STATIC FIELDS =================================

// Game instance
unique_ptr<Game> Game::gameInstance = nullptr;

// === PRIVATE METHODS =======================================

Game::Game(string title, int width, int height)
    : window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer)
{
  // === SINGLETON CHECK

  // Check for invalid existing instance
  if (Game::gameInstance)
    throw runtime_error("Tried to instantiate another Game instance");

  // === INIT SDL

  // Retrieve the window & the renderer from the initializer
  auto pointers = InitializeSDL(title, width, height);

  // === INITIALIZE STATE

  window.reset(pointers.first);
  renderer.reset(pointers.second);

  // === INIT RANDOMNESS

  srand(time(NULL));
}

Game::~Game()
{
  // Shut down the game state before shutting down sdl
  state.reset();

  // Quit SDL
  // Release the pointers, as we will destroy them in the method
  ExitSDL(window.release(), renderer.release());
}

void Game::CalculateDeltaTime()
{
  // Get this frame's start time
  float newFrameStart = SDL_GetTicks();

  // Calculate & convert delta time from ms to s
  deltaTime = (newFrameStart - frameStart) / 1000;

  // Update frame start variable
  frameStart = newFrameStart;
}

// === PUBLIC METHODS =================================

Game &Game::GetInstance()
{
  // If it doesn't exist...
  if (gameInstance == nullptr)
  {
    // Create it
    gameInstance.reset(new Game("GuilhermeMendel-170143970", screenWidth, screenHeight));

    // Set a starting state
    gameInstance->state = make_unique<GameState>();
  }

  // Return the instance
  return *Game::gameInstance;
}

void Game::Run()
{
  // Find out how many ms to wait to achieve the configured framerate
  const int frameDelay = 1000 / Game::frameRate;

  // Get the input manager
  InputManager &inputManager = InputManager::GetInstance();

  // Start the state
  state->Start();

  // Loop while exit not requested
  while (state->QuitRequested() == false)
  {
    // Calculate frame's delta time
    CalculateDeltaTime();

    // Get input
    inputManager.Update();

    // Update the state
    state->Update(deltaTime);

    // Render the state
    state->Render();

    // Render the window
    SDL_RenderPresent(GetRenderer());

    // Delay the frame to obey the framerate
    SDL_Delay(frameDelay);
  }

  // Clear resources
  Resources::ClearAllResources();
}

GameState &Game::GetState() const
{
  if (!state)
  {
    throw std::runtime_error("No game state defined");
  }

  return *state;
}
