#ifndef NUCLEOTIDE_H
#define NUCLEOTIDE_H

#include <iostream>
#include <string>

class Nucleotide
{
public:
    char name;
    int position;
    int quality;
    Nucleotide()
    {
    }
    Nucleotide(char name, int position)
    {
        this->name = name;
        this->position = position;
    }
};

#endif