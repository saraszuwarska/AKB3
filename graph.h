#ifndef GRAPH_H
#define GRAPH_H
#include "sequence.h"

#include <iostream>
#include <string>
#include <vector>

class Graph
{
public:
    std::vector<Substring> vertices;
    std::vector<std::vector<int> > adjList;
    int k;
    std::vector<std::vector<int> > solutions;
    std::vector<std::vector<int> > simple_solutions;

    Graph(std::vector<Sequence> sequences, int k)
    {
        this->k = k;
        for (int i = 0; i < sequences.size(); i++)
        {
            for (int j = 0; j < sequences[i].substrings.size(); j++)
            {
                this->vertices.push_back(sequences[i].substrings[j]);
            }
        }
        populateAdjList();
    }

    void populateAdjList()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            std::vector<int> temporaryVec;
            for (int j = 0; j < vertices.size(); j++)
            {

                if ((vertices[i].sequenceID != vertices[j].sequenceID) && (vertices[i].name == vertices[j].name) && (abs(vertices[i].position - vertices[j].position) <= 10 * k))
                {
                    temporaryVec.push_back(j);
                }
            }
            adjList.push_back(temporaryVec);
        }
    }

    int abs(int number)
    {
        if (number > 0)
        {
            return number;
        }
        else
            return number * (-1);
    }

    void printGraph()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            std::cout << "V: " << i << vertices[i].name << std::endl;
        }
        for (int i = 0; i < adjList.size(); i++)
        {
            std::cout << "L: " << i << " ";
            for (int j = 0; j < adjList[i].size(); j++)
            {
                std::cout << adjList[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void printVector(std::vector<int> vector)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
    }

    bool contains(int element, std::vector<int> A)
    {
        for (int i = 0; i < A.size(); i++)
        {
            if (A[i] == element)
            {
                return true;
            }
        }
        return false;
    }

    std::vector<int> intersection(std::vector<int> A, std::vector<int> B)
    {
        std::vector<int> resultVector;
        for (int i = 0; i < A.size(); i++)
        {
            if (contains(A[i], B))
            {
                resultVector.push_back(A[i]);
            }
        }
        return resultVector;
    }

    std::vector<int> deleteElement(std::vector<int> A, int element)
    {
        std::vector<int> modifiedVector;
        for (int i = 0; i < A.size(); i++)
        {
            if (A[i] != element)
            {
                modifiedVector.push_back(A[i]);
            }
        }
        return modifiedVector;
    }
    void BronKerbosch(std::vector<int> R, std::vector<int> P, std::vector<int> X, std::vector<std::vector<int> > &solutions)
    {
        if ((P.size() == 0) && (X.size() == 0))
        {
            solutions.push_back(R);
        }
        else
        {
            std::vector<int> tempP = P;
            for (int i = 0; i < tempP.size(); i++)
            {
                std::vector<int> N = adjList[tempP[i]];
                std::vector<int> R1 = R;
                R1.push_back(tempP[i]);
                std::vector<int> P1 = intersection(P, N);
                std::vector<int> X1 = intersection(X, N);
                BronKerbosch(R1, P1, X1, solutions);
                P = deleteElement(P, tempP[i]);
                X.push_back(tempP[i]);
            }
        }
    }

    void runBronKerbosch()
    {
        std::vector<int> R;
        std::vector<int> P;
        for (int i = 0; i < vertices.size(); i++)
        {
            P.push_back(i);
        }
        std::vector<int> X;

        BronKerbosch(R, P, X, this->solutions);
        readMaxClique(this->solutions);
    }

    bool compare_vectors(std::vector<int> vector_1, std::vector<int> vector_2)
    {
        if (vector_1.size() != vector_2.size())
        {
            return false;
        }
        for (int i = 0; i < vector_1.size(); i++)
        {
            if (!contains(vector_1[i], vector_2))
            {
                return false;
            }
        }

        return true;
    }

    std::vector<int> add_element(int element, std::vector<int> vector)
    {
        vector.push_back(element);
        return vector;
    }
    bool check_neigbours(std::vector<int> clique, std::vector<int> neighbours)
    {
        for (int i = 0; i < neighbours.size(); i++)
        {
            std::vector<int> local = deleteElement(clique, neighbours[i]);
            if (!compare_vectors(local, this->adjList[neighbours[i]]))
            {
                return false;
            }
        }
        return true;
    }

    void mark_checked(std::vector<bool> &already_checked, std::vector<int> elements)
    {
        for (int i = 0; i < elements.size(); i++)
        {
            already_checked[elements[i]] = true;
        }
    }
    void searchGraph()
    {
        std::vector<bool> already_checked;
        for (int i = 0; i < adjList.size(); i++)
        {
            already_checked.push_back(false);
        }

        for (int i = 0; i < this->adjList.size(); i++)
        {
            if ((this->adjList[i].size() != 0) && (!already_checked[i]))
            {
                std::vector<int> clique_members = add_element(i, this->adjList[i]);
                if (check_neigbours(clique_members, this->adjList[i]))
                {
                    simple_solutions.push_back(clique_members);
                    mark_checked(already_checked, clique_members);
                }
            }
        }
        readMaxClique(this->simple_solutions);
    }
    void readMaxClique(std::vector<std::vector<int> > solutions)
    {
        int maxsize = 0;
        for (int i = 0; i < solutions.size(); i++)
        {
            if (maxsize < solutions[i].size())
            {
                maxsize = solutions[i].size();
            }
        }
        std::cout << "MAX SIZE " << maxsize << std::endl;
        for (int i = 0; i < solutions.size(); i++)
        {

            if (solutions[i].size() == maxsize)
            {
                std::cout << "Klika #" << i << std::endl;
                printResult(solutions[i]);
            }
        }
    }

    void printResult(std::vector<int> solution)
    {
        for (int i = 0; i < solution.size(); i++)
        {
            std::cout << solution[i] << ": " << vertices[solution[i]].sequenceID << ", " << vertices[solution[i]].name << ", " << vertices[solution[i]].position << std::endl;
        }
    }
};

#endif