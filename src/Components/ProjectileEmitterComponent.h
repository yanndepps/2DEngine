#ifndef PROJECTILEEMITTERCOMPNENT_H
#define PROJECTILEEMITTERCOMPNENT_H

#include "../../libs/glm/glm.hpp"
#include <SDL2/SDL.h>

struct ProjectileEmitterComponent {
  glm::vec2 projectileVelocity;
  int projectileDuration;
  int hitPercentDamage;
  bool isFriendly;
  Uint32 repeatFrequency;
  Uint32 lastEmissionTime;

  ProjectileEmitterComponent(glm::vec2 projectileVelocity = glm::vec2(0), Uint32 repeatFrequency = 0, int projectileDuration = 10000, int hitPercentDamage = 10, bool isFriendly = false)
  {
    this->projectileVelocity = projectileVelocity;
    this->repeatFrequency = repeatFrequency;
    this->projectileDuration = projectileDuration;
    this->hitPercentDamage = hitPercentDamage;
    this->isFriendly = isFriendly;
    this->lastEmissionTime = SDL_GetTicks();
  }
};

#endif
