#pragma once
#include "Airport.h"
#include "Route.h"
#include <map>
class Graph {
    public:
    
        Graph();

        Graph(std::map<int, std::vector<std::string>> airportMap, std::map<int, std::vector<std::string>> routeMap);
        /**
         * Inserts an edge between two vertices (Airports).
         * 
         * @param source - one vertex (Airport) the edge is connected to
         * @param destination - the other vertex (Airport) the edge is connected to
         */
        void addEdge(Airport source, Airport destination);

        /**
         * Checks if the vertices (Airports) are adjacent.
         * 
         * @param source - one vertex (Airport) the edge is connected to
         * @param destination - the other vertex (Airport) the edge is connected to
         * 
         * @return if airports are adjacent
         */
        bool areAdjacent(Airport source, Airport destination);

        void displayMatrix(int v);

        /**
         * Does a Breadth-First Traversal of the graph.
         * 
         * @param start the index of the node to start the traversal from
         */
        void BFS(int start);
        
    private:
        /**
         * Calculates the distance between two airports using its latitudes and longitudes.
         * 
         * @param source - one vertex (Airport) the edge is connected to
         * @param destination - the other vertex (Airport) the edge is connected to
         * 
         * @return the distance between two airports in kilometers
         */
        double euclideanDistance(Airport source, Airport destination);

        vector<vector<double>> adjMatrix;

};
