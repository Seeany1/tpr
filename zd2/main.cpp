#include "PolygonManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    PolygonManager manager;

    if (!manager.loadFromFile(argv[1])) {
        return 1;
    }

    manager.processCommands();
    return 0;
}
