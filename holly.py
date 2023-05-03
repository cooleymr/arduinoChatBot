import openai
import pyttsx3
import speech_recognition as sr
import serial
import time
import text2emotion as te
import nltk
nltk.download('omw-1.4')

openai.api_key = "sk-"

engine = pyttsx3.init()

# setting up microphone
r = sr.Recognizer()
mic = sr.Microphone(device_index=1)

# Wait for serial to connect
time.sleep(3)

# Names for bot to use
conversation = "You are a chatbot named Holly coded in Python and displaying facial features through an lED screen connected to an Arduino. You are designed to have conversation and respond in a way that would show a range of emotions on the led screen. Everything after this sentence is the conversation starting here: "
user_name = "You"
bot_name = "Holly"

user_input = ""

# connecting to serial port to communicate to Arduino
serial = serial.Serial('COM5', baudrate = 9600, write_timeout=0)


while user_input != "stop":
    print("\nHolly is listening.....")
    
    # getting user voice input
    with mic as source:
        audio = r.listen(source, phrase_time_limit = 8)  
    try:
        user_input = r.recognize_google(audio).lower()
    except sr.UnknownValueError:
        print("Sorry, I couldn't understand you, can you please say it again")
    
    # printing what the user said
    prompt = user_name + ": " + user_input + "\n" + bot_name+ ": "
    conversation += prompt  # allows for context
    print(prompt)
    
    # fetch response from open AI api
    response = openai.Completion.create(engine='text-davinci-002', prompt=conversation, max_tokens=100)
    response_str = response["choices"][0]["text"].replace("\n", "")
    response_str = response_str.split(user_name + ": ", 1)[0].split(bot_name + ": ", 1)[0]
    
    
    # getting emotions represented as list
    # {'Happy': 0.0, 'Angry': 0.0, 'Surprise': 0.0, 'Sad': 0.0, 'Fear': 0.0}
    emotion_list = te.get_emotion(response_str)
    # print(emotion_list)
    max_emotion = max(emotion_list, key = emotion_list.get)
    # print(emotion_list)
    # print(max_emotion)
    
    
    # printing Holly's reponse
    conversation += response_str + "\n"
    print(response_str)


    # speak response through speaker
    voice = engine.getProperty('voices')
    engine.setProperty('voice', voice[1].id)
    engine.say(response_str)
    # start talking
    serial.write('z'.encode())
    serial.flush()
    
    # writing emotion to serial port
    serial.write(max_emotion[2].encode())
    serial.flush()

    # running voice to speakers
    engine.runAndWait()
    
    
    # sending stop talking signal
    serial.write('x'.encode())
    serial.flush()
    user_input = ""
    
    
    
