#ifndef PinPCBouns16_h
#define PinPCBouns16_h

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <arduino.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*
 * 
 * 
 * Affectation des pin correspondant a l'utilisation du shield pour arduino mega PCBouns V1.6
 * 
 * 
 * 
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

// entrées/sorties analogique 
const uint8_t hardResetWIFI = A0; // reset du wifi
const uint8_t hardResetGSM = A1; // reset du gsm
const uint8_t pinInCoupureCourant = A2; // entree presence tension d'alimentation
const uint8_t pinInBatterie = A3; // entree niveau batterie
//A4 non disponible sur pcb
//A5 non disponible sur pcb
//A6 non disponible sur pcb
//A7 non disponible sur pcb
const uint8_t pinOutRelaisOsmolation = A8; // relais pompe osmolation
const uint8_t pinOutRelaisVentilateurBac = A9; // relais ventilateur bac
const uint8_t pinOutRelaisRemontee = A10; // relais coupure remontee // ouvert = ON
const uint8_t pinOutRelaisChauffage = A11; // relais coupure chauffage // ouvert = ON
const uint8_t pinOutRelaisEcumeur = A12; // relais ecumeur // ouvert = ON
//A13 libre pour relais tableau
//A14 libre pour relais tableau
//A15 libre pour relais tableau
//entrées/sorties digital 
//0 rx non disponible sur pcb
//1 tx non disponible sur pcb
const uint8_t pinOutBrassage[3] {2, 3, 4}; // sortie Pwmpompe Brassage 1
#define pinInSondeDs18b20 5 // entree sonde temperature aquarium + rampe
const uint8_t pinOutRelaisVentilateurRampe = 6; // relais ventilateur rampe
const uint8_t pinOutEclairage[4] {8, 9, 7, 10}; // sortie PWM eclairage bleu1, bleu2, blanc1, blanc2
const uint8_t pinOUTOscillo1 = 11; // sortie PWM ocsillateur Brassage 1
const uint8_t pinOUTOscillo2 = 12; // sortie PWM ocsillateur Brassage 2
const uint8_t pinOUTOscillo3 = 13; // sortie PWM ocsillateur Brassage 3
#define gsm Serial1 // pin18 = tx1 + pin19 = rx1
#define nextion Serial2 // pin16 = tx2 + pin17 = rx2 >>> attention !!! la definition du port serie est a declarer dans la biblioteque NEXTION, fichier "NexConfig.h" ligne 37 !!!  la modification dans le code arduino est sans effet !!! 
#define d1mini Serial3 // pin14 = tx3 + pin15 = rx3
//20 sda > ds3231
//21 scl > ds3231
//22 non disponible sur pcb
//23 non disponible sur pcb
//24 non disponible sur pcb
const uint8_t pinOutBatterie = 25; // relais distributeur nouriture
//26 non disponible sur pcb
//27 non disponible sur pcb
//28 non disponible sur pcb
//29 non disponible sur pcb
//30 non disponible sur pcb
//31 non disponible sur pcb
//32 non disponible sur pcb
const uint8_t pinInFlotteurReserve = 33; // entree flotteur niveau bas reserve d'eau (ferme si niveau bas reserve d'eau osmose)
//34 non disponible sur pcb
const uint8_t pinInFlotteurGodetEcumeur = 35; // entree flotteur godet ecumeur (ferme = ON)
//36 non disponible sur pcb
const uint8_t pinInFlotteurSecurite = 37;// entree flotteur securité decante (ouvert si niveau haut decante)
//38 non disponible sur pcb
const uint8_t pinInFlotteurNiveauEcumeur = 39; // entree flotteur niveau ecumeur (ferme = ON)
//40 non disponible sur pcb
const uint8_t pinInFlotteurOsmolation = 41; // entree flotteur osmolation (ferme = ON)
//42 non disponible sur pcb
const uint8_t pinInFlotteurDispo = 43; // >>> non disponible sur le PCBouns v1.6
//44 non disponible sur pcb
const uint8_t pinOutRelaisDistributeurNouriture = 45; // relais distributeur nouriture
//46 non disponible sur pcb
//47 non disponible sur pcb
const uint8_t pinOutbuzzer = 48; // sortie buzzer
//49 non disponible sur pcb
//50 miso > carte sd
//51 mosi > carte sd
//52 sck > carte sd
#define SD_CS_PIN // pin53  > carte sd


#endif
