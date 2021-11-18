#ifndef PinPCBouns21_h
#define PinPCBouns21_h

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <arduino.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*
 * 
 * 
 * Affectation des pin correspondant a l'utilisation du shield pour arduino mega PCBouns V2.1
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
//A0 non disponible sur pcb
//A1 non disponible sur pcb
//A2 non disponible sur pcb
//A3 non disponible sur pcb
//A4 non disponible sur pcb
const uint8_t hardResetWIFI = A5; // reset du wifi
const uint8_t hardResetGSM = A6; // reset du gsm
const uint8_t pinInCoupureCourant = A7; // entree presence tension d'alimentation
const uint8_t pinInBatterie = A8; // entree niveau batterie
const uint8_t pinOutRelaisEcumeur = A9; // relais ecumeur // ouvert = ON
const uint8_t pinOutRelaisRemontee = A10; // relais coupure remontee // ouvert = ON
const uint8_t pinOutRelaisChauffage = A11; // relais coupure chauffage // ouvert = ON
//A12 disponible pour un relais
//A13 disponible pour un relais
//A14 disponible pour un relais
//A15 disponible pour un relais
//entrées/sorties digital 
//0 rx non disponible sur pcb
//1 tx non disponible sur pcb
const uint8_t pinOutBrassage[3] {2, 3, 4}; // sortie Pwmpompe Brassage 1
const uint8_t pinOUTOscillo1 = 5; // sortie PWM ocsillateur Brassage 1
const uint8_t pinOUTOscillo2 = 6; // sortie PWM ocsillateur Brassage 2
const uint8_t pinOUTOscillo3 = 7; // sortie PWM ocsillateur Brassage 3
const uint8_t pinOutRelaisVentilateurRampe = 8; // relais ventilateur rampe
const uint8_t pinOutEclairage[4] {11, 12, 9, 10}; // sortie PWM eclairage blanc1, blanc2, bleu1, bleu2
#define pinInSondeDs18b20 13 // entree sonde temperature aquarium + rampe
#define d1mini Serial3 // pin14 = tx3 + pin15 = rx3
#define gsm Serial2 // pin18 = tx16 + pin17 = rx2
#define nextion Serial1  // pin18 = tx1 + pin19 = rx1 >>> attention !!! la definition du port serie est a declarer dans la biblioteque NEXTION, fichier "NexConfig.h" ligne 37 !!!  la modification dans le code arduino est sans effet !!! 
//20 sda > ds3231 + 3x MODUL ATLAS
//21 scl > ds3231 + 3x MODUL ATLAS
//22 non disponible sur pcb
//23 non disponible sur pcb
//24 non disponible sur pcb
//25 non disponible sur pcb
//26 non disponible sur pcb
const uint8_t pinInFlotteurGodetEcumeur = 27; // entree flotteur godet ecumeur (ferme = ON)
//28 non disponible sur pcb
const uint8_t pinInFlotteurReserve = 29; // entree flotteur niveau bas reserve d'eau (ferme si niveau bas reserve d'eau osmose)
//30 non disponible sur pcb
const uint8_t pinInFlotteurDispo = 31; // entree flotteur disponible, non utilisé pour le momment
//32 non disponible sur pcb
const uint8_t pinInFlotteurOsmolation = 33; // 33 entree flotteur osmolation (ferme = ON)
//34 non disponible sur pcb
const uint8_t pinInFlotteurNiveauEcumeur = 35; // entree flotteur niveau ecumeur (ferme = ON)
//36 non disponible sur pcb
const uint8_t pinOutRelaisDistributeurNouriture = 37; // relais distributeur nouriture
//38 non disponible sur pcb
const uint8_t pinInFlotteurSecurite = 39 ;// 39 entree flotteur securité decante (ouvert si niveau haut decante)
//40 non disponible sur pcb
const uint8_t pinOutBatterie = 41; // relais distributeur nouriture
//42 non disponible sur pcb
//43 non disponible sur pcb
//44 non disponible sur pcb
//45 non disponible sur pcb
//46 non disponible sur pcb
const uint8_t pinOutRelaisVentilateurBac = 47; // relais ventilateur bac
const uint8_t pinOutbuzzer = 48; // sortie buzzer 48
const uint8_t pinOutRelaisOsmolation = 49; // relais pompe osmolation
//50 miso > carte sd
//51 mosi > carte sd
//52 sck > carte sd
#define SD_CS_PIN // pin53  > carte sd


#endif

