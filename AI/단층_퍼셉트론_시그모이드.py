import random
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

OR_Gate = [[0,0,0],
           [1,0,1],
           [0,1,1],
           [1,1,1]]

learning_rate = 0.01
epochs = 10000


bias = np.random.rand(1)
weight_1 = np.random.rand(1)
weight_2 = np.random.rand(1)

for epoch in range(epochs):
    for i in range(len(OR_Gate)):
        # 순전파
        Net = OR_Gate[i][0] * weight_1 + OR_Gate[i][1] * weight_2 + bias
        #활성화 함수 거치기
        result = sigmoid(Net)

        # 오차 계산
        error = OR_Gate[i][2] - result

        # 역전파
        weight_1 += learning_rate * error * OR_Gate[i][0]
        weight_2 += learning_rate * error * OR_Gate[i][1]
        bias += learning_rate * error
