#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"

class EventBus
{
public:
  EventBus()
  {
    Logger::Log("EventBus constructor called!");
  }

  ~EventBus()
  {
    Logger::Log("EventBus destructor called!");
  }

  //////////////////////////////////////////////////////////////////////////
  // Subscribe to an event type <T>
  // In our implementation, a listener subscribes to an event
  // Example: eventBus->SubscribeToEvent<CollisionEvent>(&Game::onCollision);
  //////////////////////////////////////////////////////////////////////////

  void SubscribeToEvent<___>()
  {
    // TODO
  }

  //////////////////////////////////////////////////////////////////////////
  // Emit an event of type <T>
  // In our implementation, as soon as something emits an event we go ahead
  // and execute all the listener callback functions
  // Example: eventBus-> EmitEvent<CollisionEvent>(player, entity);
  //////////////////////////////////////////////////////////////////////////

  void EmitEvent<___>()
  {
    // TODO
  }
};

#endif
