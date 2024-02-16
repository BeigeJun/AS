import numpy as np

time = [1020, 1034, 1040, 1060, 1050]
day = [1,2,3,4,5]
num = 5

Y = np.array(time)
X = np.array(day)

from matplotlib.patches import Polygon
from pylab import plt,mpl
plt.style.use('seaborn')
mpl.rcParams['font.family'] = 'serif'
X_mean = X.mean()
Y_mean = Y.mean() #넘파이 평균구하기
print(X_mean)
print(Y_mean)
Plus_all_up = 0
Plus_all_down = 0
for i in range(num):
    Plus_all_up += (int(X[i])-int(X_mean))*(int(Y[i])-int(Y_mean))
    Plus_all_down += (X[i]-X_mean)**2
Inc = Plus_all_up/Plus_all_down
B_julpeun = Y.mean() - Inc * X.mean()
fig, ax = plt.subplots(figsize=(5,5))
# 자신이 그림의 크기를 지정할 때 사용한다. plt.subplots는 그림과 축 객체를 생성한다 그리고 fig, ax는 함수가 반환하는 걸 fig, ax에 할당함
#마지막 사이즈는 가로 10 세로 인치 크기로 그림을 생성하겠다는 말이다
# 그리기
plt.scatter(X,Y) #산점도 생성(점그림)
y = Inc*X+B_julpeun
plt.plot(X, y, label=f'y = {Inc}x + {B_julpeun}', color='blue')
plt.yticks(np.arange(1000,1100,10))
plt.xticks(np.arange(0,10,1))
plt.show()

Tall = int(input("날짜 : "))
y = Inc*Tall+B_julpeun
hour = y/60
time = y%60
print(int(hour),":",int(time))
