#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "AirNowRecord.h"

// Function to remove leading and trailing quotation marks from a string
std::string removeQuotes(const std::string& str) {
    if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
        return str.substr(1, str.size() - 2);
    } else {
        return str;
    }
}

std::string getAqiCategory(int category) {
    switch (category) {
        case 1:
            return "Good";
        case 2:
            return "Moderate";
        case 3:
            return "Unhealthy for Sensitive Groups";
        case 4:
            return "Unhealthy";
        case 5:
            return "Very Unhealthy";
        case 6:
            return "Hazardous";
        default:
            return "Unknown";
    }
}


int main() {
    // Open the input file for reading
    std::ifstream inputFile;
    inputFile.open("/Users/keerthanaparsa/CLionProjects/Trial/Data/20200912-01.csv");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1; // Indicate error
    }

    std::vector<AirNowRecord> airNowData;
    std::string line;
    while (std::getline(inputFile, line)) {
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

        std::stringstream inputString(line);

        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing latitude." << std::endl;
            continue;
        }
        try {
            latitude = std::stod(removeQuotes(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid latitude value: " << line << std::endl;
            continue;
        }

        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing longitude." << std::endl;
            continue;
        }
        try {
            longitude = std::stod(removeQuotes(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid longitude value: " << line << std::endl;
            continue;
        }

        if (!std::getline(inputString, timestamp, ',')) {
            std::cerr << "Error parsing timestamp." << std::endl;
            continue;
        }
        if (!std::getline(inputString, parameter, ',')) {
            std::cerr << "Error parsing parameter." << std::endl;
            continue;
        }
        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing concentration." << std::endl;
            continue;
        }
        try {
            concentration = std::stod(removeQuotes(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid concentration value: " << line << std::endl;
            continue;
        }
        if (!std::getline(inputString, unit, ',')) {
            std::cerr << "Error parsing unit." << std::endl;
            continue;
        }
        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing raw concentration." << std::endl;
            continue;
        }
        try {
            rawConcentration = std::stod(removeQuotes(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid raw concentration value: " << line << std::endl;
            continue;
        }
        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing AQI." << std::endl;
            continue;
        }
        try {
            aqi = std::stoi(removeQuotes(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid AQI value: " << line << std::endl;
            continue;
        }
        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing category." << std::endl;
            continue;
        }
        try {
            category = std::stoi(removeQuotes(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid category value: " << line << std::endl;
            continue;
        }
        if (!std::getline(inputString, siteName, ',')) {
            std::cerr << "Error parsing site name." << std::endl;
            continue;
        }
        if (!std::getline(inputString, agency, ',')) {
            std::cerr << "Error parsing agency." << std::endl;
            continue;
        }
        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing AQS ID." << std::endl;
            continue;
        }
        if (!std::getline(inputString, line, ',')) {
            std::cerr << "Error parsing full AQS ID." << std::endl;
            continue;
        }

        // Create AirNowRecord object and add to vector
        airNowData.emplace_back(latitude, longitude, timestamp, parameter,
                                concentration, unit, rawConcentration, aqi,
                                category, siteName, agency);
    }

    // Display all records
    for (const auto& record : airNowData) {
        record.display();
        std::cout << std::endl;
    }

    inputFile.close();
    // Display insights for each record
    std::cout << "INSIGHTS:"<< std::endl;
    for (const auto& record : airNowData) {
        std::cout << "Site Name: " << record.siteName << std::endl;
        std::cout << "Pollutant Parameter: " << record.parameter << std::endl;
        std::cout << "AQI: " << record.aqi << std::endl;
        std::cout << "AQI Category: " << getAqiCategory(record.category) << std::endl;
        std::cout << "Longitude: " << record.longitude << std::endl;
        std::cout << "Latitude: " << record.latitude << std::endl;
        std::cout << "Timestamp: " << record.timestamp << std::endl;
        std::cout << "Concentration: " << record.concentration << " " << record.unit << std::endl;

        // Additional insights and analysis
        if (record.aqi >= 100) {
            std::cout << "Warning: Poor air quality detected at this location." << std::endl;
        }

        // You can add more analysis and insights here...

        std::cout << std::endl;
    }
    std::cout << "Parsing complete." << std::endl;
    return 0;
}
