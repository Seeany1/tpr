#define _CRT_SECURE_NO_WARNINGS
#include "PolygonManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include <functional>
#include <numeric>
#include <algorithm>

Point PolygonManager::parsePoint(const std::string& str) {
    int x, y;
    if (sscanf(str.c_str(), "(%d;%d)", &x, &y) != 2) {
        throw std::runtime_error("Invalid point format");
    }
    return Point(x, y);
}

Polygon PolygonManager::parseLine(const std::string& line) {
    std::istringstream iss(line);
    int vertex_count;
    Polygon poly;

    if (!(iss >> vertex_count) || vertex_count < 3) return poly;

    std::vector<std::string> point_strs;
    std::string point_str;
    std::copy(std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        std::back_inserter(point_strs));

    if (point_strs.size() != vertex_count) return poly;

    try {
        std::for_each(point_strs.begin(), point_strs.end(), [this, &poly](const std::string& str) {
            poly.addPoint(parsePoint(str));
            });

    }
    catch (...) {
        return Polygon();
    }

    return poly;
}

bool PolygonManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        Polygon poly = parseLine(line);
        if (poly.getVertexCount() > 0) {
            polygons.push_back(poly);
        }
    }

    return true;
}

struct EchoInserter {
    const Polygon& target;
    int count;
    std::vector<Polygon>& result;

    EchoInserter(const Polygon& t, std::vector<Polygon>& r) : target(t), count(0), result(r) {}

    void operator()(const Polygon& poly) {
        result.push_back(poly);
        if (poly == target) {
            result.push_back(poly);
            ++count;
        }
    }
};

int PolygonManager::echo(const Polygon& target) {
    std::vector<Polygon> result;
    EchoInserter inserter(target, result);
    std::for_each(polygons.begin(), polygons.end(), std::ref(inserter));
    polygons = result;
    return inserter.count;
}

struct PointBounds {
    int min_x, max_x, min_y, max_y;

    PointBounds(const std::vector<Point>& all_points) {
        min_x = max_x = all_points[0].x;
        min_y = max_y = all_points[0].y;

        for (const auto& p : all_points) {
            if (p.x < min_x) min_x = p.x;
            if (p.x > max_x) max_x = p.x;
            if (p.y < min_y) min_y = p.y;
            if (p.y > max_y) max_y = p.y;
        }
    }

    bool contains(const Point& p) const {
        return (p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y);
    }
};

bool PolygonManager::inFrame(const Polygon& query) {
    if (polygons.empty()) return false;

    std::vector<Point> all_points;
    for (const auto& poly : polygons) {
        const auto& pts = poly.getPoints();
        all_points.insert(all_points.end(), pts.begin(), pts.end());
    }

    PointBounds bounds(all_points);

    return std::all_of(query.getPoints().begin(), query.getPoints().end(),
        [&bounds](const Point& p) { return bounds.contains(p); });
}

void PolygonManager::processCommands() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.substr(0, 5) == "ECHO ") {
            Polygon target = parseLine(line.substr(5));
            if (target.getVertexCount() > 0) {
                int count = echo(target);
                std::cout << count << std::endl;
            }
            else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        else if (line.substr(0, 8) == "INFRAME ") {
            Polygon query = parseLine(line.substr(8));
            if (query.getVertexCount() > 0) {
                bool result = inFrame(query);
                std::cout << (result ? "<TRUE>" : "<FALSE>") << std::endl;
            }
            else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
}

