#include <cstdlib>
#include <cstdint>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include <string>
#include <sstream>

#include "DataStruct.h"

int main() {
    using DataStructs = std::vector<dataStruct>;
    DataStructs dataStructs{};

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        dataStruct ds;
        iss >> ds;

        if (!ds.invalid && iss) {
            dataStructs.push_back(ds);
        }
    }

    std::sort(dataStructs.begin(), dataStructs.end(), [](const dataStruct& a, const dataStruct& b) {
        if (a.key1 < b.key1) return true;
        if (a.key1 > b.key1) return false;
        if (a.key2 < b.key2) return true;
        if (a.key2 > b.key2) return false;
        return a.key3.length() < b.key3.length();
        });

    dataStructs.erase(
        std::unique(dataStructs.begin(), dataStructs.end(), [](const dataStruct& a, const dataStruct& b) {
            return a.key1 == b.key1 && a.key2 == b.key2 && a.key3 == b.key3;
            }),
        dataStructs.end()
    );

    std::copy(
        dataStructs.begin(), dataStructs.end(),
        std::ostream_iterator<dataStruct>{std::cout, "\n"}
    );

    return 0;
}
