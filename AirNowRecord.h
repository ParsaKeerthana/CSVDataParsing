#ifndef AIRNOWRECORD_H
#define AIRNOWRECORD_H

#include <iostream>
#include <string>
#include <iomanip>

// Struct to represent an air quality record
struct AirNowRecord {
    double latitude;
    double longitude;
    std::string timestamp;
    std::string parameter;
    double concentration;
    std::string unit;
    double rawConcentration;
    int aqi;
    int category;
    std::string siteName;
    std::string agency;
    double aqsId;

    // Constructor
    AirNowRecord(double lat, double lon, const std::string& ts, const std::string& param,
                 double conc, const std::string& u, double rawConc, int aqiVal,
                 int cat, const std::string& name, const std::string& ag)
            : latitude(lat), longitude(lon), timestamp(ts), parameter(param),
              concentration(conc), unit(u), rawConcentration(rawConc),
              aqi(aqiVal), category(cat), siteName(name), agency(ag){}

    // Function to display the record
    void display() const {
        std::cout << "Latitude: " << std::setprecision(15) << latitude << std::endl;
        std::cout << "Longitude: " << std::setprecision(15) << longitude << std::endl;
        std::cout << "Timestamp: " << timestamp << std::endl;
        std::cout << "Parameter: " << parameter << std::endl;
        std::cout << "Concentration: " << concentration << std::endl;
        std::cout << "Unit: " << unit << std::endl;
        std::cout << "Raw Concentration: " << rawConcentration << std::endl;
        std::cout << "AQI: " << aqi << std::endl;
        std::cout << "Category: " << category << std::endl;
        std::cout << "Site Name: " << siteName << std::endl;
        std::cout << "Agency: " << agency << std::endl;
    }
};

#endif // AIRNOWRECORD_H
