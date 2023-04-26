import openai
import pyttsx3
import speech_recognition as sr
import serial
import time


openai.api_key = "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"

engine = pyttsx3.init()

r = sr.Recognizer()
mic = sr.Microphone(device_index=1)

# ser = serial.Serial('COM3', 9600)

# Wait for serial to connect
time.sleep(3)


# Names for bot to use
conversation = ""
user_name = "You"
bot_name = "Holly"

expressions = {
    "happy": ["great", "awesome", "fantastic"],
    "sad": ["terrible", "awful", "not good"]
}

user_input = ""

# connecting to serial port to communicate to Arduino
s = serial.Serial('COM3')


while user_input != "stop":
    print("Say Holly to begin the recording.....")
    
    # listening for voice
    with mic as source:
        r.adjust_for_ambient_noise(source, duration=1.0)
        audio = r.listen(source)
    #print("no longer listening.\n")
    try:
        user_input = r.recognize_google(audio)
    except:
        continue
    
    if user_input == "Holly test":
        s.write("t".encode())
        # s.write("t")
        print("sending serial test")
    
    # printing what the user said
    prompt = user_name + ": " + user_input + "\n" + bot_name+ ": "
    conversation += prompt  # allows for context
    print(prompt)

    # fetch response from open AI api
    response = openai.Completion.create(engine='text-davinci-003', prompt=conversation, max_tokens=100)
    response_str = response["choices"][0]["text"].replace("\n", "")
    response_str = response_str.split(user_name + ": ", 1)[0].split(bot_name + ": ", 1)[0]
    
    # printing Holly's reponse
    conversation += response_str + "\n"
    print(response_str)
    # ser.

    # determine appropriate expression based on response
    expression = "neutral"
    for exp, phrases in expressions.items():
        if any(phrase in response_str for phrase in phrases):
            expression = exp
            break

    # speak response through speaker
    voice = engine.getProperty('voices')
    engine.setProperty('voice', voice[1].id)
    engine.say(response_str)
    engine.runAndWait()
    
    # send expression to Arduino over serial
    # ser.write(expression.encode())
    
    
    
    
    
    
    