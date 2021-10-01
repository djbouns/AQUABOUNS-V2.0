
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
#include "TimerFreeTone.h"
#include <EEPROM.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include "autres.h"
#include "arduino.h"
#include "global.h"
#include "affichage.h"
#include "debug.h"
#include "gsm.h"
#include "wifi.h"
#include "carteSD.h"


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
boolean texteNourrissage = true;
boolean alerteTemperature = true;
boolean alarmeOnOff = true;
boolean distributeurOn = false;
//uint8_t Hprecedent = 0;
boolean smsAlerteEdf = true;
boolean rebootAlarmeNoLoop = true;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonctions $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* nourrissage  automatique */
void nourrissage() {
  const uint16_t oneMinuteEnMillis = 60000ul;
  for (uint8_t numeroNourrissage = numeroUn; numeroNourrissage <= numeroDeux; numeroNourrissage++) { // lance la fonction pour chaque nourrissage
    if (sauvegarde.nourrissageON[numeroNourrissage] ) { // si ON
      if (Time == sauvegarde.heureNourrissage[numeroNourrissage]) { // si heure de nourrissage ateint
        if (sauvegarde.remonteDelay == Delay) { // si en mode delay
          digitalWrite(pinOutRelaisRemontee, HIGH); // remonté off pendant alimentation
          DPRINTF("pompe de remonté OFF");  DPRINTLN(); // debug
        }
        tempsPrecedentNourrissage = millis(); // lance le compteur
        nourissageEnCours = true; // nourrissage ON
        afficherNourrissageEnCours(); // affiche le message a l'ecran
        distributeurOn = true; // active la distribution
        DPRINTF("pause nourissage n°")DPRINT(numeroNourrissage); DPRINTF(" en cours");  DPRINTLN(); // debug
      }
    }
  }
  if (texteNourrissage ) { // Pour MAJ apres distribution
    if (millis() - tempsPrecedentNourrissage > sauvegarde.dureeNourrissageMillis) { // fin distribution
      afficherNourrissageEnCoursOff(); // affiche le message
      if (sauvegarde.remonteDelay == Delay) { // remet en ON la remonte apres alimentation si en mode delay
        digitalWrite(pinOutRelaisRemontee, LOW); // relais ouvert = remonté ON
        DPRINTF("pompe remonté ON");  DPRINTLN(); // debug
      }
      DPRINTF("fin Nourrissage");  DPRINTLN(); // debug
      texteNourrissage = false; // boolean pour ne pas avoir de MAJ a repetition
    }
  } // la fonction distribution manuel est avec le bouton dans l'affichage
  if (distributeurOn) {
    if (millis() - tempsPrecedentNourrissage > oneMinuteEnMillis) { // 1 minute apres l'heure de nourissage pour que l'eau soit plus calcme.
      digitalWrite(pinOutRelaisDistributeurNouriture, HIGH); // declanche le distributeur
      delay (mille); // pause
      digitalWrite(pinOutRelaisDistributeurNouriture, LOW); // arrete le distributeur
      distributeurOn = false; // desactive la distribution
      DPRINTF("distribution en cours");  DPRINTLN(); // debug
    }
  }
}

/* alerte en cas de coupure EDF */
void coupureEdf() {
  const int16_t Val12VMin = 450; // quand 12V OK = ~573 sur l'echele de 1024 avec pont diviseur on prend une valeur inferieur pour laisser de la marge
  if (analogRead(pinInCoupureCourant) < Val12VMin) { // si coupure EDF
    if (smsAlerteEdf) { // si premiere alerte
      completerMessageAlerte(texteNextionAlerte, smsCoupureEdf); // envoie un SMS
      completerMessageAlerteTemperature(texteAlerteActuellement); // envoie un SMS
      smsAlerteEdf = false; // boolean pour ne pas avoir de SMS a repetition
      alarme();
      DPRINTF("alarme coupure edf "); DPRINTLN() // debug
    }
  }
  else {
    if (smsAlerteEdf == false) { // Si juste apres coupure EDF
      completerMessageAlerte(texteNextionFinAlerte, smsEdfOk); // envoie un SMS
      completerMessageAlerteTemperature(texteAlerteActuellement); // envoie un SMS
      smsAlerteEdf = true; // boolean pour ne pas avoir de SMS a repetition²
      delay(deuxMille); // attente de 2 seconde le temps que l'ecran se rallume
      affichePageMenu(); // on affiche la page menu sur l'ecran
      DPRINTF("alarme edf ok "); DPRINTLN() // debug
    }
  }
}

void coupureBatterie() { // coupe la batterie afin d'eviter le dechargement total et le scitillement de l'ecran lorsque la tension devient trop faible
  uint16_t mesureNiveauBatterie = analogRead(pinInBatterie); // prend la mesure
  if ((mesureNiveauBatterie < batterie0) && (sauvegarde.bootApresCoupureEDF == false)) { // si mesure est inferieur a la tension minimum necessaire.
    horodatageEtEcritSurSD (texteSurSDBatterieVide, "");
    sauvegarde.bootApresCoupureEDF = true; //
    EEPROM.put(adresseDeSauvegarde, sauvegarde);  // sauvegarde tout les parametres
    delay(mille);
    digitalWrite(pinOutBatterie , LOW); //  coupe la batterie
  }
  else {
    if (sauvegarde.bootApresCoupureEDF) {
      digitalWrite(pinOutBatterie , HIGH); // batterie active
      sauvegarde.bootApresCoupureEDF = false;
      DPRINTF("Batterie On "); DPRINTLN() // debug
    }
  }
}

/* relance les alerte toute les heure entre l'intervale configurer */
void rebootAlarme() {
  if (((Time >= sauvegarde.heureDebutAlerte) && (M == 0) && (variable.seconde == 0)) && ((Time <= sauvegarde.heureFinAlerte) && (M == 0) && (variable.seconde == 0))) { // reboot toute les heures
    if (rebootAlarmeNoLoop) { // boolean pour ne pas avoir de repetition
      if (alerteTemperature == false) {
        alerteTemperature = true;
        DPRINTF("reboot alarme temperature");  DPRINTLN(); // debug
      }
      if (smsAlerteOsmolation == false) {
        smsAlerteOsmolation = true;
        DPRINTF("reboot alarme osmolateur");  DPRINTLN(); // debug
      }
      if (alertePhBas == false) {
        alertePhBas = true;
        DPRINTF("reboot alarme ph bas");  DPRINTLN(); // debug
      }
      if (alertePhHaut == false) {
        alertePhHaut = true;
        DPRINTF("reboot alarme ph haut");  DPRINTLN(); // debug
      }
      if (smsAlerteGodet == false) {
        smsAlerteGodet = true;
        DPRINTF("reboot alarme godet ecumeur");  DPRINTLN(); // debug
      }
      if (smsAlerteEdf == false) {
        smsAlerteEdf = true;
        DPRINTF("reboot alarme EDF");  DPRINTLN(); // debug
      }
      if (smsAlerteSecurite == false) {
        smsAlerteSecurite = true;
        DPRINTF("reboot alarme securité");  DPRINTLN(); // debug
      }
      if (smsAlerteReserve == false) {
        smsAlerteReserve = true;
        DPRINTF("reboot alarme reserve");  DPRINTLN(); // debug
      }
      if (alarmeOnOff == false) {
        alarmeOnOff = true;
        DPRINTF("reboot alarme sonore");  DPRINTLN(); // debug
      }
      rebootAlarmeNoLoop = false; // boolean pour ne pas avoir de repetition
    }
  }
  else {
    rebootAlarmeNoLoop = true;// boolean pour ne pas avoir de repetition
  }
}

/* alarme sonnore */
void alarme() {
  if ((Time >= sauvegarde.heureDebutAlerte) && (Time <= sauvegarde.heureFinAlerte)) {
    if (alarmeOnOff) {
#ifdef BuzzerPassif
      DPRINTF("Buzzer Passif");  DPRINTLN(); // debug
      uint8_t i = 0;
      uint8_t i2 = 0;
      uint16_t note = 800u;
      const uint8_t repetition = 3;
      const uint8_t variationNote = 25;
      const uint8_t duree = 4;
      const uint8_t Nbr2Loop = 125;

      while (i2 < repetition) { // joue 3 fois la "melodie"
        while (i < Nbr2Loop) {
          TimerFreeTone(pinOutbuzzer, note, duree); // envoie les notes
          note = note + variationNote; // change la note
          i++;
        }
        delay (250); // pause
        while (i > 1) {
          if (i2 < 2) {
            TimerFreeTone(pinOutbuzzer, note, duree); // envoie les notes
            note = note - variationNote; // change la note
          }
          i--;
        }
        i2++;
      }
#endif
#ifdef BuzzerActif
      DPRINTF("Buzzer Actif ");  DPRINTLN(); // debug
      uint8_t i = 0;
      const uint8_t repetition = 3;
      while (i < repetition) {
        digitalWrite(pinOutbuzzer, HIGH);
        delay(500);
        digitalWrite(pinOutbuzzer, LOW);
        delay(500);
        i++;
      }
#endif
      alarmeOnOff = false;
    }
    else {
      DPRINTF("Buzzer a deja sonné");  DPRINTLN(); // debug
    }
  }
}

void reboot(const uint8_t pinHardReset) { // pour faire hard reboot
  digitalWrite(pinHardReset, LOW); // met pin en OFF
  delay (100); // attente
  digitalWrite(pinHardReset, HIGH); // met pin en On
}
