#include "RenderSystem.h"
#include "../ecs/Transform.h"
#include "../ecs/SpriteRenderer.h"
#include "../renderer/Shader.h"
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

using std::cout;
using std::endl;
using std::vector;

void RenderSystem::init(std::shared_ptr<Coordinator> coordinator) {
    m_coordinator = coordinator;
    cout << "RenderSystem Initialized." << endl;

    // Load shaders
    m_shader = std::make_shared<Shader>("assets/shaders/simple.vert", "assets/shaders/simple.frag");

    // Setup quad VAO/VBO/EBO
    initRenderData();

    // Setup projection matrix (orthographic for 2D)
    // Use fixed dimensions for now (e.g., 800x600 world units)
    // We'll get this from the window later
    float screenWidth = 1280.0f;
    float screenHeight = 720.0f;
    projection = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);

    // Configure shader uniforms that don't change often
    m_shader->use();
    m_shader->setMat4("projection", projection);

    cout << "RenderSystem Initialized." << endl;
}

void RenderSystem::shutdown() {
    // Delete OpenGL buffers
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteBuffers(1, &quadEBO);
    // Shader is managed by shared_ptr, will delete automatically
    cout << "RenderSystem Shutdown." << endl;
}

void RenderSystem::initRenderData() {
    // Define vertices for a quad (positions only for now)
    // The quad covers the [-0.5, 0.5] range in x and y
    vector<float> vertices = {
        // Pos      
        -0.5f, -0.5f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f, // Bottom Right
         0.5f,  0.5f, 0.0f, // Top Right
        -0.5f,  0.5f, 0.0f  // Top Left 
    };

    // Define indices to draw two triangles forming the quad
    vector<unsigned int> indices = {
        0, 1, 2, // First Triangle
        2, 3, 0  // Second Triangle
    };

    // 1. Create VAO, VBO, EBO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &quadEBO);

    // 2. Bind VAO
    glBindVertexArray(quadVAO);

    // 3. Copy vertex data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // 4. Copy index data to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // 5. Set vertex attribute pointers
    // Position attribute (layout location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 6. Unbind VAO (important!)
    glBindVertexArray(0);
    // VBO and EBO are unbound implicitly when VAO is unbound, but you can unbind them explicitly too if preferred
    // glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

void RenderSystem::update() {
    // Activate the shader program
    m_shader->use();

    // Bind the VAO for the quad
    glBindVertexArray(quadVAO);

    // Loop through all entities the system cares about
    for (auto const& entity : m_entities) {
        // Get the entity's components
        auto& transform = m_coordinator->getComponent<Transform>(entity);
        auto& sprite = m_coordinator->getComponent<SpriteRenderer>(entity);

        // --- Calculate Model Matrix ---
        glm::mat4 model = glm::mat4(1.0f); // Start with identity matrix

        // 1. Translate
        model = glm::translate(model, glm::vec3(transform.position, 0.0f));

        // 2. Rotate (around Z axis for 2D)
        // We translate to origin, rotate, then translate back if rotating around a pivot other than center
        // For simplicity now, just rotate around center (0,0,0) of the model space
        model = glm::rotate(model, transform.rotation, glm::vec3(0.0f, 0.0f, 1.0f));

        // 3. Scale
        model = glm::scale(model, glm::vec3(transform.scale, 1.0f));
        // ---

        // --- Set Uniforms ---
        m_shader->setMat4("model", model);
        m_shader->setVec4("spriteColor", sprite.color);
        // (Texture uniform will be set later)
        // ---

        // --- Draw Call ---
        // Draw the quad using the EBO
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 6 indices for 2 triangles
        // ---
    }

    // Unbind the VAO (good practice)
    glBindVertexArray(0);
}