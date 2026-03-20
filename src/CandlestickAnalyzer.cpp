#include "CandlestickAnalyzer.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>

std::vector<Candlestick> CandlestickAnalyzer::computeSeasonalMoisture(const std::vector<SoilData>& data) {
    std::map<std::string, std::vector<double>> seasonMoisture;

    for (const auto& d : data) {
        seasonMoisture[d.season].push_back(d.moisture);
    }

    std::vector<Candlestick> candles;
    for (auto& [season, values] : seasonMoisture) {
        if (values.empty()) continue;
        std::sort(values.begin(), values.end());

        Candlestick c;
        c.label = season;
        c.low   = values.front();
        c.high  = values.back();
        c.open  = values[values.size() / 4];
        c.close = values[values.size() * 3 / 4];
        candles.push_back(c);
    }
    return candles;
}

void CandlestickAnalyzer::displayChart(const std::vector<Candlestick>& candles) const {
    std::cout << "\n=== Seasonal Soil Moisture Candlestick Chart ===\n";
    std::cout << std::setw(12) << "Season"
              << std::setw(8) << "Open"
              << std::setw(8) << "Close"
              << std::setw(8) << "High"
              << std::setw(8) << "Low"
              << "  Visual\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& c : candles) {
        bool bullish = c.close >= c.open;
        std::string indicator = bullish ? "[G]" : "[R]";

        std::cout << std::setw(12) << c.label
                  << std::setw(8) << std::fixed << std::setprecision(1) << c.open
                  << std::setw(8) << c.close
                  << std::setw(8) << c.high
                  << std::setw(8) << c.low
                  << "  " << indicator;

        int bodySize = static_cast<int>(std::abs(c.close - c.open) / 2);
        for (int i = 0; i < bodySize; i++) std::cout << (bullish ? "+" : "-");
        std::cout << "\n";
    }
}
