#ifndef  _eeprom_h_
#define _eeprom_h_

#include "global.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
const uint32_t motClef = 0xDEADBEEF;
const uint16_t adresseMotClef = 0x00;
const uint16_t adresseDeSauvegarde = adresseMotClef + sizeof(motClef);
const uint8_t zero = 0, un = 1, deux = 2, trois = 3, quatre = 4, dix = 10, cinquante = 50, cent = 100;

struct __attribute__ ((packed)) paramS_t {// force l'ordre des champs
  // page menu
  bool tempeteAleatoireOn;
  bool nourrissageON[deux];
  uint8_t remonteDelay;
  uint8_t eclairageOnOffPwm[quatre];
  uint8_t BrassageOnOffPwm[trois];
  // page config
  uint8_t puissanceMaxEclairage[quatre];
  uint32_t leverSoleil;
  uint32_t coucherSoleil;
  uint16_t dureelevercoucher;
  float alertetemperaturebasse;
  float alertetemperaturehaute;
  float ventilationaquarium;
  uint8_t ventilationrampe;
  bool adresseSondeRampe;
  bool adresseSondeBac;
  uint32_t heureNourrissage[deux];
  uint32_t dureeNourrissageMillis;
  uint16_t dureeOsmolationMillis ;
  uint8_t compteurOsmolationMax;
  uint16_t alertephbacbas;
  uint16_t alertephbachaut;
  // page Brassage
  uint8_t puissanceDemarageBrassage[trois];
  uint8_t puissanceMaxBrassage[trois];
  uint8_t angle1Oscillo[trois];
  uint8_t angle2Oscillo[trois];
  uint16_t delaisMouvementOscilloMillis[trois];
  uint32_t dureeTempeteMillis;
  uint8_t puissanceTempete;
  uint8_t accalmieNocturne;
  // horloge
  uint32_t heureDebutAlerte;
  uint32_t heureFinAlerte;
  // etat edf
  boolean bootApresCoupureEDF;
};
extern paramS_t sauvegarde;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Declarations des fonctions dans le .cpp $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void etablirValeursParDefaut();
void majValeursParDefaut();

#endif
