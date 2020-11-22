/**
 * @file Aiport.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <string.h>
#include "readFromFile.hpp"

using namespace std;

class Airport {
  public:
    // Constructs a default Airport
    Airport();

    // Constructs an airport with below params
    Airport(int id, string name, string city, string country, 
    double lat, double longtitude, double tmz);

  private:
    // Unique OpenFlights identifier for this airport
    int id_;

    // Name of airport
    string name_;

    // Main city served by airport
    string city_;

    // Country or territory where airport is located
    string country_;

    // Decimal degrees, usually to six significant digits. 
    // Negative is South, positive is North
    double latitude_;

    // Decimal degrees, usually to six significant digits. 
    // Negative is West, positive is East
    double longitude_;

    // Hours offset from UTC. 
    // Fractional hours are expressed as decimals, eg. India is 5.5
    double timezone_;
};