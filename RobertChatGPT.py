
import openai
import pyttsx3
import speech_recognition as sr



openai.api_key = "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"
engine = pyttsx3.init()
r = sr.Recognizer()
mic = sr.Microphone(device_index=1)

conversation = ""
user_name = "You"
bot_name = "Holly"

while True:
    print("Say Holly to begin the recording.....")
    with mic as source:
        #print("\nlistening...")
        r.adjust_for_ambient_noise(source, duration=1.0)
        audio = r.listen(source)
    #print("no longer listening.\n")

    try:
        user_input = r.recognize_google(audio)
    except:
        continue

    prompt = user_name + ": " + user_input + "\n" + bot_name+ ": "

    conversation += prompt  # allows for context
    print(prompt)

    # fetch response from open AI api
    response = openai.Completion.create(engine='text-davinci-003', prompt=conversation, max_tokens=100)
    response_str = response["choices"][0]["text"].replace("\n", "")
    response_str = response_str.split(user_name + ": ", 1)[0].split(bot_name + ": ", 1)[0]

    conversation += response_str + "\n"
    print(response_str)

    
    voice = engine.getProperty('voices')
    engine.setProperty('voi..ce', voice[1].id)
    engine.say(response_str)
    engine.runAndWait()