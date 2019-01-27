//Savannah Nester
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"
using namespace std;

void createGraph(string graph_, string adjacencyQueries){
    ifstream data;
    data.open(graph_.c_str());
    if(data.fail()){
        cout << "Error opening file 1." << endl;
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
    ifstream data2;
    data2.open(adjacencyQueries.c_str());
    if (data2.fail()){
        cout << "Error opening file 2"<<endl;
      }
    string aquery;
    while (getline(data2, aquery)) {
        stringstream query(aquery);
        int vertex1;
        int vertex2;
        query >> vertex1 >> vertex2;
        if (graph.checkAdjacent(vertex1,vertex2)){
          double weight = graph.graphWeight(vertex1, vertex2);
          cout << vertex1 <<" "<< vertex2 << ": Connected, weight of edge is "<< weight << endl;
        }
        else
          cout << vertex1 <<" "<< vertex2 << ": Not connected\n";
      }
  data2.close();
}

int main(int argc, char** argv){
    if(argc != 3){
        cout << "Create and Test Graph: " << argv[0] << " needs graph file and adjacency query file. " << endl;
        return 0;
    }
    const string graph_(argv[1]);
    const string adjacencyQueries(argv[2]);
    Graph graph;
    createGraph(graph_, adjacencyQueries);

    return 0;
}