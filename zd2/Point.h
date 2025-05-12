#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    int x, y;

    Point();
    Point(int x_val, int y_val);

    bool operator==(const Point& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif
