#pragma once
#include "Airport.h"

class Graph {
    public:
        void addEdge(Airport source, Airport destination);
        
        double euclideanDistance(Airport source, Airport destination);

        
        
    private:

        vector<vector<double>> adjMatrix;
        bool isAdjacent(Airport source, Airport destination);


        // insert(chenObj, Madradobj) {
        // adjMatrix[chenn][madrad] = 1;
        // }

            
};
