/**
 * @file Aiport.h
 * Contains our declaration of the interface for the Airport class.
 */
#pragma once

#include <string>

using namespace std;

class Airport {
  public:
    // Constructs a default Airport
    Airport();

    // Constructs an airport with below params
    Airport(int id, string name, string city, string iataCode, 
    string icaoCode, double lat, double longitude);

    // Gets the id of the airport
    int getId();

    // Gets the latitude 
    double getLatitude();
    
    // Gets the longitude
    double getLongitude();

    string getName();

    string getIATA();

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

    // 3-letter IATA code of the airport
    std::string iataCode_;

    // 4-letter ICAO code of the airport
    std::string icaoCode_;
};