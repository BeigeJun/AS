import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from copy import deepcopy

Iris_csv = pd.read_csv('C:/Users/SeoJun/PycharmProjects/pythonProject3/DataSet.csv')
SepalLength = Iris_csv.SepalLength.tolist()
SepalWidth = Iris_csv.SepalWidth.tolist()
PetalLength = Iris_csv.PetalLength.tolist()
PetalWidth = Iris_csv.PetalWidth.tolist()
#아이리스 데이터 가져오기
Iris = []
Iris.append(SepalLength)
Iris.append(SepalWidth)
Iris.append(PetalLength)
Iris.append(PetalWidth)
#Iris라는 리스트로 묶어주기
k_clusters = 3
#군집의 개수는 3개

def Euclidean_distance(a,b):
    return sum([(Point_1 - Point_2) ** 2 for Point_1, Point_2 in zip(a, b)]) ** 0.5
#유클리드 거리 구하는 함수

while True:
    print("1. 2개 속성")
    print("2. 3개 속성")
    print("3. 종료")
    Choose_num = input("옵션 선택 : ")
    print("1.SepalLength")
    print("2.SepalWidth")
    print("3.PetalLength")
    print("4.PetalWidth")
    if(Choose_num == '1'):
        property_1 = input("첫번째 속성 선택 : ")
        property_2 = input("두번째 속성 선택 : ")
    elif(Choose_num == '2'):
        property_1 = input("첫번째 속성 선택 : ")
        property_2 = input("두번째 속성 선택 : ")
        property_3 = input("세번째 속성 선택 : ")
    elif(Choose_num == '3'):
        exit()
    else:
        print("잘못된 입력 재입력 하시오")
        continue

    x = Iris[int(property_1) - 1]
    y = Iris[int(property_2) - 1]
    Centroids_x = np.random.uniform(min(x), max(x), k_clusters)
    Centroids_y = np.random.uniform(min(y), max(y), k_clusters)
    if(Choose_num == '1'):
        Centroids = np.array(list(zip(Centroids_x, Centroids_y)))
        Centroids_Old = np.zeros(Centroids.shape)
        Error = np.zeros(k)
        Lables = np.zeros(150)
        Input_data_xy = np.array(list(zip(x,y)))
        
        for i in range(k):
            Error[i] = Euclidean_distance(Centroids_Old, Centroids)
            print(Centroids[i])
        Trun = 0
        while(Error.all != 0):
            Distance = np.zeros(k)
            for j in range(k):
                Distance[j] = Euclidean_distance(Input_data_xy[i], Centroids[j])
            Cluster = Distance.argmin()
            Lables[i] = Cluster
        Centroids_Old = deepcopy(Centroids)
        
        for i in range(k):
            Points = [Input_data_xy[j] for j in range(len(Input_data_xy)) if Lables[j] == i]
            Centroids[i] = np.mean(Points, axis=0)
        
        
        plt.scatter(Centroids_x, Centroids_y, s = 50, c = 'red')
        #랜덤위치 3개 찍기
        plt.scatter(x, y , alpha=0.5, s = 50)
        #데이터 찍기
        plt.show()











    elif(Choose_num == '2'):
        z = Iris[int(property_3) - 1]
        Centroids_z = np.random.uniform(min(z), max(z), k_clusters)
        print(z)
        print(x)
        print(y)
        Centroids = list(zip(Centroids_x, Centroids_y, Centroids_z))

        fig = plt.figure()
        ax = fig.add_subplot(111,projection='3d')
        ax.scatter(x, y, z, alpha=0.5)
        plt.show()
