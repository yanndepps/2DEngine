#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class MovementSystem : public System
{
      public:
	MovementSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void Update(double deltaTime)
	{
		// loop all entities that the system is interested in
		for (auto entity : GetSystemEntities()) {
			// update entity position based on its velocity
			auto& transform = entity.GetComponent<TransformComponent>();
			auto rigidbody = entity.GetComponent<RigidBodyComponent>();

			transform.position.x += rigidbody.velocity.x * deltaTime;
			transform.position.y += rigidbody.velocity.y * deltaTime;

			Logger::Log(
			    "Entity id = " +
			    std::to_string(entity.GetId()) +
			    " position is now (" +
			    std::to_string(transform.position.x) +
			    ", " +
			    std::to_string(transform.position.y) + ")");
		}
	}
};

#endif
