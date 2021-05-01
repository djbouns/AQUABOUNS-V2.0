
/* AQUABOUNS, Automate pour la gestion d'aquarium recifal
   Créé par djbouns, Copyright (C) 2021

   Ce programme est un logiciel libre: vous pouvez le redistribuer
   et/ou le modifier selon les termes de la "GNU General Public
   License", tels que publiés par la "Free Software Foundation"; soit
   la version 2 de cette licence ou (à votre choix) toute version
   ultérieure.

   Ce programme est distribué dans l'espoir qu'il sera utile, mais
   SANS AUCUNE GARANTIE, ni explicite ni implicite; sans même les
   garanties de commercialisation ou d'adaptation dans un but spécifique.

   Se référer à la "GNU General Public License" pour plus de détails.
   Vous la trouverez dans l'onglet GNU_General_Public_License.h

   Vous devriez avoir reçu une copie de la "GNU General Public License"
   en même temps que ce programme; sinon, écrivez a la "Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA".*/


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include <Wire.h>
#include "DallasTemperature.h"
#include <OneWire.h>
#include "Ezo_i2c.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include "temperature_ph.h"
// pin test
#include "global.h"
#include "debug.h"
#include "affichage.h"
#include "autres.h"
#include "gsm.h"
#include "wifi.h"
#include "carteSD.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// temperature
OneWire oneWire(pinInSondeDs18b20);
DallasTemperature sensors(&oneWire);
DeviceAddress sondeBac, sondeRampe; // adresse des sondes
boolean etatVentilationBac = false, etatVentilationRampe = false; // etat de la ventilation pour afficher l'icone adapté
boolean variationAnormalRampe = false;
boolean variationAnormalBac = false;
const uint8_t compteurErreurMax = 5; // nombre max d'erreur de mesure
uint8_t compteurErreurTempBac = compteurErreurMax, compteurErreurTempRampe = compteurErreurMax;
//ph
Ezo_board PH = Ezo_board(99, "PH"); // adresse de la sonde PH
boolean demande2MesurePH = false;
boolean alertePhHaut = true, alertePhBas = true; // on off alerte ph
boolean erreurPH = false; // pour erreur ph
uint32_t timer2ReponsePH = 0;
//ORP
Ezo_board ORP = Ezo_board(98, "ORP"); // adresse de la sonde ORP
boolean demande2MesureRedox = false;
boolean erreurORP = false ; // pour erreur
uint32_t timer2ReponseORP = 0;
//EC
Ezo_board EC = Ezo_board(100, "EC"); // adresse de la sonde EC
boolean demande2MesureSalinite = false;
boolean erreurEC = false; // pour erreur
float refEC = 0;
uint32_t timer2ReponseEC = 0;
//Pour les sondes
const char Callow[] PROGMEM = "Cal,low,"; // texte stocker en progmem
const char Calmid[] PROGMEM = "Cal,mid,"; // texte stocker en progmem
const char Calhigh[] PROGMEM = "Cal,high,"; // texte stocker en progmem
const char Cal[] PROGMEM = "Cal,"; // texte stocker en progmem
const char Caldry[] PROGMEM = "Cal,dry"; // texte stocker en progmem
const char oec1[] PROGMEM = "o,ec,1"; // texte stocker en progmem
const char os0[] PROGMEM = "o,s,0"; // texte stocker en progmem

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonctions $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* recuperation temperature des ds18b20 */
void temperature() {
  const uint8_t limiteTemperatureMinimum = 10; // temperature minimum, on en deduit que la sonde n'est pas presente // plus d'alerte en dessous de cette temperature
  const uint8_t limiteTemperatureMaximum = 85; // temperature maximum, on en deduit que la sonde n'est pas presente // plus d'alerte en dessous de cette temperature
  float stockMesure;
  // temperature Rampe
  stockMesure = sensors.getTempCByIndex(sauvegarde.adresseSondeRampe); // affecte la temperature recu a la variable
  DPRINTF("temp rampe : "); DPRINT(stockMesure); DPRINTLN();
  if (stockMesure <= limiteTemperatureMinimum || stockMesure >= limiteTemperatureMaximum) { // si relevé hors limite
    compteurErreurTempRampe++; // on incremente le compteur
    if (compteurErreurTempRampe >= compteurErreurMax) { // si le compteur est egal ou supperieur au nombre max d'erreur
      variable.temperatureRampe = zero; // = zero car trop de mesure erroné
    }
  }
  else if ((variable.temperatureRampe + 1 > stockMesure) && (variable.temperatureRampe - 1 < stockMesure)) {
    variable.temperatureRampe = stockMesure; // affecte la mesure
    compteurErreurTempRampe = zero; // met compteur d'erreur a zero
  }
  else {
    compteurErreurTempRampe++; // on incremente le compteur
    if (compteurErreurTempRampe >= compteurErreurMax) { // si le compteur est egal ou supperieur au nombre max d'erreur
      variable.temperatureRampe = stockMesure; // affecte la mesure
      compteurErreurTempRampe = zero; // met compteur d'erreur a zero
    }
  }
  // temperature Bac
  stockMesure = sensors.getTempCByIndex(sauvegarde.adresseSondeBac); // affecte la mesure
  DPRINTF("mesuré temp bac : "); DPRINT(stockMesure); DPRINTLN(); // debug
  if (stockMesure <= limiteTemperatureMinimum || stockMesure >= limiteTemperatureMaximum) { // si la mesure est hors limite
    compteurErreurTempBac++; // incremente le compteur d'erreur
    DPRINTF("mesure T hors limite : "); DPRINT(stockMesure); DPRINTLN(); // debug
    if (compteurErreurTempBac >= compteurErreurMax) { // si nombre d'erreur MAX atteind
      variable.temperatureBac = zero; // = zero car trop de mesure erroné
      DPRINTF("T en erreur : "); DPRINT(stockMesure); DPRINTLN(); // debug
    }
  }
  else if ((variable.temperatureBac + 1 > stockMesure) && (variable.temperatureBac - 1 < stockMesure)) {
    variable.temperatureBac = stockMesure; // affecte la mesure
    DPRINTF("ok temp bac : "); DPRINT(stockMesure); DPRINTLN(); // debug
    compteurErreurTempBac = zero; // met compteur d'erreur a zero
  }
  else {
    compteurErreurTempBac++; // incremente le compteur d'erreur
    DPRINTF("mesure temp bac sup ou inf de 1°/mesur eprecedente : "); DPRINT(stockMesure); DPRINTLN(); // debug
    if (compteurErreurTempBac >= compteurErreurMax) { // si nombre d'erreur MAX atteind
      variable.temperatureBac = stockMesure; // affecte la mesure
      compteurErreurTempBac = zero; // met compteur d'erreur a zero
      DPRINTF("T en erreur : "); DPRINT(stockMesure); DPRINTLN(); // debug
    }
  }
  ventilation(); // lance la fonction
  sensors.requestTemperatures(); // on lance une demande aux sondes pour prochain relevé de temperature
}

/* declanchement des ventilateurs si besoin */
void ventilation() {
  const float temperatureDeFlotement = 0.2;// fourchette de temperature haute et basse ou il ne se passe rien // evite les ON/OFF lorsque la mesure est a cheval avec la valeur de declenchement
  // ventilation bac
  if (variable.temperatureBac >= sauvegarde.ventilationaquarium) { // si temperaure est superieur a la consigne
    digitalWrite(pinOutRelaisVentilateurBac, HIGH); // relais fermé = ventilation ON
    digitalWrite(pinOutRelaisChauffage, HIGH); // relais fermé = chauffage OFF // par securité car doit deja etre OFF
    if (etatVentilationBac == false) {
      etatVentilationBac = true; // icone ventilation
      DPRINTF("  ON ventilo bac : "); DPRINT(variable.temperatureBac); DPRINTLN();
    }
  }
  else if (((float)variable.temperatureBac + temperatureDeFlotement) >= sauvegarde.ventilationaquarium) { // temperature de flotement ou on ne fait rien
    DPRINTF("flottement ventilo bac : "); DPRINT(variable.temperatureBac); DPRINTLN();
  }
  else { // si temperature inferieur a la consigne
    digitalWrite(pinOutRelaisVentilateurBac, LOW); // relais ouvert = ventilateur OFF
    digitalWrite(pinOutRelaisChauffage, LOW); // relais ouvert = chauffage ON (temperature géré par thermostat independant de l'arduino)
    if (etatVentilationBac) {
      etatVentilationBac = false; // icone ventilation
      DPRINTF("OFF ventilo bac : "); DPRINT(variable.temperatureBac); DPRINTLN();
    }
  }
  // ventilation rampe
  if (variable.temperatureRampe >= sauvegarde.ventilationrampe) { // si temperature superieur a la consigne
    digitalWrite(pinOutRelaisVentilateurRampe, HIGH); // relais fermé = ventilation ON
    if (etatVentilationRampe == false) {
      etatVentilationRampe = true; // icone ventilation
      DPRINTF("ON ventilo rampe : "); DPRINT(variable.temperatureRampe); DPRINTLN();
    }
  }
  else if (variable.temperatureRampe + temperatureDeFlotement >= (sauvegarde.ventilationrampe)) { // temperature de flotement ou on ne fait rien
    DPRINTF("flottement ventilo rampe : "); DPRINT(variable.temperatureRampe); DPRINTLN();
  }
  else { // si temperature inferieur a la consigne
    digitalWrite(pinOutRelaisVentilateurRampe, LOW); // relais ouvert = ventilateur OFF
    if (etatVentilationRampe) {
      etatVentilationRampe = false; // icone ventilation
      DPRINTF("OFF ventilo rampe : "); DPRINT(variable.temperatureRampe); DPRINTLN();
    }
  }
}

/* affiche sur l'ecran et envoie SMS si temperature hors consigne */
void messageAlerteTemperature() {
  const uint8_t limiteTemperatureMinimum = 10; // temperature minimum, on en deduit que la sonde n'est pas presente // plus d'alerte en dessous de cette temperature
  const uint8_t limiteTemperatureMaximum = 85; // temperature maximum, on en deduit que la sonde n'est pas presente // plus d'alerte en dessous de cette temperature
  const float temperatureDeFlotement = 0.2;// fourchette de temperature haute et basse ou il ne se passe rien // evite les ON/OFF lorsque la mesure est a cheval avec la valeur de declenchement
  if (variable.temperatureBac > limiteTemperatureMinimum) {
    if (variable.temperatureBac >= sauvegarde.alertetemperaturehaute) { // si la temperature du bac est egal ou depasse la temperature d'alerte
      if (alerteTemperature) { // pour ne pas avoir de message a repetition
        completerMessageAlerteTemperature(texteNextionAlerte); // prepare texte du SMS a envoyer
        alarme(); // lance la fonction
        DPRINTF("alarme temp haut "); DPRINTLN() // debug
      }
    }
    else if (variable.temperatureBac <= sauvegarde.alertetemperaturebasse) { // si la temperature du bac est egal ou depasse la temperature d'alerte
      if (alerteTemperature ) { // pour ne pas avoir de message a repetition
        completerMessageAlerteTemperature(texteNextionAlerte); // prepare texte du SMS a envoyer
        alarme(); // lance la fonction
        DPRINTF("alarme temp bas "); DPRINTLN() // debug
      }
    }
    else if (((variable.temperatureBac + temperatureDeFlotement) <= sauvegarde.alertetemperaturehaute) && ((variable.temperatureBac - temperatureDeFlotement) >= sauvegarde.alertetemperaturebasse )) {
      if (alerteTemperature == false) { // pour ne pas avoir de message a repetition
        completerMessageAlerteTemperature(texteNextionFinAlerte); // prepare texte du SMS a envoyer
        alarmeOnOff = true; // remet l'alarme sonore On
        DPRINTF("alarme temp ok "); DPRINTLN() // debug
      }
    }
  }
}

/* recuperation des mesures ph */
void ph() {
  const uint16_t delais2reponse = 800; // temps de reponse du module ph
  if (demande2MesurePH == false) { // si pas de demande de mesure en cours
    if (variable.temperatureBac == zero) {
      PH.send_read_cmd(); // envoie une demande de mesure au module
    }
    else {
      PH.send_read_with_temp_comp(variable.temperatureBac); // envoie une demande de mesure au module
    }
    timer2ReponsePH = millis() + delais2reponse; // met a jour le timer
    demande2MesurePH = true; //  passe la demande de mesure en ON
  }
}

void attenteMesurePH() {
  float mesurePH;
  if ((demande2MesurePH) && (millis() >= timer2ReponsePH)) { // si demande de mesure & timer de reponse depassé
    uint16_t minPh = 300;
    uint16_t maxPh = 1300;
    PH.receive_read_cmd(); // reception des mesures
    switch (PH.get_error()) { // switch selon reponse recu
        DPRINTF("sonde ph : "); // debug
      case Ezo_board::SUCCESS: // reception de mesure OK
        mesurePH = PH.get_last_received_reading(); // stock la mesure
        variable.phBac = mesurePH * cent;
        rafraichirPhBacNextion();
        rafraichirMesuresEtalonnage();
        erreurPH = false ; // pas d'erreur
        DPRINTF("mesure Ph moyen : "); DPRINTLN(variable.phBac); // debug
        break;
      case Ezo_board::FAIL: // si erreur
        DPRINTF("Failed PH"); DPRINTLN() // debug
        if (erreurPH == true) { // si deja en erreur
          variable.phBac = 0; // valeur nul
        }
        else {
          erreurPH = true;
        }
        break;
      case Ezo_board::NOT_READY: // si pas pret
        DPRINTF("Pending PH"); DPRINTLN() // debug
        if (erreurPH == true) { // si deja en erreur
          variable.phBac = 0; // valeur nul
        }
        else {
          erreurPH = true;
        }
        break;
      case Ezo_board::NO_DATA: // si pas de reception
        DPRINTF("No Data PH"); DPRINTLN() // debug
        if (erreurPH == true) { // si deja en erreur
          variable.phBac = 0; // valeur nul
        }
        else {
          erreurPH = true;
        }
        break;
        DPRINTLN();
    }
    demande2MesurePH = false; // passe la demande de mesure en OFF
    if (variable.phBac < minPh || variable.phBac > maxPh) {
      DPRINTF("mesure PH hors limite :"); DPRINTLN(variable.phBac); // debug
      variable.phBac = 0;
    }
  }
}

/* affiche sur l'ecran et envoie SMS si PH hors consigne */
void alertePhBac() { // alerte ph bac
  const uint8_t phDeFlotement = 5; // fourchette ph haut et bas ou il ne se passe rien // evite les ON/OFF lorsque la mesure est a cheval avec la valeur de declenchement
  if (sauvegarde.alertephbacbas != sauvegarde.alertephbachaut) { // si l'alerte PH est activé (si alerte bas = haut, alerte desactivé)
    if (variable.phBac <= sauvegarde.alertephbacbas && variable.phBac != zero) { // alerte ph bas et si pas d'erreur de mesure
      if (alertePhBas) { // pour ne pas avoir de message a repetition
        alertePhBas = false;
        afficherAlertepPhBacBas(); // lance la fonction
        completerMessageAlertePh(texteNextionAlerte); // prepare texte du SMS a envoyer
        alarme(); // lance la fonction
        DPRINTF("alarme ph bas "); DPRINTLN() // debug
      }
    }
    else if (variable.phBac >= sauvegarde.alertephbachaut && variable.phBac != zero) { // alerte ph haut et si pas d'erreur de mesure
      if (alertePhHaut) { // pour ne pas avoir de message a repetition
        alertePhHaut = false;
        afficherAlertepPhBacHaut();// lance la fonction
        completerMessageAlertePh(texteNextionAlerte); // prepare texte du SMS a envoyer
        alarme();// lance la fonction
        DPRINTF("alarme ph haut "); DPRINTLN() // debug
      }
    }
    else { // si pas de probleme PH dans le bac
      if (alertePhBas == false || alertePhHaut == false) {
        if (variable.phBac - phDeFlotement >= sauvegarde.alertephbacbas && variable.phBac + phDeFlotement <= sauvegarde.alertephbachaut && variable.phBac != zero) {
          afficherAlertepPhBacOff(); // fin / pas d'alerte
          completerMessageAlertePh(texteNextionFinAlerte); // prepare texte du SMS a envoyer
          alarmeOnOff = true; // remet l'alarme sonore On
          DPRINTF("alarme ph ok "); DPRINTLN() // debug
        }
      }
    }
  }
  else {
    DPRINTF("alarme ph OFF"); DPRINTLN() // debug
  }
}

/* recuperation des mesures REDOX */
void redox() {
  const uint16_t delais2reponse = 810; // temps de reponse du module
  if (demande2MesureRedox == false) { // si pas de demande de mesure en cours
    ORP.send_read_cmd(); // envoie une demande de mesure au module
    timer2ReponseORP = millis() + delais2reponse; // met a jour le timer
    demande2MesureRedox = true; //  passe la demande de mesure en ON
  }
}

void attenteMesureRedox() {
  if ((demande2MesureRedox) && (millis() >= timer2ReponseORP)) { // si demande de mesure & timer de reponse depassé
    uint16_t minRedox = 100;
    uint16_t maxRedox = 550;
    ORP.receive_read_cmd(); // reception des mesures
    switch (ORP.get_error()) { // switch selon reponse recu
        DPRINTF("sonde redox : "); // debug
      case Ezo_board::SUCCESS: // reception de mesure OK
        variable.redox = ORP.get_last_received_reading();
        rafraichirRedoxNextion();
        rafraichirMesuresEtalonnage();
        erreurORP = false ; // pas d'erreur
        DPRINTF("mesure Redox : "); DPRINTLN(variable.redox); // debug
        break;
      case Ezo_board::FAIL: // si erreur
        DPRINTF("Failed REDOX"); DPRINTLN() // debug
        if (erreurORP == true) { // si deja en erreur
          variable.redox = 0 ;
        }
        else {
          erreurORP = true;
        }
        break;
      case Ezo_board::NOT_READY: // si pas pret
        DPRINTF("Pending REDOX"); DPRINTLN() // debug
        if (erreurORP == true) { // si deja en erreur
          variable.redox = 0 ;
        }
        else {
          erreurORP = true;
        }
        break;
      case Ezo_board::NO_DATA: // si pas de reception
        DPRINTF("No Data REDOX"); DPRINTLN() // debug
        if (erreurORP == true) { // si deja en erreur
          variable.redox = 0 ;
        }
        else {
          erreurORP = true;
        }
        break;
        DPRINTLN();
    }
    demande2MesureRedox = false; // passe la demande de mesure en OFF
    if (variable.redox < minRedox || variable.redox > maxRedox) {
      DPRINTF("mesure redox hors limite :"); DPRINTLN(variable.redox); // debug
      variable.redox = 0;
    }
  }
}

/* recuperation des mesures de conductivité */
void salinite() {
  const uint16_t delais2reponse = 600; // temps de reponse du module
  if (demande2MesureSalinite == false) { // si pas de demande de mesure en cours
    if (variable.temperatureBac == zero) {
      EC.send_read_cmd(); // envoie une demande de mesure au module
    }
    else {
      EC.send_read_with_temp_comp(variable.temperatureBac); // envoie une demande de mesure au module avec compensation de la temperature
    }
    timer2ReponseEC = millis() + delais2reponse; // met a jour le timer
    demande2MesureSalinite = true; //  passe la demande de mesure en ON
  }
}

void attenteMesureSalinite() {
  if ((demande2MesureSalinite) && (millis() >= timer2ReponseEC)) { // si demande de mesure & timer de reponse depassé
    uint8_t minSal = 30;
    uint8_t maxSal = 40;
    EC.receive_read_cmd(); // reception des mesures
    switch (EC.get_error()) { // switch selon reponse recu
        DPRINTF(" sonde cuductivite : "); // debug
      case Ezo_board::SUCCESS: // reception de mesure OK
        variable.salinite = EC.get_last_received_reading();
        rafraichirMesuresEtalonnage();
        erreurEC = false ; // pas d'erreur
        DPRINTF("mesure Salinite : "); DPRINTLN(variable.salinite); // debug
        break;
      case Ezo_board::FAIL: // si erreur
        DPRINTF("Failed EC"); DPRINTLN() // debug
        if (erreurEC == true) { // si deja en erreur
          variable.salinite = 0 ;
        }
        else {
          erreurEC = true;
        }
        break;
      case Ezo_board::NOT_READY: // si pas pret
        DPRINTF("Pending EC"); DPRINTLN() // debug
        if (erreurEC == true) { // si deja en erreur
          variable.salinite = 0 ;
        }
        else {
          erreurEC = true;
        }
        break;
      case Ezo_board::NO_DATA: // si pas de reception
        DPRINTF("No Data EC"); DPRINTLN() // debug
        if (erreurEC == true) { // si deja en erreur
          variable.salinite = 0 ;
        }
        else {
          erreurEC = true;
        }
        break;
        DPRINTLN();
        demande2MesureSalinite = false; // passe la demande de mesure en OFF
    }
    demande2MesureSalinite = false; // passe la demande de mesure en OFF
    if ((pageActuelNextion != orph) && (variable.salinite < minSal || variable.salinite > maxSal)) {
      DPRINTF("mesure Salinite hors limite :"); DPRINTLN(variable.salinite); // debug
      variable.salinite = 0;
    }
  }
}

void saliniteModeMesure() {
  uint8_t maxCommandeEtalonnage = 15;
  char commandeEtalonnage[maxCommandeEtalonnage + 1];
  if (pageActuelNextion == orph) {
    while (demande2MesureSalinite) {
      attenteMesureSalinite();
    }
    strcpy_P(commandeEtalonnage, oec0);
    commandeEtalonnage[maxCommandeEtalonnage] = '\0';
    EC.send_cmd(commandeEtalonnage);
    delay(400); // laisse le temps au module de traiter la commande
    strcpy_P(commandeEtalonnage, os1);
    commandeEtalonnage[maxCommandeEtalonnage] = '\0';
    EC.send_cmd(commandeEtalonnage);
    delay(400); // laisse le temps au module de traiter la commande
    variable.salinite = 0;
  }
  DPRINTF("EZO EC en mode Mesure "); DPRINTLN();
}

void saliniteModeEtalonnage() {
  uint8_t maxCommandeEtalonnage = 15;
  char commandeEtalonnage[maxCommandeEtalonnage + 1];
  while (demande2MesureSalinite) {
    attenteMesureSalinite();
  }
  strcpy_P(commandeEtalonnage, oec1);
  commandeEtalonnage[maxCommandeEtalonnage] = '\0';
  EC.send_cmd(commandeEtalonnage);
  delay(400); // laisse le temps au module de traiter la commande
  strcpy_P(commandeEtalonnage, os0);
  commandeEtalonnage[maxCommandeEtalonnage] = '\0';
  EC.send_cmd(commandeEtalonnage);
  delay(400); // laisse le temps au module de traiter la commande
  variable.salinite = 0;
  DPRINTF("EZO EC en mode Etalonnage "); DPRINTLN();
}

void etalonnageDesSondes(uint8_t sondeACalibrer, uint16_t valeur, float valeurfloat) {
  uint8_t maxTampon = 7; // taille max de tampon
  char tampon[maxTampon + 1]; // taille max de tampon + caractere de fin
  uint8_t maxCommandeEtalonnage = 15;
  char commandeEtalonnage[maxCommandeEtalonnage + 1];
  for (int i = 0; i < 10; i++) { // boucle pour recuperer les eventuel demande de mesure en cours
    attenteMesurePH(); // attend la reception des mesures
    attenteMesureRedox(); // attend la reception des mesures
    attenteMesureSalinite(); // attend la reception des mesures
    delay(100);
  }
  switch (sondeACalibrer) {
    case 11: // etalonnage PH
      strcpy_P(commandeEtalonnage, Callow);
      commandeEtalonnage[maxCommandeEtalonnage] = '\0';
      dtostrf(valeurfloat, 3, 2, tampon);
      strcat(commandeEtalonnage, tampon); // ajoute la commande
      PH.send_cmd(commandeEtalonnage);
      DPRINTF("etalonnage PH low a : ")
      break;
    case 12: // etalonnage PH
      strcpy_P(commandeEtalonnage, Calmid);
      commandeEtalonnage[maxCommandeEtalonnage] = '\0';
      dtostrf(valeurfloat, 3, 2, tampon);
      strcat(commandeEtalonnage, tampon); // ajoute la commande
      PH.send_cmd(commandeEtalonnage);
      DPRINTF("etalonnage PH mid a : ")
      break;
    case 13: // etalonnage PH
      strcpy_P(commandeEtalonnage, Calhigh);
      commandeEtalonnage[maxCommandeEtalonnage] = '\0';
      dtostrf(valeurfloat, 3, 2, tampon);
      strcat(commandeEtalonnage, tampon); // ajoute la commande
      PH.send_cmd(commandeEtalonnage);
      DPRINTF("etalonnage PH high a : ")
      break;
    case 2: // etalonnage ORP
      strcpy_P(commandeEtalonnage, Cal);
      commandeEtalonnage[maxCommandeEtalonnage] = '\0';
      itoa (valeur, tampon, 10);
      strcat(commandeEtalonnage, tampon); // ajoute la commande
      ORP.send_cmd(commandeEtalonnage);
      DPRINTF("etalonnage ORP a : ")
      break;
    case 3: // etalonnage EC
      if (valeur == zero) { // etalonnage a sec
        strcpy_P(commandeEtalonnage, Caldry);
        commandeEtalonnage[maxCommandeEtalonnage] = '\0';
        EC.send_cmd(commandeEtalonnage);
        DPRINTF("etalonnage EC a sec"); DPRINTLN();
      }
      else {
        strcpy_P(commandeEtalonnage, Cal);
        commandeEtalonnage[maxCommandeEtalonnage] = '\0';
        ultoa (valeur, tampon, 10);
        DPRINTF("tampon: "); DPRINTLN(tampon);
        strcat(commandeEtalonnage, tampon); // ajoute la commande
        EC.send_cmd(commandeEtalonnage);
      }
      DPRINTF("etalonnage EC a : ")
      break;
  }
  delay(1200); // laisse le temps au module de traiter la commande
  DPRINT(commandeEtalonnage); DPRINTLN() // debug
}

void etalonnageEnCours() {
  switch (roulement1) {
    case 0 :
      ph();
      break;
    case 1:
      redox();
      break;
    case 2:
      salinite();
      break;
  }
}

void initialisationEC(char*commandeIni) {
  EC.send_cmd(commandeIni);
}
