#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

// Helper function to handle GLFW errors
void glfw_error_callback(int error, const char* description) {
    cerr << "GLFW Error (" << error << "): " << description << endl;
}

Window::Window() {
    glfwSetErrorCallback(glfw_error_callback);
}

Window::~Window() {
    close();
}

void Window::init(const EngineConfig& cfg) {
    m_config = cfg;

    // Set OpenGL version hints (Core profile, Modern OpenGL 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(cfg.width, cfg.height, cfg.windowTitle, nullptr, nullptr);

    if (!m_window) {
        cerr << "Failed to create GLFW window." << endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }

    // Set the window as the current OpenGL context
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD (OpenGL loader)." << endl;
        throw std::runtime_error("Failed to initialize GLAD.");
    }
    cout << "GLAD Initialized (OpenGL " << GLVersion.major << "." << GLVersion.minor << ")." << endl;

    // Set the viewport and a clear color
    glViewport(0, 0, cfg.width, cfg.height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Dark teal background

    // Enable V-Sync
    glfwSwapInterval(1);

    // Setup callbacks (Input, Resize, etc.)
    setGLFWCallbacks();

    cout << "Window created: " << cfg.width << "x" << cfg.height << endl;
}

void Window::setGLFWCallbacks() {
    // We can set up mouse/keyboard/resize callbacks here later
    // Example: glfwSetFramebufferSizeCallback(m_window, onResize);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void Window::close() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}