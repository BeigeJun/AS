import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

AND_Gate = [[0, 0, 0],
            [1, 0, 0],
            [0, 1, 0],
            [1, 1, 1]]

OR_Gate = [[0, 0, 0],
           [1, 0, 1],
           [0, 1, 1],
           [1, 1, 1]]

NAND_Gate = [[0, 0, 1],
             [1, 0, 1],
             [0, 1, 1],
             [1, 1, 0]]

XOR_Gate = [[0, 0, 0],
            [1, 0, 1],
            [0, 1, 1],
            [1, 1, 0]]

learning_rate = 0.01
epochs = 100000
bias = np.random.randn(1)
weight_1 = np.random.randn(1)
weight_2 = np.random.randn(1)

x = int(input("And : 1 Or : 2 Nand : 3"))

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def calculate_error(gate):
    total_error = 0
    Gate = gate
    for i in range(len(Gate)):
        net = Gate[i][0] * weight_1 + Gate[i][1] * weight_2 + bias
        result = sigmoid(net)
        error = Gate[i][2] - result
        total_error += error ** 2
    return total_error / len(Gate)

def learn(w1, w2, b , g):
    Gate = g
    prev_error = float('inf')
    for epoch in range(epochs):
        for i in range(len(Gate)):
            net = Gate[i][0] * w1 + Gate[i][1] * w2 + b
            result = sigmoid(net)
            error = Gate[i][2] - result
            w1 += learning_rate * error * Gate[i][0]
            w2 += learning_rate * error * Gate[i][1]
            b += learning_rate * error

        current_error = calculate_error(Gate)

        print(current_error,prev_error)

        if current_error >= prev_error - 0.0000000001:
            print(epoch)
            break

        prev_error = current_error

def generate_surface(w1, w2, b):
    X = np.linspace(0, 1, 121)
    Y = np.linspace(0, 1, 121)
    X, Y = np.meshgrid(X, Y)
    Z = sigmoid(w1 * X + w2 * Y + b)
    return X, Y, Z
if x == 1 : GATE = AND_Gate
elif x == 2 : GATE = OR_Gate
elif x == 3 : GATE = NAND_Gate

learn(weight_1, weight_2, bias, GATE)

X, Y, Z = generate_surface(weight_1, weight_2, bias)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis')

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()
