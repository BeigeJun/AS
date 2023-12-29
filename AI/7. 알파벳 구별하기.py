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

out_1 = [0.0] * 15  # 은닉층 1번째 15개
out_2 = [0.0] * 7  # 은닉층 2번째 7개
weight_hid2_to_out = np.random.rand(3, 7)
weight_hid1_to_hid2 = np.random.rand(7, 15)
weight_in_to_hid1 = np.random.rand(15, 25)
neurons_in_layers = [25, 15, 7, 3]
biases = [np.random.rand(neurons, 1) for neurons in neurons_in_layers[1:]]

target = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
output = [0.0, 0.0, 0.0]
bias = 1.0
error = 0.0
total_error = 0.0
lrate = 0.1
epochs = 100000


def Forward_pass(data, w1, w2, w3, b):
    out_1 = [0.0] * 15  # 초기화
    out_2 = [0.0] * 7  # 초기화

    for i in range(len(w1)):  # 15개의 델타값을 만들어야하니까 15번
        for number in range(len(w1[i])):  # 가중치랑 인풋값 곱학기 25번
            out_1[i] += w1[i][number] * data[number]
        out_1[i] = sigmoid(out_1[i] + b[0][i])
    # ---------------------입력층 - > 1차 은닉층--------------------------------------------
    for i in range(len(w2)):  # 7개의 델타값을 만들어야 하니까 7번
        for number in range(len(w2[i])):  # 15번의 곱셈을 진행
            out_2[i] += w2[i][number] * data[number]
        out_2[i] = sigmoid(out_2[i] + b[1][i])
    # ---------------------1차 은닉층 - > 2차 은닉층----------------------------------------
    for i in range(len(w3)):  # 3개의 출력을 만들어야 하니까 3번
        for number in range(len(w3[i])):  # 7번의 곱셈을 진행
            output[i] += w3[i][number] * out_2[number]
        output[i] = sigmoid(output[i] + b[2][i])
    # ---------------------2차 은닉층 - > 출력층--------------------------------------------

def Backward_pass(data, target, w1, w2, w3, b, out_1, out_2, output, lrate):
    delta_1 = np.zeros(len(w3))
    delta_2 = np.zeros(len(w2))
    delta_3 = np.zeros(len(w1))
    first_error = 0
    second_error = 0
    third_error = 0
    for i in range(len(w3)): #3번 반복
        first_error = target[i] - output[i] #출력층 에러 구하기
        delta_1[i] = first_error * output[i] * (1 - output[i]) #델타값 구하기
        for j in range(len(w3[i])): #7번 반복
            w3[i][j] += lrate * delta_1[i] * out_2[j]
        b[2][i] += lrate * delta_1[i]
    #--------------출력층에서 에러 구하고 그 밑 은닉층_2을 이어주는 가중치 업데이트-----------------
    for i in range(len(w2)): #7번
        for j in range(len(w3)): #3번
            second_error += delta_1[j] * w3[j][i]
        delta_2[i] = second_error * out_2[i] * (1 - out_2[i])
        for number in range(len(w2[i])):
            w2[i][number] += lrate * delta_2[i] * out_1[number]
        b[1][i] += lrate * delta_2[i]

    for i in range(len(w1)):
        for j in range(len(w2)):
            third_error += delta_2[j] * w2[j][i]

        delta_3[i] = third_error * out_1[i] * (1 - out_1[i])

        for number in range(len(w1[i])):
            w1[i][number] += lrate * delta_3[i] * data[number]
        b[0][i] += lrate * delta_3[i]

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
            Backward_pass(input_data[i], target_data[i], w1, w2, w3, b, out_1, out_2, output, lrate)
        #학습수가 10000의 배수일때만 출력하자~ 눈 아프다
        if (epoch % 100 == 0):
            print("step : %4d    Error : %7.4f " % (epoch, total_error))

# 가중치 초기화
weight_in_to_hid1 = np.random.rand(15, 25)
weight_hid1_to_hid2 = np.random.rand(7, 15)
weight_hid2_to_out = np.random.rand(3, 7)
biases = [np.random.rand(neurons, 1) for neurons in neurons_in_layers[1:]]

# 예시 호출
train(input_data, target, weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_out, biases, out_1, out_2, lrate, epochs)

i = [1.0, 1.0, 1.0, 1.0, 1.0,
     0.1, 0.1, 1.0, 0.1, 0.1,
     0.1, 0.1, 1.0, 0.1, 0.1,  # T
     0.1, 0.1, 1.0, 0.1, 0.1,
     0.1, 0.1, 1.0, 0.1, 0.1]
Forward_pass(i, weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_out, biases)
print(output)
