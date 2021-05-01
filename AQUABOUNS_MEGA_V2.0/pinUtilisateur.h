#ifndef PinUtilisateur_h
#define PinUtilisateur_h

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <arduino.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// entrées/sorties analogique 
const uint8_t hardResetGSM = A5; // reset du gsm
const uint8_t hardResetWIFI = A6; // reset du wifi
const uint8_t pinInCoupureCourant = A7; // entree presence tension d'alimentation
const uint8_t pinInBatterie = A8; // entree niveau batterie
const uint8_t pinOutRelaisChauffage = A10; // relais coupure chauffage // ouvert = ON
const uint8_t pinOutRelaisEcumeur = A11; // relais ecumeur // ouvert = ON
const uint8_t pinOutRelaisRemontee = A13; // relais coupure remontee // ouvert = ON

//entrées/sorties digital 
const uint8_t pinOutBrassage[3] {2, 3, 4}; // sortie PWM pompe Brassage >>> definir dans cette ordre {pompe 1, pompe 2, pompe 3}
const uint8_t pinOUTOscillo1 = 5; // sortie PWM ocsillateur Brassage 1
const uint8_t pinOUTOscillo2 = 6; // sortie PWM ocsillateur Brassage 2
const uint8_t pinOUTOscillo3 = 7; // sortie PWM ocsillateur Brassage 3
const uint8_t pinOutRelaisVentilateurRampe = 8; // relais ventilateur rampe
const uint8_t pinOutEclairage[4] {11, 12, 9, 10}; // >>> attention !!! définir les Pin dans cette ordre : blanc1, blanc2, bleu1, bleu2
#define pinInSondeDs18b20 13 // entree sonde temperature aquarium + rampe
// disponible Serial1, Serial2 et Serial3 :
#define d1mini Serial3 
#define gsm Serial2 
#define nextion Serial1  // >>> attention !!! la definition du port serie est a declarer dans la biblioteque NEXTION, fichier "NexConfig.h" ligne 37 !!!  la modification dans le code arduino est sans effet !!! 
//20 sda > ds3231 + 3x MODUL ATLAS
//21 scl > ds3231 + 3x MODUL ATLAS
const uint8_t pinInFlotteurGodetEcumeur = 27; // entree flotteur godet ecumeur (ferme = ON)
const uint8_t pinInFlotteurReserve = 29; // entree flotteur niveau bas reserve d'eau (ferme si niveau bas reserve d'eau osmose)
const uint8_t pinInFlotteurOsmolation = 33; // entree flotteur osmolation (ferme = ON)
const uint8_t pinInFlotteurNiveauEcumeur = 35; // entree flotteur niveau ecumeur (ferme = ON)
const uint8_t pinOutRelaisDistributeurNouriture = 37; // relais distributeur nouriture
const uint8_t pinInFlotteurSecurite = 39;// entree flotteur securité decante (ouvert si niveau haut decante)
const uint8_t pinOutBatterie = 41; // relais distributeur nouriture
const uint8_t pinOutRelaisOsmolation = 49; // relais pompe osmolation
const uint8_t pinOutbuzzer = 48; // sortie buzzer 48
const uint8_t pinOutRelaisVentilateurBac = 47; // relais ventilateur bac
//50 miso > carte sd
//51 mosi > carte sd
//52 sck > carte sd
#define SD_CS_PIN // pin53  > carte sd

#endif
