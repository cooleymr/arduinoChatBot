import openai
import pyttsx3
import speech_recognition as sr
import serial
import time
import text2emotion as te
import nltk
nltk.download('omw-1.4')



openai.api_key = "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"
#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

engine = pyttsx3.init()

# setting up microphone
r = sr.Recognizer()
mic = sr.Microphone(device_index=1)

# Wait for serial to connect
time.sleep(3)

# Names for bot to use
conversation = ""
user_name = "You"
bot_name = "Holly"

user_input = ""

# connecting to serial port to communicate to Arduino
serial = serial.Serial('COM5')


while user_input != "stop":
    print("Say Holly to begin the recording.....")
    
    # listening for voice
    with mic as source:
        print("mic as source")
        r.adjust_for_ambient_noise(source, duration=1.0)
        audio = r.listen(source)
    
    # getting what user said
    try:
        user_input = r.recognize_google(audio)
    except:
        continue
    
    # printing what the user said
    prompt = user_name + ": " + user_input + "\n" + bot_name+ ": "
    conversation += prompt  # allows for context
    print(prompt)
    
    # fetch response from open AI api
    response = openai.Completion.create(engine='text-davinci-003', prompt=conversation, max_tokens=100)
    response_str = response["choices"][0]["text"].replace("\n", "")
    response_str = response_str.split(user_name + ": ", 1)[0].split(bot_name + ": ", 1)[0]
    
    # response_str = "I LOVE MY LIFE I AM SO HAPPY"
    
    
    # getting emotions represented as list
    # {'Happy': 0.0, 'Angry': 0.0, 'Surprise': 0.0, 'Sad': 0.0, 'Fear': 0.0}
    emotion_list = te.get_emotion(response_str)
    max_emotion = max(emotion_list, key = emotion_list.get)
    # print(emotion_list)
    # print(max_emotion)
    
    # Writing to serial port (to be read by Arduino)
    serial.write(max_emotion[2].encode())
    
    
    # printing Holly's reponse
    conversation += response_str + "\n"
    print(response_str)


    # speak response through speaker
    voice = engine.getProperty('voices')
    engine.setProperty('voice', voice[1].id)
    engine.say(response_str)
    engine.runAndWait()
    
