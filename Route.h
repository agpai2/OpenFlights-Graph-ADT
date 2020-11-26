/**
 * @file Route.h
 * Contains our declaration of the interface for the Route class.
 */
#pragma once
#include <string.h>
#include "readFromFile.hpp"
using namespace std;

class Route {
    private:

        // 2-letter (IATA) or 3-letter (ICAO) code of the airline
        std::string airlineCode_;

        // Unique OpenFlights identifier for airline
        int airlineId_;

        // 3-letter (IATA) or 4-letter (ICAO) code of the source airport
        std::string sourceCode_;

        // Unique OpenFlights identifier for source airport
        int sourceId_;

        // 3-letter (IATA) or 4-letter (ICAO) code of the destination airport
        std::string destinationCode_;

        // Unique OpenFlights identifier for destination airport
        int destinationId_;

        // Number of stops on this flight ("0" for direct)
        int stops_;

    public:
        Route(std::string airlineCode, int airlineId, std::string source, int sourseId,
                std::string destination, int destinationId, int stops);
};