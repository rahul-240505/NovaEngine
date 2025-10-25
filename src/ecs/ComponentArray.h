#pragma once

#include "Entity.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <cassert>

// --- The Interface ---
// This allows ComponentManager to hold a collection of ComponentArray<T> 
// without needing to know the type T.
class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    // We need a virtual method to notify the array when an entity is destroyed
    virtual void entityDestroyed(Entity entity) = 0;
};


// --- The Templated Array ---
template<typename T>
class ComponentArray : public IComponentArray {
public:
    // Adds a component for an entity
    void insertData(Entity entity, T component) {
        assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

        // Put new entry at the end of the packed array
        size_t newIndex = m_size;
        m_entityToIndexMap[entity] = newIndex;
        m_indexToEntityMap[newIndex] = entity;
        m_componentArray[newIndex] = component;
        ++m_size;
    }

    // Removes a component from an entity
    void removeData(Entity entity) {
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Removing non-existent component.");

        // This is the "packed array" trick:
        // To remove an element, we move the *last* element in the array
        // into the deleted element's slot. This keeps the array packed.

        // 1. Get the index of the entity to remove
        size_t indexOfRemoved = m_entityToIndexMap[entity];

        // 2. Get the index of the last element
        size_t indexOfLast = m_size - 1;

        // 3. Move the last element's data into the removed element's slot
        m_componentArray[indexOfRemoved] = m_componentArray[indexOfLast];

        // 4. Update the maps to point to the new locations
        Entity entityOfLast = m_indexToEntityMap[indexOfLast];
        m_entityToIndexMap[entityOfLast] = indexOfRemoved;
        m_indexToEntityMap[indexOfRemoved] = entityOfLast;

        // 5. Erase the old map entries
        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(indexOfLast);

        --m_size;
    }

    // Gets a reference to an entity's component
    T& getData(Entity entity) {
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Retrieving non-existent component.");
        return m_componentArray[m_entityToIndexMap[entity]];
    }

    // Implementation for the interface's virtual method
    void entityDestroyed(Entity entity) override {
        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end()) {
            // If the entity has a component in this array, remove it
            removeData(entity);
        }
    }

private:
    // The packed array of components
    std::array<T, MAX_ENTITIES> m_componentArray;

    // Maps from an entity ID to an array index
    std::unordered_map<Entity, size_t> m_entityToIndexMap;

    // Maps from an array index back to an entity ID
    std::unordered_map<size_t, Entity> m_indexToEntityMap;

    // Total number of valid components in the array
    size_t m_size = 0;
};