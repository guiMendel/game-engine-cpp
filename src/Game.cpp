#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Game.h"

using namespace std;

// === EXTERNAL METHODS =================================

// Initializes SDL
auto InitializeSDL(string title, int width, int height) -> pair<SDL_Window *, SDL_Renderer *>
{
  cout << "Initializing SDL..." << endl;

  // === BASE SDL

  // Initialize SDL & all it's necessary subsystems
  auto encounteredError = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

  // Catch any errors
  if (encounteredError)
    throw runtime_error("Failed to initialize SDL. Reported error: " + string(SDL_GetError()));

  // === SDL IMAGE

  // Initialize the image module
  int requestedFlags = IMG_INIT_JPG | IMG_INIT_PNG;
  int returnedFlags = IMG_Init(requestedFlags);

  // Check if everything went alright
  if ((returnedFlags & requestedFlags) != requestedFlags)
    throw runtime_error("Failed to initialize SDL-image. Reported error: " + string(IMG_GetError()));

  // === SDL MIXER

  // Commented out, still no need to initialize anything other than wav, which ships out of the box
  // Initialize the mixer
  // Mix_Init();

  // Initialize open audio
  encounteredError = Mix_OpenAudio(
      MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

  // Catch any errors
  if (encounteredError)
    throw runtime_error("Failed to initialize SDL-mixer. Reported error: " + string(Mix_GetError()));

  // Allocate more sound channels
  Mix_AllocateChannels(32);

  // === GAME WINDOW

  auto gameWindow = SDL_CreateWindow(
      title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  // Catch any errors
  if (gameWindow == nullptr)
    throw runtime_error("Failed to create SDL window. Reported error: " + string(SDL_GetError()));

  // Create renderer
  auto renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

  // Catch any errors
  if (renderer == nullptr)
    throw runtime_error("Failed to create SDL renderer. Reported error: " + string(SDL_GetError()));

  cout << "Done!" << endl;

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
    throw invalid_argument("Tried to instantiate another Game instance");

  // === INIT SDL

  // Retrieve the window & the renderer from the initializer
  auto pointers = InitializeSDL(title, width, height);

  // === INITIALIZE STATE
  window.reset(pointers.first);
  renderer.reset(pointers.second);

  state = make_unique<GameState>();
}

Game::~Game()
{
  // Quit SDL
  // Release the pointers, as we will destroy them in the method
  ExitSDL(window.release(), renderer.release());
}

// === PUBLIC METHODS =================================

Game &Game::GetInstance()
{
  // If it doesn't exist...
  if (!gameInstance)
  {
    // Create it
    gameInstance = unique_ptr<Game>(new Game("The Watch Penguins", 600, 600));
  }

  // Return the instance
  return *gameInstance;
}

void Game::Run()
{
  // Find out how many ms to wait to achieve the configured framerate
  const int frameDelay = 1000 / Game::frameRate;

  // Loop while exit not requested
  while (state->QuitRequested() == false)
  {
    // Update the state
    state->Update(0);

    // Render the state
    state->Render();

    // Render the window
    SDL_RenderPresent(GetRenderer());

    // Delay the frame to obey the framerate
    SDL_Delay(frameDelay);
  }
}