import numpy as np
import polars as pl
import matplotlib.pyplot as plt
from sklearn.utils import shuffle
from sklearn.metrics import r2_score
from sklearn.metrics import mean_squared_error
from sklearn.neighbors import KNeighborsRegressor
from sklearn.model_selection import train_test_split

# Load the data
data_file = 'Advertising.csv'
df = pl.read_csv(data_file)

print(df.head())

x = df['TV'].to_numpy()
y = df['Sales'].to_numpy()

# Split the data: test_size = 40%, train_size = 60%
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=66)

k_min, k_max = 1, 70

k_list = np.linspace(k_min, k_max, num=70, dtype=int)

fig, ax = plt.subplots(figsize=(10, 6))

knn_dict = {}
j = 0

for k_val in k_list:
    model = KNeighborsRegressor(n_neighbors=int(k_val))
    model.fit(x_train.reshape(-1, 1), y_train)

    y_pred = model.predict(x_test.reshape(-1, 1))
    MSE = mean_squared_error(y_test, y_pred)

    knn_dict[k_val] = MSE

    # Helper code to plot the data and various kNN model predictions
    colors = ['grey','r','b']
    if k_val in [1,10,70]:
        xvals = np.linspace(x.min(),x.max() - 1,100).reshape(-1,1)
        ypreds = model.predict(xvals)
        ax.plot(xvals, ypreds,'-',label = f'k = {int(k_val)}',linewidth=j+2,color = colors[j])
        j+=1

ax.legend(loc='lower right',fontsize=20)
ax.plot(x_train, y_train,'x',label='test',color='k')
ax.set_xlabel('TV budget in $1000',fontsize=20)
ax.set_ylabel('Sales in $1000',fontsize=20)
plt.tight_layout()

plt.figure(figsize=(8,6))

plt.plot(knn_dict.keys(), knn_dict.values(),'k.-',alpha=0.5,linewidth=2)

# Set the title and axis labels
plt.xlabel('k',fontsize=20)
plt.ylabel('MSE',fontsize = 20)
plt.title('Test $MSE$ values for different k values - KNN regression',fontsize=20)
plt.tight_layout()

print(knn_dict)
min_mse = min(knn_dict.values())
best_model = [key for (key, value) in knn_dict.items() if value == min_mse]

print(f"Best k value: {best_model[0]} with MSE: {min_mse}")

model = KNeighborsRegressor(n_neighbors=best_model[0])
model.fit(x_train.reshape(-1, 1), y_train)
y_pred = model.predict(x_test.reshape(-1, 1))

print(f"R2 score: {r2_score(y_test, y_pred)}")

plt.show(block=True)
