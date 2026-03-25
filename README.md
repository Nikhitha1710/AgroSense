# AgroSense — Soil Data Analysis & Crop Advisory System

A multi-layer agricultural data system that processes Indian soil and crop data through a C++ pipeline, applies machine learning for crop prediction, and visualises results through an interactive web dashboard.

---

## Overview_

AgroSense takes raw soil sensor readings — nitrogen, phosphorus, potassium, pH, moisture, temperature, and rainfall — and processes them through three layers:

1. **C++ Data Pipeline** — loads CSV data, filters by region and season using `set_intersection`, computes seasonal soil moisture candlestick patterns, and generates crop advisories
2. **Python ML Engine** — trains a Random Forest classifier on the Indian Crop Recommendation Dataset to predict the most suitable crop for given soil conditions
3. **Web Dashboard** — interactive HTML/CSS/JavaScript interface displaying live soil metrics, NPK levels, seasonal moisture patterns, and crop recommendations for 5 Indian states

---

## Project Structure

```
AgroSense/
├── src/
│   ├── main.cpp                  Entry point
│   ├── SoilData.h / .cpp         Soil data class with advisory logic
│   ├── Pipeline.h / .cpp         CSV loader, multi-filter analysis
│   └── CandlestickAnalyzer.h / .cpp   Seasonal moisture pattern visualisation
├── python/
│   └── predict.py                Random Forest crop prediction engine
├── data/
│   └── crop_data.csv             Indian soil and crop dataset
└── web/
    └── index.html                Interactive dashboard
```

---

## Dataset

**Indian Crop Recommendation Dataset**
Source: Created my own dataset for testing purposes

Features: N, P, K (soil nutrients), pH, temperature, humidity, rainfall, crop label
Records: 2,200 samples across multiple Indian agricultural regions

---

## How to Run

### C++ Pipeline

```bash
g++ -std=c++17 src/main.cpp src/SoilData.cpp src/Pipeline.cpp src/CandlestickAnalyzer.cpp -o agrosense
./agrosense
```

### Python ML Engine

```bash
pip install pandas numpy scikit-learn
python python/predict.py
```

### Web Dashboard

Open `web/index.html` in any browser. No server required.

---

## Features

- Multi-filter analysis using `set_intersection` (filter by region AND season simultaneously)
- Seasonal soil moisture candlestick chart (Open/High/Low/Close pattern per season)
- NPK deficiency detection with specific advisory output
- Random Forest classifier with top-3 crop probability ranking
- Interactive dashboard with region selector for Andhra Pradesh, Maharashtra, Punjab, Karnataka, Tamil Nadu
- Colour-coded advisory system (green / amber / red) based on soil condition thresholds

---

## Sample Output

```
=========================================
   AgroSense - Soil Data Analysis System
=========================================

Loaded 20 records.

--- Filter: Andhra Pradesh, Kharif Season ---
[REGION: Andhra Pradesh | SEASON: Kharif]
Moisture : OPTIMAL - No irrigation needed
Nutrients: N:56 P:52 K:32 | WARNING: Potassium deficiency
pH       : 6.8 (Optimal range)
Temp     : 26 C
Rainfall : 85 mm
Suggested crop: red chilli

=== Seasonal Soil Moisture Candlestick Chart ===
      Season    Open   Close    High     Low  Visual
------------------------------------------------------------
      Kharif    55.0    68.0    90.0    48.0  [G]++++++
        Rabi    48.0    62.0    75.0    35.0  [G]+++++++
```

---

## Technologies Used

- C++17 — data pipeline, OOP design, STL algorithms
- Python 3 — scikit-learn, pandas, NumPy
- HTML / CSS / JavaScript — interactive frontend dashboard
- Dataset — Kaggle (Indian Crop Recommendation Dataset)

---

## Author

Cheparthi Sri Nikhitha
BSc Computer Science — University of London
[LinkedIn](https://www.linkedin.com/in/cheparthi-sri-nikhitha-886b381b1)
