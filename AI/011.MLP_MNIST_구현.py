import torch
import matplotlib.pyplot as plt
from torchvision import datasets, transforms

mnist_dataset = datasets.MNIST('dataset', train=True, download=True, 
               transform=transforms.Compose([
                   transforms.ToTensor()
]))
#'dataset' = 데이터셋이 저장 될 디렉터리
#train = 이 데이터를 학습 데이터 인가
#download = 만약 기기 안에 저장되어 있지 않으면 다운로드 받을 것인가
# transform = 데이터셋에 적용할 변환을 정의. ToTensor()을 통해 이미지를 텐서로 변환
print(mnist_dataset)
# 데이터 로더로 전환하여 학습 테스트를 바로 진행할 수 있습니다.
train_loader = torch.utils.data.DataLoader(
    mnist_dataset
)
#데이터셋을 미니배치로 나누어줌 인자로는(데이터셋 객체, 미니배치의 크기, 값을 섞을지의 유무, 데이터로드를 위한 병렬 프로세스 수, 미니배치를 생성하기 위한 사용자 정의함수, CPU에서 GPU로 전송할 때 메모리 피닝의 여부)가있다.

img , label = next(iter(train_loader))
#iter이란 순차적으로 항목을 반환하는 객체이다. next를 이용하여 다음 항목에 접근한다.
print(img.shape, label)

img_show = img[0, 0, :, :]
print(img_show.shape)
#첫인자는 한번에 처리되는이미지의 수, 이미지의 채널 수, 이미지의 높이, 이미지의 너비

plt.imshow(img_show, 'gray')
plt.show()
