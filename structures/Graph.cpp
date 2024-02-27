

#include <vector>
#include "Graph.h"
#include "fstream"
#include "iostream"
#include "iomanip"
using namespace std;
Graph::Graph(int v){
    vertices = v;
    edges = new int * [vertices];
    for(int i = 0; i < vertices; ++i) edges[i] = new int[vertices];

    for(int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            edges[i][j] = INT_MAX;
        }
    }
}

Graph::~Graph() {
    if(vertices > 0) {
        for (int i = 0; i < vertices; i++) {
            delete[] edges[i];
            edges[i] = nullptr;
        }
        delete[] edges;
        edges = nullptr;
    }
}


void Graph::changeSize(int size) {
    if(vertices > 0) {
        for (int i = 0; i < vertices; i++) {
            delete[] edges[i];
            edges[i] = nullptr;
        }
        delete[] edges;
        edges = nullptr;
    }
    vertices = size;
    edges = new int * [vertices];
    for(int i = 0; i < vertices; ++i) edges[i] = new int[vertices];

    for(int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            edges[i][j] = INT_MAX;
        }
    }
}

void Graph::readGraphDirected(const std::string &s) {
    string name = R"(..\input\)" + s;
    ifstream file(name);


    if(file.is_open()) {
        string line;
        vector<int> lineData;


        for(int i =0; i < 4; i++){
            getline(file,line);
        }
        string numerToString;
        for(char c : line){
            if(isdigit(c))
                numerToString += c;
        }

        int dimension;
        dimension = stoi(numerToString);


        if(dimension != vertices)
            changeSize(dimension);
        cout << "dimension = " << dimension << endl;
        cout << "vertices = " << vertices << endl;

        int i = 0;
        while(getline(file,line)) {
            stringstream lineStream(line);
            int value;
            while(lineStream >> value) {
                lineData.push_back(value);
                if(lineData.size() == vertices) {
                    copy(lineData.begin(), lineData.end(), edges[i]);
                    i++;
                    lineData.clear();
                }
            }
        }
        cout << "Read completed from " <<  s  << "\n\n";

        file.close();
    } else
        cout << "There was a problem with opening your file\n\n";



}
void Graph::display() const{

    const int fieldWidth = 4;
    std::cout << "Graph as matrix" << std::endl;

    std::cout << std::setw(fieldWidth) << " " << " | ";
    for (int j = 0; j < vertices; j++) {
        std::cout << std::setw(fieldWidth) << j << " ";
    }
    std::cout << std::endl;

    std::cout << std::setfill('-') << std::setw(fieldWidth + 1) << "" << "+" << std::setw((fieldWidth + 1) * vertices) << "" << std::setfill(' ') << std::endl;

    for (int i = 0; i < vertices; i++) {
        std::cout << std::setw(fieldWidth) << i << " | ";
        for (int j = 0; j < vertices; j++) {
            if(edges[i][j] == INT_MAX )
                std::cout << std::setw(fieldWidth) << "-" << " ";
            else
                std::cout << std::setw(fieldWidth) << edges[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

