#include "Polygon.h"
#include <algorithm>
#include <iterator>
#include <numeric>

Polygon::Polygon() {}

void Polygon::addPoint(const Point& p) {
    vertices.push_back(p);
}

int Polygon::getVertexCount() const {
    return static_cast<int>(vertices.size());
}

const std::vector<Point>& Polygon::getPoints() const {
    return vertices;
}

bool Polygon::operator==(const Polygon& other) const {
    return vertices.size() == other.vertices.size() &&
        std::equal(vertices.begin(), vertices.end(), other.vertices.begin());
}

std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
    os << poly.getVertexCount() << " ";
    std::for_each(poly.vertices.begin(), poly.vertices.end(),
        [&os](const Point& p) { os << p << " "; });
    return os;
}
