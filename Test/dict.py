# Assuming your data looks like this:
data = [
    {'name': 'Alice', 'AGATC': '2', 'AATG': '8', 'TATC': '3'},
    {'name': 'Bob', 'AGATC': '4', 'AATG': '1', 'TATC': '5'},
    {'name': 'Charlie', 'AGATC': '3', 'AATG': '2', 'TATC': '5'}
]

print(dir(data))

# Extract the column names from the first row
column_names = list(data[0].keys())

# Iterate over the STRs after the 'name' column
for column_name in column_names[1:]:
    if column_name != 'name':
        print(f"Processing {column_name} column:")

        # Extract the values for the current STR column
        values = [row[column_name] for row in data]

        # Do something with the values (e.g., convert to integers)
        values_as_int = list(map(int, values))

        # Print the values
        print(values_as_int)
        print("------")
