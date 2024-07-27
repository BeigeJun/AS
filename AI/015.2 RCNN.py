import os
import selectivesearch
import cv2
import shutil
import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision.transforms as transforms
import matplotlib.pyplot as plt

transform = transforms.Compose([
    transforms.Resize((224, 224)),  
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
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
        self.bbox_regressor = nn.Linear(4096, 4)  # Bounding box prediction layer

    def forward(self, x):
        x = self.features(x)
        x = torch.flatten(x, 1)
        x = self.classifier(x)
        class_output = x
        bbox_output = self.bbox_regressor(x)  # Bounding box prediction
        return class_output, bbox_output

loaded_model = AlexNet(num_classes=10)
loaded_model.load_state_dict(torch.load('alexnet_cifar10.pth'))
loaded_model.eval()

directory_path = 'C:/Users/wns20/PycharmProjects/Secondgit/RCNN/Slice_photo'
shutil.rmtree(directory_path, ignore_errors=True)
os.makedirs(directory_path)

image_path = 'C:/Users/wns20/PycharmProjects/Secondgit/RCNN/DataFile/Plane.jpg'
img = cv2.imread(image_path)
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

_, regions = selectivesearch.selective_search(img_rgb, scale=750, min_size=1000)
cand_rects = [cand['rect'] for cand in regions if cand['size'] > 1000]
green_rgb = (125, 255, 51)
img_rgb_copy = img_rgb.copy()
num = 0

for rect in cand_rects:
    left, top, width, height = rect
    right = left + width
    bottom = top + height
    cropped_image = img[top:bottom, left:right]
    cropped_image_resized = cv2.resize(cropped_image, (224, 224))
    cropped_image_tensor = transform(cropped_image_resized).unsqueeze(0)

    with torch.no_grad():
        class_output, bbox_output = loaded_model(cropped_image_tensor)
    
    class_prob = F.softmax(class_output, dim=1)
    bbox_coords = bbox_output[0].tolist()
    
    # 바운딩 박스 좌표를 원본 이미지 좌표로 변환
    x1, y1, w, h = bbox_coords
    x1 = int(x1 * width + left)
    y1 = int(y1 * height + top)
    w = int(w * width)
    h = int(h * height)
    
    x2 = x1 + w
    y2 = y1 + h
    
    print(f"Class Probabilities: {class_prob}")
    print(f"Bounding Box Prediction: {bbox_coords}")
    
    if class_prob[0][1] > 0.95:
        name = os.path.join(directory_path, f'cropped_image_{num}.jpg')
        cv2.imwrite(name, cropped_image)
        num += 1
        img_rgb_copy = cv2.rectangle(img_rgb_copy, (x1, y1), (x2, y2), color=green_rgb, thickness=5)
        print("Rectangle drawn")

plt.figure(figsize=(8, 8))
plt.imshow(img_rgb_copy)
plt.show()
