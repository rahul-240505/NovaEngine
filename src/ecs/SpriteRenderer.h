#pragma once
#include <glm/glm.hpp>

// SpriteRenderer component: defines the visual appearance.
struct SpriteRenderer {
    // Placeholder for a texture ID (will be an unsigned integer)
    unsigned int textureID = 0;

    // Color tint (RGBA)
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};