#ifndef PARSER_H
#define PARSER_H

#include "dataStruct.h"
#include <string>

class Parser {
public:
    static DataStruct parseLine(const std::string& line);
};

#endif
