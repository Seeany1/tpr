#include "Point.h"

Point::Point() : x(0), y(0) {}

Point::Point(int x_val, int y_val) : x(x_val), y(y_val) {}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ";" << p.y << ")";
    return os;
}
