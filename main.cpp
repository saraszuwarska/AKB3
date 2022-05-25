#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "nucleotide.h"
#include "sequence.h"
#include "substring.h"
#include "graph.h"

std::string fasta = "inst1FASTA.txt";
std::string quality = "inst1QUAL.txt";

std::vector<Sequence> readFastaFile(std::string filename)
{
    std::vector<Sequence> sequences;
    std::string line;
    std::ifstream ist(filename);
    std::string name;
    std::string sequence;
    if (!ist)
        std::cout << "Podany plik nie istnieje!\n"
                  << std::endl;
    else
    {
        while (getline(ist, line))
        {
            std::istringstream ss(line);

            if (line[0] == '>')
            {
                ss >> name;
                name = name.substr(1, name.length() - 1);
            }
            else
            {
                ss >> sequence;
                sequences.push_back(Sequence(name, sequence));
            }
        }
    }
    for (int i = 0; i < sequences.size(); i++)
    {
        sequences[i].readNucleotides();
    }
    return sequences;
}

void readQualFile(std::string filename, std::vector<Sequence> &sequences)
{
    std::string line;
    std::ifstream ist(filename);

    std::vector<int> qualities;
    int index = 0;
    if (!ist)
        std::cout << "Podany plik nie istnieje!\n"
                  << std::endl;
    else
    {
        while (getline(ist, line))
        {
            std::istringstream ss(line);

            if (line[0] == '>')
            {
                continue;
            }
            else
            {
                qualities = std::vector<int>(std::istream_iterator<int>(ss), std::istream_iterator<int>());
                sequences[index].assignQualities(qualities);
                index++;
            }
        }
    }
}
int readBaseline()
{
    int baseline;
    std::string input = "";
    std::cout << "Podaj prog jakosciowy: " << std::endl;
    while (true)
    {
        getline(std::cin, input);
        std::stringstream myStream(input);
        if (myStream >> baseline)
            break;
        std::cout << "Wartosc niepoprawna. Sprobuj ponownie." << std::endl;
    }
    return baseline;
}

int readLength()
{
    int k;
    std::string input = "";
    std::cout << "Wskaz długość podciągow: " << std::endl;
    while (true)
    {
        getline(std::cin, input);
        std::stringstream myStream(input);
        if (myStream >> k)
            break;
        std::cout << "Wartosc niepoprawna. Sprobuj ponownie." << std::endl;
    }
    return k;
}
int main()
{
    std::vector<Sequence> sequences = readFastaFile(fasta);
    readQualFile(quality, sequences);
    int baseline = readBaseline();
    int k = readLength();
    for (int i = 0; i < sequences.size(); i++)
    {
        //std::cout << i << std::endl;
        sequences[i].filterSequence(baseline);
        sequences[i].createSubstrings(k);
        //sequences[i].printSubstrings();
    }
    Graph newGraph(sequences, k);
    //newGraph.printGraph();
    std::cout << std::endl;
    std::cout << "B-K algorithm found:" << std::endl;
    std::cout << std::endl;
    newGraph.runBronKerbosch();
    std::cout << "---------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Clique search algorithm found:" << std::endl;
    newGraph.searchGraph();
}