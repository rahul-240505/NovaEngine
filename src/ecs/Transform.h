#pragma once
#include <glm/glm.hpp>

// Transform component: basic position, rotation, and scale data.
struct Transform {
    // glm::vec2/3 for performance and math convenience
    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    float rotation = 0.0f; // Rotation in radians
};