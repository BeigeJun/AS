import torch
import torch.nn as nn
import numpy as np
#입력, 출력값 선언
Input = torch.FloatTensor([[0, 0], [0, 1], [1, 0], [1, 1]])
Output = torch.FloatTensor([[0], [1], [1], [0]])
#신경망 모델 만들기
Model = nn.Sequential(
          nn.Linear(2, 2, bias=True),
          nn.Sigmoid(),
          nn.Linear(2, 1, bias=True),
          nn.Sigmoid())

criterion = nn.BCELoss() #BCELoss란 PyTorch에서 제공하는 이진 분류(binary classification)를 위한 손실 함수(loss function) 중 하나인 이진 교차 엔트로피 손실(Binary Cross Entropy Loss)
optimizer = torch.optim.SGD(Model.parameters(), lr=0.5)
#모델의 파라미터를 SGD 옵티마이저를 사용하여 업데이트하기 위한 설정을 생성
#Model.parameters(): 모델의 파라미터들을 인자로 전달
#lr : 학습률(learning rate)
for epoch in range(10001):
    optimizer.zero_grad() #그래디언트 초기화

    reselt = Model(Input) #순전파

    Error = criterion(reselt, Output) #Error값 계산후 역전파 진행

    Error.backward() #역전파 실행 그래디언트(기울기 추출)
    optimizer.step() #역전파를 통해 얻은 기울기로 가중치 업데이트
    #위 두개는 세트

    if epoch % 100 == 0:
        print(epoch, Error.item())


Reselt = Model(Input)
print('출력값: ', Reselt.detach().numpy())
print('실제값: ', Output.numpy())

def generate_surface():
    X = np.linspace(0, 1, 121)
    Y = np.linspace(0, 1, 121)
    X, Y = np.meshgrid(X, Y)  # X, Y 그리드 생성

    X_tensor = torch.from_numpy(X).float()
    Y_tensor = torch.from_numpy(Y).float()

    input_tensor = torch.stack((X_tensor, Y_tensor), dim=2).view(-1, 2)
    result_tensor = Model(input_tensor)

    Z = result_tensor.view(X.shape).detach().numpy()

    return X, Y, Z


import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

X, Y, Z = generate_surface()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(X, Y, Z, cmap='viridis')

ax.set_xlabel('X1')
ax.set_ylabel('X2')
ax.set_zlabel('Output')

plt.show()
