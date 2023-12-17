
#ifndef ENTITY_MANAGER_HPP_
#define ENTITY_MANAGER_HPP_

#include <cstdint>
#include <vector>

using Entity = std::uint32_t;

class EntityManager
{
public:
    EntityManager() {};
    Entity create_entity()
    {
        if (this->unused_entities.size() > 0) {
            Entity entity = this->unused_entities.back();
            this->unused_entities.pop_back();
            return entity;
        }
        return entity_counter++;
    }
    void destroy_entity(Entity entity)
    {
        this->unused_entities.push_back(entity);
    }
private:
    std::vector<Entity> unused_entities;
    Entity entity_counter;
};

#endif // ENTITY_MANAGER_HPP_
