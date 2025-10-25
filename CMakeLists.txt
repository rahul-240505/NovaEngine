# --- Project Definition ---
cmake_minimum_required(VERSION 3.16)
project(NovaEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setting a consistent output directory for binaries (e.g., /bin/Debug/NovaEngineDemo.exe)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# --- Dependencies (from extern/) ---
# We tell CMake to build our submodules and what to include from them.

# GLM (Header-only)
add_subdirectory(extern/glm)
# We just need its include directory
include_directories(extern/glm)

# nlohmann_json (Header-only)
add_subdirectory(extern/nlohmann_json)
# We just need its include directory
include_directories(extern/nlohmann_json/include)

# sol2 (Header-only)
add_subdirectory(extern/sol2)
# We just need its include directory
include_directories(extern/sol2/include)

# stb (Header-only, just headers)
# We just add its location to the include path.
include_directories(extern/stb)

# GLFW (Needs to be built)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(extern/glfw)


# Dear ImGui (Needs to be built)
add_library(imgui
    # Add the core imgui source files
    extern/imgui/imgui.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_widgets.cpp
    # Add the backend implementation files
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
 "src/ecs/ComponentManager.cpp")
# The imgui lib needs to include its own headers and GLFW headers
target_include_directories(imgui
    PUBLIC
        extern/imgui
        extern/imgui/backends
    PRIVATE
        extern/glfw/include
)
# The imgui lib needs to link to OpenGL
target_link_libraries(imgui
    PRIVATE
        ${OpenGL_LIBRARIES}
)

# GoogleTest (Needs to be built, optional)
# We'll set this up later if/when we write unit tests
# add_subdirectory(extern/googletest)

# --- Find Required Packages ---
# Find OpenGL (which is platform-specific)
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})

# --- Engine Library Target ---
# Defines the core "NovaEngine" library (e.g., NovaEngine.lib)
add_library(NovaEngine
    # We will list all our engine's .cpp files here
    src/core/Engine.cpp
    src/ecs/EntityManager.cpp
 "src/ecs/ComponentManager.cpp")

# Tell the Engine target where to find its own headers
target_include_directories(NovaEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include # Public headers (for the Demo)
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src     # Private headers (for implementation)
)

# Link all dependencies to the Engine library
target_link_libraries(NovaEngine
    PUBLIC
        # GLM, JSON, and Sol2 are header-only and just need to be "linked"
        # so their include paths are passed on.
        glm::glm
        nlohmann_json::nlohmann_json
        sol2::sol2
    PRIVATE
        # These are compiled libraries the engine uses internally
        glfw
        imgui
        ${OpenGL_LIBRARIES}
)

# --- Demo Executable Target ---
# Defines the "NovaEngineDemo.exe" that runs the game
add_executable(NovaEngineDemo
    src/core/main.cpp
    src/demo/demo_game.cpp
 "src/ecs/ComponentManager.cpp")

# The Demo needs to include the engine's public headers
target_include_directories(NovaEngineDemo
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src # For main.cpp
)

# The Demo LINKS against the Engine library
target_link_libraries(NovaEngineDemo
    PRIVATE
        NovaEngine
)