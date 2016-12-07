#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Graph.h"
using namespace std;


int Graph::containsNode(string node){
    return graph.count(node);
}

string Graph::getStartNode() {
    std::srand ( unsigned ( std::time(0) ) );
    vector<string> words;
    for(outer_map::iterator it = graph.begin(); it != graph.end(); ++it){
         words.push_back(it->first);
    }
    random_shuffle(words.begin(), words.end());
    return words[0];
}

void Graph::addNode(string node) {
    map<string, int> inner;
    if (!containsNode(node)) {
        graph[node] = inner;
    }
}

int Graph::getTotalEdgeWeight(string node) {
    int result = 0;
    if (Graph::containsNode(node)) {
        outer_map::iterator it_out = graph.find(node);
        for (inner_map::iterator it=it_out->second.begin(); it!=it_out->second.end(); ++it) {
            result += it->second;
        }
    }
    
    return result;
}

void Graph::addEdge(string node, string edge) {
    if (Graph::containsNode(node)) {
        outer_map::iterator it_out = graph.find(node);
        inner_map::iterator it = it_out->second.find(edge);
        if (it!=it_out->second.end()) {
            it->second++;
        } else {
            it_out->second[edge] = 1;
        }
    }            
}

string Graph::getNext(string node){
    if(Graph::containsNode(node)){
        map<string, int> currentEdges = graph[node];
        float frequency = Graph::getTotalEdgeWeight(node);
        if(frequency != 0){
            int currSum = 0;
            double percent = ((double)rand()/(double)RAND_MAX);
            for(inner_map::iterator it = currentEdges.begin(); it != currentEdges.end(); ++it){
                currSum += it->second;
                if(currSum/frequency > percent){
                    return it->first;
                }
            }
        }
        else{
            return Graph::getStartNode();
        }
    }
    else{
        return "ERROR";
    }

}

