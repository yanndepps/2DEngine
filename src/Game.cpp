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
  //---
  std::cout << "Game destructor called!" << std::endl;
}

// member functions
void Game::Initialize() {
  //---
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error initializing SDL!" << std::endl;
    return;
  }
  // create SDL window
  SDL_Window *window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_BORDERLESS);
  if (!window) {
    std::cerr << "Error creating SDL window!" << std::endl;
    return;
  }
  // create a renderer inside our window
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    std::cerr << "Error creating SDL renderer!" << std::endl;
    return;
  }
}

void Game::Run() {
  //---
}

void Game::ProcessInput() {
  //---
}

void Game::Update() {
  //---
}

void Game::Render() {
  //---
}

void Game::Destroy() {
  //---
}
