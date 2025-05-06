import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load the data
data = pd.read_csv('Advertising.csv')

print(data.head())

x_true = data['TV'].iloc[5:13]
y_true = data['Sales'].iloc[5:13]

idx = np.argsort(x_true).values

x_true = x_true.iloc[idx].values
y_true = y_true.iloc[idx].values

def find_nearest(array, value):

    idx = pd.Series(np.abs(array - value)).idxmin()

    return idx, array[idx]

x = np.linspace(np.min(x_true), np.max(x_true), 100)
y = np.zeros_like(x)

for i, xi in enumerate(x):
    _, nearest = find_nearest(x_true, xi)
    y[i] = y_true[np.where(x_true == nearest)[0][0]]

plt.plot(x, y, '.-', label='True')
plt.plot(x_true, y_true, 'o', label='Data')
plt.title('TV vs Sales')
plt.xlabel('TV')
plt.ylabel('Sales')
plt.legend()
plt.show(block=True)
