
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


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include "flotteurs.h"
#include "global.h"
#include "debug.h"
#include "affichage.h"
#include "gsm.h"
#include "autres.h"
#include "wifi.h"
#include "carteSD.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
boolean osmolationOn = true;
uint8_t compteurOsmolation = 0;
uint32_t tempsPrecedentOsmolation;
uint32_t tempsAttenteOsmolation;
uint32_t compteurPinInFlotteurReserveBas = 1800000ul; // doit etre egal a const uint32_t delayFlottement (reserve pleine) pour que l'osmolation soit active des le demarrage
uint32_t compteurPinInFlotteurReserveHaut;
uint32_t compteurPinInFlotteurNiveauConstant;
boolean compteurPinInFlotteurNiveauConstantBasON = false;
boolean compteurPinInFlotteurNiveauConstantHautON = false;
boolean smsAlerteOsmolation = true;
boolean smsAlerteGodet = true;
boolean smsAlerteSecurite = true;
boolean smsAlerteReserve = true;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonction $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* lit l'etat du flotteurs securite decante*/
void flotteurs() {
  if (digitalRead (pinInFlotteurSecurite) == HIGH) { // flotteur securite HAUT = tout couper
    digitalWrite(pinOutRelaisOsmolation, LOW); // relais OFF = osmolateur OFF
    digitalWrite(pinOutRelaisEcumeur, HIGH);// relais ecumeur ON = ecumeur OFF
    if (smsAlerteSecurite ) { // si boolean alerte true envoie alerte + alarme
      completerMessageAlerte(texteNextionAlerte, smsAlerteSecuriteDecante); // lance la fonction
      smsAlerteSecurite = false; // boolean pour ne pas avoir de message a repetition
      alarme(); // lance la fonction
      DPRINTF("alarme flotteur securite haut "); DPRINTLN() // debug
    }
  }
  else {// flotteur securite BAS = voir autres flotteurs
    if (smsAlerteSecurite == false) { // si fin d'alerte
      completerMessageAlerte(texteNextionFinAlerte, smsSecuriteDecanteOk); // lance la fonction
      smsAlerteSecurite = true; // boolean pour ne pas avoir de message a repetition
      alarmeOnOff = true; // remet l'alarme sonore On
      DPRINTF("flotteur securite bas "); DPRINTLN() // debug
    }
    // DPRINTF("securite decante OK");  DPRINTLN(); // debug
    flotteurNiveauEcumeur(); // lance la fonction qui lit l'etat d'autres flotteurs
    flotteurReserve(); // lance la fonction qui lit l'etat d'autres flotteurs
  }
}

/* lit l'etat du flotteur niveau reserve d'eau osmosé */
void flotteurReserve() {
  if (digitalRead (pinInFlotteurReserve) == HIGH) { // reserve d'eau osmose OK
    const uint32_t delayFlottement = 1800000ul; // 30 minutes en millis pour ne pas avoir d'alerte/redemarage a repetition lors du remplissage de la reserve
    compteurPinInFlotteurReserveHaut = millis();
    if ( millis() - compteurPinInFlotteurReserveBas > delayFlottement) {
      flotteurNiveauConstant(); // lance la fonction qui lit l'etat d'autres flotteurs
      if (smsAlerteReserve == false) { // boolean pour ne pas avoir de message a repetition
        smsAlerteReserve = true; // remet SMS en On
        alarmeOnOff = true; // remet l'alarme sonore On
        compteurOsmolation = zero ; // remet le compteur d'osmolation a zero
        DPRINTF("reserve OK");  DPRINTLN(); // debug
      }
    }
  }
  else { // si reserve VIDE
    const uint16_t delayFlottement = 5000u; // 5 secondes en millis pour ne pas avoir d'alerte/redemarage a repetition lors de l'arret de la pompe
    if ( millis() - compteurPinInFlotteurReserveHaut > delayFlottement ) {
      digitalWrite(pinOutRelaisOsmolation, LOW); // relais osmolateur OFF
      compteurPinInFlotteurReserveBas = millis();
      // DPRINTF(" !!! reserve d'eau osmose vide");  DPRINTLN(); // debug
      if ( smsAlerteReserve ) { // si boolean true
        smsAlerteReserve = false; // boolean pour ne pas avoir de message a repetition
        completerMessageAlerte(texteNextionAlerte, smsReserveVide); // lance la fonction
        afficherAlerteOsmolationOffReserveVide(); // message erreur plus d'eau
        alarme(); // lance la fonction
        DPRINTF("alarme reserve bas "); DPRINTLN() // debug
      }
    }
  }
}

/* lit l'etat du flotteur niveau constant de la decante */
void flotteurNiveauConstant() {
  if (sauvegarde.dureeOsmolationMillis != zero) { // si la durée d'osmolation n'est pas OFF
    if ((digitalRead (pinInFlotteurOsmolation) == LOW) && (digitalRead (pinInFlotteurNiveauEcumeur) == LOW)) { // si flotteurniveau constant + flotteur niveau ecumeur bas
      if (compteurPinInFlotteurNiveauConstantBasON == false) {
        compteurPinInFlotteurNiveauConstant = millis();
        compteurPinInFlotteurNiveauConstantBasON = true;
      }
      if (osmolationOn) { // si boolean true
        tempsPrecedentOsmolation = millis(); // activation de la duree d'osmolation
        osmolationOn = false; // boolean pour ne pas avoir de remise a zero du compteur a repetition
      }
      if (compteurOsmolation < sauvegarde.compteurOsmolationMax) { //si compteur MAX pas atteind
        if (millis() - tempsPrecedentOsmolation < sauvegarde.dureeOsmolationMillis) { // osmolation si duree d'osmolation non depassé
          digitalWrite(pinOutRelaisOsmolation, HIGH); // relais osmolateur ON
          compteurPinInFlotteurNiveauConstantBasON = false; // passe le compteur OFF
          tempsAttenteOsmolation = millis(); // activation de la duree d'attente apres osmolation
          if ( smsAlerteOsmolation == false) { // si il y avait une alerte
            afficherAlerteOsmolationOff(); // efface le message d'alerte a l'ecran
          }
          DPRINTF("osmolation en cours");  DPRINTLN(); // debug
        }
        else if (millis() - tempsAttenteOsmolation <= (sauvegarde.dureeOsmolationMillis * quatre)) { // pause de 4 fois duree osmolation si duree osmolation depassee
          digitalWrite(pinOutRelaisOsmolation, LOW); // relais osmolateur OFF
          DPRINTF("osmolation en pause");  DPRINTLN(); // debug
        }
        else {
          digitalWrite(pinOutRelaisOsmolation, LOW);
          compteurOsmolation++; // +1 au compteur d'osmolation
          osmolationOn = true; // boolean pour remetre l'osmolation ON
          DPRINTF("+1 compte tour osmolation");  DPRINTLN(); // debug
        }
      }
      else { // quand compteur MAX atteind
        digitalWrite(pinOutRelaisOsmolation, LOW); // on coupe l'osmolation
        if (smsAlerteOsmolation ) { // si true
          smsAlerteOsmolation = false; // boolean pour ne pas avoir de message a repetition
          afficherAlerteOsmolation(); // affiche le message d'erreur a l'ecran
          completerMessageAlerte(texteNextionAlerte, smsTropOsmolation); // lance la fonction
          alarme(); // lance la fonction
          DPRINTF("alarme trop osmolation "); DPRINTLN() // debug
        }
      }
    }
    else { // quand flotteur osmolation en position haute
      if (compteurPinInFlotteurNiveauConstantBasON == false) { // si compteur OFF
        compteurPinInFlotteurNiveauConstant = millis(); // lance le compteur
        compteurPinInFlotteurNiveauConstantBasON = true; // passe le compteur en ON
      }
      digitalWrite(pinOutRelaisOsmolation, LOW); // relais osmolateur OFF
      compteurPinInFlotteurNiveauConstantHautON = false; // passe le compteur OFF
      if (osmolationOn == false) { // si false
        osmolationOn = true; // boolean pour remetre l'osmolation ON
        compteurOsmolation = zero ; // remet le compteur d'osmolation a zero
      }
      if ( smsAlerteOsmolation == false) { // si false
        afficherAlerteOsmolationOff(); // efface le message d'alerte a l'ecran
        completerMessageAlerte(texteNextionFinAlerte, smsOsmolationOk ); // envoie un SMS de fin d'alerte
        smsAlerteOsmolation = true; // boolean pour ne pas avoir de message a repetition
        alarmeOnOff = true; // remet l'alarme sonore On
        DPRINTF("niveau constant OK"); DPRINTF("/// "); DPRINT(variable.Heure); DPRINTF("h"); DPRINT(variable.minut); DPRINTLN(); // debug
      }
    }
  }
}

/* lit l'etat du flotteur niveau ecumeur + godet ecumeur */
void flotteurNiveauEcumeur() { //
  if ((digitalRead (pinInFlotteurNiveauEcumeur) == LOW) && (digitalRead (pinInFlotteurGodetEcumeur) == LOW)) { // flotteur niveau ecumeur + godet en bas
    digitalWrite(pinOutRelaisEcumeur, LOW); // relais ouvert = ecumeur ON
    //DPRINTF("ecumeur ok");  DPRINTLN(); // debug
    if (smsAlerteGodet == false) { // fin d'alerte godet plein
      afficherAlerteGodetOK();
      DPRINTF("godet ecumeur OK");  DPRINTLN(); // debug
    }
  }
  else {
    if (digitalRead (pinInFlotteurNiveauEcumeur) == HIGH) {// flotteur niveau ecumeur
      digitalWrite(pinOutRelaisEcumeur, HIGH); // relais fermer = cumeur OFF
      digitalWrite(pinOutRelaisOsmolation, LOW); // relais osmolateur OFF
      //DPRINTF("flotteurs haut ecumeur Off");  DPRINTLN(); // debug
    }
    if (digitalRead (pinInFlotteurGodetEcumeur) == HIGH) {// flotteur godet ecumeur haut
      digitalWrite(pinOutRelaisEcumeur, HIGH); // relais fermer = cumeur OFF
      //DPRINTF("godet plein, ecumeur Off");  DPRINTLN(); // debug
      if (smsAlerteGodet ) { // alerte godet plein
        completerMessageAlerte(texteNextionAlerte, smsGodetPlein);
        alarme(); // lance la fonction
        smsAlerteGodet = false; // boolean pour ne pas avoir de message a repetition
        afficherAlerteGodetPlein();
        DPRINTF("SMS godet plein, ecumeur Off, smsAlerteGodet = ");  DPRINTLN(smsAlerteGodet); // debug
      }
    }
    else {
      if (smsAlerteGodet == false) {
        afficherAlerteGodetOK();
      }
    }
  }
}
