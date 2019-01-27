//Savannah Nester
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"
using namespace std;

void createGraph(string graph_, string vertex){
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
    graph.dijkstra(stoi(vertex));
}

int main(int argc, char** argv){
    if(argc != 3){
        cout << "Find Paths " << argv[0] << " needs graph file and starting vertex " << endl;
        return 0;
    }
    const string graph_(argv[1]);
    const string vertex(argv[2]);

    createGraph(graph_, vertex);
    return 0;
}