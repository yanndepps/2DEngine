#include "Game.h"
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
