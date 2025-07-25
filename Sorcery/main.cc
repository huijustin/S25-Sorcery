#include "GameEngine.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    bool testing = false;
    bool graphics = false;
    std::string initFile = "";
    std::string deck1File = "";
    std::string deck2File = "";

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-init" && i + 1 < argc) {
            initFile = argv[++i];
        }
        else if (arg == "-deck1" && i + 1 < argc) {
            deck1File = argv[++i];
        }
        else if (arg == "-deck2" && i + 1 < argc) {
            deck2File = argv[++i];
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

    GameEngine engine{testing, graphics, initFile, deck1File, deck2File};
    engine.run();
    return 0;
}
