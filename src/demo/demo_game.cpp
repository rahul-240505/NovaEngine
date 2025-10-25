#include "../core/Engine.h"
#include "../ecs/Coordinator.h"
#include "../ecs/Transform.h"
#include "../ecs/SpriteRenderer.h"
#include <iostream>

// Forward declaration of the Engine instance (defined in main.cpp)
// This is a simple way to access it, though more complex games might use singletons or service locators.
extern Engine g_engine;

void loadDemoScene() {
    std::cout << "Loading Demo Scene..." << std::endl;

    // Get the coordinator from the global engine instance
    auto coordinator = g_engine.m_coordinator;

    // Create an entity
    Entity testEntity = coordinator->createEntity();
    std::cout << "Created Entity: " << testEntity << std::endl;

    // Add a Transform component
    coordinator->addComponent(
        testEntity,
        Transform{
            .position = glm::vec2(640.0f, 360.0f), // Center of 1280x720 window
            .scale = glm::vec2(100.0f, 100.0f),    // 100x100 pixels
            .rotation = 0.0f
        }
    );
    std::cout << "Added Transform component to Entity " << testEntity << std::endl;


    // Add a SpriteRenderer component
    coordinator->addComponent(
        testEntity,
        SpriteRenderer{
            .textureID = 0, // No texture yet
            .color = glm::vec4(0.8f, 0.2f, 0.2f, 1.0f) // Red color
        }
    );
    std::cout << "Added SpriteRenderer component to Entity " << testEntity << std::endl;

    std::cout << "Demo Scene Loaded." << std::endl;
}

// We need a function to call this scene loading logic.
// Let's create a placeholder for now. We'll call it from main.cpp later.
void setupDemo() {
    loadDemoScene();
}