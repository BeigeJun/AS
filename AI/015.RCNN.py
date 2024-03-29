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

class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=9, kernel_size=3, stride=1, padding=1)
        self.conv2 = nn.Conv2d(in_channels=9, out_channels=18, kernel_size=3, stride=1, padding=1)
        self.conv3 = nn.Conv2d(in_channels=18, out_channels=27, kernel_size=3, stride=1, padding=1)
        self.conv4 = nn.Conv2d(in_channels=27, out_channels=36, kernel_size=3, stride=1, padding=1)
        self.fc1 = nn.Linear(36, 100)
        self.fc2 = nn.Linear(100, 2)

    def forward(self, x):
        x = F.relu(self.conv1(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)
        x = F.relu(self.conv2(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)
        x = F.relu(self.conv3(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)
        x = F.relu(self.conv4(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)
        x = F.relu(self.fc1(x.view(-1, 36)))
        x = self.fc2(x)
        x = F.softmax(x, dim=1)
        return x

loaded_model = CNN()
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
    name = os.path.join(directory_path, 'cropped_image' + str(num) + '.jpg')
    cv2.imwrite(name, cropped_image)
    num += 1
    img_rgb_copy = cv2.rectangle(img_rgb_copy, (left, top), (right, bottom), color=green_rgb, thickness=5)

plt.figure(figsize=(8, 8))
plt.imshow(img_rgb_copy)
plt.show()
