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

out_1 = [0.0] * 15
out_2 = [0.0] * 7
output = [0.0, 0.0, 0.0]
weight_hid2_to_out = np.random.uniform(low=-0.5, high=0.5, size=(3, 7))
weight_hid1_to_hid2 = np.random.uniform(low=-0.5, high=0.5, size=(7, 15))
weight_in_to_hid1 = np.random.uniform(low=-0.5, high=0.5, size=(15, 25))
neurons_in_layers = [25, 15, 7, 3]
biases = [2 * np.random.rand(neurons, 1) - 1 for neurons in neurons_in_layers[1:]]
#가중치 초기화 할 때는 -0.5 ~ 0.5로하자
target = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
bias = 1.0
error = 0.0
total_error = 0.0
lrate = 0.01
epochs = 100000

def weight_write(epoch,total_error, w1, w2, w3, b):
    f = open("C:/Users/wns20/PycharmProjects/pythonProject10/weight.txt", 'w')
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
            write += "%.1f " % biases[i][j]
    f.write(write)
    f.close()
def forward_pass(data,w,b,bias_num,out):
    for i in range(len(w)):
        for number in range(len(w[i])):
            out[i] += w[i][number] * data[number]
        out[i] = sigmoid(out[i] + b[bias_num][i])
def Forward_pass(data, w1, w2, w3, b):
    forward_pass(data, w1, b, 0, out_1)
    forward_pass(data, w2, b, 1, out_2)
    forward_pass(data, w3, b, 2, output)
    return out_1 , out_2 , output
def Backward_pass(data, target, w1, w2, w3, b, out_1, out_2, output, lrate):
    delta_1 = np.zeros(len(w3))
    delta_2 = np.zeros(len(w2))
    delta_3 = np.zeros(len(w1))
    first_error = 0
    second_error = 0
    third_error = 0
    # --------------출력층에서 에러 구하고 그 밑 은닉층_2을 이어주는 가중치 업데이트-----------------
    for i in range(len(w3)): #3번 반복
        first_error = target[i] - output[i] #출력층 에러 구하기
        delta_1[i] = first_error * output[i] * (1 - output[i]) #델타값 구하기

        for j in range(len(w3[i])): #7번 반복
            w3[i][j] += lrate * delta_1[i] * out_2[j]

        b[2][i] += lrate * delta_1[i]
    # ----------------------은닉층_2 -> 은닉층_1 로 가는 가중치 없데이트 -----------------------
    for i in range(len(w2)): #7번
        for j in range(len(w3)): #3번
            second_error += delta_1[j] * w3[j][i]

        delta_2[i] = second_error * out_2[i] * (1 - out_2[i])

        for number in range(len(w2[i])):
            w2[i][number] += lrate * delta_2[i] * out_1[number]

        b[1][i] += lrate * delta_2[i]
    # ---------------------은닉층_1 -> 입력층 가중치 업데이트---------------------------------
    for i in range(len(w1)):
        for j in range(len(w2)):
            third_error += delta_2[j] * w2[j][i]

        delta_3[i] = third_error * out_1[i] * (1 - out_1[i])

        for number in range(len(w1[i])):
            w1[i][number] += lrate * delta_3[i] * data[number]

        b[0][i] += lrate * delta_3[i]
        return w1,w2,w3,b
def train(input_data, target_data, w1, w2, w3, b, lrate, epochs):
    minimun_error = 10.0
    comparison_error = 10.0
    for epoch in range(epochs):
        total_error = 0.0
        for i in range(len(input_data)):
            #순전파
            out_1, out_2, output = Forward_pass(input_data[i], w1, w2, w3, b)
            #에너지 구하기
            error = 0.0
            for j in range(len(target_data[i])):
                error += 0.5 * (target_data[i][j] - output[j]) ** 2
            total_error += error
            comparison_error = total_error
            #역전파
            Backward_pass(input_data[i], target_data[i], w1, w2, w3, b, out_1, out_2, output, lrate)
        #학습수가 10000의 배수일때만 출력하자~ 눈 아프다
        if (epoch % 100 == 0):
            print("step : %4d    Error : %7.4f " % (epoch, total_error))
        #에러가 전에 나온 에러보다 제일 작을 때만 텍스트 파일에 저장하기
        if(minimun_error > comparison_error):
            minimun_error = comparison_error
            weight_write(epoch,total_error, w1, w2, w3, b)
# 예시 호출
train(input_data, target, weight_in_to_hid1, weight_hid1_to_hid2, weight_hid2_to_out, biases, lrate, epochs)
