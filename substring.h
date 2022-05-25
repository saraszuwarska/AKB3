#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <iostream>
#include <string>

class Substring
{
public:
    int position;
    std::string name;
    std::string sequenceID;
    Substring()
    {
    }
    Substring(std::string name, int position, std::string sequenceID)
    {
        this->name = name;
        this->position = position;
        this->sequenceID = sequenceID;
    }
};

#endif