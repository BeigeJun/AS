import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'
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
    def __init__(self):
        super().__init__()
        self.layer1 = nn.Sequential(
            nn.Conv2d(in_channels=1, out_channels=96, kernel_size=11, stride=4, padding=0),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=3, stride=2)
        )
        self.layer2 = nn.Sequential(
            nn.Conv2d(96, 256, 5, 1, 2),  # in_channels: 96, out_channels: 256, kernel_size=5x5, stride=1, padding=2
            nn.ReLU(),
            nn.MaxPool2d(3, 2)
        )
        self.layer3 = nn.Sequential(
            nn.Conv2d(256, 384, 3, 1, 1),
            nn.ReLU()
        )
        self.layer4 = nn.Sequential(
            nn.Conv2d(384, 384, 3, 1, 1),
            nn.ReLU()
        )
        self.layer5 = nn.Sequential(
            nn.Conv2d(384, 256, 3, 1, 1),
            nn.ReLU(),
            nn.MaxPool2d(3, 2)
        )
        self.fc1 = nn.Linear(256 * 6 * 6, 4096)
        self.fc2 = nn.Linear(4096, 4096)
        self.fc3 = nn.Linear(4096, 10)

    def forward(self, x):  # input size = 3x227x227
        out = self.layer1(x)
        out = self.layer2(out)
        out = self.layer3(out)
        out = self.layer4(out)
        out = self.layer5(out)  # 64x4096x1x1
        out = out.view(out.size(0), -1)  # 64x4096

        out = F.relu(self.fc1(out))
        out = F.dropout(out, 0.5)
        out = F.relu(self.fc2(out))
        out = F.dropout(out, 0.5)
        out = self.fc3(out)
        out = F.log_softmax(out, dim=1)

        return out

loaded_model = AlexNet()
loaded_model.load_state_dict(torch.load('model_state_dict.pt'))


directory_path = 'C:/Users/wns20/PycharmProjects/face/slice'
shutil.rmtree(directory_path)
os.makedirs(directory_path)

image_path = '1.jpg'
img = cv2.imread(image_path)
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

_, regions = selectivesearch.selective_search(img_rgb, scale=750, min_size=1000)

cand_rects = [cand['rect'] for cand in regions if cand['size'] > 1000]
green_rgb = (125, 255, 51)
img_rgb_copy = img_rgb.copy()
num = 0
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
