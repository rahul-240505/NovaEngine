#pragma once

#include "../core/EngineConfig.h"
#include <string>

// Forward declaration to avoid including the GLFW header everywhere
struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    void init(const EngineConfig& cfg);
    void swapBuffers();
    void close();
    bool shouldClose() const;

    // The core GLFW window pointer
    GLFWwindow* getGLFWwindow() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
    EngineConfig m_config;

    void setGLFWCallbacks();
};