#include "PolygonManager.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Kullanım: " << argv[0] << " <dosya_adi>" << std::endl;
        return EXIT_FAILURE;
    }

    PolygonManager manager;

    if (!manager.loadFromFile(argv[1])) {
        return EXIT_FAILURE;
    }

    manager.processCommands();
    return 0;
}
