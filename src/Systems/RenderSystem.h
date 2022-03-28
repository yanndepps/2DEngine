#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../AssetStore/AssetStore.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <algorithm>

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
		// Create a vector with both Sprite and Transform components of all entities
		struct RenderableEntity {
			TransformComponent transformComponent;
			SpriteComponent spriteComponent;
		};
		std::vector<RenderableEntity> renderableEntities;
		for (auto entity : GetSystemEntities()) {
			RenderableEntity renderableEntity;
			renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();
			renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
			renderableEntities.emplace_back(renderableEntity);
		}

		// Sort the vector by the z-index value
		std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) {
			return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
		});

		// loop all entities that the system is interested in
		for (auto entity : renderableEntities) {
			const auto transform = entity.transformComponent;
			const auto sprite = entity.spriteComponent;

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
