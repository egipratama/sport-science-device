import RPi.GPIO as GPIO
from time import sleep
import requests
import json

GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.IN) #pin sensor
GPIO.setup(17, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(27, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(22, GPIO.OUT, initial=GPIO.LOW)

data = 0
idDevice = "001" #id alat
track = "1" # lintasan satu
gate = "A"

def led(color):
        if color == "R":
                GPIO.output(17, GPIO.HIGH)
                GPIO.output(27, GPIO.LOW)
                GPIO.output(22, GPIO.LOW)
        elif color == "G":
                GPIO.output(17, GPIO.LOW)
                GPIO.output(27, GPIO.HIGH)
                GPIO.output(22, GPIO.LOW)
        elif color == "B":
                GPIO.output(17, GPIO.LOW)
                GPIO.output(27, GPIO.LOW)
                GPIO.output(22, GPIO.HIGH)
        else:
                GPIO.output(17, GPIO.LOW)
                GPIO.output(27, GPIO.LOW)
                GPIO.output(22, GPIO.LOW)

urlKalibrasi = "https://us-central1-unikom-sport-science.cloudfunctions.net/kalibrasi?id=" + idDevice
res = requests.get(urlKalibrasi)
resEncode = json.loads(res.text)
kalibrasi = resEncode["kalibrasi"]["track_1_kalibrasi"]
sleep(5)
if kalibrasi == True:
        while True:
                if GPIO.input(25) == 0:
                        led("R")
                else:
                        led("B")

try:
        while True:
                led("G")
                if not GPIO.input(25): #jika sensor low
                        led("B")
                        sleep(0.5)
                        led("C")
                        data = data + 1
                        url = "https://us-central1-unikom-sport-science.cloudfunc$
                        r = requests.get(url)
                        print(r.text)
                        sleep(5)
                sleep(0.01)
finally:
    GPIO.cleanup()
