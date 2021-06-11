#!/usr/bin/python3
import serial
import pygame
from pygame.locals import *
arduino = serial.Serial('/dev/ttyACM0', 9600)
pygame.mixer.init(frequency=44100, size=-16, channels=1, buffer=1024)
pygame.mixer.set_num_channels(40)
pygame.display.set_mode()
sounds=[]
def checkArduino():
    dane = arduino.readline().strip() #the last bit gets rid of the new-line chars
    if dane:
            return int(dane)
    else:
            return 0
def chooseSong(x):
    temp=0
    if x>=100 and x<=115:
        temp=x-100
    elif x>=200 and x<=215:
        temp=x-200+16
    elif x>=300 and x<315:
        temp=x-300+32
    return temp
for x in range(43):
    if x<10:
        str="Sounds/Harfa000{}.wav".format(x)
        sounds.append(pygame.mixer.Sound(str))
    else:
        str="Sounds/Harfa00{}.wav".format(x)
        sounds.append(pygame.mixer.Sound(str))
x=0
while x==0:
        try:
            struna=checkArduino()
        except:
            struna=0
        if struna>=100:
            print(struna)
            try:
                sounds[chooseSong(struna)].play()
            except IndexError:
                print("String do not exist")
            
        for event in pygame.event.get():
            if event.type== pygame.KEYDOWN:
                if event.key==pygame.K_ESCAPE:
                    pygame.quit()
                    x=1
