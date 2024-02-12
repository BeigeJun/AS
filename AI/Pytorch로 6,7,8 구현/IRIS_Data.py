import torch.nn as nn
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
import torch

iris = load_iris()
X = iris.data
y = iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1)

X_train_tensor = torch.tensor(X_train, dtype=torch.float32)
y_train_tensor = torch.tensor(y_train, dtype=torch.long)
X_test_tensor = torch.tensor(X_test, dtype=torch.float32)
y_test_tensor = torch.tensor(y_test, dtype=torch.long)

class IrisNet(torch.nn.Module):
    def __init__(self):
        super(IrisNet, self).__init__()
        self.fc1 = torch.nn.Linear(4, 7)
        self.fc2 = torch.nn.Linear(7, 3)

    def forward(self, x):
        x = torch.sigmoid(self.fc1(x))
        x = self.fc2(x)
        return x

Model = IrisNet()

criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(Model.parameters(), lr=0.01)
for epoch in range(1001):
    for i in range(len(X_train_tensor)):
        optimizer.zero_grad()
        outputs = Model(X_train_tensor[i])
        loss = criterion(outputs, y_train_tensor[i])
        loss.backward()
        optimizer.step()

    if epoch % 10 == 0:
        print(epoch, loss.item())

Reselt = Model(X_test_tensor)
Max = torch.argmax(Reselt, dim=1)
print('출력값: ', Max.numpy())
print('실제값: ', y_test_tensor.numpy())
