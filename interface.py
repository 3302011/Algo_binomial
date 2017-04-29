from tkinter import *
import subprocess as sp
from easygui import *
import os
import sys



msgbox("Bonjour et bienvenue dans l'interface d'algorithmique crée par Fatine BENTIRES! Pour voir la suite du programme appuyez sur ok.")


choices=["Lire la documentation","Lancer le filtre de bloom","Lancer le tas binomial","Exit"]
reply=buttonbox(image="pho.gif",msg="Que voulez vous faire?",title="On se décide !",choices=choices)

os.system('make') #lance le makefile

if reply==choices[0]:
    os.system('open Rapport_bentires.pdf')
    choix=["Oui","Exit"]
    reponse=choicebox("On va quand même pas s'arrêter là... on lance le programme?",choices=choix)
    ok=["Thanks","I don't care what you think"]
    buttonbox(image="giphy.gif",msg="Merci, là tu me fais plaisir !! ",choices=ok)


    if reponse==choix[0]:
        cho=["Filtre de bloom","Tas binomial","Exit"]
        reply=buttonbox(image="res.gif",msg="",title="Va falloir se décider",choices=cho)
        
        while reply==cho[0] or reply==cho[1]: 
            if reply==cho[0]:
                os.system('./bloom')
            
            if reply==cho[1]:
                os.system('./heap')

        if reply==cho[2]:
            c=["Exit"]
            buttonbox(image="really.gif",msg="Trop déçue là franchement, j'attendais plus de vous Mme Braunstein ...",choices=c)
        
if reply==choices[1]:
    os.system('./bloom')

if reply==choices[2]:
    os.system('./heap')

if reply==choices[3]:
    c=["Exit"]
    buttonbox(image="really.gif",msg="Trop déçue là franchement,; je m'attentais pas à un coup comme ça de votre part Mme Braunstein",choices=c)
