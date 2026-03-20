#include "Pipeline.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>

void Pipeline::loadCSV(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filepath << "\n";
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 10) continue;

        try {
            SoilData entry(
                tokens[0], tokens[1],
                std::stod(tokens[2]), std::stod(tokens[3]),
                std::stod(tokens[4]), std::stod(tokens[5]),
                std::stod(tokens[6]), std::stod(tokens[7]),
                std::stod(tokens[8]), tokens[9]
            );
            dataset.push_back(entry);
        } catch (...) {
            continue;
        }
    }
    std::cout << "Loaded " << dataset.size() << " records.\n";
}

std::vector<SoilData> Pipeline::filterByRegion(const std::string& region) const {
    std::vector<SoilData> result;
    std::copy_if(dataset.begin(), dataset.end(), std::back_inserter(result),
        [&region](const SoilData& d) { return d.region == region; });
    return result;
}

std::vector<SoilData> Pipeline::filterBySeason(const std::string& season) const {
    std::vector<SoilData> result;
    std::copy_if(dataset.begin(), dataset.end(), std::back_inserter(result),
        [&season](const SoilData& d) { return d.season == season; });
    return result;
}

std::vector<SoilData> Pipeline::filterByMoistureRange(double minM, double maxM) const {
    std::vector<SoilData> result;
    std::copy_if(dataset.begin(), dataset.end(), std::back_inserter(result),
        [minM, maxM](const SoilData& d) {
            return d.moisture >= minM && d.moisture <= maxM;
        });
    return result;
}

std::vector<SoilData> Pipeline::filterCombined(const std::string& region, const std::string& season) const {
    std::set<int> regionIndices, seasonIndices;
    for (int i = 0; i < (int)dataset.size(); i++) {
        if (dataset[i].region == region) regionIndices.insert(i);
        if (dataset[i].season == season) seasonIndices.insert(i);
    }

    std::vector<int> combined;
    std::set_intersection(regionIndices.begin(), regionIndices.end(),
                          seasonIndices.begin(), seasonIndices.end(),
                          std::back_inserter(combined));

    std::vector<SoilData> result;
    for (int idx : combined) result.push_back(dataset[idx]);
    return result;
}

void Pipeline::printSummary(const std::vector<SoilData>& data) const {
    if (data.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    std::cout << "\n=== Summary (" << data.size() << " records) ===\n";
    for (const auto& d : data) {
        std::cout << d.getAdvisory() << "\n";
    }
}
