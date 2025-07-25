#include "GameEngine.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    bool testing = false;
    bool graphics = false;
    std::string initFile = "";

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-init" && i + 1 < argc) {
            initFile = argv[++i];
        }
        else if (arg == "-testing") {
            testing = true;
        }
        else if (arg == "-graphics") {
            graphics = true;
        }
        else {
            std::cerr << "Unkown argument: " << arg << std::endl;
        }
    }

    GameEngine engine{testing, graphics, initFile};
    engine.run();
    return 0;
}
