#ifndef PinPCBounsMini10_h
#define PinPCBounsMini10_h

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <arduino.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*
ATTENTION, Vous ne devez pas affecter les pin suivant car ils sont deja utilisés
A0, A1, 13, 14, 15, 16, 17, 18, 19, 22, 49, 50, 51, 52, 53
*/ 

const uint8_t pinOutRelaisChauffage = A2; // relais coupure chauffage // ouvert = ON
const uint8_t pinOutRelaisEcumeur = A3; // relais ecumeur // ouvert = ON
const uint8_t pinOutRelaisRemontee = A4; // relais coupure remontee // ouvert = ON
const uint8_t pinOutRelaisVentilateurRampe = A5; // relais ventilateur rampe
const uint8_t pinOutRelaisDistributeurNouriture = A6; // relais distributeur nouriture
const uint8_t pinOutRelaisVentilateurBac = A7; // relais ventilateur bac
const uint8_t pinOutRelaisOsmolation = A8; // relais pompe osmolation
const uint8_t pinOutBatterie = A9; 
const uint8_t pinInBatterie = A10; // entree niveau batterie
const uint8_t pinOutBrassage[3] {2, 3, 4}; // sortie Pwmpompe Brassage 1
const uint8_t pinOUTOscillo1 = 5; // sortie PWM ocsillateur Brassage 1
const uint8_t pinOUTOscillo2 = 6; // sortie PWM ocsillateur Brassage 2
const uint8_t pinOUTOscillo3 = 7; // sortie PWM ocsillateur Brassage 3
const uint8_t pinOutEclairage[4] {10, 11, 8 , 9}; // sortie PWM eclairage blanc1, blanc2, bleu1, bleu2
const uint8_t pinInFlotteurGodetEcumeur = 24; // entree flotteur godet ecumeur (ferme = ON)
const uint8_t pinInFlotteurReserve = 25; // entree flotteur niveau bas reserve d'eau (ferme si niveau bas reserve d'eau osmose)
const uint8_t pinInFlotteurOsmolation = 26; // 33 entree flotteur osmolation (ferme = ON)
const uint8_t pinInFlotteurNiveauEcumeur = 27; // entree flotteur niveau ecumeur (ferme = ON)
const uint8_t pinInFlotteurSecurite = 28;// entree flotteur securité decante (ouvert si niveau haut decante)
const uint8_t pinInFlotteurDispo = 29; // entree flotteur disponible, non utilisé pour le momment
 
  
 /*
  888b    888 8888888888      8888888b.  888     888     888  .d8888b.       88888888888 .d88888b.  888     888  .d8888b.  888    888 8888888888 8888888b.
  8888b   888 888             888   Y88b 888     888     888 d88P  Y88b          888    d88P" "Y88b 888     888 d88P  Y88b 888    888 888        888   Y88b
  88888b  888 888             888    888 888     888     888 Y88b.               888    888     888 888     888 888    888 888    888 888        888    888
  888Y88b 888 8888888         888   d88P 888     888     888  "Y888b.            888    888     888 888     888 888        8888888888 8888888    888   d88P
  888 Y88b888 888             8888888P"  888     888     888     "Y88b.          888    888     888 888     888 888        888    888 888        8888888P"
  888  Y88888 888             888        888     888     888       "888          888    888     888 888     888 888    888 888    888 888        888 T88b
  888   Y8888 888             888        888     Y88b. .d88P Y88b  d88P          888    Y88b. .d88P Y88b. .d88P Y88b  d88P 888    888 888        888  T88b
  888    Y888 8888888888      888        88888888 "Y88888P"   "Y8888P"           888     "Y88888P"   "Y88888P"   "Y8888P"  888    888 8888888888 888   T88b

                   d8888      8888888b.     d8888 8888888b. 88888888888 8888888 8888888b.       8888888b.  d8b 8888888 .d8888b. 8888888
                  d88888      888   Y88b   d88888 888   Y88b    888       888   888   Y88b      888  "Y88b 88    888  d88P  Y88b  888
                 d88P888      888    888  d88P888 888    888    888       888   888    888      888    888       888  888    888  888
                d88P 888      888   d88P d88P 888 888   d88P    888       888   888   d88P      888    888       888  888         888
               d88P  888      8888888P" d88P  888 8888888P"     888       888   8888888P"       888    888       888  888         888
              d88P   888      888      d88P   888 888 T88b      888       888   888 T88b        888    888       888  888    888  888
             d8888888888      888     d8888888888 888  T88b     888       888   888  T88b       888  .d88P       888  Y88b  d88P  888
            d88P     888      888    d88P     888 888   T88b    888     8888888 888   T88b      8888888P"      8888888 "Y8888P" 8888888
*/

const uint8_t hardResetWIFI = A0; // reset du wifi
const uint8_t hardResetGSM = A1; // reset du gsm
#define pinInSondeDs18b20 13 // entree sonde temperature aquarium + rampe
const uint8_t pinInCoupureCourant = 22; // entree presence tension d'alimentation
#define d1mini Serial2 // pin16 = tx2 + pin17 = rx2
#define gsm Serial3 // pin14 = tx3 + pin15 = rx3
#define nextion Serial1  // pin18 = tx1 + pin19 = rx1 >>> attention !!! la definition du port serie est a declarer dans la biblioteque NEXTION, fichier "NexConfig.h" ligne 37 !!!  la modification dans le code arduino est sans effet !!! 
const uint8_t pinOutbuzzer = 49; // sortie buzzer
//50 miso > carte sd
//51 mosi > carte sd
//52 sck > carte sd
#define SD_CS_PIN // pin53  > carte sd

#endif
