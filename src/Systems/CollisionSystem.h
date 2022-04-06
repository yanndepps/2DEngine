#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class CollisionSystem : public System
{
      public:
	CollisionSystem()
	{
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update()
	{
		// TODO:
		// Check all entities that have a boxcollider
		// to see if they are colliding with each other
		// Tips : AABB collision check -> Axis-Aligned Bounding Boxes
	}
};

#endif
