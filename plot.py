import matplotlib.pyplot as plt

def plot(x, y):
    plt.ion()
    plt.title("Exponential Graph")
    plt.plot(x, y)
    plt.show(block=True)

def main():
    x = [i for i in range(100)]
    y = [i**2 for i in x]
    plot(x, y)

if __name__ == '__main__':
    main()
