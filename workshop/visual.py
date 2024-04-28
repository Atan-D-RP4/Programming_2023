import matplotlib.pyplot as plt
import pandas as pd
data = pd.read_csv("algo.csv")
data['BRANCH'] = data['BRANCH'].str[0:3]  # Take the first 3 characters
data['BRANCH'] = data['BRANCH'].str.strip()  # Strip whitespace
data['BRANCH'] = data['BRANCH'].str.upper()  # Convert to uppercase
branch_counts = data['BRANCH'].value_counts()
branch_proportions = branch_counts / branch_counts.sum()
plt.figure(figsize=(10, 6))
plt.pie(branch_proportions, labels=branch_proportions.index, autopct='%1.1f%%', startangle=100)

plt.xlabel('Branch')
plt.ylabel('Proportion')
plt.title('Proportions of Different Branches')
plt.show()
print()
