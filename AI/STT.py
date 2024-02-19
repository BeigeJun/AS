# -*- coding:utf-8 -*-
import urllib3
import json
import base64
import pyaudio
import wave

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

print("[responseCode] " + str(response.status))
print("[responBody]")
print(str(response.data, "utf-8"))
