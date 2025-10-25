# NovaEngine

NovaEngine is a lightweight C++ game engine built from scratch, focusing on a modern Entity Component System (ECS) architecture and tooling.

*(Work in Progress - Current Milestone: Basic Rendering)*


*(You can add a screenshot here later!)*

## Current Features (MVP In Progress)

* **Core Engine:** Basic game loop, window creation (GLFW), and OpenGL context initialization (GLAD).
* **Entity Component System (ECS):**
    * Coordinator facade managing entities, components, and systems.
    * `EntityManager` for creating/destroying entities.
    * `ComponentManager` using packed arrays (`ComponentArray<T>`) for efficient data storage.
    * `SystemManager` for registering systems and managing entity signatures.
* **Rendering:**
    * Basic `RenderSystem` capable of drawing colored quads.
    * Shader loading and management class (`Shader`).
    * Simple vertex and fragment shaders (GLSL 330 core).
    * Orthographic projection setup.
* **Build System:** Configured with CMake, supporting Windows (Visual Studio).
* **Dependencies:** Uses GLFW, GLAD, GLM, nlohmann/json, sol2, ImGui (integrated via CMake).

## Getting Started

*(Instructions for building and running will be added here once the demo is more stable.)*

### Prerequisites

* C++ Compiler (MSVC via Visual Studio 2022 recommended)
* CMake (3.16+)
* Git

### Build Steps (Example - Windows with VS 2022)

1.  Clone the repository:
    ```bash
    git clone [https://github.com/rahul-240505/NovaEngine.git](https://github.com/rahul-240505/NovaEngine.git)
    cd NovaEngine
    ```
2.  Initialize submodules:
    ```bash
    git submodule update --init --recursive
    ```
3.  Generate build files using CMake (from Developer Command Prompt):
    ```bash
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022"
    ```
4.  Build the solution (either via Visual Studio IDE or command line):
    ```bash
    cmake --build . --config Debug
    ```
5.  Run the demo:
    ```bash
    ./bin/Debug/NovaEngineDemo.exe
    ```

## Next Steps (MVP Goals)

* Texture Loading & Rendering
* Input Handling
* Scene Loading from JSON
* Basic Physics & Asset Management
* Dear ImGui Editor Integration