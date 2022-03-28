#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../AssetStore/AssetStore.h"
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

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore)
	{
		// TODO: Sort all the entities of our system by the z-index
		// loop all entities that the system is interested in
		for (auto entity : GetSystemEntities()) {
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			// Set the source rectangle of our original sprite texture
			SDL_Rect srcRect = sprite.srcRect;

			// Set the destination rectangle with the x,y position to be rendered
			SDL_Rect dstRect = {
			    static_cast<int>(transform.position.x),
			    static_cast<int>(transform.position.y),
			    static_cast<int>(sprite.width * transform.scale.x),
			    static_cast<int>(sprite.height * transform.scale.y)};

			SDL_RenderCopyEx(
			    renderer,
			    assetStore->GetTexture(sprite.assetId),
			    &srcRect,
			    &dstRect,
			    transform.rotation,
			    NULL,
			    SDL_FLIP_NONE);
		}
	}
};

#endif
