#include <iostream>
#include <fstream>
#include "Pipeline.h"
#include "CandlestickAnalyzer.h"

void exportJSON(const std::vector<SoilData>& data, const std::vector<Candlestick>& candles) {
    std::ofstream json("web/output.json");
    if (!json.is_open()) {
        std::cerr << "Error: Cannot write output.json\n";
        return;
    }

    json << "{\n";

    // Records
    json << "  \"records\": [\n";
    for (int i = 0; i < (int)data.size(); i++) {
        const auto& d = data[i];
        json << "    {\n";
        json << "      \"region\": \"" << d.region << "\",\n";
        json << "      \"season\": \"" << d.season << "\",\n";
        json << "      \"nitrogen\": " << d.nitrogen << ",\n";
        json << "      \"phosphorus\": " << d.phosphorus << ",\n";
        json << "      \"potassium\": " << d.potassium << ",\n";
        json << "      \"pH\": " << d.pH << ",\n";
        json << "      \"moisture\": " << d.moisture << ",\n";
        json << "      \"temperature\": " << d.temperature << ",\n";
        json << "      \"rainfall\": " << d.rainfall << ",\n";
        json << "      \"crop\": \"" << d.crop << "\",\n";
        json << "      \"moistureStatus\": \"" << d.getMoistureStatus() << "\",\n";
        json << "      \"npkStatus\": \"" << d.getNPKStatus() << "\"\n";
        json << "    }" << (i < (int)data.size() - 1 ? "," : "") << "\n";
    }
    json << "  ],\n";

    // Candlesticks
    json << "  \"candlesticks\": [\n";
    for (int i = 0; i < (int)candles.size(); i++) {
        const auto& c = candles[i];
        json << "    {\n";
        json << "      \"season\": \"" << c.label << "\",\n";
        json << "      \"open\": " << c.open << ",\n";
        json << "      \"close\": " << c.close << ",\n";
        json << "      \"high\": " << c.high << ",\n";
        json << "      \"low\": " << c.low << "\n";
        json << "    }" << (i < (int)candles.size() - 1 ? "," : "") << "\n";
    }
    json << "  ]\n";
    json << "}\n";

    json.close();
    std::cout << "Data exported to web/output.json\n";
}

int main() {
    std::cout << "=========================================\n";
    std::cout << "   AgroSense - Soil Data Analysis System \n";
    std::cout << "=========================================\n\n";

    Pipeline pipeline;
    pipeline.loadCSV("data/crop_data.csv");

    std::cout << "\n--- Filter: Andhra Pradesh, Kharif Season ---\n";
    auto filtered = pipeline.filterCombined("Andhra Pradesh", "Kharif");
    pipeline.printSummary(filtered);

    std::cout << "\n--- Filter: Optimal Moisture Range (50-70%) ---\n";
    auto optimal = pipeline.filterByMoistureRange(50.0, 70.0);
    std::cout << "Records with optimal moisture: " << optimal.size() << "\n";

    std::cout << "\n--- Seasonal Moisture Candlestick Analysis ---\n";
    CandlestickAnalyzer analyzer;
    auto allData = pipeline.filterByRegion("Andhra Pradesh");
    auto candles = analyzer.computeSeasonalMoisture(allData);
    analyzer.displayChart(candles);

    // Export all data to JSON for web dashboard
    auto allRecords = pipeline.filterByMoistureRange(0, 100);
    exportJSON(allRecords, candles);

    std::cout << "\n=========================================\n";
    std::cout << "Analysis complete. Open web/index.html\n";
    std::cout << "to view the interactive dashboard.\n";
    std::cout << "=========================================\n";

    return 0;
}
