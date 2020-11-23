#include "Airport.h"

Airport::Airport() {
  id_ = 0;
  name_ = "";
  city_ = "";
  country_ = "";
  latitude_ = 0.0;
  longitude_ = 0.0;
  timezone_ = 0.0;
} 

Airport::Airport(int id, string name, string city, string country,
          double lat, double longtitude, double tmz) {
  
  id_ = id;
  name_ = name;
  city_ = city;
  country_ = country;
  latitude_ = lat;
  longitude_ = longtitude;
  timezone_ = tmz;
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