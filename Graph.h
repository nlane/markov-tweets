#ifndef _Graph_H // must be unique name in the project
#define _Graph_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

class Graph {
    public:
        typedef std::map<std::string, int> inner_map;
        typedef std::map<std::string, inner_map> outer_map;
        std::string getStartNode();
        int containsNode(std::string node);
        void addNode(std::string node);
        int getTotalEdgeWeight(std::string node);
        void addEdge(std::string node, std::string edge);
        std::string getNext(std::string node);
    private:
        std::map<std::string, std::map<std::string, int> > graph;
};

#endif 