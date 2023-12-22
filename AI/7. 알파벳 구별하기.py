import numpy as np
import random
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def sigmoid(data):
    return 1.0 / (1.0 + np.exp(-data))

target = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]

input_data = [[1.0, 1.0, 1.0, 1.0, 1.0,
               0.1, 0.1, 1.0, 0.1, 0.1,
               0.1, 0.1, 1.0, 0.1, 0.1,  # T
               0.1, 0.1, 1.0, 0.1, 0.1,
               0.1, 0.1, 1.0, 0.1, 0.1],
              [1.0, 1.0, 1.0, 1.0, 1.0,
               1.0, 0.1, 0.1, 0.1, 0.1,
               1.0, 1.0, 1.0, 1.0, 1.0,  # E
               1.0, 0.1, 0.1, 0.1, 0.1,
               1.0, 1.0, 1.0, 1.0, 1.0],
              [1.0, 0.1, 0.1, 0.1, 1.0,
               1.0, 0.1, 0.1, 0.1, 1.0,
               1.0, 1.0, 1.0, 1.0, 1.0,  # H
               1.0, 0.1, 0.1, 0.1, 1.0,
               1.0, 0.1, 0.1, 0.1, 1.0]]
# 0.0으로 안하는 이유는 가중치 업데이트가 안되기 때문이다.
delta_1 = [0.0] * 15  # 은닉층 1번째 15개
delta_2 = [0.0] * 7  # 은닉층 2번째 7개
weight_out_to_hid2 = np.random.rand(3, 7)
weight_hid1_to_hid2 = np.random.rand(7, 15)
weight_in_to_hid1 = np.random.rand(15, 25)
neurons_in_layers = [25, 15, 7, 3]
biases = [np.random.rand(neurons, 1) for neurons in neurons_in_layers[1:]]
# print(biases)
# print(weight_out_to_hid2)
# print(weight_hid1_to_hid2)
# print(weight_in_to_hid1)

target = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
output = [0.0, 0.0, 0.0]
bias = 1.0
error = 0.0
total_error = 0.0
lrate = 0.01
epochs = 100000


def Forward_pass(data, w1, w2, w3, b):
    delta_1 = [0.0] * 15  # 초기화
    delta_2 = [0.0] * 7  # 초기화

    for i in range(len(w1)):  # 15개의 델타값을 만들어야하니까 15번
        for number in range(len(w1[i])):  # 가중치랑 인풋값 곱학기 25번
            delta_1[i] += w1[i][number] * data[number]
        delta_1[i] = sigmoid(delta_1[i] + b[0][i])
    # ---------------------입력층 - > 1차 은닉층--------------------------------------------
    for i in range(len(w2)):  # 7개의 델타값을 만들어야 하니까 7번
        for number in range(len(w2[i])):  # 15번의 곱셈을 진행
            delta_2[i] += w2[i][number] * data[number]
        delta_2[i] = sigmoid(delta_2[i] + b[1][i])
    # ---------------------1차 은닉층 - > 2차 은닉층----------------------------------------
    for i in range(len(w3)):  # 3개의 출력을 만들어야 하니까 3번
        for number in range(len(w3[i])):  # 7번의 곱셈을 진행
            output[i] += w3[i][number] * delta_2[number]
        output[i] = sigmoid(output[i] + b[2][i])
    # ---------------------2차 은닉층 - > 출력층--------------------------------------------


def Backward_pass(data, target, w1, w2, w3, b, output, delta_1, delta_2, lrate):



def train(input_data, target_data, w1, w2, w3, b, delta_1, delta_2, lrate, epochs):
    for epoch in range(epochs):
        total_error = 0.0
        for i in range(len(input_data)):
            #순전파
            Forward_pass(input_data[i], w1, w2, w3, b)

            #에너지 구하기
            error = 0.0
            for j in range(len(target_data[i])):
                error += 0.5 * (target_data[i][j] - output[j]) ** 2
            total_error += error

            #역전파
            Backward_pass(input_data[i], target_data[i], w1, w2, w3, b, output, delta_1, delta_2, lrate)
        #학습수가 10000의 배수일때만 출력하자~ 눈 아프다
        if (epoch % 100 == 0):
            print("step : %4d    Error : %7.4f " % (epoch, total_error))


# 예시 호출
train(input_data, target, weight_in_to_hid1, weight_hid1_to_hid2, weight_out_to_hid2, biases, delta_1, delta_2, lrate, epochs)

i = [1.0, 1.0, 1.0, 1.0, 1.0,
     0.1, 0.1, 1.0, 0.1, 0.1,
     0.1, 0.1, 1.0, 0.1, 0.1,  # T
     0.1, 0.1, 1.0, 0.1, 0.1,
     0.1, 0.1, 1.0, 0.1, 0.1]
Forward_pass(i, weight_in_to_hid1, weight_hid1_to_hid2, weight_out_to_hid2, biases)
print(output)
