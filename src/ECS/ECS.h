#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

//////////////////////////////////////////////////////////////////
// Signature
//////////////////////////////////////////////////////////////////
// Use a bitset ( 0s and 1s ) to keep track of which components
// an entity has, and also helps keep track of which entities
// a system is interested in.
//////////////////////////////////////////////////////////////////

typedef std::bitset<MAX_COMPONENTS> Signature;

class Component {
  // TODO: ...
};

class Entity {
private:
  int id;

public:
  Entity(int id) : id(id){};
  int GetId() const;
};

//////////////////////////////////////////////////////////////////
// System
//////////////////////////////////////////////////////////////////
// the system processes entities that contain a specific signature
//////////////////////////////////////////////////////////////////

class System {
private:
  Signature componentSignature;
  std::vector<Entity> entities;

public:
  System() = default;
  ~System() = default;

  void AddEntityToSystem(Entity entity);
  void RemoveEntityFromSystem(Entity entity);
  std::vector<Entity> GetSystemEntities() const;
  Signature &GetComponentSignature() const;
};

class Registry {
  // TODO: ...
};

#endif
