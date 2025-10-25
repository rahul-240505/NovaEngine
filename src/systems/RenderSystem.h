#pragma once

#include "../ecs/System.h"
#include "../ecs/Coordinator.h"
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader;

class RenderSystem : public System {
public:
    void init(std::shared_ptr<Coordinator> coordinator);
    void shutdown(); // Add a shutdown method
    void update();

private:
    void initRenderData();

    std::shared_ptr<Coordinator> m_coordinator;
    std::shared_ptr<Shader> m_shader; // Pointer to our shader

    GLuint quadVAO = 0; // Vertex Array Object
    GLuint quadVBO = 0; // Vertex Buffer Object
    GLuint quadEBO = 0; // Element Buffer Object

    glm::mat4 projection; // Projection matrix
};