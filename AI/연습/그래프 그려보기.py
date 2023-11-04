from matplotlib import pyplot as plt  #from A impot B 는 A에서 B기능만 가져온다는말
import numpy as np        #as는 줄임말  넘파이는 파이썬의 고성능 수치계산을 위한 라이브러리

x = np.arange(1,10) #arnage를통해 배열생성
#x=np.array([0,1,2])이런식으로 생성하는 방법이 기본이다.
#a = np.zeros(2) 이렇게하면 0두개의 배열이 생성된다.
#a = np.ones(10) 이렇게 하면 1이 10개인 배열이 생성된다.
#np.ones(10,dtype=np.int64)기본 생성인자는 float이지만 2번째 인자를 주어서 변경가능하다.
# 행렬곱은 @을 사용한다.
y = x*5

plt.plot(x,y,'ro') #.plot = 기본 그래프그리기 첫번째 인자는 x 두번째 인자는 y
#3번째 인자값도 존재한다. 3번째는 문자열을 넣는 방식인데 'ro'를 추가하면 빨간색의 원형 마커를 의미 여러가지종류가 있다.
plt.show() #화면에 그래프 표시하기
