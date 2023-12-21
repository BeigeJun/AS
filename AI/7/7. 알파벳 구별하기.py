import numpy as np
import random
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def sigmoid(data):
    return 1.0 / (1.0 + np.exp(-data))

target = [[1.0,0.0,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]]

input = [[1.0,1.0,1.0,1.0,1.0,
          0.1,0.1,1.0,0.1,0.1,
          0.1,0.1,1.0,0.1,0.1,      #T
          0.1,0.1,1.0,0.1,0.1,
          0.1,0.1,1.0,0.1,0.1,],
         [1.0,1.0,1.0,1.0,1.0,
          1.0,0.1,0.1,0.1,0.1,
          1.0,1.0,1.0,1.0,1.0,       #E
          1.0,0.1,0.1,0.1,0.1,
          1.0,1.0,1.0,1.0,1.0],
         [1.0,0.1,0.1,0.1,1.0,
          1.0,0.1,0.1,0.1,1.0,
          1.0,1.0,1.0,1.0,1.0,      #H
          1.0,0.1,0.1,0.1,1.0,
          1.0,0.1,0.1,0.1,1.0]]
        #0.0으로 안하는 이유는 가중치 업데이트가 안되기 때문이다.
hid1_no = 7 #은닉층 1번째 7개
hid2_no = 15 #은닉층 2번쩨 15개
weight_out_to_hid1 = np.zeros((3,7))
weight_hid1_to_hid2 = np.zeros((7,15))
weight_hid2_to_in = np.zeros((15,25))
print(weight_out_to_hid1)
print(weight_hid1_to_hid2)
print(weight_hid2_to_in)

target = [[1.0, 0.0, 0.0],[0.0, 1.0, 0.0],[0.0, 0.0, 1.0]]
output = [0.0, 0.0, 0.0]
bias = 1.0
error = 0.0
total_error = 0.0
lrate = 0.01
epochs = 1000000
