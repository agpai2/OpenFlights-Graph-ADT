#include "Airport.h"

using namespace std;

Airport::Airport() {
  id_ = 0;
  name_ = "";
  city_ = "";
  country_ = "";
  latitude_ = 0.0;
  longitude_ = 0.0;
  timezone_ = 0.0;
} 


Airport::Airport(int id, string name, string city, string iataCode, string icaoCode,
          double lat, double longitude) {
  id_ = id;
  name_ = name;
  city_ = city;
  iataCode_ = iataCode;
  icaoCode_ = icaoCode;
  latitude_ = lat;
  longitude_ = longitude;
}

int Airport::getId() {
  return id_;
}

double Airport::getLatitude() {
  return latitude_; 
}

double Airport::getLongitude() {
  return longitude_; 
}