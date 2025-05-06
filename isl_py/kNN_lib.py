import polars as pl
import numpy as np
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsRegressor

# Load the data
df = pl.read_csv('Advertising.csv')

x = df[['TV']].to_numpy().reshape(-1, 1)
y = df[['Sales']].to_numpy()

# Split the data into training (60%) and test sets (40%)
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.6, random_state=42)

k_value_min, k_value_max = 1, 70
k_list = np.linspace(k_value_min, k_value_max, 70)

fig, ax = plt.subplots(figsize=(10, 6))

j = 0
for k_value in k_list:
    model = KNeighborsRegressor(n_neighbors=int(k_value))
    model.fit(x_train, y_train)
    y_pred = model.predict(x_test)

    # Helper code to plot the data along with the model predictions
    colors = ['grey','r','b']
    if k_value in [1,10,70]:
        xvals = np.linspace(x.min(),x.max(),100).reshape(-1,1)
        ypreds = model.predict(xvals)
        ax.plot(xvals, ypreds,'-',label = f'k = {int(k_value)}',linewidth=j+2,color = colors[j])
        j += 1

ax.legend(loc='lower right', fontsize=20)
ax.plot(x_train, y_train, 'o', color='black', label='Training data')
ax.set_xlabel('TV', fontsize=20)
ax.set_ylabel('Sales', fontsize=20)
plt.tight_layout()
plt.show(block=True)
