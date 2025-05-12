#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include <vector>
#include <iostream>

class Polygon {
private:
    std::vector<Point> vertices;

public:
    Polygon();

    void addPoint(const Point& p);
    int getVertexCount() const;
    const std::vector<Point>& getPoints() const;

    bool operator==(const Polygon& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly);
};

#endif
