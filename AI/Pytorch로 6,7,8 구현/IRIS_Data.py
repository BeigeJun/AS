import torch.nn as nn
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
import torch
from torch.utils.data import DataLoader, TensorDataset

iris = load_iris()
X, y = iris.data, iris.target

X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=0.2, random_state=42)

X_train_tensor = torch.tensor(X_train, dtype=torch.float32)
y_train_tensor = torch.tensor(y_train, dtype=torch.long)
X_val_tensor = torch.tensor(X_val, dtype=torch.float32)
y_val_tensor = torch.tensor(y_val, dtype=torch.long)

train_dataset = TensorDataset(X_train_tensor, y_train_tensor)
train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
val_dataset = TensorDataset(X_val_tensor, y_val_tensor)
val_loader = DataLoader(val_dataset, batch_size=32, shuffle=False)

Model = nn.Sequential(
          nn.Linear(4, 7, bias=True),
          nn.Sigmoid(),
          nn.Linear(7, 5, bias=True),
          nn.Sigmoid(),
          nn.Linear(5, 3, bias=True),
          nn.Sigmoid())

criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(Model.parameters(), lr=0.1)
for epoch in range(100001):
    for inputs, labels in train_loader:
        optimizer.zero_grad()
        outputs = Model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

    if epoch % 100 == 0:
        print(epoch, loss.item())
Reselt = Model(X_val_tensor)
Max = torch.argmax(Reselt, dim=1) + 1
print('출력값: ', Max.numpy())
