#include "core/Engine.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Starting main()..." << std::endl;
    
    Engine engine;
    EngineConfig cfg;
    cfg.windowTitle = "NovaEngine Demo (Smoke Test)";
    
    engine.init(cfg);
    engine.run();
    engine.shutdown();
    
    std::cout << "Exiting main()." << std::endl;
    return 0;
}