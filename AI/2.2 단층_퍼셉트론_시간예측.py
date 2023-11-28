import numpy as np
import matplotlib.pyplot as plt

time = np.array([1020, 1034, 1040, 1060, 1050])
day = np.array([1, 2, 3, 4, 5])

learning_rate = 0.01
epochs = 10000

weights = np.random.rand(1)
bias = np.random.rand(1)

for epoch in range(epochs):
    for i in range(len(time)):
        # 순전파
        predicted_time = day[i] * weights + bias

        # 오차 계산
        error = time[i] - predicted_time

        # 역전파
        weights += learning_rate * error * day[i]
        bias += learning_rate * error

# 학습된 모델로 예측
predicted_time = day * weights + bias

# 그래프 그리기
fig, ax = plt.subplots(figsize=(5, 5))
plt.scatter(day, time, label='Data')
plt.plot(day, predicted_time, color='red')
plt.yticks(np.arange(1000,1100,10))
plt.xticks(np.arange(0,10,1))
plt.xlabel('Day')
plt.ylabel('Time')
plt.legend()
plt.show()

Day = int(input("날짜 : "))
y =  Day* weights + bias
hour = y/60
time = y%60
print(int(hour),":",int(time))
