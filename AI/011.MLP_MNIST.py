import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms
import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))
])

train_dataset = datasets.MNIST(root='./data', train=True, download=True, transform=transform)
test_dataset = datasets.MNIST(root='./data', train=False, download=True, transform=transform)
#'dataset' = 데이터셋이 저장 될 디렉터리
#train = 이 데이터를 학습 데이터 인가
#download = 만약 기기 안에 저장되어 있지 않으면 다운로드 받을 것인가
# transform = 데이터셋에 적용할 변환을 정의. ToTensor()을 통해 이미지를 텐서로 변환
# print(train_dataset)
# 데이터 로더로 전환하여 학습 테스트를 바로 진행할 수 있습니다.
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=64, shuffle=True)
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=64, shuffle=False)
#데이터셋을 미니배치로 나누어줌 인자로는(데이터셋 객체, 미니배치의 크기, 값을 섞을지의 유무, 데이터로드를 위한 병렬 프로세스 수, 미니배치를 생성하기 위한 사용자 정의함수, CPU에서 GPU로 전송할 때 메모리 피닝의 여부)가있다.

# img , label = next(iter(train_loader))
# #iter이란 순차적으로 항목을 반환하는 객체이다. next를 이용하여 다음 항목에 접근한다.
# print(img.shape, label)
#
# img_show = img[0, 0, :, :]
# print(img_show.shape)
# #첫인자는 한번에 처리되는이미지의 수, 이미지의 채널 수, 이미지의 높이, 이미지의 너비

class MNISTNet(torch.nn.Module):
    def __init__(self):
        super(MNISTNet, self).__init__()
        self.fc1 = torch.nn.Linear(28*28, 590)
        self.fc2 = torch.nn.Linear(590, 397)
        self.fc3 = torch.nn.Linear(397, 200)
        self.fc4 = torch.nn.Linear(200, 10)

    def forward(self, x):
        x = x.view(-1, 28 * 28) #이미지 평탄화
        x = torch.sigmoid(self.fc1(x))
        x = torch.sigmoid(self.fc2(x))
        x = torch.sigmoid(self.fc3(x))
        x = self.fc4(x)
        return x

Model = MNISTNet()

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(Model.parameters(), lr=0.001)
#Adaptive Moment Estimation : 경사하강법의 한 종류이고 기울기가 가파르면 조금 옮겨가서 다음 기울기를 측정하고 완만하면 많이 옮겨가서 기울기를 측정함
for epoch in range(5):  # 데이터셋을 여러 번 반복합니다.
    running_loss = 0.0
    for i, data in enumerate(train_loader, 0): #enumerate는 train_loader에 있는 순서와 데이터를 뽑아오는 기능을 한다.
        inputs, labels = data
        optimizer.zero_grad()

        outputs = Model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.item()
        if i % 100 == 99:
            print('[%d, %d] loss: %.5f' %(epoch + 1, i + 1, running_loss / 100))
            running_loss = 0.0


correct = 0
total = 0
with torch.no_grad():
    for data in test_loader:
        images, labels = data
        outputs = Model(images)
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

print("정확도 : ",100 * correct / total)
