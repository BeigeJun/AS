import numpy as np

tall = [150,156,163,165,168,170,182,183,187,189]
weight = [35,45,50,54,70,63,75,77,85,90]
tall_new = [0,0,0,0,0,0,0,0,0,0]
weight_new = [0,0,0,0,0,0,0,0,0,0]
for i in range(10):
    tall_new[i] = tall[i]/200
    weight_new[i] = weight[i]/100
Y = np.array(tall_new)
X = np.array(weight_new)

learning_rate = 0.01
epochs = 10000

weights = np.random.rand(1)
bias = np.random.rand(1)

for epoch in range(epochs):
    for i in range(len(Y)):
        # 순전파
        predicted_weight = Y[i] * weights + bias

        # 오차 계산
        error = X[i] - predicted_weight

        # 역전파
        weights += learning_rate * error * Y[i]
        bias += learning_rate * error

import matplotlib.pyplot as plt
fig, ax = plt.subplots(figsize=(5,10))
plt.scatter(tall, weight, label='Data')
plt.plot(tall, (Y * weights + bias)*100, color='red')
plt.xlabel('Height')
plt.ylabel('Weight')
plt.legend()
plt.show()

input_height = int(input("예측:"))
input_height_new = input_height / 200
output = input_height_new * weights + bias
predicted_weight = output * 100

print(f"입력한 키 {input_height}에 대한 예측 몸무게: {predicted_weight[0]}")
