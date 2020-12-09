#pragma once

#include "Airport.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <vector>
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
         * Returns the number of vertices (Airports) of graph
         */
        int getNumVertices();

        /** 
         * Computes the number of destinations that can be reached from a given airport.
         * 
         * @param startAirport - the matrix index of the source airport in the adjacency matrix
         * 
         * @return the number of destinations corresponding to startAirport
         */
        int getNumberOfDestinations(int startAirport);

        /** 
         * Returns the airport code map
         */
        std::map<std::string, Airport> getAirportCodeMap();

        /** 
         * Returns the adjacency matrix
         */
        vector<vector<double>> getAdjacencyMatrix();

        /** 
         * Displays the elements of the adjacency matrix
         * 
         * @param v - the number of columns/rows to display. For instance, if v = 5, 
         * it will print a 5*5 square matrix starting
         * from the top left of the adjacency matrix
         */
        void displayMatrix(int v);

        /**
         * Does a Breadth-First Traversal of the graph.
         * 
         * @param start- the index of the node to start the traversal from
         */
        void BFS(std::string startNode);

        /** 
         * Finds the shortest path between vertices in a graph, where 
         * the vertices are airports in this case
         *
         * @param src - the 3-letter IATA code of the source vertex
         * @param dest - the 3-letter IATA code of the destination vertex
         *
         * @return the shortest path between vertices in a graph
         */
        std::vector<int> dijkstra(std::string startNode, std::string endNode);

        /** 
         * Finds the shortest path between two vertices in a graph through an 
         * intermediary vertex, where the vertices are airports in this case
         *
         * @param startNode - the 3-letter IATA code of the starting vertex/node
         * @param intermediateNode - the 3-letter IATA code of intermediary vertex/node
         * @param endNode - the 3-letter IATA code of ending vertex/node
         *
         * @return the shortest path between two vertices in a graph through an 
         * intermediary vertex
         */
        std::vector<int> landmarkPath(std::string startNode, std::string intermediateNode, 
            std::string endNode);

        /** 
         * Plots all of the airports from the dataset onto the world map
         */
        void plotAirports();

        /** 
         * Plots all of the airports from the dataset onto the world map
         * as well as the route contained in the path vector
         * 
         * @param path - the path from one airport to another through an
         * intermediary airport
         */
        void plotLandmarkPath(std::vector<string> path);

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
         * A helper function for djikstra's algorithm
         * 
         * Calculates the minimum distance value from the set of vertices 
         * not yet included in shortest path tree
         * 
         * @param dist - a vector that holds the shortest distance from source airport to ith airport 
         * @param reached - a vector that contains bool values based on if the shortest distance
         * from source airport to ith airport is finalized
         * 
         * @return The minimum distance value from the set of vertices 
         * not yet included in shortest path tree
         */
        int minDist(std::vector<int>& dist, std::vector<bool>  &reached);

        /** 
         * Computes the XY coordinates of an airport
         * 
         * @param lat - the latitude of the airport
         * @param longt - the longitude of the airport
         * @param image - the image onto which the airports are to be plotted upon
         * 
         * @return the XY coordinates of an airport
         */
        std::pair<double, double> getXYCoordinates(double lat, double longt, cs225::PNG image);

        // adjacency matrix representing the graph
        std::vector<std::vector<double>> adjMatrix;

        // maps IATA codes to corresponding airport objects
        std::map<std::string, Airport> airportCodeMap;
};