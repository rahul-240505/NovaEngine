#pragma once

#include "System.h"
#include "Signature.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <cassert>

class SystemManager {
public:
    // --- System Management ---

    template<typename T>
    std::shared_ptr<T> registerSystem() {
        // Get the system's name
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

        // Create a new system and store it
        auto system = std::make_shared<T>();
        m_systems[typeName] = system;
        return system;
    }

    template<typename T>
    void setSignature(Signature signature) {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) != m_systems.end() && "System not registered before setting signature.");

        // Set the signature for this system
        m_signatures[typeName] = signature;
    }

    // --- Entity Management ---

    void entityDestroyed(Entity entity) {
        // When an entity is destroyed, remove it from all systems
        for (auto const& pair : m_systems) {
            auto const& system = pair.second;

            // Efficiently remove the entity from the system's set
            system->m_entities.erase(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entitySignature) {
        // This is a key part of the ECS!
        // When an entity's components change, check if it should be
        // added to or removed from any systems.
        for (auto const& pair : m_systems) {
            auto const& systemTypeName = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = m_signatures[systemTypeName];

            // Bitwise AND. If the entity's signature contains all the bits
            // from the system's signature, then the system is interested in it.
            if ((entitySignature & systemSignature) == systemSignature) {
                // Matched! Add to system's set.
                system->m_entities.insert(entity);
            }
            else {
                // No match. Remove from system's set.
                system->m_entities.erase(entity);
            }
        }
    }

private:
    // Map from system type name (string) to its signature
    std::unordered_map<const char*, Signature> m_signatures{};

    // Map from system type name (string) to the system object
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
};