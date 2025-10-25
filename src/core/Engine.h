#pragma once

#include "../ecs/Coordinator.h"
#include "EngineConfig.h"
#include <memory>

class Window;
class RenderSystem;

class Engine {
public:
    Engine();
    ~Engine();

    void init(const EngineConfig& cfg);
    void run();
    void shutdown();

    std::shared_ptr<Coordinator> m_coordinator;
    std::unique_ptr<Window> m_window;
    std::shared_ptr<RenderSystem> m_renderSystem;

private:
    void initSubsystems();
    void registerComponents();
    void registerSystems();

    void processEvents();
    void update();
    void render();
    
    float m_deltaTime = 0.0f;
    bool m_isRunning = false;

    EngineConfig m_config;
};