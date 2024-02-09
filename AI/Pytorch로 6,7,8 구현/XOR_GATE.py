import torch
import torch.nn as nn
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
