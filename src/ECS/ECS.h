#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <set>
#include <typeindex>
#include <unordered_map>
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

struct IComponent {
  protected:
    static int nextId;
};

// used to assign a unique id to a component type
template <typename T>
class Component : public IComponent
{
    // returns the unique id of Component<T>
    static int GetId()
    {
	static auto id = nextId++;
	return id;
    }
};

class Entity
{
  private:
    int id;

  public:
    Entity(int id) : id(id){};
    Entity(const Entity& entity) = default;
    int GetId() const;

    Entity& operator=(const Entity& other) = default;
    bool operator==(const Entity& other) const { return id == other.id; }
    bool operator!=(const Entity& other) const { return id != other.id; }
    bool operator>(const Entity& other) const { return id > other.id; }
    bool operator<(const Entity& other) const { return id < other.id; }
};

//////////////////////////////////////////////////////////////////
// System
//////////////////////////////////////////////////////////////////
// the system processes entities that contain a specific signature
//////////////////////////////////////////////////////////////////

class System
{
  private:
    Signature componentSignature;
    std::vector<Entity> entities;

  public:
    System() = default;
    ~System() = default;

    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;
    const Signature& GetComponentSignature() const;

    // defines the component type that entities must have to be considered by the
    // system
    template <typename TComponent>
    void RequireComponent();
};

//////////////////////////////////////////////////////////////////
// Pool
//////////////////////////////////////////////////////////////////
// A pool is just a vector ( contiguous data ) of objects of
// type T.
//////////////////////////////////////////////////////////////////
class IPool
{
  public:
    virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool
{
  private:
    std::vector<T> data;

  public:
    Pool(int size = 100) { data.resize(size); }
    virtual ~Pool() = default;
    bool isEmpty() const { return data.empty(); }
    int GetSize() const { return data.size(); }
    void Resize(int n) { data.resize(n); }
    void Clear() { data.clear(); }
    void Add(T object) { data.push_back(object); }
    void Set(int index, T object) { data[index] = object; }
    T& Get(int index) { return static_cast<T&>(data[index]); }
    T& operator[](unsigned int index) { return data[index]; }
};

//////////////////////////////////////////////////////////////////
// Registry
//////////////////////////////////////////////////////////////////
// The registry manages the creation and destruction of entities,
// add systems and components.
//////////////////////////////////////////////////////////////////
class Registry
{
  private:
    int numEntities = 0;

    // Vector of component pools; each pool contains all the data
    // for a certain component type
    // [ Vector index = component type id ]
    // [ Pool index = entity id ]
    std::vector<IPool*> componentPools;

    // Vector of component signatures per entity, saying which
    // component is turned "on" for a given entity.
    // [ Vector index = entity ID ]
    std::vector<Signature> entityComponentSignatures;

    std::unordered_map<std::type_index, System*> systems;

    // Set of entities that are flagged to be added or removed
    // in the next registry Update()
    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

  public:
    Registry() = default;

    void Update();

    Entity CreateEntity();

    // TODO: AddComponent<T>( ... );

    void AddEntityToSystem(Entity entity);

    // TODO:
    //
    //
    // AddComponent(Entity entity)
    // GetComponent(Entity entity)
    //
    // AddSystem()
};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

#endif
