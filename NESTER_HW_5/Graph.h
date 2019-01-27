//Savannah Nester
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <cfloat>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

class Graph{
public:
    Graph(){}
    bool checkAdjacent(int vertex1, int vertex2){
        if(_vertices.find(vertex2) == _vertices.end() || _vertices.find(vertex1) == _vertices.end()){
            return false;
        }
        if(_vertices[vertex1]._neighbors.find(vertex2) != _vertices[vertex1]._neighbors.end()){
            return true;
        }
        return false;
    }
    bool containsVertex(int val){
        if(_vertices.find(val) == _vertices.end()){
            return false;
        }
        else{
             return true;
        }
    }
    bool addVertex(int val){
        if(containsVertex(val)){
            return false;
        }
        else {
            _vertices.insert(pair<int, Vertex>(val, Vertex(val)));
            return true;
        }
    }
    void addEdge(int vertex, int neighbor, double weight){
        addVertex(neighbor);
        addVertex(vertex);
        _vertices[vertex]._neighbors[neighbor] = weight;
        _vertices[neighbor]._index++;
    }
    double graphWeight(int vertex1, int vertex2){
        return _vertices[vertex1]._neighbors[vertex2];
    }
    void dijkstra(int start){
        if(_vertices.empty()){
            cout << "Graph empty.\n";
            return;
        }
        if(_vertices.find(start) == _vertices.end()){
            cout << "Starting vertex not found.\n";
            return;
        }
        set<int> sort;
        computePaths(start);
        for(auto v : _vertices){
            sort.insert(v.first);
        }
        for(auto v : sort){
            cout << v << ": ";
            print(&_vertices[v]);
            if(_vertices[v].distance < DBL_MAX){
                cout << " (Cost: " << _vertices[v].distance << ")\n\n";
            }
            else {
                cout << "Cannot be reached\n\n";
            }
        }
    }
        void topoSort(){
            if(_vertices.empty()){
                cout << "Graph empty\n";
                return;
            }
            stringstream output;
            map<int, int> indegree;
            queue<Vertex*> queue;
            unsigned int n = 0;
            for(auto& vert : _vertices){
                indegree.emplace(vert.first, vert.second._index);
                if(vert.second._index == 0)
                    queue.push(&_vertices[vert.first]);
            }
            while(!queue.empty()){
                Vertex* vertexx = queue.front();
                queue.pop();
                vertexx->topnum = ++n;
                output << vertexx->_id;
                if(!vertexx->_neighbors.empty()){
                    output << ", ";
                }
                for(auto& w : vertexx->_neighbors){
                    if(--indegree[w.first] == 0){
                        queue.push(&_vertices[w.first]);
                    }
                }
            }
            if(n != _vertices.size()){
                cout << "Cycle found" << endl;
                return;
            }
            else {
                cout << output.str() << endl;
            }
        }
private:
    struct Vertex {
        int _id;
        double distance = DBL_MAX;
        bool isKnown = false;
        Vertex* path = nullptr;
        int _index = 0;
        int topnum = 0;
        unordered_map<int, double> _neighbors;

        Vertex(int vertexValue=-1){
            _id = vertexValue;
        }
        bool operator==(const Vertex& rhs) const {
            return _id == rhs._id;
        }
    };

    unordered_map<int, Vertex> _vertices;

    class ComputeDistance {
    public:
        bool operator()(Vertex* vertex1, Vertex* vertex2){
            bool r = vertex1->distance > vertex2->distance;
            return r;
        }
    };
    void print(Vertex* vertex, int n = 0){
        if(vertex->path == nullptr){
            cout << vertex->_id;
            if(!(n == 0)){
                cout << ", ";
            }
        }
        else {
            print(vertex->path, ++n);
            if(!(n == 1)){
               cout << vertex->_id << ", ";
            }
            else {
                cout << vertex->_id;
            }
        }
    }
    void reset(){
        for(auto& ver : _vertices){
            ver.second.path = nullptr;
            ver.second.isKnown = false;
            ver.second.distance = DBL_MAX;
        }
    }
    void computePaths(int start){
        reset();
        priority_queue<Vertex*, vector<Vertex*>, ComputeDistance> queue;
        _vertices[start].distance = 0;
        queue.push(&_vertices[start]);
        for(; ;){
            bool check = false;
            while(!check && !queue.empty()){
                if(!(queue.top()->isKnown)){
                    check = true;
                }
                else {
                    queue.pop();
                }
            }
            if(!check){
                break;
            }
            Vertex* current = queue.top();
            queue.pop();
            current->isKnown = true;
            for(auto neighbor : current->_neighbors){
                int numb = neighbor.first;
                double dis = neighbor.second + current->distance;
                if(dis < _vertices[numb].distance){
                    _vertices[numb].distance = dis;
                    _vertices[numb].path = current;
                    queue.push(&_vertices[numb]);
                }
            }
        }
    }
};

#endif