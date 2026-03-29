# AgroSense — Soil Data Analysis & Crop Advisory System 🌾

A multi-layer agricultural data system that processes Indian soil and crop data through a C++ pipeline, applies machine learning for crop prediction, and visualises results through an interactive web dashboard.

# Goal 🎯

The goal of this project is to explore how data processing and machine learning can be combined to support agricultural decision-making.

---

## System Overview 🧩

AgroSense processes soil and environmental features such as nitrogen (N), phosphorus (P), potassium (K), pH level, moisture, temperature, and rainfall as input parameters for analysis and prediction.

The system is designed as a three-layer pipeline architecture, where each layer handles a specific stage of data processing, machine learning, and visualization.

### System Architecture 🏗️ 
**1. C++ Data Processing Layer**
- Loads and parses structured soil dataset (CSV format)
- Performs region and season-based filtering using STL algorithms
- Generates statistical summaries of soil conditions
- Computes seasonal moisture patterns for analysis

**2. Python Machine Learning Layer**
- Implements a Random Forest classifier using scikit-learn
- Trains on soil nutrient and environmental parameters
- Predicts suitable crop based on input conditions
- Outputs probability-based crop recommendations

**3. Web Visualization Layer**
- Built using HTML, CSS, and JavaScript
- Displays soil parameters and model predictions
- Provides an interactive region-based analysis dashboard
- Visualizes seasonal trends and nutrient levels

## How the System Works ⚙️
1. Soil data is loaded and processed in C++
2. Cleaned data is passed to ML model for training/prediction
3. Predictions are displayed through a web-based dashboard

---

## Project Structure 🧩

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

## Dataset 📊

**Indian Crop Recommendation Dataset**
Source: Indian Crop Recommendation Dataset (Kaggle-based, with minor modifications for testing)

Features: 
- Soil Nutrients: Nitrogen (N), Phosphorus (P), Potassium (K) 
- Environmental Variables: pH level, temperature, humidity, rainfall
- Target Variable: crop label
  
Records: subset of the Indian Crop Recommendation dataset used for experimentation

---

## How to Run 🚀

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

## Key Features 💡

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

## Technologies Used 🛠️

- C++17: data pipeline, OOP design, STL algorithms
- Python 3: scikit-learn, pandas, NumPy
- JavaScript (frontend logic)
- HTML / CSS (Interactive Dashboard)
- Kaggle Dataset (Indian Crop Recommendation Dataset)

---

## Built By 🙋‍♀️😄

Cheparthi Sri Nikhitha
- [LinkedIn](https://www.linkedin.com/in/cheparthi-sri-nikhitha-886b381b1)
- [Portfolio](https://nikhithaprofessionalportfolio.netlify.app/)
