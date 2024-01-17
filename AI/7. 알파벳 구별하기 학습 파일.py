import numpy as np
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
               1.0, 0.1, 0.1, 0.1, 0.1,
               1.0, 0.1, 0.1, 0.1, 1.0]]

weight_hid2_to_out = np.random.uniform(low=-5.0, high=5.0, size=(3, 7))
weight_hid1_to_hid2 = np.random.uniform(low=-5.0, high=5.0, size=(7, 15))
weight_in_to_hid1 = np.random.uniform(low=-5.0, high=5.0, size=(15, 25))
neurons_in_layers = [25, 15, 7, 3]
biases = [2 * np.random.rand(neurons, 1) - 1 for neurons in neurons_in_layers[1:]]
#가중치 초기화 할 때는 -0.5 ~ 0.5로하자
target = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
bias = 1.0
error = 0.0
total_error = 0.0
lrate = 0.1
epochs = 20000
out_1 = [0.0] * 15  # 은닉층 1번째 15개
out_2 = [0.0] * 7  # 은닉층 2번째 7개
output = [0.0, 0.0, 0.0]
def weight_write(total_error, w1, w2, w3,b):
    f = open("C:/Users/SeoJun/PycharmProjects/pythonProject2/weight.txt", 'w')
    write = "error : %f \n w1 : " % total_error
    for i in range(len(w1)):
        for j in range(len(w1[i])):
            write += "%.1f " % w1[i][j]
    write += "\n w2 : "
    for i in range(len(w2)):
        for j in range(len(w2[i])):
            write += "%.1f " % w2[i][j]
    write += "\n w3 : "
    for i in range(len(w3)):
        for j in range(len(w3[i])):
            write += "%.1f " % w3[i][j]
    write += "\n biases : "
    for i in range(len(biases)):
        for j in range(len(biases[i])):
            write += "%.1f " % b[i][j]
    f.write(write)
    f.close()
def forward_pass(data, w, b, bias_num, out):
    for i in range(len(w)):
        for number in range(len(w[i])):
            out[i] += w[i][number] * data[number]
        out[i] = sigmoid(out[i] + b[bias_num][i])
    return out

def Forward_pass(data, w1, w2, w3, b):
    out_1 = forward_pass(data, w1, b, 0, [0.0] * 15)
    out_2 = forward_pass(out_1, w2, b, 1, [0.0] * 7)
    output = forward_pass(out_2, w3, b, 2, [0.0, 0.0, 0.0])
    return out_1, out_2, output

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

def Backward_pass(data, target, w1, w2, w3, b, out1, out2, out_put, lrate):
    delta_1 = np.zeros(len(w3))
    delta_2 = np.zeros(len(w2))
    delta_3 = np.zeros(len(w1))
    delta_1, w3 = first_delta_rule(w3, b, 2, delta_1, target, out_put, out2)
    delta_2, w2 = delta_rule(w2, w3, b, 1, delta_1, delta_2, lrate, out1, out2)
    delta_3, w1 = delta_rule(w1, w2, b, 0, delta_2, delta_3, lrate, data, out1)
    return w1, w2, w3

def train(input_data, target_data, w1, w2, w3, b, lrate, epochs):
    minimum_error = 10.0
    comparison_error = 10.0
    for epoch in range(epochs):
        total_error = 0.0
        for i in range(len(input_data)):
            out_1, out_2, output = Forward_pass(input_data[i], w1, w2, w3, b)
            error = 0.0
            for j in range(len(target_data[i])):
                error += 0.5 * (target_data[i][j] - output[j]) ** 2
            total_error += error
            comparison_error = total_error
            w1, w2, w3 = Backward_pass(input_data[i], target_data[i], w1, w2, w3, b, out_1, out_2, output, lrate)
        if epoch % 100 == 0:
            print("step : %4d    Error : %7.4f " % (epoch, total_error))
        if minimum_error > comparison_error:
            minimum_error = comparison_error
            weight_write(total_error, w1, w2, w3,b)

train(input_data, target, weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_out, biases, lrate, epochs)
input_data = [[1.0, 1.0, 1.0, 1.0, 1.0,
               1.0, 0.1, 1.0, 1.0, 0.1,
               1.0, 0.1, 1.0, 0.1, 0.1,  # T
               0.1, 0.1, 1.0, 0.1, 0.1,
               0.1, 0.1, 1.0, 0.1, 0.1],
              [1.0, 1.0, 1.0, 1.0, 1.0,
               1.0, 0.1, 1.0, 0.1, 0.1,
               0.1, 0.1, 1.0, 0.1, 0.1,  # T
               0.1, 0.1, 1.0, 0.1, 0.1,
               0.1, 0.1, 1.0, 0.1, 0.1],
              [1.0, 1.0, 1.0, 1.0, 1.0,
               0.1, 0.1, 0.1, 0.1, 0.1,
               1.0, 1.0, 1.0, 1.0, 1.0,  # E
               1.0, 0.1, 0.1, 0.1, 0.1,
               1.0, 1.0, 1.0, 1.0, 1.0],
              [1.0, 1.0, 1.0, 1.0, 1.0,
               1.0, 0.1, 0.1, 0.1, 0.1,
               1.0, 1.0, 1.0, 1.0, 0.1,  # E
               1.0, 0.1, 0.1, 0.1, 0.1,
               1.0, 1.0, 1.0, 1.0, 1.0],
              [1.0, 0.1, 0.1, 0.1, 1.0,
               1.0, 0.1, 0.1, 0.1, 1.0,
               1.0, 1.0, 1.0, 1.0, 1.0,  # H
               1.0, 0.1, 0.1, 0.1, 0.1,
               1.0, 0.1, 0.1, 1.0, 1.0],
              [1.0, 1.0, 1.0, 1.0, 1.0,
               1.0, 1.0, 1.0, 1.0, 1.0,
               1.0, 1.0, 1.0, 1.0, 1.0,  # H
               1.0, 1.0, 1.0, 1.0, 1.0,
               1.0, 1.0, 1.0, 1.0, 1.0]
              ]
while True:
    i = int(input("실험할 데이터 선택 : "))
    a,b,c = Forward_pass(input_data[i-1], weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_out, biases)
    print(c)
