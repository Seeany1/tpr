#include "Point.h"
#include <functional>
#include <ostream>

Point::Point() : x(0), y(0) {}

Point::Point(int x_val, int y_val) : x(x_val), y(y_val) {}

bool Point::operator==(const Point& other) const {
    return std::equal_to<int>()(x, other.x) && std::equal_to<int>()(y, other.y);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << ";" << p.y << ")";
}
