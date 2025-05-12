#ifndef POLYGONMANAGER_H
#define POLYGONMANAGER_H

#include "Polygon.h"
#include <vector>
#include <string>

class PolygonManager {
private:
    std::vector<Polygon> polygons;
    Point parsePoint(const std::string& str);
    Polygon parseLine(const std::string& line);

public:
    bool loadFromFile(const std::string& filename);
    int echo(const Polygon& target);
    bool inFrame(const Polygon& query);
    void processCommands();
};

#endif
