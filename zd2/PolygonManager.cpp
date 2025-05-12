#define _CRT_SECURE_NO_WARNINGS
#include "PolygonManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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
    while (iss >> point_str) {
        point_strs.push_back(point_str);
    }

    if (point_strs.size() != vertex_count) return poly;

    try {
        for (const auto& str : point_strs) {
            poly.addPoint(parsePoint(str));
        }
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

int PolygonManager::echo(const Polygon& target) {
    int count = 0;
    std::vector<Polygon> result;

    for (const auto& poly : polygons) {
        result.push_back(poly);
        if (poly == target) {
            result.push_back(poly);
            count++;
        }
    }

    polygons = result;
    return count;
}

bool PolygonManager::inFrame(const Polygon& query) {
    if (polygons.empty()) return false;

    std::vector<Point> all_points;
    for (const auto& poly : polygons) {
        const auto& points = poly.getPoints();
        all_points.insert(all_points.end(), points.begin(), points.end());
    }

    int min_x = all_points[0].x, max_x = all_points[0].x;
    int min_y = all_points[0].y, max_y = all_points[0].y;

    for (const auto& p : all_points) {
        if (p.x < min_x) min_x = p.x;
        if (p.y < min_y) min_y = p.y;
        if (p.x > max_x) max_x = p.x;
        if (p.y > max_y) max_y = p.y;
    }

    for (const auto& p : query.getPoints()) {
        if (p.x < min_x || p.x > max_x || p.y < min_y || p.y > max_y) {
            return false;
        }
    }

    return true;
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
