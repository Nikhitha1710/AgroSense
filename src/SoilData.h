#pragma once
#include <string>

class SoilData {
public:
    std::string region;
    std::string season;
    double nitrogen;
    double phosphorus;
    double potassium;
    double pH;
    double moisture;
    double temperature;
    double rainfall;
    std::string crop;

    SoilData(std::string region, std::string season,
             double n, double p, double k,
             double pH, double moisture,
             double temp, double rain,
             std::string crop);

    std::string getAdvisory() const;
    std::string getMoistureStatus() const;
    std::string getNPKStatus() const;
};
