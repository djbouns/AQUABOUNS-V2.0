
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
#include "SdFat.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include "global.h"
#include "debug.h"
#include "affichage.h"
#include "wifi.h"
#include "carteSD.h"
#include "RTClib.h"
#include "eeprom.h"
#include <avr/wdt.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
SdFat SD;
File myFile;
const char* ssidSurSD = "ssid.txt";
const char* mdpSurSD = "mdp.txt";
const char* numero2TelSurSD = "numero2tel.txt";
const char* erreursSurSD = "erreur.txt";
const char* indexErreursSurSD = "indexErreurs.txt";
const char* mesuresEnBinaire = "mesuresBinairePourGraph.txt";
const uint8_t tailleMaxNomFichier = 20; // la taille max d'un nom de fichier
stockDansSD_t stockMesuresDansSD;
boolean unEnregistrement = true;
const uint8_t nbr2Lignes = 1;
uint8_t numero2Ligne = 0 ;
boolean SDPrecedementVersLeBas = true;
uint16_t dernierPage = 0;
NexText*tableauLigneAffichageSd[] = {&valeursd00, &valeursd01, &valeursd02, &valeursd03, &valeursd04, &valeursd05, &valeursd06, &valeursd07,
                                     &valeursd08, &valeursd09, &valeursd10, &valeursd11, &valeursd12, &valeursd13, &valeursd14, &valeursd15, &valeursd16, &valeursd17
                                    };

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonctions $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* écrit sur la carte SD */
void ecritSurSd(const char * nomDuFichierTxt, char * donneeAEcrireSurSD) {
  if (strcmp (nomDuFichierTxt, erreursSurSD) != 0) { // si il ne s'agit pas du fichier erreur
    DPRINTF("Pas le fichier erreur.txt = on supprime l'ancien fichier : "); DPRINTLN(nomDuFichierTxt); DPRINTLN();
    SD.remove(nomDuFichierTxt); // suprime l'ancien fichier
    myFile = SD.open(nomDuFichierTxt, O_WRITE | O_CREAT);
    DPRINTF("Ouverture du fichier : "); DPRINTLN(nomDuFichierTxt);
  }
  else {
    DPRINTF("fichier erreur.txt"); DPRINTLN();
    myFile = SD.open(nomDuFichierTxt, O_WRITE | O_CREAT | O_AT_END);
    DPRINTF("Ouverture du fichier : "); DPRINTLN(nomDuFichierTxt);
  }
  if (myFile) {
    if (strcmp (nomDuFichierTxt, erreursSurSD) == 0) { // si il s'agit du fichier erreur
      while (strlen(donneeAEcrireSurSD) < maxbufferTexte - 2) {
        strcat(donneeAEcrireSurSD, " "); // ajoute a la chaine de caractere
      }
    }
    myFile.print(donneeAEcrireSurSD); // ecrit dans le fichier
  }
  if (strcmp (nomDuFichierTxt, erreursSurSD) == 0) { // si il s'agit du fichier erreur
    myFile.println(); // on passe a la ligne suivante
  }
  myFile.close(); // ferme le fichier
}

/* lis sur la carte SD */
boolean lisSurSd(const char * nomDuFichierTxt, char *donneeLueSurSD, size_t indexEcritureMAX) {
  boolean lectureOK = false; // retourne l'etat de lecture
  uint8_t i = 0;
  DPRINTF("Ouverture de : "); DPRINTLN(nomDuFichierTxt);//debug
  myFile = SD.open(nomDuFichierTxt, O_READ); // ouvre le fichier
  if (myFile) {
    donneeLueSurSD[0] = '\0'; // on initialise la chaine à vide
    while (myFile.available()) { // on lit l'intégralité du fichier, à concurrence de l'espace dispo dans notre buffer
      if (i <= indexEcritureMAX) {
        donneeLueSurSD[i] = myFile.read(); // lit le fichier
        i++;
      }
      else {
        donneeLueSurSD[indexEcritureMAX] = '\0'; // ajoute caractere de fin
        break;
        DPRINTF("break 3"); DPRINTLN();
      }
    }
    DPRINTF("plus rien a lire"); DPRINTLN();
    donneeLueSurSD[i] = '\0';  // il n'y a plus rien à lire dans le fichier, on termine
    lectureOK = true; // la lecture c'est bien passé
    myFile.close(); // ferme le fichier
    effaceBufferTexte(); // efface le buffer
    strncpy_P (bufferTexte, texteNextionImportationDe, maxbufferTexte); // recupere "char" en memoire flash et le copie
    bufferTexte[maxbufferTexte] = '\0'; // ajoute le caractere de fin
    if (strlen(bufferTexte) + strlen(nomDuFichierTxt) < maxbufferTexte) {
      strcat(bufferTexte, nomDuFichierTxt); // ajoute a la chaine de caractere
      if (strlen(bufferTexte) + strlen(nomDuFichierTxt) < maxbufferTexte) {
        strcat(bufferTexte, ", OK"); // ajoute a la chaine de caractere
        if (pageActuelNextion == demarrage) { // si l'ecran est sur la page de demarrage
          texte4.Set_font_color_pco(vert); // texte couleur vert
          texte4.setText(bufferTexte);// envoi char a l'ecran nextion// envoi char a l'ecran nextion
          DDELAY(mille);
        }
        else {
          effaceBufferTexte();
          strncpy_P (bufferTexte, texteNextionPasDeFichier, maxbufferTexte); // recupere "char" en memoire flash et le copie
          bufferTexte[maxbufferTexte] = '\0'; // ajoute le caractere de fin
          strcat(bufferTexte, nomDuFichierTxt); // ajoute a la chaine de caractere
          if (pageActuelNextion == demarrage) { // si l'ecran est sur la page de demarrage
            texte4.Set_font_color_pco(rouge); // text couleur rouge
            texte4.setText(bufferTexte);// envoi char a l'ecran nextion// envoi char a l'ecran nextion
          }
          DPRINT(bufferTexte); DPRINTLN(); // debug
          DDELAY(mille);
        }
        DPRINT(bufferTexte); DPRINTLN(); // debug
      }
      else {
        DPRINTF("probleme de place memoire dans lisSurSd niveau 2");  DPRINTLN(); // debug
      }
    }
    else {
      DPRINTF("probleme de place memoire dans lisSurSd niveau 1");  DPRINTLN(); // debug
    }
  }
  else {
    myFile = SD.open(nomDuFichierTxt, O_WRITE | O_CREAT | O_AT_END);
    myFile.close(); // ferme le fichier
  }
  return lectureOK;
}

/* ecrit l'heure sur la carte sd */
void horodatageEtEcritSurSD (const char Erreur1AAjouter[] PROGMEM, const char* Erreur2AAjouter) {
  uint8_t maxstock = 60;
  char stock [maxstock + 1];
  char stock2 [maxstock + 1];
  memset(stock2, '\0', maxstock); // effacer buffer
  //effaceBufferTexte();
  //strcat(stock2, " ");
  itoa (jour, stock, 10); // converti numerique en char
  strcat(stock2, stock); // ajoute a la chaine
  strcat(stock2, "/"); // ajoute a la chaine
  itoa (mois, stock, 10); // converti numerique en char
  if (mois < dix) { // si inferieur a dix on ajoute un zero
    strcat(stock2, "0"); // ajoute a la chaine
  }
  strcat(stock2, stock); // ajoute a la chaine
  strcat(stock2, " "); // ajoute a la chaine
  itoa (variable.Heure, stock, 10); // converti numerique en char
  strcat(stock2, stock); // ajoute a la chaine
  strcat(stock2, "H"); // ajoute a la chaine
  itoa (variable.minut, stock, 10); // converti numerique en char
  if (variable.minut < dix) { // si inferieur a dix on ajoute un zero
    strcat(stock2, "0"); // ajoute a la chaine
  }
  strcat(stock2, stock); // ajoute a la chaine
  strcat(stock2, " : "); // ajoute a la chaine
  strncpy_P (stock, Erreur1AAjouter, maxstock); // recupere "char" en memoire flash et le copie
  stock[maxstock] = '\0'; // caractere de fin
  DPRINTF("horodatage3 : "); DPRINTLN(stock); // debug
  strcat(stock2, stock); // ajoute a la chaine
  DPRINTF("horodatage4 : "); DPRINTLN(stock2); // debug
  DPRINTF("horodatage5 : "); DPRINTLN(Erreur2AAjouter); // debug
  strcat(stock2, Erreur2AAjouter);  // ajoute a la chaine
  DPRINTF("horodatageEtEcritSurSD : "); DPRINTLN(stock2); // debug
  logMessage(stock2);
}

/*vide le fichier erreur de la carte sd */
void videFichierErreur() {
  SD.remove(erreursSurSD); // suprimme l'ancien fichier
  SD.remove(indexErreursSurSD); // suprimme l'ancien fichier
  prepareFichiersLog(finDuFichier, false); // true -> on force la destruction des fichiers // "        *.*.*.*.*.* FIN DU FICHIER *.*.*.*.*.*"
}

/* ecrit sur la carte SD en binnaire les donner pour le graphique */
void stockMesuresEnBinaire() {
  DateTime now = rtc.now(); // recupere la date et heure
  stockMesuresDansSD.horodatage = now.unixtime(); // stock date et heure en binaire
  stockMesuresDansSD.clef = motClef ; // clef pour controler que l'on lit bien en face
  stockMesuresDansSD.mesuresT = variable.temperatureBac * cent; // copie et convertie la temperature du bac 26°5 = 2650 // pour test : random (2600, 2650)
  if (pageActuelNextion != orph) { // si sur page orph on n'enregistre pas les mesure sur la carte sd // garde la valeur precedente la mesure precedente
    stockMesuresDansSD.mesuresPh = variable.phBac; // variable.phBac; // copie le Ph du bac // pour test : random (780, 820)
    stockMesuresDansSD.mesuresRedox = variable.redox; // copie le redox du bac // pour test : random (250, 500)
    stockMesuresDansSD.mesuresSalinite = variable.salinite; // copie la salinitedu bac // pour test : random (1023, 1025)
  }
  myFile = SD.open(mesuresEnBinaire, O_WRITE | O_CREAT | O_AT_END); // ouvre le fichier
  DPRINTF("Ouverture du fichier : "); DPRINTLN(mesuresEnBinaire); // debug
  if (myFile) {
    myFile.write(&stockMesuresDansSD, sizeof(stockMesuresDansSD)); // ecrit dans le fichier
    DPRINTF("Ecrit les mesures sur la carte SD"); DPRINTLN(); // debug
  } else {
    DPRINTF("Erreur d'écriture dans le fichier "); DPRINTLN(); // debug
  }
  myFile.close(); // ferme le fichier
}

/* lit sur la carte SD les données binnaire pour le graphique 7 jours */
void lisMesuresEnBinaire24h() {
  boolean heureDerniereMesure = false;
  uint16_t nbr2MesuresPourLeGraphique = (92 + (variable.minut / 15)) ; // 23 heures * 4 mesures par heure + 1 mesure toute les 15 min de l'heure en cours
  uint16_t indexMesure = 1; // index des mesures
  myFile = SD.open(mesuresEnBinaire, O_READ); // ouvre le fichier
  if (myFile) { // fichier ouvert
    uint8_t indexErreur = 0; // index pour decaler la lecture si erreur/clef non conforme
    uint16_t nbr2MesureMax = (myFile.fileSize() / sizeof(stockDansSD_t)) + indexMesure; // stock le nombre de mesure maximum qu'il y a sur la carte sd
    uint16_t quinzeMinutes = 900; // 15 minutes en secondes
    uint16_t bufferT = 0;
    uint16_t bufferPh = 0;
    uint16_t bufferRedox = 0;
    float bufferSalinite = 0.00;
    DateTime now = rtc.now(); // recupere la date et heure actuel
    uint32_t tempsEntreLesMesures = now.unixtime(); // recupere date/heure au format unixtime = en seconde
    DPRINTF("taille du fichier mesuresEnBinaire : "); DPRINTLN(myFile.fileSize()); // debug
    while (indexMesure < nbr2MesuresPourLeGraphique) { // on boucle autent de fois qu'il faut de pixel pour le graphique
      if (indexMesure >= nbr2MesureMax) { // si index est supperieur au nombre de mesure dispo sur la carte SD
        graphique24H(zero, bufferT, zero, bufferPh, zero, bufferRedox, zero, bufferSalinite); // lance la fonction
        bufferT = 0;
        bufferPh = 0;
        bufferRedox = 0;
        bufferSalinite = 0;
        indexMesure++; // incremente l'index
      }
      else {
        //DPRINTF("emplacement : "); DPRINTLN((myFile.fileSize() - (indexErreur + (sizeof(stockDansSD_t)*indexMesure)))); // debug
        myFile.seek(myFile.fileSize() - (indexErreur + (sizeof(stockDansSD_t)*indexMesure))); // on se place dans le fichier
        myFile.read(&stockMesuresDansSD, sizeof(stockDansSD_t)); // lit le fichier
        //DPRINTF("clef : "); DPRINTLN(stockMesuresDansSD.clef); // debug
        if (stockMesuresDansSD.clef == motClef) { // si la clef lu correspond a la clef de controle
          if (heureDerniereMesure == false) { // pour lire la date une fois
            DateTime dateDesMesures = stockMesuresDansSD.horodatage; // convertie l'unixtime en date
            //DPRINTF("date : ");  DPRINT(dateDesMesures.day()); DPRINTF("/"); DPRINT(dateDesMesures.month()); DPRINTF("/"); DPRINTLN(dateDesMesures.year()); // debug
            heureDerniereMesure = true; // pour lire la date une fois
          }
          if (tempsEntreLesMesures - quinzeMinutes < stockMesuresDansSD.horodatage) { // si la mesure lu est prise dans les 15 minutes precedent la derniere mesure lu
            if (bufferT == 0) {
              bufferT = stockMesuresDansSD.mesuresT;
            }
            if ( bufferPh == 0) {
              bufferPh = stockMesuresDansSD.mesuresPh;
            }
            if ( bufferRedox == 0) {
              bufferRedox = stockMesuresDansSD.mesuresRedox;
            }
            if ( bufferSalinite == 0) {
              bufferSalinite = stockMesuresDansSD.mesuresSalinite;
            }
            graphique24H(stockMesuresDansSD.mesuresT, bufferT, stockMesuresDansSD.mesuresPh, bufferPh, stockMesuresDansSD.mesuresRedox, bufferRedox, stockMesuresDansSD.mesuresSalinite, bufferSalinite); // lance la fonction
            bufferT = stockMesuresDansSD.mesuresT;
            bufferPh = stockMesuresDansSD.mesuresPh;
            bufferRedox = stockMesuresDansSD.mesuresRedox;
            bufferSalinite = stockMesuresDansSD.mesuresSalinite;
            indexMesure++; // increment l'index des mesures
          }
          else {
            graphique24H(zero, zero, zero, zero, zero, zero, zero, zero); // lance la fonction graphique24H(zero, bufferT, zero, bufferPh, zero, bufferRedox);
            bufferT = 0;
            bufferPh = 0;
            bufferRedox = 0;
            bufferSalinite = 0;
            nbr2MesuresPourLeGraphique--; // on decremente le nbr de mesure pour le graph puisque on a dessiner un pixel sans incrementer l'index
            //DPRINTF("trou dans la chronologie des mesures"); DPRINTLN(); // debug
          }
          tempsEntreLesMesures = tempsEntreLesMesures - quinzeMinutes;
          //DPRINTF("tempsEntreLesMesures : "); DPRINT(tempsEntreLesMesures); DPRINTLN(); // debug
          //DPRINTF("stockMesuresDansSD.horodatage : "); DPRINT(stockMesuresDansSD.horodatage); DPRINTLN(); // debug
        }
        else {
          //DPRINTLN("erreur dans la lecture binaire des mesures"); // debug
          indexErreur++; // increment l'index des erreurs
        }
      }
      wdt_reset(); // indique que le loop est OK, pas de bug, remise a zero du compteur "reboot" du watchdog car la lecture de toute les mesure pourait depasser le timer du watchdog
    }
    //DPRINTF("taille : "); DPRINTLN(sizeof(stockDansSD_t)); // debug
    myFile.close(); // ferme le fichier
  }
  else { // erreur a l'ouverture du fichier
    //DPRINTLN("Erreur a l'ouverture du fichier mesuresEnBinaire"); // debug
    while (indexMesure < nbr2MesuresPourLeGraphique) { // on boucle autent de fois qu'il faut de pixel pour le graphique
      graphique24H(zero, zero, zero, zero, zero, zero, zero, zero); // lance la fonction
      nbr2MesuresPourLeGraphique--; // on decremente le nbr de mesure pour le graph puisque on a dessiner un pixel sans incrementer l'index
    }
  }
}

/* lit sur la carte SD les données binnaire pour le graphique 7 jours */
void lisMesuresEnBinaire7J() {
  boolean dateDerniereMesure = false;
  const byte pixParH = 4; // 4 pixels par heure sur le graph
  const byte TempParPix = 15; // 1 pixel represente 15 min minutes
  const uint16_t PixPour6J = 576; // 6 jours represente 576 pixel sur le graph
  uint16_t nbr2MesuresPourLeGraphique = (PixPour6J + (variable.Heure * pixParH) + (variable.minut / TempParPix)) ; // 96 pixels = 1 jours /// 6 jours = 576 pixel + 4 pixels par heure du jour J + 1 pixel toute les 15 min du jour J
  uint16_t indexMesure = 1; // index des mesures
  myFile = SD.open(mesuresEnBinaire, O_READ); // ouvre le fichier
  if (myFile) { // fichier ouvert
    uint8_t indexErreur = 0; // index pour decaler la lecture si erreur/clef non conforme
    uint16_t nbr2MesureMax = (myFile.fileSize() / sizeof(stockDansSD_t)) + indexMesure; // stock le nombre de mesure maximum qu'il y a sur la carte sd
    uint16_t quinzeMinutes = 900; // 15 minutes en secondes
    DateTime now = rtc.now(); // recupere la date et heure actuel
    uint32_t tempsEntreLesMesures = now.unixtime(); // recupere date/heure au format unixtime = en seconde
    DPRINTF("taille du fichier mesuresEnBinaire : "); DPRINTLN(myFile.fileSize()); // debug
    while (indexMesure < nbr2MesuresPourLeGraphique) { // on boucle autent de fois qu'il faut de pixel pour le graphique
      if (indexMesure >= nbr2MesureMax) { // si index est supperieur au nombre de mesure dispo sur la carte SD
        graphique7J(zero, zero, zero, zero); // lance la fonction
        indexMesure++; // incremente l'index
      }
      else {
        //DPRINTF("emplacement : "); DPRINTLN((myFile.fileSize() - (indexErreur + (sizeof(stockDansSD_t)*indexMesure)))); // debug
        myFile.seek(myFile.fileSize() - (indexErreur + (sizeof(stockDansSD_t)*indexMesure))); // on se place dans le fichier
        myFile.read(&stockMesuresDansSD, sizeof(stockDansSD_t)); // lit le fichier
        //DPRINTF("clef : "); DPRINTLN(stockMesuresDansSD.clef); // debug
        if (stockMesuresDansSD.clef == motClef) { // si la clef lu correspond a la clef de controle
          if (dateDerniereMesure == false) { // pour lire la date une fois
            DateTime dateDesMesures = stockMesuresDansSD.horodatage; // convertie l'unixtime en date
            //DPRINTF("date : ");  DPRINT(dateDesMesures.day()); DPRINTF("/"); DPRINT(dateDesMesures.month()); DPRINTF("/"); DPRINTLN(dateDesMesures.year()); // debug
            dateDerniereMesure = true; // pour lire la date une fois
          }
          if (tempsEntreLesMesures - quinzeMinutes < stockMesuresDansSD.horodatage) { // si la mesure lu est prise dans les 15 minutes precedent la derniere mesure lu
            graphique7J(stockMesuresDansSD.mesuresT, stockMesuresDansSD.mesuresPh, stockMesuresDansSD.mesuresRedox, stockMesuresDansSD.mesuresSalinite ); // lance la fonction
            indexMesure++; // increment l'index des mesures
          }
          else {
            graphique7J(zero, zero, zero, zero); // lance la fonction
            nbr2MesuresPourLeGraphique--; // on decremente le nbr de mesure pour le graph puisque on a dessiner un pixel sans incrementer l'index
            //DPRINTF("trou dans la chronologie des mesures"); DPRINTLN(); // debug
          }
          tempsEntreLesMesures = tempsEntreLesMesures - quinzeMinutes;
        }
        else {
          //DPRINTLN("erreur dans la lecture binaire des mesures"); // debug
          indexErreur++; // increment l'index des erreurs
        }
      }
      wdt_reset(); // indique que le loop est OK, pas de bug, remise a zero du compteur "reboot" du watchdog car la lecture de toute les mesure pourait depasser le timer du watchdog
    }
    //DPRINTF("taille : "); DPRINTLN(sizeof(stockDansSD_t)); // debug
    myFile.close(); // ferme le fichier
  }
  else { // erreur a l'ouverture du fichier
    //DPRINTLN("Erreur a l'ouverture du fichier mesuresEnBinaire"); // debug
    while (indexMesure < nbr2MesuresPourLeGraphique) {
      graphique7J(zero, zero, zero, zero); // lance la fonction
      nbr2MesuresPourLeGraphique--; // on decremente le nbr de mesure pour le graph puisque on a dessiner un pixel sans incrementer l'index
    }
  }
}

/* enregistre les mesure toutes les 15 minutes */
void stockLesMesures() {
  if (variable.minut == 0 || variable.minut == 15 || variable.minut == 30 || variable.minut == 45) { // tout les 1/4 d'heure
    if (unEnregistrement) { // boolean pour ne pas avoir d'enregistrement a repetition
      stockMesuresEnBinaire(); // lance la fonction
      unEnregistrement = false; // passe en false
    }
  }
  else {
    unEnregistrement = true; // passe en true
  }
}

bool logMessage(const char* unMessage) { // ecrit le message d'erreur et index
  DPRINTF("ecrit le message sur sd : "); DPRINTLN(unMessage);
  static uint8_t ligneEnCours = 0;
  File fichierLog;
  File fichierIndex;
  uint32_t dernierePosition;
  bool erreur = true;
  size_t longueurLigne = strlen(unMessage);
  bool retourChariot = (longueurLigne == 0) ? false : (unMessage[longueurLigne - 1] == '\n'); // pour savoir si on le rajoutera
  longueurLigne += retourChariot ? 0 : 2; // +2 si on n'avait pas déjà un retour chariot car println rajoutera "\r\n"
  if (!SD.exists(indexErreursSurSD)) {
    DPRINTF("LOG: Erreur fichier index non existant"); DPRINTLN();
    return false; // il faut préparer
  }
  if (fichierLog.open(erreursSurSD, FILE_WRITE)) { //  FILE_WRITE = (O_RDWR | O_CREAT | O_AT_END) ouvert en lecture écriture, à la fin
    size_t n = 0;
    if (retourChariot) n = fichierLog.print(unMessage);
    else n = fichierLog.println(unMessage);
    dernierePosition  = fichierLog.position();
    fichierLog.close();
    if (n == longueurLigne) { // on a bien écrit la ligne
      ligneEnCours++;
      DPRINTF("tout est bien ecrit : "); DPRINTLN(unMessage);
      erreur = false;
      if (ligneEnCours >= nbr2Lignes) { // on a atteint une page, on note la position dans le fichier d'index
        erreur = true;
        ligneEnCours = 0;
        if (fichierIndex.open(indexErreursSurSD, FILE_WRITE)) {
          if (fichierIndex.write(&dernierePosition, sizeof(dernierePosition)) != sizeof(dernierePosition)) {
            DPRINTF("Erreur écriture Index"); DPRINTLN();
          } else erreur = false;
          fichierIndex.close();
        } else DPRINTF("Erreur ouverture Index"); DPRINTLN();
      } // fin gestion nouvelle page
    } else DPRINTF("Erreur écriture Log"); DPRINTLN();
  } else DPRINTF("Erreur ouverture Log"); DPRINTLN();
  return erreur;
}

bool indexPage(uint32_t& page, uint32_t& teteDeLecture) {
  File fichierIndex;
  bool erreur = true;
  if (SD.exists(indexErreursSurSD) && fichierIndex.open(indexErreursSurSD, O_RDONLY)) {
    uint32_t tailleFichierIndex = fichierIndex.size();
    if (tailleFichierIndex >= sizeof(uint32_t)) {
      if (page == 0xFFFFFFFF) { // on veut la dernière page
        page = tailleFichierIndex / sizeof(uint32_t) - 1;
        fichierIndex.seek(tailleFichierIndex - sizeof(uint32_t)); // on se positionne au bon endroit
        erreur = ((fichierIndex.read(&teteDeLecture, sizeof(uint32_t)) != sizeof(uint32_t)));
      }
      else if (page < tailleFichierIndex / sizeof(uint32_t)) { // on veut une page qui existe bien
        fichierIndex.seek(page * sizeof(uint32_t)); // on se positionne au bon endroit
        erreur = ((fichierIndex.read(&teteDeLecture, sizeof(uint32_t)) != sizeof(uint32_t)));
      } else {
        DPRINTLN("Page inexistante");
      }
    }
    fichierIndex.close();
  } // fin de si on peut ouvrir le fichier d'index
  if (!erreur) {
    DPRINTF("L'index de la page "); DPRINT(page);
    DPRINTF(" est "); DPRINTLN(teteDeLecture);
  }
  return erreur;
}

const char* lireLigne(File& f) { // lit une ligne dans le fichier qui est déjà ouvert est positionné au bon endroit
  const uint8_t caractereParLigne = maxbufferTexte;
  char ligne[caractereParLigne + 1] = {0};
  uint8_t nbCar = 0;
  ligne[0] = '\0';
  while (true) {
    int v = f.read(); // on lit le prochain caractère
    if ((v == -1) || (v == '\n')) break; // fin de fichier ou fin de ligne, on a fini
    else if ((v != '\r') && (nbCar < caractereParLigne)) ligne[nbCar++] = (char) v; // on ignore '\r' et la fin si buffer plein
  }
  ligne[nbCar] = '\0';
  effaceBufferTexte();
  strcpy (bufferTexte, ligne);
  return ligne;
}

bool lirePage(pageActuel commande) {
  File fichierLog;
  bool erreur = true;
  static uint8_t ligneSurNextion = 18;
  static uint32_t numeroPage = 0;
  static uint32_t teteDeLecture = 0;
  switch (commande) {
    case PAGE_FIN: // lire dans le fichier d'index la position toute à la fin
      DPRINTF("Demande lecture dernière page "); DPRINTLN();
      numeroPage = 0xFFFFFFFF;
      erreur = indexPage(numeroPage, teteDeLecture);
      dernierPage = numeroPage;
      DPRINTF("N derniere page : "); DPRINTLN(dernierPage);
      break;
    case PAGE_SUIVANTE:
      if (numeroPage != 0xFFFFFFFF) {
        numeroPage++;
        if (SDPrecedementVersLeBas) {
          DPRINTF("+ apres - : "); DPRINTLN(numeroPage);
          numeroPage = numeroPage + ligneSurNextion - 1;
          DPRINTF("+ apres - apres rectif : "); DPRINTLN(numeroPage);
          SDPrecedementVersLeBas = false;
        }
        DPRINTF("N de page "); DPRINTLN(numeroPage);
        if (((numeroPage + ligneSurNextion - 1 ) > dernierPage) && (numero2Ligne == (ligneSurNextion - 1))) {
          numeroPage = dernierPage - ligneSurNextion ;
          DPRINTF("N de page 2 : "); DPRINTLN(numeroPage);
        }
        DPRINTF("Demande lecture page "); DPRINTLN(numeroPage);
        erreur = indexPage(numeroPage, teteDeLecture);
        if (erreur) numeroPage = 0xFFFFFFFF;
      } else DPRINTF("Pas de page suivante"); DPRINTLN();
      break;
    case PAGE_PRECEDENTE:
      if (numeroPage != 0) {
        numeroPage--;
        erreur = indexPage(numeroPage, teteDeLecture);
      } else DPRINTF("Pas de page précédente"); DPRINTLN();
      break;
    default: break;
  }
  if (!erreur) {
    if (fichierLog.open(erreursSurSD, O_RDONLY)) {
      fichierLog.seek(teteDeLecture);
      DPRINTF("PAGE: "); DPRINTLN(numeroPage);
      for (uint8_t i = 0; i < nbr2Lignes; i++) {
        DPRINTF("Ligne "); DPRINT(i); Serial.write('\t');
        lireLigne(fichierLog);
        DPRINTLN(bufferTexte);
        // numero2Ligne = (nbr2Lignes - 1) - i;
        tableauLigneAffichageSd[numero2Ligne]->setText(bufferTexte);
      }
      fichierLog.close();
    }
  } else {
    DPRINTF("Commande impossible"); DPRINTLN();
  }
  return erreur;
}

bool prepareFichiersLog(const char enTete[] PROGMEM, bool forceDestruction = false) {
  File fichierLog;
  File fichierIndex;
  if (!forceDestruction && SD.exists(erreursSurSD) && SD.exists(indexErreursSurSD)) {
    DPRINTF("Le log et l'index existent, on suppose qu'ils sont corrects"); DPRINTLN();
    return true; // existent déjà on ne détruit pas
  }
  if (SD.exists(indexErreursSurSD)) { // si un des deux seulement existe on le détruit
    DPRINTF("Mais L'index existe"); DPRINTLN();
    if (fichierIndex.open(indexErreursSurSD, FILE_WRITE)) {
      fichierIndex.remove();
      fichierIndex.close();
      DPRINTF("Index détruit"); DPRINTLN();
    }
  }
  if (SD.exists(erreursSurSD)) {
    DPRINTF("Mais Le log existe déjà"); DPRINTLN();
    if (fichierLog.open(erreursSurSD, FILE_WRITE)) {
      fichierLog.remove();
      fichierLog.close();
      DPRINTF("Log détruit"); DPRINTLN();
    }
  }
  if (fichierIndex.open(indexErreursSurSD, FILE_WRITE)) {  // On prépare le fichier d'index avec comme première valeur 0
    uint32_t pos = 0;
    fichierIndex.write(&pos, sizeof(pos));
    fichierIndex.close();
    DPRINTF("Index créé avec 0"); DPRINTLN();
  } else DPRINTF("Erreur création fichier index"); DPRINTLN();
  effaceBufferTexte();
  strcpy_P(bufferTexte, enTete);
  logMessage(bufferTexte);  // on écrit l'en-tête
  return true;
}
