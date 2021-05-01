
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
#include <Wire.h>
#include "RTClib.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "horloge.h"
#include "global.h"
#include "affichage.h"
#include "autres.h"
#include "debug.h"
#include "wifi.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// *************************************** recuperation de l'heure du ds3231 ***************************************************************************
RTC_DS3231 rtc;
uint32_t Time, H;
uint16_t M, annee;
uint8_t jour, mois, jourJ, moisM;
const uint8_t minuteEnSeconde = 60; // pour convertir seconde en minute
const uint16_t HeureEnSeconde = 3600u;
uint32_t tempsPrecedentNourrissage, tempsPrecedentTempete, tempsPrecedentTempeteAleatoire;
const uint8_t maxTexTime = 5;
char textime[maxTexTime + 1]; // pour stocker l'heure en char
const uint8_t maxminuteEnTexte = 2; // place pour convertir les minute en texte
char minuteEnTexteIn[maxminuteEnTexte + 1]; // pour stoker minute en char
char minuteEnTexteOut[maxminuteEnTexte + 1]; // pour stoker minute en char

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonctions $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* recupere l'heure */
void horaire() {
  DateTime now = rtc.now(); // recupere l'heure
  variable.Heure = now.hour(); // copie les heures
  variable.minut = now.minute(); // copie les minutes
  variable.seconde = now.second(); // copie les seconde
  jour = now.day(); // copie le jour
  mois = now.month(); // copie le mois
  annee = now.year(); // copis l'annee
  /* convertie l'heure au format seconde */
  H = (uint32_t)variable.Heure * HeureEnSeconde; // heure en seconde
  //DPRINTF("H : "); DPRINT(H); DPRINTLN();
  M = (uint16_t)variable.minut * minuteEnSeconde; // minute en seconde
  //DPRINTF("M : "); DPRINT(M); DPRINTLN();
  Time = H + M + variable.seconde; // adition pour avoir l'heure en seconde
  //DPRINTF("Time : "); DPRINT(Time); DPRINTLN();
}

/* converti l'heure en char */
void TIMEenTEXTE(uint32_t t) {
  uint16_t h, m;
  uint8_t maxTampon = 2; // taille max de tampon
  char tampon[maxTampon + 1]; // taille max de tampon + caractere de fin
  textime[0] = '\0'; // on initialise la chaine à vide
  //DPRINTF("t : "); DPRINT(t); DPRINTLN();
  h = t / HeureEnSeconde; // convertie seconde en heure
  // DPRINTF("h : "); DPRINT(h); DPRINTLN();
  if (h == zero) { // si = zero
    h = zero;
  }
  itoa (h, textime, 10); // met numerique dans char
  strcat(textime, "H");
  m = (t / minuteEnSeconde) % minuteEnSeconde; // converti seconde en minut
  // DPRINTF("m : "); DPRINT(m); DPRINTLN();
  if (m < dix) { // si inferieur a 10 ajoute un zero
    strcat(textime, "0");
  }
  itoa (m, tampon, 10); // met numerique dans char
  strcat(textime, tampon);
  //DPRINTF("textime : "); DPRINT(textime); DPRINTLN();
}

/* converti temps en seconde en heure/minute puis minute en char */
void secondeEnHorraire(uint32_t t) {
  uint32_t h, m;
  minuteEnTexteOut[0] = '\0'; // initialise la chaine
  h = t / HeureEnSeconde; // converti en heure
  m = (t / minuteEnSeconde) % minuteEnSeconde; // converti en minute
  number = h;
  if (m == zero) { // si minute = 0
    minuteEnTexteOut[0] = '0'; // on ajoute 0
    minuteEnTexteOut[1] = '0';// on ajoute 0
    minuteEnTexteOut[2] = '\0'; // caractere de fin
  }
  else if (m == 5) {
    minuteEnTexteOut[0] = '0'; // on ajoute 0
    minuteEnTexteOut[1] = '5'; // on ajoute 5
    minuteEnTexteOut[2] = '\0'; // carractere de fin
  }
  else { // sinon
    itoa (m, minuteEnTexteOut, 10); // converti minute en "char"
  }
}

/* converti heure + minute en char en seconde */
void horraireEnSeconde(uint32_t h, char m [maxminuteEnTexte]) {
  uint16_t M = atoi(m); // convertie les minute char en numerique
  recupHorraireTemporraire = ((h * HeureEnSeconde) + (M * minuteEnSeconde)); // cumule heure et minute
}

/* initialisation de l'horloge */
void initialisationDuDs3231() {
  boolean horlogeDS3231 = false; // si l'horloge est detecté passe en true
  Wire.beginTransmission(DS3231_ADDRESS); // cherche si horloge presente a  son adresse
  byte erreur = Wire.endTransmission(); // transmission ok ou pas
  if (erreur == 0) { // si transmission ok
    texteProgmemAuNextion(texte2, texteNextionHorlogeDetectee, vert); // champ, texte, couleur
    horlogeDS3231 = true; // l'horloge est presente
    DDELAY(deuxMille);
    if (rtc.lostPower()) { // regarde si l'horloge a deja ete initialisé (mise a l'heure) et si il n'y a pas de probleme de batterie
      texteProgmemAuNextion(texte2, texteNextionHorlogeJamaisInitialise, orange); // champ, texte, couleur
    }
    else {
      texteProgmemAuNextion(texte2, texteNextionInitialisationHorlogeOK, vert); // champ, texte, couleur
    }
    rtc.now(); // recupere l'heure
  }
  if (horlogeDS3231 == false) { // l'horloge n'as pas ete detecte
    texteProgmemAuNextion(texte2, texteNextionPasDeReponseHorloge, rouge); // champ, texte, couleur
  }
}

void dateGraph(int8_t jourX) {
  uint8_t maxTampon = 2; // taille max de tampon
  char tampon[maxTampon + 1]; // taille max de tampon + caractere de fin
  textime[0] = '\0'; // on initialise la chaine à vide
  DateTime now = rtc.now(); // recupere l'heure
  DateTime datePrecedente (now + TimeSpan(jourX, 0, 0, 0));
  jourJ = datePrecedente.day(); // copie le jour
  moisM = datePrecedente.month(); // copie le mois
  if (jourJ < dix) {
    strcat(textime, "0");
  }
  itoa (jourJ, tampon, 10); // met numerique dans char
  strcat(textime, tampon);
  strcat(textime, "/");
  if (moisM < dix) {
    strcat(textime, "0");
  }
  itoa (moisM, tampon, 10); // met numerique dans char
  strcat(textime, tampon);
}

void heureGraph(int8_t heureX) {
  uint8_t maxTampon = 2; // taille max de tampon
  char tampon[maxTampon + 1]; // taille max de tampon + caractere de fin
  textime[0] = '\0'; // on initialise la chaine à vide
  DateTime now = rtc.now(); // recupere l'heure
  DateTime heurePrecedente (now + TimeSpan(0, heureX, 0, 0));
  uint8_t heureH = heurePrecedente.hour(); // copie le jour
  if (heureH < dix) {
    strcat(textime, "0");
  }
  itoa (heureH, tampon, 10); // met numerique dans char
  strcat(textime, tampon);
  strcat(textime, "h");
}
