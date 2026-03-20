#include "SoilData.h"
#include <sstream>

SoilData::SoilData(std::string region, std::string season,
                   double n, double p, double k,
                   double pH, double moisture,
                   double temp, double rain,
                   std::string crop)
    : region(region), season(season),
      nitrogen(n), phosphorus(p), potassium(k),
      pH(pH), moisture(moisture),
      temperature(temp), rainfall(rain),
      crop(crop) {}

std::string SoilData::getMoistureStatus() const {
    if (moisture > 70) return "HIGH - Monitor waterlogging risk";
    if (moisture >= 50) return "OPTIMAL - No irrigation needed";
    if (moisture >= 30) return "LOW - Irrigation recommended";
    return "CRITICAL - Immediate irrigation required";
}

std::string SoilData::getNPKStatus() const {
    std::ostringstream oss;
    oss << "N:" << nitrogen << " P:" << phosphorus << " K:" << potassium;
    if (potassium < 30) oss << " | WARNING: Potassium deficiency";
    if (nitrogen < 20)  oss << " | WARNING: Nitrogen deficiency";
    return oss.str();
}

std::string SoilData::getAdvisory() const {
    std::ostringstream oss;
    oss << "[REGION: " << region << " | SEASON: " << season << "]\n";
    oss << "Moisture : " << getMoistureStatus() << "\n";
    oss << "Nutrients: " << getNPKStatus() << "\n";
    oss << "pH       : " << pH;
    if (pH < 6.0) oss << " (Acidic - consider liming)";
    else if (pH > 7.5) oss << " (Alkaline - consider acidifying)";
    else oss << " (Optimal range)";
    oss << "\nTemp     : " << temperature << " C";
    oss << "\nRainfall : " << rainfall << " mm";
    oss << "\nSuggested crop: " << crop << "\n";
    return oss.str();
}
