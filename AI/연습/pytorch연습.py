import torch
#토치 버전 체크
print(torch.__version__)
#초기화 되지 않은 텐서 생성
x = torch.empty(4, 2)
print(x)
#무작위로 초기화된 텐서 생성
x = torch.rand(4, 2)
print(x)
#데이터 타입이 정해진 0으로 채우기
x = torch.zeros(4, 2, dtype=torch.float)
print(x)
#사용자가 입력한 값으로 텐서 초기화
x = torch.tensor([1, 1.0])
print(x)
#2*4, double 타입, 1로 채워진 텐서
x = x.new_ones(2, 4, dtype=torch.double)
print(x)
#x와 같은 크기, float, 무작위로 생성된 텐서
x = torch.randn_like(x, dtype=torch.float)
print(x)
#텐서 크기 계산
print(x.size())
#파이토치의 데이터타입
ft = torch.FloatTensor([1, 2, 3])
print(ft)
print(ft.dtype)
#데이터 타입변환
print(ft.short())
print(ft.int())
print(ft.long())

it = torch.IntTensor([1, 2, 3])
print(it)
print(it.dtype)

print(it.float())
print(it.double())
print(it.half())

x = torch.randn(1)
print(x)
print(x.item())
print(x.dtype)
#CPU, GPU로 텐서 옮기기
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(device)
y = torch.ones_like(x, device=device)
print(y)
x = x.to(device)
print(x)
z = x + y
print(z)
print(z.to('cpu', torch.double))

#0D Tensor(Scalar)
t0 = torch.tensor(0)
print(t0.ndim) #차원정보
print(t0.shape)
print(t0)

#1D Tensor(Vector)
t1 = torch.tensor([1, 2, 3])
print(t1.ndim) #차원정보
print(t1.shape)
print(t1)

#2D Tensor(Matrix)
t2 = torch.tensor([[1, 2, 3],
                  [1, 2, 3],
                  [1, 2, 3]])
print(t2.ndim) #차원정보
print(t2.shape)
print(t2)
print(torch.cuda.is_available())
#3D Tensor
t3 = torch.tensor([[[1, 2, 3],
                    [1, 2, 3],
                    [1, 2, 3]],
                   [[1, 2, 3],
                    [1, 2, 3],
                    [1, 2, 3]],
                   [[1, 2, 3],
                    [1, 2, 3],
                    [1, 2, 3]]])
print(t3.ndim) #차원정보
print(t3.shape)
print(t3)
#4D Tensor
#4개의 축
#컬러 이미지 데이터가 대표적
#주로 샘플, 높이, 너비, 컬러채널을 가진 구조로 사용

#5D Tensor
#5개의 축
#비디오 데이터가 대표적
#주로 샘플, 프라임, 높이, 너비 , 컬러 채널을 가진 구조로 사용

#텐서 연산
import math

a = torch.rand(1, 2) * 2 - 1
print(a)
print(torch.abs(a))
print(torch.ceil(a)) #올림
print(torch.floor(a)) #내림
# print(torch.clamp((a, -0.5, 0.5))) #최소가 -0.5, 최대가 0.5로 바꿔버림(오버하거나 언더)
print(torch.max(a))
print(torch.min(a))
#print(a.max(dim=0)) 0으로 설정하면 전체에서 제일큰 위치 반환, 1로하면 각 텐서에서 하나씩 위치 반환
print(torch.mean(a))
print(torch.std(a))
print(torch.prod(a))
print(torch.unique(torch.tensor([1,2,3,1,2,2])))
#a+b 같은경우 torch.add(a,b)로 표현할 수 있는데 이때 3번째 인자에 out='이름'으로 하면 결과값을 '이름'에 넣어준다
#inplace 방식으로는 y.add_(x)로 표현이 가능한데 _가 붙는 차이점이 있다 이러면 y = y + x와 같다
#빼기는 torch.sub로 사용

x = torch.rand(2, 2)
y = torch.rand(2, 2)

print(x)
print(y)
print(x * y)
print(torch.mul(x, y))

print(x / y)
print(torch.div(x, y))

#dot product
print(torch.matmul(x, y))
z = torch.mm(x, y)
print(z)
#행렬 분해(U,S,V tensor로 분해)
# print(torch.svd(z))

#인덱싱
x = torch.Tensor([[1,2],
                 [3,4]])
print(x)
print(x[0, 0])
print(x[1][1])
print(x[0, 1])
print(x[1, 0])
print(x[1, 1])
print(x[:, 0])
print(x[:, 1]) #모든 행에서 1열
print(x[0, :])
print(x[1, :])

#view는 텐서의 크기나 모양을 변경하는데 사용 단, 기본적으로 변경 전과 후레 텐서 안의 원소 개수가 유지되어야 함 -1로 설정되면 계산을 통해 해당 크기값을 유추(자동으로 설정)
x = torch.randn(4,5)
print(x)
y = x.view(20)
print(y)
z = x.view(5, -1)
print(z)
#item: 텐서에 값이 단 하나라도 존재하면 숫자값을 얻을 수 있음 단, 스칼라 값 하나만 존재해야 item()사용 가능
x = torch.randn(1)
print(x)
print(x.item())

#차원을 축소(제거)
tensor = torch.rand(1,3,3)
print(tensor)
print(tensor.shape)
t=tensor.squeeze()
print(t)
print(t.shape)
#차원을 생성
tensor = torch.rand(3,3)
print(tensor)
print(tensor.shape)
t=tensor.unsqueeze(dim=0)
print(t)
print(t.shape)
#텐서간 결합 (stack)
x = torch.FloatTensor([1,4])
print(x)
y = torch.FloatTensor([2,5])
print(y)
z = torch.FloatTensor([3,6])
print(z)
print(torch.stack([x,y,z]))
#cat : 텐서를 결합하는 메소드
a = torch.rand(1,3,3)
print(a)
b = torch.rand(1,3,3)
print(b)
c = torch.cat((a,b),dim=0) #dim을 이용해 몇차원을 이용할지 선택가능
print(c)
print(c.size())
#chunk : 텐서를 여러개로 나눌 때
tensor = torch.rand(3,6)
print(tensor)
t1,t2,t3 = torch.chunk(tensor,3,dim=1)
print(t1)
print(t2)
print(t3)
#split : chunk와 동일한 기능이지만 다름 chunk는 몇개로 나룰지를 선택하지만 텐서의 크기로 split이 이루어짐
tensor = torch.rand(3,6)
print(tensor)
t1,t2 = torch.split(tensor,3,dim=1)
print(tensor)
print(t1)
print(t2)
#토치에서 넘파이로 변환
import numpy as np
a = torch.ones(7)
print(a)
b = a.numpy()
print(b)
#텐서가 CPU상에 있으면 넘파이 배열은 메모리 공간을 공유하므로 하나가 변하면 다른 하나도 변함
a.add_(1)
print(a)
print(b)

a = np.ones(7)
b = torch.from_numpy(a)
np.add(a,1,out=a)
print(a)
print(b)
