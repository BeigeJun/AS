import numpy as np
import random
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
def sigmoid(data) :
    return 1.0 / (1.0 + math.exp(-data))

x1 = [0.0, 1.0, 0.0, 1.0]
x2 = [0.0, 0.0, 1.0, 1.0]
target = [0.0, 1.0, 1.0, 0.0]
output = [0.0, 0.0, 0.0, 0.0]
bias = 1.0
hid1_no = 2
error = 0.0
total_error = 0.0

delta = [0.0, 0.0, 0.0]    # 역전파 변수
delta_error = [0.0, 0.0]

lrate = 0.01
epochs = 1000000

hiddenLayer = np.zeros(hid1_no, dtype=np.float32) #히든레이어 값 두개 받기위해서 두개 선언
weight = [[0.0, 0.0, 0.0],[0.0, 0.0, 0.0],[0.0, 0.0, 0.0]]

for i in range(3):
    for j in range(3):
        weight[i][j] = random.random() #가중치 초기화
        print("weight = %f\t" % weight[i][j])
    print("\n")


def learn():
    for epoch in range(epochs):
        total_error = 0.0
        for i in range(4):
            for k in range(2):
                 hiddenLayer[k] = sigmoid((x1[i] * weight[k][0]) + (x2[i] * weight[k][1]) + (bias * weight[k][2]))
            output[i] = (hiddenLayer[0] * weight[2][0]) + (hiddenLayer[1] * weight[2][1]) + (bias * weight[2][2]) #입력층에서 은닉층으로 가는 구간
            output[i] = sigmoid(output[i]) #간 다음 각 시그모이드 씌우기
            error = target[i] - output[i]
            total_error += math.pow(error, 2)  # 에러 제곱 합 구하기 (에너지)

            delta[2] = error * output[i] * (1 - output[i])  # 가로가 시그모이드 도함수

            for k in range(2):  # 히든 델타 에러 값
                 delta_error[k] = delta[2] * weight[2][k]
            for k in range(2): # 히든 델타 값
                 delta[k] = delta_error[k] * hiddenLayer[k] * (1 - hiddenLayer[k])
            weight[0][0] += lrate * delta[0] * x1[i]
            weight[0][1] += lrate * delta[0] * x2[i]
            weight[0][2] += lrate * delta[0]             #change bias

            weight[1][0] += lrate * delta[1] * x1[i]
            weight[1][1] += lrate * delta[1] * x2[i]
            weight[1][2] += lrate * delta[1]

            weight[2][0] += lrate * delta[2] * hiddenLayer[0]
            weight[2][1] += lrate * delta[2] * hiddenLayer[1]
            weight[2][2] += lrate * delta[2]

        if(epoch % 10000 == 0):
            print("step : %4d    Error : %7.4f " % (epoch, total_error))
learn()
# while True:
#     input1 = int(input("1:"))
#     input2 = int(input("2:"))
#     h_lay1 = sigmoid((input1 * weight[0][0]) + (input2 * weight[0][1]) + (bias * weight[0][2]))
#     h_lay2 = sigmoid((input1 * weight[1][0]) + (input2 * weight[1][1]) + (bias * weight[1][2]))
#     out = sigmoid((h_lay1 * weight[2][0]) + (h_lay2 * weight[2][1]) + (bias * weight[2][2]))
#     print(out)



def sigmoid1(data):
    return 1.0 / (1.0 + np.exp(-data))
def generate_surface(weight):
    X = np.linspace(0, 1, 121)
    Y = np.linspace(0, 1, 121)
    X, Y = np.meshgrid(X, Y)

    h_lay1 = sigmoid1((X * weight[0][0]) + (Y * weight[0][1]) + weight[0][2])
    h_lay2 = sigmoid1((X * weight[1][0]) + (Y * weight[1][1]) + weight[1][2])
    Z = sigmoid1((h_lay1 * weight[2][0]) + (h_lay2 * weight[2][1]) + weight[2][2])

    return X, Y, Z

X, Y, Z = generate_surface(weight)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(X, Y, Z, cmap='viridis')

ax.set_xlabel('X1')
ax.set_ylabel('X2')
ax.set_zlabel('Output')

plt.show()
