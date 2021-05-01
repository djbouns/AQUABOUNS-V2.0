
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
#include <arduino.h>
#include <EEPROM.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include "wifi.h"
#include "global.h"
// pin test
#include "debug.h"
#include "eeprom.h"
#include "autres.h"
#include "carteSD.h"
#include "affichage.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
const uint8_t maxSsid = 30;// prévois la place
const uint8_t maxMdp = 30;// prévois la place
valeursActuel_t variable; // structure variable
identifiantDeConnection_t identifiantWifi; // structure indentifiantwifi
etatconnection_t connectionWifi; // structure connectionwifi
const size_t tailleCommande = 4; // 4 caractères pour la taille des commande
const char *  lesCommandes[] = {"$E1$", "$E2$", "$E3$", "$E4$", "$R1$", "$R2$", "$R3$", "$R4$"}; // nom des commande
const size_t nbCommandes = sizeof(lesCommandes) / sizeof(lesCommandes[0]); // pour le nbr de commande
const size_t tailleParamS_t = sizeof(paramS_t); // taille de la structure
const size_t taillevaleursActuel_t = sizeof(valeursActuel_t); // taille de la structure
const size_t tailleetatconnection_t = sizeof(etatconnection_t); // taille de la structure
const size_t tailleidentifiantDeConnection_t = sizeof(identifiantDeConnection_t); // taille de la structure

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonctions $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
boolean envoyerData(uint8_t * d, size_t taille ) {
  size_t somme = d1mini.write((uint8_t *) d, taille); // envoi des données
  DPRINTF("somme : "); DPRINT(somme); DPRINTF(" // taille : "); DPRINT(taille); DPRINTLN();
  return (somme == taille); // retourne vrai si le bon nombre d'octet a été envoyé
}

boolean recevoirData(uint8_t * d, size_t taille) {
  size_t somme =  d1mini.readBytes(d, taille); // reception des données
  DPRINTF("somme : "); DPRINT(somme); DPRINTF(" // taille : "); DPRINT(taille); DPRINTLN();
  return (somme == taille); // retourne vrai si le bon nombre d'octet a été reçu avant le timeout
}

void ecouterModuleWifi() {
  typeCommande_t commandeDistante = ecouterCommandeDistante();
  if (commandeDistante != AUCUNE) executer(commandeDistante, false);
}

void executer(typeCommande_t uneCommande, boolean commandeLocale) { // execute la commande demandée
  switch (uneCommande) {
    case ENVOYERsauvegarde:
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[RECEVOIRsauvegarde], tailleCommande); // on envoie la demande
      }
      if (!envoyerData((uint8_t *) &sauvegarde, tailleParamS_t )) { // si la structure envoyer ne correspond pas a la structure demandée
        DPRINTF("Erreur envoi params"); DPRINTLN();
        horodatageEtEcritSurSD (texteSurSDErreurEnvoiParamS, "");
      }
      else { // sinon c'est OK
        DPRINTF("params envoyer"); DPRINTLN();
      }
      break;
    case ENVOYERvariable:
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[RECEVOIRvariable], tailleCommande); // on envoie la demande
      }
      /* pour connaitre le nombre de pompe en ON pour ensuite faire la moyenne */
      variable.nbrBrassageEnON = zero; // on initialise le nombre de pompe de Brassage en ON
      for (uint8_t i = numeroUn; i <= numeroTrois ; i++) { //boucle de la pompe 1 a 3
        if (sauvegarde.BrassageOnOffPwm[i] != Arret) { // si la pompe n'est pas arreté
          variable.nbrBrassageEnON++; // on ajoute +1 pompe en ON
          DPRINTF("nbr de pompe ON ou PWM = "); DPRINT(variable.nbrBrassageEnON); DPRINTLN();
        }
      }
      if (!envoyerData((uint8_t *) &variable, taillevaleursActuel_t )) { // si la structure envoyer ne correspond pas a la structure demandée
        DPRINTF("Erreur envoi variables"); DPRINTLN();
        horodatageEtEcritSurSD (texteSurSDErreurEnvoiVariables, "");
      }
      else { // sinon c'est OK
        DPRINTF("variables envoyer"); DPRINTLN();
      }
      break;
    case ENVOYERidentifiantWifi:
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[RECEVOIRidentifiantWifi], tailleCommande); // on envoie la demande
      }
      if (!envoyerData((uint8_t *) &identifiantWifi, tailleidentifiantDeConnection_t )) { // si la structure envoyer ne correspond pas a la structure demandée
        DPRINTF("Erreur envoi identifiantWifi"); DPRINTLN();
        horodatageEtEcritSurSD (texteSurSDErreurEnvoiIdentifiant, "");
      }
      else { // sinon c'est OK
        DPRINTF("identifiantWifi envoyer"); DPRINTLN();
      }
      break;
    case ENVOYERconnectionWifi:
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[RECEVOIRconnectionWifi], tailleCommande); // on envoie la demande
      }
      if (!envoyerData((uint8_t *) &connectionWifi, tailleetatconnection_t )) { // si la structure envoyer ne correspond pas a la structure demandée
        horodatageEtEcritSurSD (texteSurSDErreurEnvoiConnection, "");
        DPRINTF("Erreur envoie connectionWifi"); DPRINTLN();
      }
      else { // sinon c'est OK
        DPRINTF("connectionWifi envoyer"); DPRINTLN();
      }
      break;
    case  RECEVOIRsauvegarde:
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[ENVOYERsauvegarde], tailleCommande); // on envoie la demande
      }
      if (!recevoirData((uint8_t *) &sauvegarde, tailleParamS_t)) { // si la structure demander ne correspond pas a la structure recu
        DPRINTF("Erreur reception params"); DPRINTLN();
        horodatageEtEcritSurSD (texteSurSDErreurRecepParamS, "");
      }
      else { // sinon c'est OK
        EEPROM.put(adresseDeSauvegarde, sauvegarde); // sauvegarde tout les parametres
        DPRINTF("params recu et sauvegarder"); DPRINTLN();
      }
      break;
    case  RECEVOIRvariable:
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[ENVOYERvariable], tailleCommande); // on envoie la demande
      }
      if (!recevoirData((uint8_t *) &variable, taillevaleursActuel_t)) { // si la structure demander ne correspond pas a la structure recu
        DPRINTF("Erreur reception variables"); DPRINTLN();
        horodatageEtEcritSurSD (texteSurSDErreurRecepVariable, "");
      }
      else { // sinon c'est OK
        DPRINTF("variables recu"); DPRINTLN();
      }
      break;
    case  RECEVOIRidentifiantWifi:
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[ENVOYERidentifiantWifi], tailleCommande); // on envoie la demande
      }
      if (!recevoirData((uint8_t *) &identifiantWifi, tailleidentifiantDeConnection_t)) { // si la structure demander ne correspond pas a la structure recu
        DPRINTF("Erreur reception identifiantWifi"); DPRINTLN();
        horodatageEtEcritSurSD (texteSurSDErreurRecepIdentifiant, "");
      }
      else { // sinon c'est OK
        DPRINTF("identifiantWifi recu"); DPRINTLN();
      }
      break;
    case  RECEVOIRconnectionWifi:
      connectionWifi.connecter = false; // initialise le statut "non connecter au wifi" // passe en true si connecter au reseau wifi
      if (commandeLocale) { // si demande local
        d1mini.write((uint8_t *) lesCommandes[ENVOYERconnectionWifi], tailleCommande); // on envoie la demande
      }
      if (!recevoirData((uint8_t *) &connectionWifi, tailleetatconnection_t)) { // si la structure demander ne correspond pas a la structure recu
        DPRINTF("Erreur reception connectionWifi"); DPRINTLN();
        connectionWifi.presenceModule = false; // initialise le statut "non connecter au wifi" // passe en true si reponse du module
        horodatageEtEcritSurSD (texteSurSDErreurRecepConnection, "");
      }
      else { // sinon c'est OK
        DPRINTF("connectionWifi.presenceModule : "); DPRINT(connectionWifi.presenceModule); DPRINTLN();
        DPRINTF("connectionWifi recu"); DPRINTLN();
      }
      break;
    case  AUCUNE:
      break;
  }
}

typeCommande_t ecouterCommandeDistante() {
  static uint8_t sentinelle[tailleCommande]; // pour recevoir les données
  static uint8_t indice = zero; // la position dans le buffer circulaire
  typeCommande_t commandeRecue = AUCUNE;
  if (d1mini.available()) {
    if (indice == tailleCommande) indice = zero;
    sentinelle[indice] = (uint8_t) d1mini.read();
    for (uint8_t c = zero; c < nbCommandes; c++) { // on regarde si on a reçu une des commandes
      commandeRecue = (typeCommande_t) c; // petit hack car on a aligné l'enum pour qu'il commence à 0
      for (uint8_t i = zero; i < tailleCommande; i++) {
        if (sentinelle[(indice + un + i) % tailleCommande] != lesCommandes[c][i]) {
          commandeRecue = AUCUNE;
          break;
        }
      }
      if (commandeRecue != AUCUNE) break;
    }
    if (commandeRecue != AUCUNE) {
      // on se reprépare pour la prochaine fois
      memset(sentinelle, zero, tailleCommande); // On efface la sentinelle pour la prochaine fois (http://www.cplusplus.com/reference/cstring/memset/)
      indice = zero;
    } else indice++;
  }
  return commandeRecue;
}

void etatWifi() {
  executer(RECEVOIRconnectionWifi, true); // demande le statut de connection // pour voir si le module est connecté et repond
  if (connectionWifi.presenceModule == false) {
    horodatageEtEcritSurSD (texteSurSDRebootGWifi, "");
    reboot(hardResetWIFI);
  }
  else {
    if (connectionWifi.connecter == false) {
      if (SD.begin(SD_CS_PIN)) { // Si carte SD bien initialisée
        lisSurSd(ssidSurSD, identifiantWifi.ssid, maxSsid); // lance la lecture/copie du fichier
        lisSurSd(mdpSurSD, identifiantWifi.mdp, maxMdp); // lance la lecture/copie du fichier
        lisSurSd(numero2TelSurSD, numero2tel, maxnumero2tel); // lance la lecture/copie du fichier
      }
    }
  }
}
