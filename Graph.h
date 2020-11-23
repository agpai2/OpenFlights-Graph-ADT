#pragma once
#include "Airport.h"

class Graph {
    public:
    
        Graph();
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
