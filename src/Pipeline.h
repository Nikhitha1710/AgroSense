#pragma once
#include "SoilData.h"
#include <vector>
#include <string>

class Pipeline {
private:
    std::vector<SoilData> dataset;

public:
    void loadCSV(const std::string& filepath);
    std::vector<SoilData> filterByRegion(const std::string& region) const;
    std::vector<SoilData> filterBySeason(const std::string& season) const;
    std::vector<SoilData> filterByMoistureRange(double minMoisture, double maxMoisture) const;
    std::vector<SoilData> filterCombined(const std::string& region, const std::string& season) const;
    void printSummary(const std::vector<SoilData>& data) const;
    int getSize() const { return dataset.size(); }
};
