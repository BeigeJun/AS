# -*- coding:utf-8 -*-
import urllib3
import json
import base64
import pyaudio
import wave
import keyboard
import csv
import numpy as np
accessKey = 
key = "C:/Users/SeoJun/PycharmProjects/음성인식/"
num_dic = {"하나": 1, "두": 2, "세": 3, "네": 4, "다섯": 5, "여섯": 6, "일곱": 7, "여덜": 8, "아홉": 9, "열": 10,
           "일": 1, "이": 2, "삼": 3, "사": 4, "오": 5, "육": 6, "칠": 7, "팔": 8, "구": 9, "십": 10,
           "한": 1}
CHOSUNG_LIST = ['ㄱ', 'ㄲ', 'ㄴ', 'ㄷ', 'ㄸ', 'ㄹ', 'ㅁ', 'ㅂ', 'ㅃ', 'ㅅ', 'ㅆ', 'ㅇ', 'ㅈ', 'ㅉ', 'ㅊ', 'ㅋ', 'ㅌ', 'ㅍ', 'ㅎ']
JUNGSUNG_LIST = ['ㅏ', 'ㅐ', 'ㅑ', 'ㅒ', 'ㅓ', 'ㅔ', 'ㅕ', 'ㅖ', 'ㅗ', 'ㅘ', 'ㅙ', 'ㅚ', 'ㅛ', 'ㅜ', 'ㅝ', 'ㅞ', 'ㅟ', 'ㅠ', 'ㅡ', 'ㅢ',
                 'ㅣ']
JONGSUNG_LIST = [' ', 'ㄱ', 'ㄲ', 'ㄳ', 'ㄴ', 'ㄵ', 'ㄶ', 'ㄷ', 'ㄹ', 'ㄺ', 'ㄻ', 'ㄼ', 'ㄽ', 'ㄾ', 'ㄿ', 'ㅀ', 'ㅁ', 'ㅂ', 'ㅄ', 'ㅅ',
                 'ㅆ', 'ㅇ', 'ㅈ', 'ㅊ', 'ㅋ', 'ㅌ', 'ㅍ', 'ㅎ']
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
    def Clear(self):
        for i in range(len(self.queue)):
            self.queue.pop(0)
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
    keyboard.wait('shift')
    print("Recording")
    Keyboard_flag = True
    while Keyboard_flag == True:
        if keyboard.is_pressed('shift'):
            Keyboard_flag = True
        else:
            Keyboard_flag = False
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

def transform(accessKey,key):
    openApiURL = "http://aiopen.etri.re.kr:8000/WiseASR/Recognition"
    audioFilePath =key + "output.wav"
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
    text = parsed_data['return_object']['recognized']
    # print(text)
    return text

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

    # print("[responseCode] " + str(response.status))
    # print("[responBody]")
    # print(str(response.data, "utf-8"))
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
def text_to_number(txt , dic):
    if txt in dic:
        return dic[txt]
    else:
        return "없는값"

def List_save(key):
    file_path = key + '아이스크림.csv'
    with open(file_path, 'r', encoding='cp949') as f:
        rdr = csv.reader(f)
        rows = list(rdr)
    return rows
def Find_object(name, rows, count_Q,key):
    flag = False
    file_path = key + '아이스크림.csv'
    with open(file_path, 'w', newline='', encoding='cp949') as f:
        writer = csv.writer(f)
        for line in rows:
            if str(name) == line[0]:
                # print("이름 : ", line[0], "가격 : ", line[1], "수량 : ", line[2])
                flag = True
                cnt = count_Q.dequeue()
                number = int(line[2])
                count = text_to_number(cnt, num_dic)
                if number >= count:
                    line[2] = str(number - count)
                    print("선택하신 아이스크림 : ", line[0], "갯수 : ", count, "가격 : ",int(line[1])*count)
                else:
                    print("재고가 선택하신 수량보다 적습니다.")
                    continue
            writer.writerow(line)

        if not flag:
            Icecream_hold_name.enqueue(name)
            cnt = Icecream_count.dequeue()
            Icecream_hold_count.enqueue(cnt)

def korean_decomposition(korean_word):
    reselt = []
    for w in list(korean_word.strip()):
        ch1 = (ord(w) - ord('가')) // 588
        ch2 = ((ord(w) - ord('가')) - (588 * ch1)) // 28
        ch3 = (ord(w) - ord('가')) - (588 * ch1) - 28 * ch2
        reselt.append([CHOSUNG_LIST[ch1], JUNGSUNG_LIST[ch2], JONGSUNG_LIST[ch3]])
    return reselt

def Korean_compare(word1, word2):
    word1 = np.array(word1)
    word2 = np.array(word2)
    if(word1.shape == word2.shape):
        total = 0
        total_same = 0
        for i in range(len(word1)):
            for j in range(len(word1[i])):
                if(word1[i][j] == word2[i][j]):
                    total_same = total_same + 1
                total = total + 1
        return total_same / total
    else:
        return 0
Icecream_name = Queue()
Icecream_count = Queue()
Icecream_hold_name = Queue()
Icecream_hold_count = Queue()
while True:
    Icecream_name.Clear()
    Icecream_count.Clear()
    Icecream_hold_name.Clear()
    Icecream_count.Clear()
    print("shift를 누르면 녹음 됩니다.")
    recording()
    text = transform(accessKey, key)
    split(accessKey, text)
    List = List_save(key)
    if(Icecream_name.size() == Icecream_count.size()):
        # print("정상적인 이름 찾기")
        for i in range(Icecream_name.size()):
            name = Icecream_name.dequeue()
            Find_object(name, List, Icecream_count,key)
        # print("------------------------")
        # print("아이스크림 이름들만 뽑아서 리스트 만들기")
        List_names = []
        for i in range(len(List)):
            List_names.append(List[i][0])
        # print(List_names)
        # print("------------------------")
        # print("뽑아온 리스트들 분해하기")
        List_names_split = []
        splited_List = []
        for i in range(len(List_names)):
            split_reselt = korean_decomposition(List_names[i])
            splited_List.append(split_reselt)
        # print(splited_List)
        # print("---------------------------")
        # print("홀드 큐 갯수 :",Icecream_hold_name.size())
        # print("매칭 안된 이름들 뽑아서 가장 비슷한 아이스크림 이름 출력")
        for i in range(Icecream_hold_name.size()):
            name = Icecream_hold_name.dequeue()
            Icecream_ = korean_decomposition(name)
            Max_rate = 0
            Max_rate_num = 0
            for j in range(len(splited_List)):
                rate = Korean_compare(Icecream_, splited_List[j])
                # print(rate)
                if(rate > Max_rate):
                    Max_rate = rate
                    Max_rate_num = j
            Icecream_hold_name.enqueue(List_names[Max_rate_num])
            # print("찾은 이름 :",List_names[Max_rate_num])
        # print("---------------------------")
        # print("찾은 이름으로 다시 검색하기")
        for i in range(Icecream_hold_name.size()):
            name = Icecream_hold_name.dequeue()
            Find_object(name, List, Icecream_hold_count)
        # print("---------------------------")
    else:
        print("다시 시도해 주세요!")
