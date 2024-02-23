# -*- coding:utf-8 -*-
import urllib3
import json
import base64
import pyaudio
import wave
import keyboard
import csv
accessKey = 

class Queue:
    def __init__(self):
        self.queue = []
    def enqueue(self, string):
        self.queue.append(string)
    def dequeue(self):
        if len(self.queue) == 0:
            return None
        return self.queue.pop(0)
    def size(self):
        return len(self.queue)
def recording():
    FORMAT = pyaudio.paInt16
    CHANNELS = 1  # 단일 채널(모노)
    RATE = 16000  # 샘플링 레이트 (16kHz)
    CHUNK = 1024  # 버퍼 크기
    RECORD_SECONDS = 5  # 녹음 시간 (초)
    WAVE_OUTPUT_FILENAME = "output.wav"
    # PyAudio 객체 생성
    audio = pyaudio.PyAudio()
    stream = audio.open(format=FORMAT,
                        channels=CHANNELS,
                        rate=RATE,
                        input=True,
                        frames_per_buffer=CHUNK)
    Keyboard_flag = False
    frames = []
    keyboard.wait('space')
    print("Start")
    Keyboard_flag = True
    while Keyboard_flag == True:
        if keyboard.is_pressed('space'):
            Keyboard_flag = True
        else:
            Keyboard_flag = False
        data = stream.read(CHUNK)
        frames.append(data)
        print("Recording")

    print("End")
    stream.stop_stream()
    stream.close()
    audio.terminate()

    with wave.open(WAVE_OUTPUT_FILENAME, 'wb') as wf:
        wf.setnchannels(CHANNELS)
        wf.setsampwidth(audio.get_sample_size(FORMAT))
        wf.setframerate(RATE)
        wf.writeframes(b''.join(frames))

def transform(accessKey):
    openApiURL = "http://aiopen.etri.re.kr:8000/WiseASR/Recognition"
    audioFilePath = "C:/Users/wns20/PycharmProjects/음성인식/output.wav"
    languageCode = "korean"

    file = open(audioFilePath, "rb")
    audioContents = base64.b64encode(file.read()).decode("utf8")
    file.close()

    requestJson = {
        "argument": {
            "language_code": languageCode,
            "audio": audioContents
        }
    }

    http = urllib3.PoolManager()
    response = http.request(
        "POST",
        openApiURL,
        headers={"Content-Type": "application/json; charset=UTF-8", "Authorization": accessKey},
        body=json.dumps(requestJson)
    )
    parsed_data = json.loads(response.data)
    recognized_text = parsed_data['return_object']['recognized']
    recognized_text = recognized_text.replace(" "," ")
    slice_ = len(recognized_text) - 1
    text = recognized_text[:]
    print(text)
    return text
# flag = False
# f = open('C:/Users/SeoJun/PycharmProjects/음성인식/아이스크림.csv', 'r', encoding='cp949')
# rdr = csv.reader(f)
# read = rdr
# for line in rdr:
#     print(line)
#     if(str(icecream_name) == line[0]):
#         print("이름 : ", line[0], "가격 : ", line[1], "수량 : ", line[2])
#         flag = True
# if(flag == False):
#     print("없는 아이스크림")
# f.close()
# print(rdr)
def split(accessKey, text):
    openApiURL = "http://aiopen.etri.re.kr:8000/WiseNLU_spoken"
    analysisCode = "morp"

    requestJson = {
        "argument": {
            "text": text,
            "analysis_code": analysisCode
        }
    }

    http = urllib3.PoolManager()
    response = http.request(
        "POST",
        openApiURL,
        headers={"Content-Type": "application/json; charset=UTF-8", "Authorization": accessKey},
        body=json.dumps(requestJson)
    )

    print("[responseCode] " + str(response.status))
    print("[responBody]")
    print(str(response.data, "utf-8"))
    data = response.data

    data = json.loads(data)
    for sentence_info in data["return_object"]["sentence"]:
        for morpheme in sentence_info["morp"]:
            if morpheme["type"] == "NNG" or morpheme["type"] == "NNP":
                Icecream_name.enqueue(morpheme["lemma"])
    sentence_info = data["return_object"]["sentence"]
    for word_info in sentence_info:
        for morpheme in word_info["morp"]:
            if morpheme["type"] == "MM" or morpheme["type"] == "NR":
                Icecream_count.enqueue(morpheme["lemma"])

Icecream_name = Queue()
Icecream_count = Queue()
recording()
text = transform(accessKey)
split(accessKey, text)
for i in range(Icecream_name.size()):
    name = Icecream_name.dequeue()
    print(name)
for i in range(Icecream_count.size()):
    name = Icecream_count.dequeue()
    print(name)
