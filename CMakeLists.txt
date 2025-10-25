# --- Project Definition ---
cmake_minimum_required(VERSION 3.16)
project(NovaEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set a consistent output directory for binaries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# --- Find Required System Packages ---
find_package(OpenGL REQUIRED)

# ===================================================================
# === 1. DEFINE ALL EXTERNAL LIBRARIES
# ===================================================================

# --- GLM (Header-only) ---
add_subdirectory(extern/glm)

# --- nlohmann_json (Header-only) ---
add_subdirectory(extern/nlohmann_json)

# --- sol2 (Header-only) ---
add_subdirectory(extern/sol2)

# --- stb (Header-only) ---
# We just add its location to the include path for targets that need it.
# We'll add it to NovaEngine later.

# --- GLFW (Compiled) ---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(extern/glfw)

# --- Dear ImGui (Compiled) ---
add_library(imgui STATIC
    extern/imgui/imgui.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_widgets.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
)
# imgui needs its own headers, GLFW headers, and OpenGL
target_include_directories(imgui PUBLIC
    extern/imgui
    extern/imgui/backends
    extern/glfw/include
)
target_link_libraries(imgui PRIVATE ${OpenGL_LIBRARIES})

# --- GLAD (Compiled) ---
# We build the C source file as a static library
add_library(glad STATIC
    extern/glad/src/glad.c
)
# The glad library needs its own headers (which are in extern/glad/include)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/include
)

# ===================================================================
# === 2. DEFINE THE ENGINE LIBRARY
# ===================================================================

add_library(NovaEngine
    src/core/Engine.cpp
    src/ecs/EntityManager.cpp
    src/ecs/ComponentManager.cpp
    src/ecs/SystemManager.cpp
    src/renderer/Window.cpp
    src/systems/RenderSystem.cpp
    src/renderer/Shader.cpp
)

# --- Configure NovaEngine Includes ---
target_include_directories(NovaEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include # Public API
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src     # Internal implementation
        extern/stb                         # For loading images
        ${OpenGL_INCLUDE_DIR}              # For OpenGL functions
)

# --- Configure NovaEngine Links ---
target_link_libraries(NovaEngine
    PUBLIC
        # Header-only libs (propagates their include paths)
        glm::glm
        nlohmann_json::nlohmann_json
        sol2::sol2
    PRIVATE
        # Compiled libs
        glfw
        imgui
        glad                
        ${OpenGL_LIBRARIES}
)

# ===================================================================
# === 3. DEFINE THE DEMO EXECUTABLE
# ===================================================================

add_executable(NovaEngineDemo
    src/core/main.cpp
    src/demo/demo_game.cpp
)

# The demo just needs to link against the engine
target_link_libraries(NovaEngineDemo
    PRIVATE
        NovaEngine
)