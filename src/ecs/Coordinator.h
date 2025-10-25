#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include <memory>

class Coordinator {
public:
    Coordinator() {
        // Create the managers
        m_entityManager = std::make_shared<EntityManager>();
        m_componentManager = std::make_shared<ComponentManager>();
        m_systemManager = std::make_shared<SystemManager>();
    }

    // --- Entity Methods ---
    Entity createEntity() {
        return m_entityManager->createEntity();
    }

    void destroyEntity(Entity entity) {
        m_entityManager->destroyEntity(entity);
        m_componentManager->entityDestroyed(entity);
        m_systemManager->entityDestroyed(entity);
    }


    // --- Component Methods ---
    template<typename T>
    void registerComponent() {
        m_componentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        m_componentManager->addComponent<T>(entity, component);

        // Get the entity's new signature and update the managers
        auto signature = m_entityManager->getSignature(entity);
        signature.set(m_componentManager->getComponentType<T>(), true);
        m_entityManager->setSignature(entity, signature);
        m_systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        m_componentManager->removeComponent<T>(entity);

        // Get the entity's new signature and update the managers
        auto signature = m_entityManager->getSignature(entity);
        signature.set(m_componentManager->getComponentType<T>(), false);
        m_entityManager->setSignature(entity, signature);
        m_systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& getComponent(Entity entity) {
        return m_componentManager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType() {
        return m_componentManager->getComponentType<T>();
    }


    // --- System Methods ---
    template<typename T>
    std::shared_ptr<T> registerSystem() {
        return m_systemManager->registerSystem<T>();
    }

    template<typename T>
    void setSystemSignature(Signature signature) {
        m_systemManager->setSignature<T>(signature);
    }

private:
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<ComponentManager> m_componentManager;
    std::shared_ptr<SystemManager> m_systemManager;
};