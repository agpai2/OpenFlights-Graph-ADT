#include "Airport.h"

Airport::Airport() {
  id_ = 134;
  name_ = "";
  city_ = "";
  country_ = "";
  latitude_ = 0.0;
  longitude_ = 0.0;
  timezone_ = 0.0;
} 

// Airport::Airport(int id, string name, string city, string country,
//           double lat, double longtitude, double tmz) {
  
//   id_ = id;
//   name_ = name;
//   city_ = city;
//   country_ = country;
//   latitude_ = lat;
//   longitude_ = longtitude;
//   timezone_ = tmz;
// }

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


string Airport::getName() {
  return name_;
}