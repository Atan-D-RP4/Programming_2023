import yfinance as yf
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import tensorflow as tf
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# Step 1: Extract Data from Yahoo Finance
stock_symbol = 'RELIANCE.NS'  # Example stock symbol for Reliance Industries
stock_data = yf.download(stock_symbol, start='2020-01-01', end='2022-01-01')

# Step 2: Preprocess Data
data = stock_data[['Close']].copy()
scaler = MinMaxScaler()
data['Close'] = scaler.fit_transform(data['Close'].values.reshape(-1,1))

# Create sequences of historical prices
def create_sequences(data, seq_length):
    sequences = []
    for i in range(len(data) - seq_length):
        sequence = data[i:i+seq_length]
        sequences.append(sequence)
    return np.array(sequences)

SEQ_LENGTH = 20
sequences = create_sequences(data.values, SEQ_LENGTH)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(sequences[:,:-1], sequences[:,-1], test_size=0.2, shuffle=False)

# Step 3: Build and Train Model
model = tf.keras.Sequential([
    tf.keras.layers.LSTM(50, input_shape=(X_train.shape[1], X_train.shape[2])),
    tf.keras.layers.Dense(1)
])
model.compile(optimizer='adam', loss='mse')
history = model.fit(X_train, y_train, epochs=50, batch_size=32, validation_data=(X_test, y_test), verbose=2)

# Step 4: Evaluate Model
y_pred = model.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
print("Mean Squared Error:", mse)

# Step 5: Visualize Results
plt.plot(y_test, label='True Values')
plt.plot(y_pred, label='Predictions')
plt.xlabel('Time')
plt.ylabel('Price')
plt.title('Reliance Stock Price Prediction')
plt.legend()
plt.show()