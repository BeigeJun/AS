import torch
import torch.nn as nn
import numpy as np
#입력, 출력값 선언
def normalize(array):
    Max = 0.0
    Min = 10.0
    for i in range(len(array)):
        compare_Max = max(array[i])
        compare_Min = min(array[i])
        if compare_Max > Max:
            Max = compare_Max
        if compare_Min < Min:
            Min = compare_Min
    array = (array - Min+0.01) / (Max - Min)
    return array

data = torch.FloatTensor([[0.12610, 0.12615, 0.01],
                          [0.12601, 0.12640, 0.01],
                          [0.12599, 0.12615, 0.01]])
data = normalize(data)
print(data)
Output = torch.FloatTensor([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]])
#신경망 모델 만들기
Model = nn.Sequential(
          nn.Linear(3, 15, bias=True),
          nn.Sigmoid(),
          nn.Linear(15, 7, bias=True),
          nn.Sigmoid(),
          nn.Linear(7, 5, bias=True),
          nn.Sigmoid(),
          nn.Linear(5, 3, bias=True),
          nn.Sigmoid())

criterion = nn.BCELoss() #BCELoss란 PyTorch에서 제공하는 이진 분류(binary classification)를 위한 손실 함수(loss function) 중 하나인 이진 교차 엔트로피 손실(Binary Cross Entropy Loss)
optimizer = torch.optim.SGD(Model.parameters(), lr=0.1)
#모델의 파라미터를 SGD 옵티마이저를 사용하여 업데이트하기 위한 설정을 생성
#Model.parameters(): 모델의 파라미터들을 인자로 전달
#lr : 학습률(learning rate)
for epoch in range(100000):
    optimizer.zero_grad() #그래디언트 초기화

    reselt = Model(data) #순전파

    Error = criterion(reselt, Output) #Error값 계산후 역전파 진행

    Error.backward() #역전파 실행 그래디언트(기울기 추출)
    optimizer.step() #역전파를 통해 얻은 기울기로 가중치 업데이트
    #위 두개는 세트

    if epoch % 1000 == 0:
        print(epoch, Error.item())
Input = torch.FloatTensor([[0.12610, 0.12632,1.0],
                          [0.12628, 0.12636,1.0],
                          [0.12599, 0.12615,1.0]])
Input = normalize(Input)
Reselt = Model(Input)
Max = torch.argmax(Reselt, dim=1) + 1
print('출력값: ', Max.numpy())
