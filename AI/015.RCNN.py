import os
import selectivesearch
import cv2
import shutil
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
import matplotlib.pyplot as plt


transform = transforms.Compose([
    transforms.Grayscale(),
    transforms.Resize((28, 28)),
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))
])

class AlexNet(nn.Module):
    def __init__(self, num_classes=10):
        super(AlexNet, self).__init__()
        self.features = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=11, stride=4, padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            nn.Conv2d(64, 192, kernel_size=5, padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            nn.Conv2d(192, 384, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(384, 256, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(256, 256, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
        )
        self.classifier = nn.Sequential(
            nn.Dropout(),
            nn.Linear(256 * 6 * 6, 4096),
            nn.ReLU(inplace=True),
            nn.Dropout(),
            nn.Linear(4096, 4096),
            nn.ReLU(inplace=True),
            nn.Linear(4096, num_classes),
        )

    def forward(self, x):
        x = self.features(x)
        x = torch.flatten(x, 1)
        x = self.classifier(x)
        return x

loaded_model = AlexNet()
loaded_model.load_state_dict(torch.load('alexnet_cifar10.pth'))


directory_path = 'C:/Users/wns20/PycharmProjects/Secondgit/RCNN/Slice_photo'
shutil.rmtree(directory_path)
os.makedirs(directory_path)

image_path = 'C:/Users/wns20/PycharmProjects/Secondgit/RCNN/DataFile/Plane.jpg'
img = cv2.imread(image_path)
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
print('start')
_, regions = selectivesearch.selective_search(img_rgb, scale=750, min_size=1000)
print('end')
cand_rects = [cand['rect'] for cand in regions if cand['size'] > 1000]
green_rgb = (125, 255, 51)
img_rgb_copy = img_rgb.copy()
num = 0
print('end')
for rect in cand_rects:
    left = rect[0]
    top = rect[1]
    right = left + rect[2]
    bottom = top + rect[3]
    cropped_image = img[top:bottom, left:right]  # 이미지 잘라내기
    cropped_image_gray = cv2.cvtColor(cropped_image, cv2.COLOR_BGR2GRAY)  # 컬러 이미지를 그레이스케일로 변환
    cropped_image_tensor = torch.tensor(cropped_image_gray, dtype=torch.float32).unsqueeze(0).unsqueeze(0)  # 배치 차원 추가 및 텐서로 변환

    output = loaded_model(cropped_image_tensor)
    print(output[0][1])
    print(output[0][0])
    print("=============================")
    if(output[0][1] > 0.95 or output[0][0] > 0.95):
        name = os.path.join(directory_path, 'cropped_image' + str(num) + '.jpg')
        cv2.imwrite(name, cropped_image)
        num += 1
        img_rgb_copy = cv2.rectangle(img_rgb_copy, (left, top), (right, bottom), color=green_rgb, thickness=5)
        print("rec")
plt.figure(figsize=(8, 8))
plt.imshow(img_rgb_copy)
plt.show()
