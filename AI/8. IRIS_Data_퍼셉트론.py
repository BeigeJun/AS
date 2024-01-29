import numpy as np
from sklearn.datasets import load_iris
import pandas as pd

def sigmoid(data):
    return 1.0 / (1.0 + np.exp(-data))

Iris = load_iris()

Iris_Data = pd.DataFrame(data=Iris['data'], columns=Iris['feature_names'])
Iris_Target = pd.DataFrame(data=Iris['target'], columns=['target'])
Iris_Target.replace({0: 'setosa', 1: 'versicolor', 2: 'virginica'}, inplace=True)

test = []
test.append(Iris_Data)
Test = np.array(test)
Test = Test.reshape(150,4)

iris_data = np.array([])
iris_data_slices = []
iris_data_slices.append(Iris_Data.iloc[:40])
iris_data_slices.append(Iris_Data.iloc[50:90])
iris_data_slices.append(Iris_Data.iloc[100:140])
iris_data = np.concatenate(iris_data_slices)
iris_data = iris_data.reshape(120, 4)

Target = np.array([])
for i in range(len(Iris_Target)):
    if(Iris_Target['target'].iloc[i] == 'setosa'):
        Target = np.vstack([Target, [1.0, 0.0, 0.0]]) if Target.size else np.array([[1.0, 0.0, 0.0]])
    elif Iris_Target['target'].iloc[i] == 'versicolor':
        Target = np.vstack([Target, [0.0, 1.0, 0.0]]) if Target.size else np.array([[0.0, 1.0, 0.0]])
    elif Iris_Target['target'].iloc[i] == 'virginica':
        Target = np.vstack([Target, [0.0, 0.0, 1.0]]) if Target.size else np.array([[0.0, 0.0, 1.0]])

target = np.array([])
target_slices = []
target_slices.append(Target[:40])
target_slices.append(Target[50:90])
target_slices.append(Target[100:140])
target = np.concatenate(target_slices)
target = target.reshape(120, 3)

out1 = 4
out2 = 4
out3 = 4
out_put = 3
weight_hid3_to_out = np.random.uniform(low=-5.0, high=5.0, size=(out_put, out3))
weight_hid2_to_hid3 = np.random.uniform(low=-5.0, high=5.0, size=(out3, out2))
weight_hid1_to_hid2 = np.random.uniform(low=-5.0, high=5.0, size=(out2, out1))
weight_in_to_hid1 = np.random.uniform(low=-5.0, high=5.0, size=(out1, 4))
neurons_in_layers = [4, out1, out2, out3, out_put]
biases = [2 * np.random.rand(neurons, 1) - 1 for neurons in neurons_in_layers[1:]]
bias = 1.0
error = 0.0
total_error = 0.0
lrate = 0.1
epochs = 3000

def forward_pass(data, w, b, bias_num, out):
    for i in range(len(w)):
        for number in range(len(w[i])):
            out[i] += w[i][number] * data[number]
        out[i] = sigmoid(out[i] + b[bias_num][i])
    return out

def Forward_pass(data, w1, w2, w3, w4, b):
    out_1 = forward_pass(data, w1, b, 0, [0.0] * out1)
    out_2 = forward_pass(out_1, w2, b, 1, [0.0] * out2)
    out_3 = forward_pass(out_2, w3, b, 2, [0.0] * out3)
    output = forward_pass(out_3, w4, b, 3, [0.0] * out_put)
    return out_1, out_2, out_3, output


def delta_rule(weight1, weight2, b, b_num, delta_1, delta_2, lrate, out_1, out_2):
    error = 0
    for i in range(len(weight1)):
        for j in range(len(weight2)):
            error += delta_1[j] * weight2[j][i]
        delta_2[i] = error * out_2[i] * (1 - out_2[i])
        for number in range(len(weight1[i])):
            weight1[i][number] += lrate * delta_2[i] * out_1[number]
        b[b_num][i] += lrate * delta_2[i]
    return delta_2, weight1


def first_delta_rule(weight, b, b_num, delta, target, output, out_2):
    for i in range(len(weight)):
        first_error = target[i] - output[i]
        delta[i] = first_error * output[i] * (1 - output[i])
        for j in range(len(weight[i])):
            weight[i][j] += lrate * delta[i] * out_2[j]
        b[b_num][i] += lrate * delta[i]
    return delta, weight


def Backward_pass(data, target, w1, w2, w3, w4, b, out1, out2, out3, out_put, lrate):
    delta_1 = np.zeros(len(w4))
    delta_2 = np.zeros(len(w3))
    delta_3 = np.zeros(len(w2))
    delta_4 = np.zeros(len(w1))
    delta_1, w4 = first_delta_rule(w4, b, 3, delta_1, target, out_put, out3)
    delta_2, w3 = delta_rule(w3, w4, b, 2, delta_1, delta_2, lrate, out2, out3)
    delta_3, w2 = delta_rule(w2, w3, b, 1, delta_2, delta_3, lrate, out1, out2)
    delta_4, w1 = delta_rule(w1, w2, b, 0, delta_3, delta_4, lrate, data, out1)
    return w1, w2, w3, w4

def train(input_data, target_data, w1, w2, w3, w4, b, lrate, epochs):
    for epoch in range(epochs):
        total_error = 0.0
        for i in range(len(input_data)):
            out_1, out_2, out_3, output = Forward_pass(input_data[i], w1, w2, w3,w4, b)
            error = 0.0
            for j in range(len(target_data[i])):
                error += 0.5 * (target_data[i][j] - output[j]) ** 2
            total_error += error
            w1, w2, w3, w4 = Backward_pass(input_data[i], target_data[i], w1, w2, w3, w4, b, out_1, out_2, out_3, output, lrate)
        if epoch % 100 == 0:
            total_error = total_error / 150
            print("step : %4d    Error : %7.10f " % (epoch, total_error))

train(iris_data, target, weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_hid3, weight_hid3_to_out, biases, lrate, epochs)

while True:
    #직접입력
    # i = [0.0,0.0,0.0,0.0]
    # a = input("데이터 입력 : ")
    # i = a.split(' ')
    # data = list(map(float, i))
    # print(data)

    i = int(input("번호 선택 :"))
    a, b, c, d = Forward_pass(Test[i], weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_hid3, weight_hid3_to_out, biases)
    Max = d[0]
    Max_num = 0
    for j in range(len(d)-1):
        if(Max < d[j+1]):
            Max = d[j+1]
            Max_num = j+1
    if(Max_num == 0):
        print("setosa")
    elif(Max_num == 1):
        print("versicolor")
    elif(Max_num == 2):
        print("virginica")
    print(d)
