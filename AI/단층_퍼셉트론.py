import numpy as np
import matplotlib.pyplot as plt

tall = np.array([150, 156, 163, 165, 168, 170, 182, 183, 187, 189])
weight = np.array([35, 45, 50, 54, 70, 63, 75, 77, 85, 90])

data = np.array([
    [1, 150, 35],
    [1, 156, 45],
    [1, 163, 50],
    [1, 165, 54],
    [1, 168, 70],
    [1, 170, 63],
    [1, 182, 75],
    [1, 183, 77],
    [1, 187, 85],
    [1, 189, 90]
])

target_output = np.array([0, 0, 0, 0, 1, 0, 1, 1, 1, 1])

weights = np.random.rand(3)
learning_rate = 0.1
epochs = 1000000

for epoch in range(epochs):
    output = data.dot(weights)
    predicted_output = np.where(output <= 0, 0, 1)
    error = target_output - predicted_output
    weights += learning_rate * data.T.dot(error)

x_values = np.linspace(140, 200, 100)
y_values = (-weights[1] / weights[2]) * x_values - weights[0] / weights[2]

plt.scatter(tall, weight)

plt.plot(x_values, y_values, color='red', label='Decision Boundary')

plt.xlabel('Tall')
plt.ylabel('Weight')
plt.title('Perceptron Decision Boundary')
plt.legend()
plt.show()
