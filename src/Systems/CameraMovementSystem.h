#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>

class CameraMovementSystem : public System
{
public:
  CameraMovementSystem()
  {
    RequireComponent<CameraFollowComponent>();
    RequireComponent<TransformComponent>();
  }

  void Update(SDL_Rect& camera)
  {
    for (auto entity : GetSystemEntities()) {
      auto transform = entity.GetComponent<TransformComponent>();
      // TODO: change camera.x & camera.y based on the entity transform position
    }
  }
};

#endif
