import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

OR_Gate = [[0, 0, 0],
           [1, 0, 1],
           [0, 1, 1],
           [1, 1, 1]]

learning_rate = 0.01
epochs = 100000
bias = np.random.randn(1)
weight_1 = np.random.randn(1)
weight_2 = np.random.randn(1)

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def learn(w1, w2, b):
    for epoch in range(epochs):
        for i in range(len(OR_Gate)):
            # 순전파
            net = OR_Gate[i][0] * w1 + OR_Gate[i][1] * w2 + b

            # 활성화 함수 거치기
            result = sigmoid(net)

            # 오차 계산
            error = OR_Gate[i][2] - result

            # 역전파
            w1 += learning_rate * error * OR_Gate[i][0]
            w2 += learning_rate * error * OR_Gate[i][1]
            b += learning_rate * error

def generate_surface(w1, w2, b):
    X = np.linspace(0, 1, 121)
    Y = np.linspace(0, 1, 121)
    X, Y = np.meshgrid(X, Y)
    Z = sigmoid(w1 * X + w2 * Y + b)
    return X, Y, Z

learn(weight_1, weight_2, bias)

X, Y, Z = generate_surface(weight_1, weight_2, bias)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis')

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()
