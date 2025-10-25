#include "core/Engine.h"
#include <iostream>

#include <GLFW/glfw3.h>

using std::cout;
using std::cerr;
using std::endl;

Engine::Engine() {
    cout << "Engine constructed." << endl;
}

Engine::~Engine() {
    cout << "Engine destructed." << endl;
}

void Engine::init(const EngineConfig& cfg) {
    cout << "Initializing Engine: " << cfg.windowTitle << endl;
    
    // Test GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW!" << endl;
        return;
    }
    cout << "GLFW Initialized." << endl;

    initSubsystems();
    m_isRunning = true; 
}

void Engine::run() {
    cout << "Engine run() started." << endl;
    
    while (m_isRunning) {
        processEvents();
        update();
        render();

        cout << "Engine loop ran once. Shutting down." << endl;
        m_isRunning = false; 
    }
}

void Engine::shutdown() {
    cout << "Shutting down Engine." << endl;
    glfwTerminate();
    cout << "GLFW Terminated." << endl;
}

void Engine::initSubsystems() {
    cout << "Initializing subsystems..." << endl;
}

void Engine::processEvents() {
    glfwPollEvents();
}

void Engine::update() {
    // Update game logic
}

void Engine::render() {
    // Render frame
}