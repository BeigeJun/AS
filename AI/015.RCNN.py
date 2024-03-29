import selectivesearch
import cv2
import matplotlib.pyplot as plt
import os
import shutil

directory_path = 'C:/Users/SeoJun/PycharmProjects/capstone/data'
shutil.rmtree(directory_path)
os.makedirs(directory_path)

image_path = '1.jpeg'
img = cv2.imread(image_path)
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

_, regions = selectivesearch.selective_search(img_rgb, scale=750, min_size=1000)

cand_rects = [cand['rect'] for cand in regions if cand['size'] > 10000]
green_rgb = (125, 255, 51)
img_rgb_copy = img_rgb.copy()
num = 0
for rect in cand_rects:
    left = rect[0]
    top = rect[1]
    right = left + rect[2]
    bottom = top + rect[3]

    cropped_image = img[top:bottom, left:right]
    name = os.path.join(directory_path, 'cropped_image' + str(num) + '.jpg')
    cv2.imwrite(name, cropped_image)
    num += 1
    img_rgb_copy = cv2.rectangle(img_rgb_copy, (left, top), (right, bottom), color=green_rgb, thickness=5)

plt.figure(figsize=(8, 8))
plt.imshow(img_rgb_copy)
plt.show()
