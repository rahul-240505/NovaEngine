#include "Engine.h"
#include "EngineConfig.h"
#include <iostream>

void setupDemo();

Engine g_engine;

int main(int argc, char* argv[]) {
    std::cout << "Starting main()..." << std::endl;
    
    EngineConfig cfg;
    cfg.windowTitle = "NovaEngine Demo";
    
    g_engine.init(cfg);

    setupDemo();

    g_engine.run();
    g_engine.shutdown();
    
    std::cout << "Exiting main()." << std::endl;
    return 0;
}