//Savannah Nester
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"
using namespace std;

void createGraph(string graph_){
   ifstream data;
    data.open(graph_.c_str());
    if(data.fail()){
        cout << "Error opening file." << endl;
    }
    string line;
    Graph graph;

    getline(data, line);
    while(getline(data, line)){
        stringstream ss(line);
        int vertex, adjacencyVertex;
        double weight;
        ss >> vertex;
        graph.addVertex(vertex);
        while(ss >> adjacencyVertex >> weight){
            graph.addVertex(adjacencyVertex);
            graph.addEdge(vertex, adjacencyVertex, weight);
        }
    }
    data.close();
    graph.topoSort();
}

int main(int argc, char** argv){
    if(argc != 2){
        cout << "Error with topological sort algorithm!\n";
        return 1;
    }
    string graph_(argv[1]);
    createGraph(graph_);
    return 0;

}