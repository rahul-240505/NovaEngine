#include "EntityManager.h"
#include <cassert>

EntityManager::EntityManager() {
    // Initialize the queue with all possible entity IDs
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        m_availableEntities.push(entity);
    }
}

Entity EntityManager::createEntity() {
    // Ensure we haven't exceeded the max number of entities
    assert(m_livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

    // Take an ID from the front of the queue
    Entity id = m_availableEntities.front();
    m_availableEntities.pop();
    ++m_livingEntityCount;

    return id;
}

void EntityManager::destroyEntity(Entity entity) {
    // Ensure the entity ID is valid
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Reset its signature
    m_signatures[entity].reset();

    // Put the destroyed ID back in the queue
    m_availableEntities.push(entity);
    --m_livingEntityCount;
}

void EntityManager::setSignature(Entity entity, Signature signature) {
    // Ensure the entity ID is valid
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    m_signatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity) {
    // Ensure the entity ID is valid
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    return m_signatures[entity];
}