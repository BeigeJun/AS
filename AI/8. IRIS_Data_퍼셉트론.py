import numpy as np
from sklearn.datasets import load_iris
import pandas as pd
from copy import deepcopy
def sigmoid(data):
    return 1.0 / (1.0 + np.exp(-data))

Iris = load_iris()

Iris_Data = pd.DataFrame(data=Iris['data'], columns=Iris['feature_names'])
Iris_Target = pd.DataFrame(data=Iris['target'], columns=['target'])
Iris_Target.replace({0: 'setosa', 1: 'versicolor', 2: 'virginica'}, inplace=True)

test = []
test.append(Iris_Data)
Test = np.array(test)
Test = Test.reshape(150, 4)

iris_data = np.array([])
iris_data_slices1 = []
iris_data_slices2 = []
iris_data_slices3 = []
iris_data_slices4 = []
iris_data_slices5 = []
iris_data_slices1.append(Iris_Data.iloc[:40])
iris_data_slices1.append(Iris_Data.iloc[50:90])
iris_data_slices1.append(Iris_Data.iloc[100:140])

iris_data_slices2.append(Iris_Data.iloc[:30])
iris_data_slices2.append(Iris_Data.iloc[40:50])
iris_data_slices2.append(Iris_Data.iloc[50:80])
iris_data_slices2.append(Iris_Data.iloc[90:100])
iris_data_slices2.append(Iris_Data.iloc[100:130])
iris_data_slices2.append(Iris_Data.iloc[140:150])

iris_data_slices3.append(Iris_Data.iloc[:20])
iris_data_slices3.append(Iris_Data.iloc[30:50])
iris_data_slices3.append(Iris_Data.iloc[50:70])
iris_data_slices3.append(Iris_Data.iloc[80:100])
iris_data_slices3.append(Iris_Data.iloc[100:120])
iris_data_slices3.append(Iris_Data.iloc[130:150])

iris_data_slices4.append(Iris_Data.iloc[:10])
iris_data_slices4.append(Iris_Data.iloc[20:50])
iris_data_slices4.append(Iris_Data.iloc[50:60])
iris_data_slices4.append(Iris_Data.iloc[70:100])
iris_data_slices4.append(Iris_Data.iloc[100:110])
iris_data_slices4.append(Iris_Data.iloc[120:150])

iris_data_slices5.append(Iris_Data.iloc[10:50])
iris_data_slices5.append(Iris_Data.iloc[60:100])
iris_data_slices5.append(Iris_Data.iloc[110:150])

iris_data1 = np.concatenate(iris_data_slices1)
iris_data2 = np.concatenate(iris_data_slices2)
iris_data3 = np.concatenate(iris_data_slices3)
iris_data4 = np.concatenate(iris_data_slices4)
iris_data5 = np.concatenate(iris_data_slices5)

iris_data1 = iris_data1.reshape(120, 4)
iris_data2 = iris_data2.reshape(120, 4)
iris_data3 = iris_data3.reshape(120, 4)
iris_data4 = iris_data4.reshape(120, 4)
iris_data5 = iris_data5.reshape(120, 4)


Target = np.array([])
for i in range(len(Iris_Target)):
    if(Iris_Target['target'].iloc[i] == 'setosa'):
        Target = np.vstack([Target, [1.0, 0.0, 0.0]]) if Target.size else np.array([[1.0, 0.0, 0.0]])
    elif Iris_Target['target'].iloc[i] == 'versicolor':
        Target = np.vstack([Target, [0.0, 1.0, 0.0]]) if Target.size else np.array([[0.0, 1.0, 0.0]])
    elif Iris_Target['target'].iloc[i] == 'virginica':
        Target = np.vstack([Target, [0.0, 0.0, 1.0]]) if Target.size else np.array([[0.0, 0.0, 1.0]])

target1 = np.array([])
target2 = np.array([])
target3 = np.array([])
target4 = np.array([])
target5 = np.array([])

target_slices1 = []
target_slices2 = []
target_slices3 = []
target_slices4 = []
target_slices5 = []

target_slices1.append(Target[:40])
target_slices1.append(Target[50:90])
target_slices1.append(Target[100:140])

target_slices2.append(Target[:30])
target_slices2.append(Target[40:50])
target_slices2.append(Target[50:80])
target_slices2.append(Target[90:100])
target_slices2.append(Target[100:130])
target_slices2.append(Target[140:150])

target_slices3.append(Target[:20])
target_slices3.append(Target[30:50])
target_slices3.append(Target[50:70])
target_slices3.append(Target[80:100])
target_slices3.append(Target[100:120])
target_slices3.append(Target[130:150])

target_slices4.append(Target[:10])
target_slices4.append(Target[20:50])
target_slices4.append(Target[50:60])
target_slices4.append(Target[70:100])
target_slices4.append(Target[100:110])
target_slices4.append(Target[120:150])

target_slices5.append(Target[10:50])
target_slices5.append(Target[60:100])
target_slices5.append(Target[110:150])

target1 = np.concatenate(target_slices1)
target2 = np.concatenate(target_slices2)
target3 = np.concatenate(target_slices3)
target4 = np.concatenate(target_slices4)
target5 = np.concatenate(target_slices5)

target1 = target1.reshape(120, 3)
target2 = target2.reshape(120, 3)
target3 = target3.reshape(120, 3)
target4 = target4.reshape(120, 3)
target5 = target5.reshape(120, 3)

out1 = 10
out2 = 7
out3 = 5
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
epochs = 1000
def normalization():
    choose = int(input("학습 데이터 선택 : "))
    choose_iris = globals()["iris_data" + str(choose)]
    choose_target = globals()["target" + str(choose)]
    Max = 0.0
    Min = 10.0
    for i in range(120):
        compare_Max = max(choose_iris[i])
        compare_Min = min(choose_iris[i])
        if compare_Max > Max:
            Max = compare_Max
        if compare_Min < Min:
            Min = compare_Min
    for i in range(120):
        for j in range(4):
            choose_iris[i][j] = (choose_iris[i][j] - Min) / (Max - Min)
    return choose_iris, choose_target

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
    return delta_2, weight1, b


def first_delta_rule(weight, b, b_num, delta, target, output, out_2):
    for i in range(len(weight)):
        first_error = target[i] - output[i]
        delta[i] = first_error * output[i] * (1 - output[i])
        for j in range(len(weight[i])):
            weight[i][j] += lrate * delta[i] * out_2[j]
        b[b_num][i] += lrate * delta[i]
    return delta, weight, b


def Backward_pass(data, target, w1, w2, w3, w4, b, out1, out2, out3, out_put, lrate):
    delta_1 = np.zeros(len(w4))
    delta_2 = np.zeros(len(w3))
    delta_3 = np.zeros(len(w2))
    delta_4 = np.zeros(len(w1))
    delta_1, w4, b = first_delta_rule(w4, b, 3, delta_1, target, out_put, out3)
    delta_2, w3, b = delta_rule(w3, w4, b, 2, delta_1, delta_2, lrate, out2, out3)
    delta_3, w2, b = delta_rule(w2, w3, b, 1, delta_2, delta_3, lrate, out1, out2)
    delta_4, w1, b = delta_rule(w1, w2, b, 0, delta_3, delta_4, lrate, data, out1)
    return w1, w2, w3, w4, b

def train(input_data, target_data, w1, w2, w3, w4, b, lrate, epochs):
    minimum_error = 10.0
    comparison_error = 10.0
    Lowerror = []
    for epoch in range(epochs):
        total_error = 0.0
        for i in range(len(input_data)):
            out_1, out_2, out_3, output = Forward_pass(input_data[i], w1, w2, w3,w4, b)
            error = 0.0
            for j in range(len(target_data[i])):
                error += 0.5 * (target_data[i][j] - output[j]) ** 2
            total_error += error
            comparison_error = total_error
            w1, w2, w3, w4, b = Backward_pass(input_data[i], target_data[i], w1, w2, w3, w4, b, out_1, out_2, out_3, output, lrate)
        total_error = total_error / 150
        if epoch % 100 == 0:
            print("step : %4d    Error : %7.10f " % (epoch, total_error))
    #     if minimum_error > comparison_error:
    #         minimum_error = comparison_error
    #         Use_w1 = np.zeros(len(w1))
    #         Use_w1 = deepcopy((w1))
    #         Use_w2 = np.zeros(len(w2))
    #         Use_w2 = deepcopy((w2))
    #         Use_w3 = np.zeros(len(w3))
    #         Use_w3 = deepcopy((w3))
    #         Use_w4 = np.zeros(len(w4))
    #         Use_w4 = deepcopy((w4))
    #         Use_bias = np.zeros(len(b))
    #         Use_bias = deepcopy((b))
    #         print("Saved weight's Error : ", minimum_error)
    return w1, w2, w3, w4, b

choose_iris, choose_target = normalization()
# Use_w1, Use_w2, Use_w3, Use_w4, Use_bias =
a, b, c, d, e = train(choose_iris, choose_target, weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_hid3, weight_hid3_to_out, biases, lrate, epochs)
# print(Use_w1)
# print(Use_w2)
# print(Use_w3)
# print(Use_w4)
# print(Use_bias)
    #직접입력
    # i = [0.0,0.0,0.0,0.0]
    # a = input("데이터 입력 : ")
    # i = a.split(' ')
    # data = list(map(float, i))
    # print(data)

    # i = int(input("번호 선택 :"))
    # if i < 0 and i > 150:
    #     continue
    # a, b, c, d = Forward_pass(Test[i], Use_w1, Use_w2, Use_w3, Use_w4, Use_bias)
    # Max = d[0]
    # Max_num = 0
    # for j in range(len(d)-1):
    #     if(Max < d[j+1]):
    #         Max = d[j+1]
    #         Max_num = j+1
    # if(Max_num == 0):
    #     print("setosa")
    # elif(Max_num == 1):
    #     print("versicolor")
    # elif(Max_num == 2):
    #     print("virginica")
    # print(d)
Correct = 0
for i in range(150):
    a,b,c,d = Forward_pass(Test[i],  a, b, c, d, e)
    Max = d[0]
    Max_num = 0
    for j in range(len(d) - 1):
        if (Max < d[j + 1]):
            Max = d[j + 1]
            Max_num = j + 1
    if i < 50:
        if Max_num == 0:
            Correct += 1
        else:
            print("적중 실패 :", i)
    elif i > 49 and i < 100:
        if Max_num == 1:
           Correct += 1
        else:
            print("적중 실패 :", i)
    elif i > 99 and i < 150:
        if Max_num == 2:
           Correct += 1
        else:
            print("적중 실패 :", i)
print("적중한 횟수 :", Correct)
