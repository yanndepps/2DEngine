#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>

class RenderSystem : public System
{
      public:
	RenderSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(SDL_Renderer* renderer)
	{
		// loop all entities that the system is interested in
		for (auto entity : GetSystemEntities()) {
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			// For now, simply render a rectangle with SDL
			SDL_Rect objRect = {
			    static_cast<int>(transform.position.x),
			    static_cast<int>(transform.position.y),
			    sprite.width,
			    sprite.height,
			};
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &objRect);
		}
	}
};

#endif
