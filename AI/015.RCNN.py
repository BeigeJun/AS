import os
import selectivesearch
import cv2
import shutil
import torch
import torch.nn as nn
from torchvision import transforms
from PIL import Image
import matplotlib.pyplot as plt

# Define the device for GPU usage
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# Define the image transformation
transform = transforms.Compose([
    transforms.Resize(224),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),
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

# Load the model
loaded_model = AlexNet()
loaded_model.load_state_dict(torch.load('alexnet_cifar10.pth'))
loaded_model.to(device)  # Move the model to GPU

directory_path = 'C:/Users/wns20/PycharmProjects/RCNN/Slice_photo'
if os.path.exists(directory_path):
    shutil.rmtree(directory_path)
os.makedirs(directory_path)

image_path = 'C:/Users/wns20/PycharmProjects/RCNN/DataFile/Car.jpg'
img = cv2.imread(image_path)
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

_, regions = selectivesearch.selective_search(img_rgb, scale=750, min_size=1000)

cand_rects = [cand['rect'] for cand in regions if cand['size'] > 500]

img_rgb_copy = img_rgb.copy()
num = 0


for rect in cand_rects:
    left = rect[0]
    top = rect[1]
    right = left + rect[2]
    bottom = top + rect[3]
    cropped_image = img[top:bottom, left:right]  # Image cropping
    cropped_image_rgb = cv2.cvtColor(cropped_image, cv2.COLOR_BGR2RGB)  # Convert to RGB
    cropped_image_rgb = cv2.resize(cropped_image_rgb, (224, 224))  # Resize to match AlexNet input size

    # Convert to PIL image for torchvision transforms
    cropped_image_pil = Image.fromarray(cropped_image_rgb)
    cropped_image_tensor = transform(cropped_image_pil).unsqueeze(0).to(device)  # Apply transforms and move to GPU

    with torch.no_grad():
        output = loaded_model(cropped_image_tensor)

    output = output.cpu()
    print(output[0][1].item())
    print(output[0][0].item())
    print("=============================")
    if output[0][1].item() > 0.95 or output[0][0].item() > 0.95:
        name = os.path.join(directory_path, 'cropped_image' + str(num) + '.jpg')
        cv2.imwrite(name, cropped_image)
        num += 1
        img_rgb_copy = cv2.rectangle(img_rgb_copy, (left, top), (right, bottom), color=(125, 255, 51), thickness=5)
        print("rec")

plt.figure(figsize=(8, 8))
plt.imshow(img_rgb_copy)
plt.show()
