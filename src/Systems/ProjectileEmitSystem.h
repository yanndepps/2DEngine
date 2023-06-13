#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>

class ProjectileEmitSystem : public System
{
public:
  ProjectileEmitSystem()
  {
    RequireComponent<ProjectileEmitterComponent>();
    RequireComponent<TransformComponent>();
  }

  void Update()
  {
    for (auto entity : GetSystemEntities()) {
      auto projectile = entity.GetComponent<ProjectileEmitterComponent>();
      auto transform = entity.GetComponent<TransformComponent>();

      // check if its time to re-emit a new projectile
      if (SDL_GetTicks() - projectile.lastEmissionTime > projectile.repeatFrequency) {
	// TODO: add a new projectile to the game scene
      }
    }
  }
};

#endif
