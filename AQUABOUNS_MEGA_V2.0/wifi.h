#ifndef  _wifi_h_
#define _wifi_h_

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "global.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
struct __attribute__ ((packed)) valeursActuel_t { // structure des valeurs actuels
  uint8_t Heure; // pour l'heure
  uint8_t minut; // pour les minutes
  uint8_t seconde; // pour les seconde
  float temperatureBac; // pour la temperature du bac
  uint8_t temperatureRampe; // pour la temperature de la rampe
  uint8_t pwmEclairage[quatre]; // pour la puissance d'eclairage
  uint8_t pwmBrassage[trois]; // pour la puissance de grefresh brassage
  uint16_t phBac; // pour le PH du bac
  uint16_t redox; // pour le redox du bac
  float salinite; // pour la Salinite du bac
  uint8_t nbrBrassageEnON; // nombre de pompe de Brassage ON ou PWM
};
extern valeursActuel_t variable;

struct __attribute__ ((packed)) identifiantDeConnection_t { // structure identifiant de connection
  char ssid[31]; // pour le SSID prevois la place + carractere de fin
  char mdp[31]; // pour le MDP prevois la place + carractere de fin
};
extern identifiantDeConnection_t identifiantWifi;

struct __attribute__ ((packed)) etatconnection_t { // structure etat de connection
  boolean connecter; // pour savoir si le modul est connecté au wifi
  boolean presenceModule; // pour savoir si le module repond
  uint8_t puissanceSignal; // pour la puissance du signal
  char adresseIP [30]; // pour adresse ip
};
extern etatconnection_t connectionWifi;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Declarations des fonctions dans le .cpp $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
boolean envoyerData(uint8_t * d, size_t taille );
boolean recevoirData(uint8_t * d, size_t taille);
void ecouterModuleWifi();
void executer(typeCommande_t uneCommande, boolean commandeLocale);
typeCommande_t ecouterCommandeDistante();
void etatWifi();

#endif
