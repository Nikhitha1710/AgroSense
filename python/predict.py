import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import warnings
warnings.filterwarnings('ignore')

def load_data(filepath):
    df = pd.read_csv(filepath)
    print(f"Loaded {len(df)} records from {filepath}")
    return df

def train_model(df):
    features = ['N', 'P', 'K', 'pH', 'moisture', 'temperature', 'rainfall']
    
    available = [f for f in features if f in df.columns]
    X = df[available]
    y = df['crop'] if 'crop' in df.columns else df.iloc[:, -1]

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    model = RandomForestClassifier(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)

    y_pred = model.predict(X_test)
    acc = accuracy_score(y_test, y_pred)
    print(f"Model accuracy: {acc:.2%}")
    return model, available

def predict_crop(model, features, soil_input):
    input_array = np.array([[soil_input.get(f, 0) for f in features]])
    prediction = model.predict(input_array)[0]
    probabilities = model.predict_proba(input_array)[0]
    top_idx = np.argsort(probabilities)[::-1][:3]
    top_crops = [(model.classes_[i], round(probabilities[i] * 100, 1)) for i in top_idx]
    return prediction, top_crops

def main():
    print("=" * 45)
    print("  AgroSense - ML Crop Prediction Engine")
    print("=" * 45)

    try:
        df = load_data("data/crop_data.csv")
    except FileNotFoundError:
        print("Dataset not found. Please download from:")
        print("https://www.kaggle.com/datasets/atharvaingle/crop-recommendation-dataset")
        print("\nRunning with sample data...\n")
        df = pd.DataFrame({
            'N': [90, 85, 60, 74, 78],
            'P': [42, 58, 55, 35, 42],
            'K': [43, 41, 44, 40, 42],
            'pH': [6.5, 7.0, 6.0, 6.8, 6.5],
            'moisture': [65, 55, 70, 48, 62],
            'temperature': [20.8, 21.7, 23.0, 26.0, 22.0],
            'rainfall': [82.0, 80.3, 85.0, 95.0, 88.0],
            'crop': ['rice', 'rice', 'maize', 'chickpea', 'rice']
        })

    model, feature_cols = train_model(df)

    test_input = {
        'N': 56, 'P': 52, 'K': 32,
        'pH': 6.8, 'moisture': 62.0,
        'temperature': 26.0, 'rainfall': 85.0
    }

    print("\n--- Predicting for Andhra Pradesh soil sample ---")
    print(f"Input: N={test_input['N']}, P={test_input['P']}, K={test_input['K']}, "
          f"pH={test_input['pH']}, Moisture={test_input['moisture']}%, "
          f"Temp={test_input['temperature']}C, Rainfall={test_input['rainfall']}mm")

    prediction, top_crops = predict_crop(model, feature_cols, test_input)
    print(f"\nTop recommendation: {prediction.upper()}")
    print("\nTop 3 crop matches:")
    for crop, prob in top_crops:
        bar = "#" * int(prob / 5)
        print(f"  {crop:<15} {prob:>5.1f}%  {bar}")

    print("\n" + "=" * 45)

if __name__ == "__main__":
    main()
