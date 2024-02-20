# -*- coding:utf-8 -*-
import urllib3
import json
import base64
import pyaudio
import wave
import csv

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
print("Start")
frames = []

# 녹음 데이터 수집
for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
    data = stream.read(CHUNK)
    frames.append(data)

print("End")

stream.stop_stream()
stream.close()
audio.terminate()

with wave.open(WAVE_OUTPUT_FILENAME, 'wb') as wf:
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(audio.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(frames))

openApiURL = "http://aiopen.etri.re.kr:8000/WiseASR/Recognition"
accessKey = 
audioFilePath = "C:/Users/SeoJun/PycharmProjects/음성인식/output.wav"
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
recognized_text = recognized_text.replace(" ","")
slice_ = len(recognized_text) - 1
icecream_name = recognized_text[:slice_]
print(icecream_name)
flag = False
f = open('C:/Users/SeoJun/PycharmProjects/음성인식/아이스크림.csv', 'r', encoding='cp949')
rdr = csv.reader(f)
for line in rdr:
    if(str(icecream_name) == line[0]):
        print("이름 : ", line[0], "가격 : ", line[1], "수량 : ", line[2])
        flag = True
if(flag == False):
    print("없는 아이스크림")
f.close()
