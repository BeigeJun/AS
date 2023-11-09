import numpy as np
num = 10
tall = [150,156,163,165,168,170,182,183,187,189]
weight = [35,45,50,54,70,63,75,77,85,90]
for i in range(10):
    tall[i] = tall[i]/200
    weight[i] = weight[i]/100
Y = np.array(tall)
X = np.array(weight)
print(X)
print(Y)
w1,w2,b = 0,0,0
def setwb(wt1,wt2,bt):
    global w1,w2,b
    w1,w2,b = wt1,wt2,bt

def discriminate(x1,x2):
    if(w1*x1+w2*x2+b<=0):
        return 0
    else:
        return 1

def test(ds,wt1,wt2,bt):
    setwb(wt1,wt2,bt)
    ok,total=0,0
    for x1,x2,y in ds:
        if(discriminate(x1,x2)==y):
            ok+=1
        total+=1
        print(total)
    return ok/total

def myr(s,e,st):   #range와 같은 목적, step이 실수
    r=s
    while(r<e):
        yield r
        r+=st
def find_wb(ds): #기계 학습
    for wt1 in myr(0,1,0.1):
        for wt2 in myr(0,1,0.1):
            for bt in myr(-1,1,0.1):
                if(test(ds,wt1,wt2,bt)==1.0):
                    return True
    return False

ds_and = [[0,0,0],[0,1,0],[1,0,0],[1,1,1]]
ds_or = [[0,0,0],[0,1,1],[1,0,0],[1,1,1]]
ds_xor = [[0,0,0],[0,1,1],[1,0,0],[1,1,0]]


if find_wb(ds_and):
    print("w1:{0:.1f} w2:{1:.1f} b:{2:.1f} ## and".format(w1,w2,b))
else:
    print("not founded ## and")

if find_wb(ds_or):
    print("w1:{0:.1f} w2:{1:.1f} b:{2:.1f} ## or".format(w1,w2,b))
else:
    print("not founded ## or")

if find_wb(ds_xor):
    print("w1:{0:.1f} w2:{1:.1f} b:{2:.1f} ## xor".format(w1,w2,b))
else:
    print("not founded ## xor")
