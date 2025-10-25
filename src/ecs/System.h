#pragma once

#include "Entity.h"
#include <set>

class System {
public:
    // This set contains all entities that this system is interested in
    std.set<Entity> m_entities;

    virtual ~System() = default;
};