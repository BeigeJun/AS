import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
import matplotlib.pyplot as plt
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.1307,), (0.3081,))
])
train_dataset = datasets.MNIST(root='./data', train=True, download=True, transform=transform)
test_dataset = datasets.MNIST(root='./data', train=False, download=True, transform=transform)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=100, shuffle=True)
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=100, shuffle=False)
class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=20, kernel_size=5, stride=1)
        self.conv2 = nn.Conv2d(in_channels=20, out_channels=50, kernel_size=5, stride=1)
        self.fc1 = nn.Linear(4 * 4 * 50, 500)
        self.fc2 = nn.Linear(500, 10)

    def forward(self, x):
        x = F.relu(self.conv1(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)
        x = F.relu(self.conv2(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)

        x = x.view(-1, 4 * 4 * 50)
        x = F.relu(self.fc1(x))
        x = self.fc2(x)
        return x

cnn = CNN()
criterion = torch.nn.CrossEntropyLoss()
optimizer = optim.SGD(cnn.parameters(), lr=0.01)

cnn.train()
for epoch in range(5):
    running_loss = 0.0
    for i, data in enumerate(train_loader, 0):
        inputs, labels = data
        optimizer.zero_grad()

        outputs = cnn(inputs)

        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.item()
        if i % 100 == 99:
            print('[%d, %d] loss: %.5f' % (epoch + 1, i + 1, running_loss / 100))
            running_loss = 0.0


cnn.eval()  # test case 학습 방지를 위함
test_loss = 0
correct = 0
with torch.no_grad():
    data_iter = iter(test_loader)
    images, labels = next(data_iter)
    First_conv_outputs = F.relu(cnn.conv1(images))
    First_pool_outputs = F.max_pool2d(First_conv_outputs, kernel_size=2, stride=2)
    Second_conv_outputs = F.relu(cnn.conv2(First_pool_outputs))
    Second_pool_outputs = F.max_pool2d(Second_conv_outputs, kernel_size=2, stride=2)
    plt.imshow(images[0][0].detach().numpy(), cmap='gray')
    plt.title("Original Image")
    plt.show()
    #앞이 배치 순서, 뒤가 배치에서의 순서
    for i in range(20):
        plt.subplot(5, 4, i + 1)
        plt.imshow(First_conv_outputs[0][i].squeeze().detach().numpy(), cmap='gray')
        plt.title("First Convolution Output")
    plt.show()
    for i in range(20):
        plt.subplot(5, 4, i + 1)
        plt.imshow(First_pool_outputs[0][i].squeeze().detach().numpy(), cmap='gray')
        plt.title("First Pooling Output")
    plt.show()
    for i in range(50):
        plt.subplot(10, 5, i + 1)
        plt.imshow(Second_conv_outputs[0][i].squeeze().detach().numpy(), cmap='gray')
        plt.title("Second Convolution Output")
    plt.show()
    for i in range(50):
        plt.subplot(10, 5, i + 1)
        plt.imshow(Second_pool_outputs[0][i].squeeze().detach().numpy(), cmap='gray')
        plt.title("Second Pooling Output")
    plt.show()
    for data, target in test_loader:
       output = cnn(data)
       test_loss += criterion(output, target).item()
       pred = output.argmax(dim=1, keepdim=True)
       correct += pred.eq(target.view_as(pred)).sum().item()
print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))
