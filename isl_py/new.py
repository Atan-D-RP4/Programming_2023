import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import GridSearchCV
from sklearn.ensemble import RandomForestRegressor
from sklearn.linear_model import Ridge
import matplotlib
matplotlib.use('TkAgg')

df = pd.read_csv('CASP.csv')
print(df.head())

print(df.shape)
print(df.isnull().sum())

scaler = StandardScaler()
scaled = scaler.fit_transform(df)
scaled_df = pd.DataFrame(scaled, columns=df.columns)
print(scaled_df.head())

# Define features and target variable
X = scaled_df.drop('RMSD', axis=1)
y = df['RMSD']

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=42)

# Initialize the Linear Regression model
lr_model = LinearRegression()
# Train the model
lr_model.fit(X_train, y_train)
# Make predictions on the test set
y_pred_lr = lr_model.predict(X_test)
# Evaluate the model
mse_lr = mean_squared_error(y_test, y_pred_lr)
print("Linear Regression Mean Squared Error:", mse_lr)
r2_lr = r2_score(y_test, y_pred_lr)
print("Linear Regression R2┬áScore:", r2_lr)

# Initialize the Decision Tree Regression model
dt_model = DecisionTreeRegressor(random_state=42)
# Train the model
dt_model.fit(X_train, y_train)
# Make predictions on the test set
y_pred_dt = dt_model.predict(X_test)
# Evaluate the model
mse_dt = mean_squared_error(y_test, y_pred_dt)
print("Decision Tree Mean Squared Error:", mse_dt)
r2_dt = r2_score(y_test, y_pred_dt)
print("Decision Tree R2 Score:", r2_dt)
# Define Random Forest model
rf_model = RandomForestRegressor(random_state=42)
# Define the grid of hyperparameters
param_grid_rf = {
    'n_estimators': [5, 10],
    'max_depth': [None, 10],
    'min_samples_split': [2, 5],
    'min_samples_leaf': [1]
}

# Initialize Grid Search Cross-Validation
grid_search_rf = GridSearchCV(estimator=rf_model, param_grid=param_grid_rf,
                              cv=5, scoring='neg_mean_squared_error', n_jobs=1)

grid_search_rf.fit(X_train, y_train)
ridge_model = Ridge(alpha=1.0)  # You can adjust the value of alpha
 # Train the model
ridge_model.fit(X_train, y_train)
 # Make predictions on the test set
y_pred_ridge = ridge_model.predict(X_test)
 # Evaluate the model

mse_ridge = mean_squared_error(y_test, y_pred_ridge)

print("Ridge Regression Mean Squared Error:", mse_ridge)
r2_ridge = r2_score(y_test, y_pred_ridge)
print("Ridge Regression R2 Score:", r2_ridge)

# Initialize the Random Forest Regression model

rf_model = RandomForestRegressor(n_estimators=15, random_state=42)
# Train the model
rf_model.fit(X_train, y_train)
# Make predictions on the test set
y_pred_rf = rf_model.predict(X_test)
# Evaluate the model
mse_rf = mean_squared_error(y_test, y_pred_rf)

print("Random Forest Mean Squared Error:", mse_rf)
r2_rf = r2_score(y_test, y_pred_rf)
print("Random Forest R2 Score:", r2_rf)

# Get the best parameters and best score

best_params_rf = grid_search_rf.best_params_

best_score_rf = -grid_search_rf.best_score_ # Negate the score to

print("Best Parameters (Random Forest):", best_params_rf)

print("Best Negative MSE (Random Forest):", best_score_rf)

# Use the best model obtained from Grid Search

best_rf_model = grid_search_rf.best_estimator_

# Make predictions on the test set using the best model

y_pred_best_rf = best_rf_model.predict(X_test)

# Evaluate the model

mse_best_rf = mean_squared_error(y_test, y_pred_best_rf)

print("Best Random Forest Mean Squared Error:", mse_best_rf)

param_grid_dt = {
   'max_depth': [None, 10, 20, 30],
   'min_samples_split': [2, 5, 10],
   'min_samples_leaf': [1, 2, 4]
}
# Initialize Grid Search Cross-Validation
grid_search_dt = GridSearchCV(estimator=dt_model, param_grid=param_grid_dt, cv=5, scoring='neg_mean_squared_error', n_jobs=-1)
# Perform Grid Search CV
grid_search_dt.fit(X_train, y_train)
# Get the best parameters and best score
best_params_dt = grid_search_dt.best_params_
best_score_dt = -grid_search_dt.best_score_
print("Best Parameters (Decision Tree):", best_params_dt)
print("Best Negative MSE (Decision Tree):", best_score_dt)
# Use the best model obtained from Grid Search
best_dt_model = grid_search_dt.best_estimator_
# Make predictions on the test set using the best model
y_pred_best_dt = best_dt_model.predict(X_test)
# Evaluate the model
mse_best_dt = mean_squared_error(y_test, y_pred_best_dt)
print("Best Decision Tree Mean Squared Error:", mse_best_dt)
r2_best_dt = r2_score(y_test, y_pred_best_dt)
print("Decision Tree R2 Score:", r2_best_dt)

r2_best_rf = r2_score(y_test, y_pred_best_rf)

print("Random Forest R2 Score:",r2_best_rf)



 # Print all scores
print("Linear Regression (Default) MSE:", mse_lr)
print("Linear Regression (Default) R2 Score:", r2_lr)
print("Ridge Regression MSE:", mse_ridge)
print("Ridge Regression R2 Score:", r2_ridge)
print("Decision Trees (Default) MSE:", mse_dt)
print("Decision Trees (Default) R2 Score:", r2_dt)
print("Decision Trees (Best) MSE:", mse_best_dt)
print("Decision Trees (Best) R2 Score:", r2_best_dt)

print("Random Forest (Default) MSE:", mse_rf)
print("Random Forest (Default) R2 Score:", r2_rf)
print("Random Forest (Best) MSE:", mse_best_rf)
print("Random Forest (Best) R2 Score:", r2_best_rf)

# Create lists of model names, MSE values, and R2 scores
models = ['Linear Regression (Default)', 'Ridge Regression',
          'Decision Trees (Default)', 'Decision Trees (Best)',
          'Random Forest (Default)', 'Random Forest (Best)']

mse_values = [mse_lr, mse_ridge, mse_dt, mse_best_dt, mse_rf, mse_best_rf]
r2_values = [r2_lr, r2_ridge, r2_dt, r2_best_dt, r2_rf, r2_best_rf]

# # Create a bar plot for MSE values
# plt.figure(figsize=(10, 6))
# # Set the color hues
# sns.barplot(x=models, y=mse_values)
#
# plt.title('Mean Squared Error (MSE) Comparison')
# plt.xlabel('Models')
# plt.ylabel('MSE')
# plt.xticks(rotation=45, ha='right')
# plt.tight_layout()
# plt.show()
# # Create a bar plot for R2 score values
# plt.figure(figsize=(10, 6))
# sns.barplot(x=models, y=r2_values, palette='Oranges')
# plt.title('R-squared (R2) Score Comparison')
# plt.xlabel('Models')
# plt.ylabel('R2 Score')
# plt.xticks(rotation=45, ha='right')
# plt.ylim(0, 1)
# plt.tight_layout()
#
# plt.ion()
# plt.show(block=True)
