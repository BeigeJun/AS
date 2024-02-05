import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from copy import deepcopy

Iris_csv = pd.read_csv('C:/Users/wns20/PycharmProjects/pythonProject10/DataSet.csv')
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

def normalization(Test):
    Max = 0.0
    Min = 10.0
    for i in range(4):
        for j in range(150):
            compare_Max = max(Test[i])
            compare_Min = min(Test[i])
            if compare_Max > Max:
                Max = compare_Max
            if compare_Min < Min:
                Min = compare_Min
        for j in range(150):
            Test[i][j] = (Test[i][j] - Min) / (Max - Min)
    return Test
#정규화
Iris = normalization(Iris)

while True:
    print("1. 2개 속성")
    print("2. 3개 속성")
    print("3. 4개 속성")
    print("4. 종료")
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
        property_1 = input("첫번째 속성 선택 : ")
        property_2 = input("두번째 속성 선택 : ")
        property_3 = input("세번째 속성 선택 : ")
        property_4 = input("네번째 속성 선택 : ")
    elif(Choose_num == '4'):
        exit()
    else:
        print("잘못된 입력 재입력 하시오")
        continue

    x = Iris[int(property_1) - 1]
    y = Iris[int(property_2) - 1]
    #선택한 속성 복사
    Centroids_x = np.random.uniform(min(x), max(x), k_clusters)
    Centroids_y = np.random.uniform(min(y), max(y), k_clusters)
    #속성에서 제일 큰 값과 작은 값을 뽑아서 그 사이 값으로 3개의 랜덤좌표 생성(중심점)
    if(Choose_num == '1'):
        #속성 2개 선택
        Centroids = list(zip(Centroids_x, Centroids_y))
        #x,y 값을 묶어서 리스트로 변환
        Centroids = np.array(Centroids)
        Centroids_Old = np.zeros(Centroids.shape)
        #변하는 위치를 저장할 변수 생성
        Error = np.ones(k_clusters)
        #데이터와 중심점의 거리 저장(Error가 전부 0 일 때 까지 반복하기 위해 1로 생성)
        Lables = np.zeros(150)
        Input_data_xy = np.array(list(zip(x,y)))
        #좌표에 찍기위해 선택한 속성 리스트로 변환
        plt.scatter(x, y, alpha=0.5)
        plt.scatter(Centroids_x, Centroids_y,alpha=0.5, c='red')
        plt.show()
        #좌표에 점찍기

        while(Error.all() != 0):
            for i in range(150):
                Distance = np.zeros(k_clusters)
                #Distance는 데이터 한 점과 중심점 3개의 거리를 저장해 둘 리스트
                for j in range(k_clusters):
                    Distance[j] = Euclidean_distance(Input_data_xy[i], Centroids[j])
                    #거리 구해서 저장하기
                Lables[i] = Distance.argmin()
                #거리가 제일 짧은 중심점으로 지정하기
            Centroids_Old = deepcopy(Centroids)
            #중심점을 옮기기 전 복사해 두기
            for i in range(k_clusters):
                Points = [Input_data_xy[j] for j in range(len(Input_data_xy)) if Lables[j] == i]
                #리스트 컴프리헨션
                # Points = []
                # for j in range(len(Input_data_xy)):
                #     if Lables[j] == i:
                #         Points.append(Input_data_xy[j])
                Centroids[i] = np.mean(Points, axis=0)
                #배정받은 데이터들의 중심점 계산

            plt.scatter(x, y, c=Lables, alpha=0.5)
            plt.scatter(Centroids_Old[:, 0], Centroids_Old[:, 1], c='blue')
            plt.scatter(Centroids[:, 0], Centroids[:, 1], c='red')
            plt.show()
            #중심점이 움직이기 전 후를 보여주고 3개로 나뉜 데이터를 찍어줌
            for i in range(k_clusters):
                Error[i] = Euclidean_distance(Centroids_Old[i], Centroids[i])
            #Error를 계산함으로써 중심점이 바뀌었는지 확인함 이는 While문의 종료에 간여함
        colors = ['r', 'g', 'b']

        for i in range(k_clusters):
            Points = np.array([Input_data_xy[j] for j in range(len(Input_data_xy)) if Lables[j] == i])
            plt.scatter(Points[:, 0], Points[:, 1], c=colors[i], alpha=0.5)
            print(colors[i], "의 개수는", len(Points[:, 1]))
        #끝이나면 r,g,b의 개수를 출력
        plt.scatter(Centroids[:, 0], Centroids[:, 1], marker='D', s=150)
        plt.show()

    elif(Choose_num == '2'):
        z = Iris[int(property_3) - 1]
        Centroids_z = np.random.uniform(min(z), max(z), k_clusters)
        Centroids = list(zip(Centroids_x, Centroids_y, Centroids_z))
        Centroids = np.array(Centroids)
        Centroids_Old = np.zeros(Centroids.shape)
        Error = np.ones(k_clusters)
        Lables = np.zeros(150)
        Input_data_xyz = list(zip(x, y, z))

        fig = plt.figure()
        ax = fig.add_subplot(projection='3d')
        ax.scatter(x, y, z, alpha=0.5)
        ax.scatter(Centroids_x, Centroids_y, Centroids_z, alpha=0.5, color="red")
        plt.show()

        while(Error.all() != 0):
            for i in range(150):
                Distance = np.zeros(k_clusters)
                for j in range(k_clusters):
                    Distance[j] = Euclidean_distance(Input_data_xyz[i], Centroids[j])
                Lables[i] = Distance.argmin()
            Centroids_Old = deepcopy(Centroids)
            for i in range(k_clusters):
                Points = [Input_data_xyz[j] for j in range(len(Input_data_xyz)) if Lables[j] == i]
                Centroids[i] = np.mean(Points, axis=0)
            fig = plt.figure()
            ax = fig.add_subplot(projection='3d')
            ax.scatter(x, y, z, c=Lables, alpha=0.5)
            ax.scatter(Centroids_Old[:, 0], Centroids_Old[:, 1], Centroids_Old[:, 2], c='blue')
            ax.scatter(Centroids[:, 0], Centroids[:, 1], Centroids[:, 2], c='red')
            plt.show()

            for i in range(k_clusters):
                Error[i] = Euclidean_distance(Centroids_Old[i],Centroids[i])

        colors = ['r', 'g', 'b']
        fig = plt.figure()
        ax = fig.add_subplot(projection='3d')
        for i in range(k_clusters):
            Points = np.array([Input_data_xyz[j] for j in range(len(Input_data_xyz)) if Lables[j] == i])
            ax.scatter(Points[:, 0], Points[:, 1], Points[:, 2], c=colors[i], alpha=0.5)
            print(colors[i], "의 개수는", len(Points[:, 1]))
        # 끝이나면 r,g,b의 개수를 출력
        ax.scatter(Centroids[:, 0], Centroids[:, 1],Centroids[:, 2], marker='D', s=150)
        plt.show()

    elif (Choose_num == '3'):
        z = Iris[int(property_3) - 1]
        s = Iris[int(property_4) - 1]
        Centroids_z = np.random.uniform(min(z), max(z), k_clusters)
        Centroids_s = np.random.uniform(min(s), max(s), k_clusters)
        Centroids = list(zip(Centroids_x, Centroids_y, Centroids_z, Centroids_s))
        Centroids = np.array(Centroids)
        Centroids_Old = np.zeros(Centroids.shape)
        Error = np.ones(k_clusters)
        Lables = np.zeros(150)
        Input_data_xyzs = list(zip(x, y, z, s))


        while(Error.all() != 0):
            for i in range(150):
                Distance = np.zeros(k_clusters)
                for j in range(k_clusters):
                    Distance[j] = Euclidean_distance(Input_data_xyzs[i], Centroids[j])
                Lables[i] = Distance.argmin()
            Centroids_Old = deepcopy(Centroids)
            for i in range(k_clusters):
                Points = [Input_data_xyzs[j] for j in range(len(Input_data_xyzs)) if Lables[j] == i]
                Centroids[i] = np.mean(Points, axis=0)

            for i in range(k_clusters):
                Error[i] = Euclidean_distance(Centroids_Old[i],Centroids[i])

        colors = ['r', 'g', 'b']
        for i in range(k_clusters):
            Points = np.array([Input_data_xyzs[j] for j in range(len(Input_data_xyzs)) if Lables[j] == i])
            print(colors[i], "의 개수는", len(Points[:, 1]))
