#pragma once

#include "Component.h"
#include "ComponentArray.h"
#include <unordered_map>
#include <memory>
#include <string>

class ComponentManager {
public:
    // --- Component Type Management ---

    template<typename T>
    void registerComponent() {
        // Get the component's name
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once.");

        // Add this component type to the maps
        m_componentTypes[typeName] = m_nextComponentType;
        m_componentArrays[typeName] = std::make_shared<ComponentArray<T>>();

        // Increment the type ID for the next component
        ++m_nextComponentType;
    }

    template<typename T>
    ComponentType getComponentType() {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        return m_componentTypes[typeName];
    }

    // --- Component Data Management ---

    template<typename T>
    void addComponent(Entity entity, T component) {
        // Add a component to the entity's component array
        getComponentArray<T>()->insertData(entity, component);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        // Remove a component from the entity's component array
        getComponentArray<T>()->removeData(entity);
    }

    template<typename T>
    T& getComponent(Entity entity) {
        // Get a reference to a component from the entity's component array
        return getComponentArray<T>()->getData(entity);
    }

    // --- Entity Management ---

    void entityDestroyed(Entity entity) {
        // Notify all component arrays that this entity is gone
        // This is a key part of the ECS!
        for (auto const& pair : m_componentArrays) {
            auto const& componentArray = pair.second;
            componentArray->entityDestroyed(entity);
        }
    }

private:
    // Helper function to get the casted ComponentArray<T>
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        // Cast the IComponentArray (base) to ComponentArray<T> (derived)
        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }

private:
    // Map from component type name (string) to a component type ID
    std::unordered_map<const char*, ComponentType> m_componentTypes{};

    // Map from component type name (string) to its ComponentArray
    // We store a pointer to the base interface.
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};

    // The next component type ID to be assigned
    ComponentType m_nextComponentType = 0;
};