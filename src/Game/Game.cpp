#include "Game.h"
#include "../../libs/glm/glm.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../Systems/MovementSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Game::Game()
{
	isRunning = false;
	registry = std::make_unique<Registry>();
	Logger::Log("Game constructor called!");
}

Game::~Game() { Logger::Log("Game destructor called!"); }

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
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
		Logger::Err("Error creating SDL window!");
		return;
	}
	// create a renderer inside our window
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		Logger::Err("Error creating SDL rendeer!");
		return;
	}
	// set the video mode to be real fullscreen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	isRunning = true;
}

void Game::ProcessInput()
{
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

void Game::Setup()
{
	// Add the systems that need to be processed in our game
	registry->AddSystem<MovementSystem>();

	// Create an entity
	Entity tank = registry->CreateEntity();

	// Add some components to that entity
	tank.AddComponent<TransformComponent>(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 0.0);
	tank.AddComponent<RigidBodyComponent>(glm::vec2(10.0, 50.0));

	// Remove a component from the entity
	// tank.RemoveComponent<TransformComponent>();
}

void Game::Update()
{
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

	// Update the registry to process the entities that are waiting to be created/deleted
	registry->Update();

	// Ask all the systems to update
	registry->GetSystem<MovementSystem>().Update(deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// TODO: Render game objects ...

	SDL_RenderPresent(renderer);
}

void Game::Run()
{
	Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
