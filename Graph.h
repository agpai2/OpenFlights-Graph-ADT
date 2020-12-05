#pragma once

#include "Airport.h"
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

        /** 
         * Displays the elements of the adjacency matrix
         * 
         * @param v - the dimension of adjacency matrix
         */
        void displayMatrix(int v);

        /**
         * Does a Breadth-First Traversal of the graph.
         * 
         * @param start the index of the node to start the traversal from
         */
        void BFS(int start);

        /** 
         * Returns the number of vertices (Airports) of graph
         */
        int getNumVertices();

        /** 
         * Returns the adjacency matrix
         */
        vector<vector<double>> getAdjacencyMatrix();

        /** 
         * Finds the vertex with minimum distance value from the 
         * set of vertices not yet included in shortest path tree 
         */
        void djikstra(std::string src);
        
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

        /**
         * A helper function for A-star algorithm
         * 
         * Computes the manhattan distance between two points.
         * A manhattan distance is the number of steps it would take to travel between the two points
         * using only up, down, left, and right movements (no diagonals)
         *
         * @param source - one vertex (Airport) the edge is connected to
         * @param second - the other vertex (Airport) the edge is connected to
         * 
         * @return The manhattan distance between the two points
         */
        double manhattanDistance(Airport source, Airport destination);

        /** 
         * A helper function for A-star algorithm
         * 
         * Computes the chebyshev distance between two points
         * The Chebyshev distance measures distance between two points as the 
         * maximum difference over any of their axis values.
         * 
         * @param source - one vertex (Airport) the edge is connected to
         * @param second - the other vertex (Airport) the edge is connected to
         * 
         * @return The chebyshev distance between the two points
         */
        double chebyshevDistance(Airport source, Airport destination);

        /** 
         * A helper function for djikstra's algorithm
         * 
         * Calculates the minimum distance value from the set of vertices 
         * not yet included in shortest path tree
         * 
         * @param dist - a vector that holds the shortest distance from source airport to ith airport 
         * @param reached - a vector that contains bool values based on if the shortest distance
         * from source airport to ith airport is finalized
         */
        int minDist(std::vector<int>& dist, std::vector<bool>  &reached);

        /** 
         * A helper function for djikstra's algorithm
         * 
         * Prints the shortest path from the source vertex to all other 
         * vertices, where vertices are the airports
         */
        void printShortestPath(std::vector<int> &parent, int j);

        /** 
         * A helper function for djikstra's algorithm
         * 
         * Prints the constructed distance array 
         * 
         * @param dist - a vector that holds the shortest distance from source airport to ith airport 
         * @param parent - 
         * @param src - the id of the source airport
         */
        int printSolution(std::vector<int> dist, std::vector<int> parent, int src) ;

        /** 
         * Computes the number of incident edges from a given vertex,
         * where vertex is an airport and edges are destinations in this case
         * 
         * @param airportIndex - the index of the airport in the adjacency matrix
         * 
         * @return the number of or incident edges from a given vertex
         */
        int getIncidentEdges(int airportIndex);

        vector<vector<double>> adjMatrix;

        std::map<std::string, Airport> airportCodeMap;
};