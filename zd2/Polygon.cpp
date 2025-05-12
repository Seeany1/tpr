#include "Polygon.h"
#include <algorithm>

Polygon::Polygon() {}

void Polygon::addPoint(const Point& p) {
    vertices.push_back(p);
}

int Polygon::getVertexCount() const {
    return vertices.size();
}

const std::vector<Point>& Polygon::getPoints() const {
    return vertices;
}

bool Polygon::operator==(const Polygon& other) const {
    if (vertices.size() != other.vertices.size()) return false;
    return std::equal(vertices.begin(), vertices.end(), other.vertices.begin());
}

std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
    os << poly.vertices.size() << " ";
    for (const auto& p : poly.vertices) {
        os << p << " ";
    }
    return os;
}
