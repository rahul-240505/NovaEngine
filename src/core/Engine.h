#pragma once

struct EngineConfig {
    const char* windowTitle = "NovaEngine";
    int width = 1280;
    int height = 720;
};

class Engine {
public:
    Engine();
    ~Engine();

    void init(const EngineConfig& cfg);
    void run();
    void shutdown();

private:
    void initSubsystems();
    void processEvents();
    void update();
    void render();
    
    bool m_isRunning = false;
};