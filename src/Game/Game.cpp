#include "Game.h"
#include "../../libs/glm/glm.hpp"
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// scope resolution
Game::Game() {
  // ---
  isRunning = false;
  // std::cout << "Game constructor called!" << std::endl;
  Logger::Log("Game constructor called!");
}

// our destructor
Game::~Game() {
  // std::cout << "Game destructor called!" << std::endl;
  Logger::Log("Game destructor called!");
}

// member functions
void Game::Initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    // std::cerr << "Error initializing SDL!" << std::endl;
    Logger::Err("Error initializing SDL!");
    return;
  }
  // create SDL window
  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = displayMode.w;
  windowHeight = displayMode.h;
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
  if (!window) {
    // std::cerr << "Error creating SDL window!" << std::endl;
    Logger::Err("Error creating SDL window!");
    return;
  }
  // create a renderer inside our window
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    // std::cerr << "Error creating SDL renderer!" << std::endl;
    Logger::Err("Error creating SDL rendeer!");
    return;
  }
  // set the video mode to be real fullscreen
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  isRunning = true;
}

void Game::ProcessInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
      break;
    }
  }
}

void Game::Setup() {
  // TODO:
  // Entitiy tank = registry.CreateEntity();
  // tank.AddComponent<TransformComponent>();
  // tank.AddComponent<BoxColliderComponent>();
  // tank.AddComponent<SpriteComponent>("../assets/images/tank.png");
}

void Game::Update() {
  // if we are too fast, waste some time until we reach the
  // MILLSECS_PER_FRAME
  // this can be bypassed to uncap the framerate
  int timeToWait =
      MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
  if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  // the difference in ticks since the last frame, converted to seconds
  double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

  // store the current frame time
  millisecsPreviousFrame = SDL_GetTicks();

  // TODO:
  // MovementSystem.Update();
  // CollisionSystem.Update();
  // DamageSystem.Update();
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  // TODO: Render game objects ...

  SDL_RenderPresent(renderer);
}

void Game::Run() {
  Setup();
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
