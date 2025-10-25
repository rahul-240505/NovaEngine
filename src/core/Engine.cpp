#include "Engine.h"
#include "../renderer/Window.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../ecs/Transform.h"
#include "../ecs/SpriteRenderer.h"

using std::cout;
using std::cerr;
using std::endl;

Engine::Engine() {
    cout << "Engine constructed." << endl;

    m_coordinator = std::make_shared<Coordinator>();
}

Engine::~Engine() {
    cout << "Engine destructed." << endl;
}

void Engine::init(const EngineConfig& cfg) {
    m_config = cfg;
    cout << "Initializing Engine: " << cfg.windowTitle << endl;
    
    // Test GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW!" << endl;
        return;
    }
    cout << "GLFW Initialized." << endl;

    initSubsystems();
    registerComponents();
    registerSystems();
    m_isRunning = true; 
}

void Engine::run() {
    cout << "Engine run() started." << endl;
    
    while (m_isRunning && !m_window->shouldClose()) {
        processEvents();
        update();
        render();
    }
}

void Engine::shutdown() {
    cout << "Shutting down Engine." << endl;
    m_window->close();
    glfwTerminate();
    cout << "GLFW Terminated." << endl;
}

void Engine::initSubsystems() {
    cout << "Initializing subsystems..." << endl;

    m_window = std::make_unique<Window>();
    m_window->init(m_config);
}

void Engine::registerComponents() {
    cout << "Registering components..." << endl;

    m_coordinator->registerComponent<Transform>();
    m_coordinator->registerComponent<SpriteRenderer>();
}

void Engine::registerSystems() {
    cout << "Registering systems..." << endl;
}

void Engine::processEvents() {
    glfwPollEvents();
}

void Engine::update() {
    // Update game logic
}

void Engine::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark grey
    glClear(GL_COLOR_BUFFER_BIT);

    m_window->swapBuffers();
}