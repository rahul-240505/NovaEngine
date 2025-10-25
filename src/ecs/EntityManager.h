#pragma once

#include "Entity.h"
#include "Signature.h"
#include <queue>
#include <array>

class EntityManager {
public:
    EntityManager();

    Entity createEntity();
    void destroyEntity(Entity entity);

    void setSignature(Entity entity, Signature signature);
    Signature getSignature(Entity entity);

private:
    // A queue of unused entity IDs
    std::queue<Entity> m_availableEntities{};

    // An array to store the signature for each entity
    std::array<Signature, MAX_ENTITIES> m_signatures{};

    // The total number of living entities
    uint32_t m_livingEntityCount = 0;
};