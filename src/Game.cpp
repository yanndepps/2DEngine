#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

// scope resolution
Game::Game() {
  // ---
  std::cout << "Game constructor called!" << std::endl;
}

// our destructor
Game::~Game() {
  isRunning = false;
  std::cout << "Game destructor called!" << std::endl;
}

// member functions
void Game::Initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error initializing SDL!" << std::endl;
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
    std::cerr << "Error creating SDL window!" << std::endl;
    return;
  }
  // create a renderer inside our window
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    std::cerr << "Error creating SDL renderer!" << std::endl;
    return;
  }
  // set the video mode to be real fullscreen
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  isRunning = true;
}

void Game::Run() {
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
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

void Game::Update() {
  // TODO: update game objects
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  // TODO: render all game objects
  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
