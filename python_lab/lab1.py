import keyword
try:
    import lab2
except ImportError:
    print("lab2 module does not exist")

# ZeroDivisionError and IndexError example
def zero_or_index_errs():
    try:
        x = 1 / 0
    except ZeroDivisionError:
        print("Division by zero")
    try:
        x = [1, 2, 3]
        print(x[3])
    except IndexError:
        print("Index out of range")

def exception_keywords():
    print("Python keywords:")
    for kw in keyword.kwlist:
        if kw == "try" or kw == "except" or kw == "else" or kw == "finally":
            print(f"'{kw}'" + " is an Exception Handling keyword")

def key_or_value_errs():
    try:
        x = {"key1": 1, "key2": 2}
        print(x["key3"])
    except KeyError:
        print("Key not found")
    try:
        x = {"key1": 1, "key2": 2}
        print(x[1])
    except ValueError:
        print("Value not found")

def syntax_name_or_io_errs():
    try:
        exec("print('Hello, World!'")
    except SyntaxError:
        print("Syntax Error")
    try:
        f = open("file.txt", "r")
    except FileNotFoundError:
        print("File not found")

if __name__ == "__main__":
    zero_or_index_errs()
    exception_keywords()
    key_or_value_errs()
    syntax_name_or_io_errs()
    lab2.print_hello()

"""
Output:

lab2 module does not exist
Division by zero
Index out of range
Python keywords:
'else' is an Exception Handling keyword
'except' is an Exception Handling keyword
'finally' is an Exception Handling keyword
'try' is an Exception Handling keyword
Key not found
Traceback (most recent call last):
  File "/mnt/c/KDev/Programming_2023/python_lab/lab1.py", line 50, in <module>
    key_or_value_errs()
  File "/mnt/c/KDev/Programming_2023/python_lab/lab1.py", line 33, in key_or_value_errs
    print(x[1])
KeyError: 1
"""

# Python program to check two exceptions at a time!
def double_exceptions():


# A Program that uses try and finally blocks
# A Program to create an Exception that is defined explicitily by the user and catch the exception
