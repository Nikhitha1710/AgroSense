#pragma once
#include "SoilData.h"
#include <vector>
#include <string>

struct Candlestick {
    std::string label;
    double open;
    double close;
    double high;
    double low;
};

class CandlestickAnalyzer {
public:
    std::vector<Candlestick> computeSeasonalMoisture(const std::vector<SoilData>& data);
    void displayChart(const std::vector<Candlestick>& candles) const;
};
