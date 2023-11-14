import numpy as np
num = 10
#y = 100*np.random.rand(10,1) #()안에 인자값은x,y하고 했을 때 x는 배열을 총 몇개, y눈 배열당 몇개
#Y = np.random.randint(150,190,size = num) #()안에 인자값은x,y하고 했을 때 x는 배열을 총 몇개, y눈 배열당 몇개
#X = np.random.randint(50,100,size = num)
tall = [150,156,163,165,168,170,182,183,187,189]
weight = [35,45,50,54,70,63,75,77,85,90]
X = np.array(tall)
Y = np.array(weight)

from matplotlib.patches import Polygon
from pylab import plt,mpl
plt.style.use('seaborn')
mpl.rcParams['font.family'] = 'serif'
X_mean = X.mean()
Y_mean = Y.mean() #넘파이 평균구하기
print(X_mean)
print(Y_mean)
Plus_all_up = 0
Plus_all_down = 0;
for i in range(num):
    Plus_all_up += (int(X[i])-int(X_mean))*(int(Y[i])-int(Y_mean))
    Plus_all_down += (X[i]-X_mean)**2
Inc = Plus_all_up/Plus_all_down
B_julpeun = Y.mean() - Inc * X.mean()
fig, ax = plt.subplots(figsize=(5,10))
# 자신이 그림의 크기를 지정할 때 사용한다. plt.subplots는 그림과 축 객체를 생성한다 그리고 fig, ax는 함수가 반환하는 걸 fig, ax에 할당함
#마지막 사이즈는 가로 10 세로 인치 크기로 그림을 생성하겠다는 말이다
# 그리기
plt.scatter(X,Y) #산점도 생성(점그림)
y = Inc*X+B_julpeun
plt.plot(X, y, label=f'y = {Inc}x + {B_julpeun}', color='blue')
plt.yticks(np.arange(30,100,10))
plt.xticks(np.arange(150,200,10))
plt.show()

Tall = int(input("키 : "))
y = Inc*Tall+B_julpeun
print(y)
