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
