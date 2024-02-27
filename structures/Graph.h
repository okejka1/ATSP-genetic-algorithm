//
// Created by User on 13.10.2023.
//

#ifndef PEA_GRAPH_H
#define PEA_GRAPH_H


#include <string>

class Graph {
private:
public:
    /*
     * two dimensional array to store adjacency matrix of graph
     */
    int **edges;
    int vertices;
    explicit Graph(int v);
    void readGraphDirected(const std::string& s);
    void changeSize(int size);
    void display() const;

    virtual ~Graph();

};



#endif //PEA_GRAPH_H
