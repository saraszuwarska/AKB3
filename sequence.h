#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "nucleotide.h"
#include "substring.h"

#include <iostream>
#include <string>
#include <vector>

class Sequence
{
public:
    std::string name;
    std::string sequence;
    std::vector<Nucleotide> nucleotides;
    std::vector<Substring> substrings;

    Sequence()
    {
    }
    Sequence(std::string name, std::string sequence)
    {
        this->name = name;
        this->sequence = sequence;
    }
    void readNucleotides()
    {
        for (int i = 0; i < sequence.length(); i++)
        {
            nucleotides.push_back(Nucleotide(sequence[i], i + 1));
        }
    }
    void assignQualities(std::vector<int> qualities)
    {
        for (int i = 0; i < qualities.size(); i++)
        {
            this->nucleotides[i].quality = qualities[i];
        }
    }
    void printNucleotides()
    {
        for (int i = 0; i < this->nucleotides.size(); i++)
        {
            std::cout << this->nucleotides[i].name << ", " << this->nucleotides[i].position << ", " << this->nucleotides[i].quality << std::endl;
        }
    }
    void filterSequence(int baseline)
    {
        std::vector<Nucleotide> validnt;
        for (int i = 0; i < nucleotides.size(); i++)
        {
            if (nucleotides[i].quality >= baseline)
            {
                validnt.push_back(Nucleotide(nucleotides[i]));
            }
        }
        nucleotides = validnt;
    }

    void createSubstrings(int k)
    {

        std::string temporaryName;

        for (int i = 0; i <= nucleotides.size() - k; i++)
        {
            temporaryName = "";
            for (int j = i; j < i + k; j++)
            {
                temporaryName += nucleotides[j].name;
            }
            substrings.push_back(Substring(temporaryName, nucleotides[i].position, this->name));
        }
    }

    void printSubstrings()
    {
        for (int i = 0; i < substrings.size(); i++)
        {
            std::cout << substrings[i].sequenceID << ", " << substrings[i].name << ", " << substrings[i].position << std::endl;
        }
    }
};

#endif