import numpy as np

def sigmoid(data):
    return 1.0 / (1.0 + np.exp(-data))

out_1 = [0.0] * 15  # 은닉층 1번째 15개
out_2 = [0.0] * 7  # 은닉층 2번째 7개
output = [0.0, 0.0, 0.0]
bias = 1.0
f = open("C:/Users/wns20/PycharmProjects/pythonProject10/weight.txt", 'r')
a = f.readline()
a = f.readline()
weight_in_to_hid1 = np.array(a.split(" ")[3:-1])
weight_in_to_hid1 = weight_in_to_hid1.reshape(15,25)
a = f.readline()
weight_hid1_to_hid2 = np.array(a.split(" ")[3:-1])
weight_hid1_to_hid2 = weight_hid1_to_hid2.reshape(7,15)
a = f.readline()
weight_hid2_to_out = np.array(a.split(" ")[3:-1])
weight_hid2_to_out = weight_hid2_to_out.reshape(3,7)
a = f.readline()
print(a)
bias_1 = np.array(a.split(" ")[3:18], dtype=float)
print(bias_1)
print(len(bias_1))
bias_2 = np.array(a.split(" ")[18:25], dtype=float)
print(bias_2)
print(len(bias_2))
bias_3 = np.array(a.split(" ")[25:28], dtype=float)
print(bias_3)
print(len(bias_3))
f.close
def Forward_pass(data, w1, w2, w3, b1,b2,b3):
    for i in range(len(w1)):  # 15개의 델타값을 만들어야하니까 15번
        for number in range(len(w1[i])):  # 가중치랑 인풋값 곱학기 25번
            out_1[i] += float(w1[i][number]) * data[number]
        out_1[i] = sigmoid(out_1[i] + b1[i])
    # ---------------------입력층 - > 1차 은닉층--------------------------------------------
    for i in range(len(w2)):  # 7개의 델타값을 만들어야 하니까 7번
        for number in range(len(w2[i])):  # 15번의 곱셈을 진행
            out_2[i] += float(w2[i][number]) * data[number]
        out_2[i] = sigmoid(out_2[i] + b2[i])
    # ---------------------1차 은닉층 - > 2차 은닉층----------------------------------------
    for i in range(len(w3)):  # 3개의 출력을 만들어야 하니까 3번
        for number in range(len(w3[i])):  # 7번의 곱셈을 진행
            output[i] += float(w3[i][number]) * out_2[number]
        output[i] = sigmoid(output[i] + b3[i])
    # ---------------------2차 은닉층 - > 출력층--------------------------------------------
print("1 :      2:      3 : ")
print("■■■■■    ■■■■■   ■■■■■")
print("■□■□□    ■□■□□   □□□□□")
print("■□■□□    □□■□□   ■■■■■")
print("□□■□□    □□■□□   ■□□□□")
print("□□■□□    □□■□□   ■■■■■")
print("4 :      5 :     6:")
print("■■■■■    ■■■■■   ■■■■■")
print("■□□□□    ■□□□□   ■■■■■")
print("■■■■■    ■■■■■   ■■■■■")
print("■□□□■    ■□□□■   ■■■■■")
print("■■■■■    ■□□■■   ■■■■■")
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
i = int(input("실험할 데이터 선택 : "))
Forward_pass(input_data[i-1],weight_in_to_hid1,weight_hid1_to_hid2,weight_hid2_to_out,bias_1,bias_2,bias_3)
print(output)
