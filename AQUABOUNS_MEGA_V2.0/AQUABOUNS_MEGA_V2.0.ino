



/*               AAA                 QQQQQQQQQ     UUUUUUUU     UUUUUUUU           AAA               BBBBBBBBBBBBBBBBB        OOOOOOOOO     UUUUUUUU     UUUUUUUUNNNNNNNN        NNNNNNNN   SSSSSSSSSSSSSSS
                A:::A              QQ:::::::::QQ   U::::::U     U::::::U          A:::A              B::::::::::::::::B     OO:::::::::OO   U::::::U     U::::::UN:::::::N       N::::::N SS:::::::::::::::S
               A:::::A           QQ:::::::::::::QQ U::::::U     U::::::U         A:::::A             B::::::BBBBBB:::::B  OO:::::::::::::OO U::::::U     U::::::UN::::::::N      N::::::NS:::::SSSSSS::::::S
              A:::::::A         Q:::::::QQQ:::::::QUU:::::U     U:::::UU        A:::::::A            BB:::::B     B:::::BO:::::::OOO:::::::OUU:::::U     U:::::UUN:::::::::N     N::::::NS:::::S     SSSSSSS
             A:::::::::A        Q::::::O   Q::::::Q U:::::U     U:::::U        A:::::::::A             B::::B     B:::::BO::::::O   O::::::O U:::::U     U:::::U N::::::::::N    N::::::NS:::::S
            A:::::A:::::A       Q:::::O     Q:::::Q U:::::D     D:::::U       A:::::A:::::A            B::::B     B:::::BO:::::O     O:::::O U:::::D     D:::::U N:::::::::::N   N::::::NS:::::S
           A:::::A A:::::A      Q:::::O     Q:::::Q U:::::D     D:::::U      A:::::A A:::::A           B::::BBBBBB:::::B O:::::O     O:::::O U:::::D     D:::::U N:::::::N::::N  N::::::N S::::SSSS
          A:::::A   A:::::A     Q:::::O     Q:::::Q U:::::D     D:::::U     A:::::A   A:::::A          B:::::::::::::BB  O:::::O     O:::::O U:::::D     D:::::U N::::::N N::::N N::::::N  SS::::::SSSSS
         A:::::A     A:::::A    Q:::::O     Q:::::Q U:::::D     D:::::U    A:::::A     A:::::A         B::::BBBBBB:::::B O:::::O     O:::::O U:::::D     D:::::U N::::::N  N::::N:::::::N    SSS::::::::SS
        A:::::AAAAAAAAA:::::A   Q:::::O     Q:::::Q U:::::D     D:::::U   A:::::AAAAAAAAA:::::A        B::::B     B:::::BO:::::O     O:::::O U:::::D     D:::::U N::::::N   N:::::::::::N       SSSSSS::::S
       A:::::::::::::::::::::A  Q:::::O  QQQQ:::::Q U:::::D     D:::::U  A:::::::::::::::::::::A       B::::B     B:::::BO:::::O     O:::::O U:::::D     D:::::U N::::::N    N::::::::::N            S:::::S
      A:::::AAAAAAAAAAAAA:::::A Q::::::O Q::::::::Q U::::::U   U::::::U A:::::AAAAAAAAAAAAA:::::A      B::::B     B:::::BO::::::O   O::::::O U::::::U   U::::::U N::::::N     N:::::::::N            S:::::S
     A:::::A             A:::::AQ:::::::QQ::::::::Q U:::::::UUU:::::::UA:::::A             A:::::A   BB:::::BBBBBB::::::BO:::::::OOO:::::::O U:::::::UUU:::::::U N::::::N      N::::::::NSSSSSSS     S:::::S
    A:::::A               A:::::AQQ::::::::::::::Q   UU:::::::::::::UUA:::::A               A:::::A  B:::::::::::::::::B  OO:::::::::::::OO   UU:::::::::::::UU  N::::::N       N:::::::NS::::::SSSSSS:::::S
    A:::::A                 A:::::A QQ:::::::::::Q      UU:::::::::UU A:::::A                A:::::A B::::::::::::::::B     OO:::::::::OO       UU:::::::::UU    N::::::N        N::::::NS:::::::::::::::SS
    AAAAAAA                 AAAAAAA  QQQQQQQQ::::QQ       UUUUUUUUU   AAAAAAA                 AAAAAAABBBBBBBBBBBBBBBBB        OOOOOOOOO           UUUUUUUUU      NNNNNNNN         NNNNNNN SSSSSSSSSSSSSSS
                                           Q:::::Q
                                            QQQQQQ
                                                                                              __      __  _____   _____
                                                                                              \ \    / / /___  \ /  _  \
                                                                                               \ \  / /   ___| | | | | |
                                                                                                \ \/ /   /  ___/ | |/| |
                                                                                                 \  /    | |___ _| |_| |
                                                                                                  \/     |_____(_)_____/


                                                                                                     du 01/05/2021

                                                                                     Automate pour la gestion d'aquarium recifal
                                                                                         Créé par Djbouns, Copyright (C) 2021

                                                                            Avec l'aide du forum https://forum.arduino.cc pour le codage
                                                                                      Un grand merci particulierement a J.M.L
                                                                      Merci a Commodore pour tout les echanges qui ont fait grandire le projet


  //                              !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                                           Tout est mis a votre disposition gratuitement et permet d'avoir un automate qui aurais coûter au minimum 1000€ dans le commerce.*/
//                                                      !!!!! Alors Soutenez le projet pour qu'il continu d’évoluer et d’êtres mis a disposition gratuitement !!!!!
//                                                                                    https://paypal.me/ProjetAquabouns

//                              !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



/* Ce programme est un logiciel libre: vous pouvez le redistribuer
  et/ou le modifier selon les termes de la "GNU General Public
  License", tels que publiés par la "Free Software Foundation"; soit
  la version 2 de cette licence ou (à votre choix) toute version
  ultérieure.

  Ce programme est distribué dans l'espoir qu'il sera utile, mais
  SANS AUCUNE GARANTIE, ni explicite ni implicite; sans même les
  garanties de commercialisation ou d'adaptation dans un but spécifique.

  Se référer à la "GNU General Public License" pour plus de détails.
  Vous la trouverez dans l'onglet GNU_General_Public_License.h
  Ou sur http://www.gnu.org/licenses/

  Vous devriez avoir reçu une copie de la "GNU General Public License"
  en même temps que ce programme; sinon, écrivez a la "Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA".*/

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <Wire.h>
#include <OneWire.h>
#include "Ezo_i2c.h"
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "DallasTemperature.h"
#include "Nextion.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include "global.h"
#include "affichage.h"
#include "autres.h"
#include "brassage.h"
#include "debug.h"
#include "eclairage.h"
#include "eeprom.h"
#include "flotteurs.h"
#include "gsm.h"
#include "horloge.h"
#include "oscillo.h"
#include "carteSD.h"
#include "temperature_ph.h"
#include "wifi.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
uint32_t roulementPrecedent1;
uint8_t roulement1 = 0;
uint8_t roulement2 = 1;
const uint16_t refreshSwitch = 1000;
/* texte en PROGMEM pour SMS, Ecran et SD */
const char texteNextionDemarrage[] PROGMEM = "Demarrage en cours, chargement des parametres";
const char smsAlerteSecuriteDecante[] PROGMEM = " Niveau securite decante, ecumeur + osmolateur OFF";
const char smsCoupureEdf[] PROGMEM = " Coupure EDF";
const char smsDegree[] PROGMEM = " degree";
const char smsEdfOk[] PROGMEM = " EDF OK";
const char smsGodetPlein[] PROGMEM = " Godet plein, ecumeur OFF";
const char smsOsmolationOk[] PROGMEM = " Osmolation ON";
const char smsPh[] PROGMEM = " Ph : ";
const char smsReserveVide[] PROGMEM = " Reserve vide";
const char smsSecuriteDecanteOk[] PROGMEM = " Niveau securite decante OK";
const char smsTemperature[] PROGMEM = " Temperature : ";
const char smsTropOsmolation[] PROGMEM = " Trop de declenchement de l'osmolateur, osmolateur OFF";
const char texteNextionAlerte[] PROGMEM = "ALERTE ";
const char texteAlerteActuellement[] PROGMEM = "Actuellement ";
const char texteNextionAquaRampe[] PROGMEM = "Aqua/Rampe"; // texte stocker en progmem
const char texteNextionAucuneReponseGsm[] PROGMEM = "Aucune reponse du module Gsm !!!";
const char texteNextionAucuneReponseSD[] PROGMEM = "Aucune reponse de la carte SD !!!";
const char texteNextionAucuneReponseWifi[] PROGMEM = "Aucune reponse du module Wifi !!!";
const char texteNextionAucuneSonde[] PROGMEM = "Aucune sonde de temperature detectee !!!";
const char texteNextionBIENVENUE[] PROGMEM = "BIENVENUE";
const char texteNextionDANS[] PROGMEM = "DANS";
const char texteNextionLAQUABOUNS[] PROGMEM = "L'AQUABOUN'S";
const char texteNextionVersion[] PROGMEM = "V2.0";
const char texteNextionTemperatureBac[] PROGMEM = "ALERTE TEMPERATURE"; // texte stocker en progmem
const char texteNextionDeuxSonde[] PROGMEM = "DEUX sondes de temperature detectees, OK !";
const char texteNextionErreurModeRoutage[] PROGMEM = "Erreur de passage en mode routage !!!";
const char texteNextionErreurModeTexte[] PROGMEM = "Erreur de passage en mode texte !!!";
const char texteNextionFinAlerte[] PROGMEM = "Fin d'alerte,";
const char texteNextionGodetHaut[] PROGMEM = "ALERTE GODET PLEIN";
const char texteNextionHorlogeDetectee[] PROGMEM = "l'Horloge a ete detectee";
const char texteNextionHorlogeJamaisInitialise[] PROGMEM = "Horloge jamais initialise ou plus de batterie !";
const char texteNextionImportationDe[] PROGMEM = "Importation de ";
const char texteNextionImportationEepromDefault[] PROGMEM = "Importation des parametres par default, OK !";
const char texteNextionImportationEepromOK[] PROGMEM = "Importation des parametres de l'eeprom, OK !";
const char texteNextionInitialisationGsm[] PROGMEM = "Initialisation du module Gsm ... ";
const char texteNextionInitialisationGsmOK[] PROGMEM = "Initialisation du module Gsm, OK";
const char texteNextionInitialisationHorloge[] PROGMEM = "Initialisation de l'Horloge... ";
const char texteNextionInitialisationHorlogeOK[] PROGMEM = "Initialisation de l'Horloge, OK !";
const char texteNextionInitialisationSD[] PROGMEM = "Initialisation de la carte SD... ";
const char texteNextionInitialisationSDOK[] PROGMEM = "Initialisation du lecteur de carte SD, OK.";
const char texteNextionInitialisationSonde[] PROGMEM = "Initialisation des sondes de temperature ... ";
const char texteNextionInitialisationWifi[] PROGMEM = "Initialisation du module Wifi ...";
const char texteNextionInitialisationWifiOK[] PROGMEM = "Initialisation du module Wifi, OK";
const char texteNextionInitialisePh[] PROGMEM = "initialise    PH";
const char texteNextionMesurePh[] PROGMEM = "mesure PH en cours";
const char texteNextionModuleNonDetecte[] PROGMEM = "Module non detecte !!!"; // texte stocker en progmem
const char texteNextionNonConnecte[] PROGMEM = "Non connecte"; // texte stocker en progmem
const char texteNextionNourissage[] PROGMEM = "Nourrissage en cours ..."; // texte stocker en progmem
const char texteNextionOsmolationOff[] PROGMEM = "OSMOLATEUR OFF"; // texte stocker en progmem
const char texteNextionPasDeFichier[] PROGMEM = "Pas de fichier ";
const char texteNextionPasDeReponseHorloge[] PROGMEM = "Pas de reponse de l'Horloge !!!";
const char texteNextionPhBas[] PROGMEM = "ALERTE PH BAS"; // texte stocker en progmem
const char texteNextionPhHaut[] PROGMEM = "ALERTE PH HAUT"; // texte stocker en progmem
const char texteNextionRampeAqua[] PROGMEM = "Rampe/Aqua"; // texte stocker en progmem
const char texteNextionReserveVide[] PROGMEM = "RESERVE VIDE"; // texte stocker en progmem
const char texteNextionUneSonde[] PROGMEM = "UNE sonde de temperature detectee, OK !";
const char texteSurSDBatterieVide[] PROGMEM = "coupure batterie vide";
const char texteSurSDDemarrage[] PROGMEM = "DEMARRAGE DE L'AQUABOUNS";
const char texteSurSDErreurEnvoiConnection[] PROGMEM = "arduino / wifi Erreur envoie connectionWifi";
const char texteSurSDErreurEnvoiIdentifiant[] PROGMEM = "arduino / wifi Erreur envoi identifiantWifi";
const char texteSurSDErreurEnvoiParamS[] PROGMEM = "arduino / wifi Erreur envoi params";
const char texteSurSDErreurEnvoiVariables[] PROGMEM = "arduino / wifi Erreur envoi variables";
const char texteSurSDErreurRecepConnection[] PROGMEM = "arduino / wifi Erreur reception connectionWifi";
const char texteSurSDErreurRecepIdentifiant[] PROGMEM = "arduino / wifi Erreur reception identifiantWifi";
const char texteSurSDErreurRecepParamS[] PROGMEM = "arduino / wifi Erreur reception params";
const char texteSurSDErreurRecepVariable[] PROGMEM = "arduino / wifi Erreur reception variables";
const char texteSurSDOsmolationMAX[] PROGMEM = "osmolation compteur MAX";
const char texteSurSDOsmolationPlus1[] PROGMEM = "osmolation compteur +1";
const char texteSurSDRebootGsm[] PROGMEM = "reboot Gsm";
const char texteSurSDRebootGsmAT[] PROGMEM = "reboot Gsm pas de reponse AT";
const char texteSurSDRebootGsmModeRoutage[] PROGMEM = "reboot Gsm erreur passage mode routage";
const char texteSurSDRebootGsmModeTexte[] PROGMEM = "reboot Gsm erreur passage mode texte";
const char texteSurSDRebootGWifi[] PROGMEM = "reboot Wifi";
const char texteSurSDRedemarrage[] PROGMEM = "REDEMARRAGE MANUEL DE L'AQUABOUNS";
const char texteVide[] PROGMEM = ""; // texte stocker en progmem
const char finDuFichier[] PROGMEM = "*.*.*.*.*.* FIN DU FICHIER *.*.*.*.*.*"; // texte stocker en progmem
const char osg0[] PROGMEM = "o,sg,0"; // texte stocker en progmem
const char otds0[] PROGMEM = "o,tds,0"; // texte stocker en progmem
const char oec0[] PROGMEM = "o,ec,0"; // texte stocker en progmem
const char os1[] PROGMEM = "o,s,1"; // texte stocker en progmem

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonction $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void loopDesFonctions() {
  if (millis() - roulementPrecedent1 > refreshSwitch) { // si compteur ateind
    roulementPrecedent1 = millis(); // reinitialise le compteur
    roulement1++;
    rafraichirHeureSiSurMenu(); // rafraichi l'heure
    flotteurs();
    oscillateur();
    coupureEdf();
    if (pageActuelNextion == orph) {
      etalonnageEnCours();
    }
    if (progressionPuissanceBrassage) {
      progressionPuissanceBrassage = false;
      Brassage();
      rafraichirBrassage1Nextion();
      rafraichirBrassage2Nextion();
      rafraichirBrassage3Nextion();
    }
    if (roulement1 == 3) { // quand compteur ateint
      roulement1 = 0;
      if (pageActuelNextion != orph) {
        salinite();
      }
      switch (roulement2) {
        case 1:
          eclairage();
          break;
        case 2:
          rafraichirEclairageBlancNextion();
          break;
        case 3:
          rafraichirEclairageBleuNextion();
          break;
        case 4:
          if (pageActuelNextion != orph) {
            ph();
          }
          break;
        case 5:
          if (pageActuelNextion != orph) {
            alertePhBac();
          }
          break;
        case 6:
          if (pageActuelNextion != orph) {
            redox();
          }
          break;
        case 7:
          if (pageActuelNextion != orph) {
            rafraichirSaliniteNextion();
          }
          break;
        case 8:
          temperature();
          break;
        case 9:
          rafraichirTemperatureBacNextion();
          break;
        case 10:
          rafraichirTemperatureRampeNextion();
          break;
        case 11:
          Brassage();
          break;
        case 12:
          rafraichirBrassage1Nextion();
          break;
        case 13:
          rafraichirBrassage2Nextion();
          break;
        case 14:
          rafraichirBrassage3Nextion();
          break;
        case 15:
          etatGSM();
          etatWifi();
          coupureBatterie();
          roulement2 = 0;
          break;
      }
      roulement2++;
    }
  }
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ SETUP $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void setup() {
  Serial.begin(74880); //configure la vitesse de communication du moniteur serie (74880 baud) >>> attention, en 115200 bug avec la biblioteque nextion
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONFIGURATION DES BROCHES DE L'ARDUINO
  /* pinmode */
  pinMode(pinOutEclairage[bleu1], OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutEclairage[bleu2], OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutEclairage[blanc1], OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutEclairage[blanc2], OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutBrassage[numeroUn], OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutBrassage[numeroDeux], OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutBrassage[numeroTrois], OUTPUT); // Définit la broche comme sortie
  oscillo[numeroUn].attach(pinOUTOscillo1); // Définit la broche comme sortie
  oscillo[numeroDeux].attach(pinOUTOscillo2); // Définit la broche comme sortie
  oscillo[numeroTrois].attach(pinOUTOscillo3); // Définit la broche comme sortie
  pinMode(pinInFlotteurOsmolation, INPUT_PULLUP); // Définit la broche comme entrée et active la resistance pull-up
  pinMode(pinInFlotteurNiveauEcumeur, INPUT_PULLUP); // Définit la broche comme entrée et active la resistance pull-up
  pinMode(pinInFlotteurGodetEcumeur, INPUT_PULLUP); // Définit la broche comme entrée et active la resistance pull-up
  pinMode(pinInFlotteurSecurite, INPUT_PULLUP); // Définit la broche comme entrée et active la resistance pull-up
  pinMode(pinInFlotteurReserve, INPUT_PULLUP); // Définit la broche comme entrée et active la resistance pull-up
  pinMode(pinOutBatterie, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutRelaisRemontee, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutRelaisChauffage, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutRelaisVentilateurBac, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutRelaisVentilateurRampe, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutRelaisOsmolation, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutRelaisDistributeurNouriture, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutRelaisEcumeur, OUTPUT); // Définit la broche comme sortie
  pinMode(pinOutbuzzer, OUTPUT); // Définit la broche comme sortie
  pinMode(hardResetGSM, OUTPUT); // Définit la broche comme sortie
  pinMode(hardResetWIFI, OUTPUT); // Définit la broche comme sortie
  pinMode(pinInCoupureCourant, INPUT); // Définit la broche comme entree
  pinMode(pinInBatterie, INPUT); // Définit la broche comme entree

  /* initialise etat des pin */
  digitalWrite(pinOutEclairage[bleu1], LOW); // Off
  digitalWrite(pinOutEclairage[bleu2], LOW); // Off
  digitalWrite(pinOutEclairage[blanc1], LOW); // Off
  digitalWrite(pinOutEclairage[blanc2], LOW); // Off
  digitalWrite(pinOutBrassage[numeroUn], LOW); // Off
  digitalWrite(pinOutBrassage[numeroDeux], LOW); // Off
  digitalWrite(pinOutBrassage[numeroTrois], LOW); // Off
  digitalWrite(pinOutBatterie, HIGH); // on
  digitalWrite(pinOutRelaisRemontee, LOW); // On
  digitalWrite(pinOutRelaisChauffage, LOW); // On
  digitalWrite(pinOutRelaisVentilateurBac, LOW); // Off
  digitalWrite(pinOutRelaisOsmolation, LOW); // Off
  digitalWrite(pinOutRelaisDistributeurNouriture, LOW); // Off
  digitalWrite(pinOutRelaisEcumeur, HIGH); // On
  digitalWrite(pinOutbuzzer, LOW); // Off

  /* reboot gsm  avant initialisation */
  reboot(hardResetGSM);

  /* Initialisation de l'ecran nextion
       configure la vitesse de communication (115200 baud)
       Communication sur RX2/TX2
       !!! IMPORTANT !!! >>> Si vous utiliser la biblioteque officiel telecharger a partir de https://github.com/itead/ITEADLIB_Arduino_Nextion vous devez effectuer des modification :
       >>> Dans NexConfig.h, vous devez modifier #define DEBUG_SERIAL_ENABLE par:
       //#define DEBUG_SERIAL_ENABLE
       Cela désactive le debug dans le moniteur serie.
       >>> Toujours dans NexConfig.h, vous devez modifier #define nexSerial Serial1 par le numero du port serial utilisé, exemple pour le serial 2 :
       #define nexSerial Serial2
       Serial2 correspond a RX2/TX2
       >>> Dans NexHardware.cpp, vous devez modifier nexSerial.begin(9600); par:
       nexSerial.begin(250000);
       Cela Correspond a la vitesse de communication (250000 baud) entre l'ecran et l'arduino
       Sans faire ces modifications la communication entre l'arduino et l'ecran ne fonctionnera pas <<< !!! IMPORTANT !!! */
  nexInit();
  pageActuelNextion = demarrage; // indique que l'ecran est sur la page de demarrage

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Debut de l'initialisation de l'aquaboun's
  /* affiche les messages de demarage sur l'ecran */
  texteProgmemAuNextion(texte1, texteNextionDemarrage, pas2Changement2Couleur); // champ, texte, couleur
  DDELAY(deuxMille);

  /* Verifie si il y a des parametres dans l'eeprom
    Si il n'y a rien, chargement des parametre par default
    Sinon, chargement des parametre de l'eeprom */
  etablirValeursParDefaut();

  /* Initialise les oscillateurs */
  for (uint8_t numeroOscillo = numeroUn; numeroOscillo <= numeroTrois; numeroOscillo++) { // effectue la fonction une fois par oscillateurs
    positionOscillo[numeroOscillo] = (((sauvegarde.angle2Oscillo[numeroOscillo] - sauvegarde.angle1Oscillo[numeroOscillo]) / deux) + sauvegarde.angle1Oscillo[numeroOscillo]); // calcul pour que l'oscillateur soit centre des deux angles parametrés
    oscillo[numeroOscillo].write(positionOscillo[numeroOscillo]); // deplace l'oscillateur
    DPRINTF("oscillo "); DPRINT(numeroOscillo); DPRINTF(" position : "); DPRINT(positionOscillo[numeroOscillo]); DPRINTLN();
  }

  /* Initialise l'horloge */
  texteProgmemAuNextion(texte2, texteNextionInitialisationHorloge, pas2Changement2Couleur); // champ, texte, couleur
  DDELAY(deuxMille);
  rtc.begin();// initialise l'horloge
  initialisationDuDs3231();
  DDELAY(deuxMille);

  /* Initialise les sondes de temperature ds18b20 */
  sensors.begin();
  texteProgmemAuNextion(texte3, texteNextionInitialisationSonde, pas2Changement2Couleur); // champ, texte, couleur
  DDELAY(deuxMille);
  if (!sensors.getDeviceCount()) { // si aucune sonde de temperature detectée
    texteProgmemAuNextion(texte3, texteNextionAucuneSonde, rouge); // champ, texte, couleur
  }
  else {
    if (sensors.getDeviceCount() == un) { // Si 1 sonde detectée
      texteProgmemAuNextion(texte3, texteNextionUneSonde, orange); // champ, texte, couleur
    }
    else if (sensors.getDeviceCount() == deux) { // si 2 sondes detectées
      texteProgmemAuNextion(texte3, texteNextionDeuxSonde, vert); // champ, texte, couleur
    }
    sensors.getAddress(sondeBac, sauvegarde.adresseSondeBac) ; // indique l'adresse de la sonde
    sensors.getAddress(sondeRampe, sauvegarde.adresseSondeRampe); // indique l'adresse de la sonde
    sensors.setResolution(sondeBac, 12);//resolution 9 = 0.5°= 93.75ms pour mesurer;, 10 = 0.25° = 187.5ms pour mesurer , 11 = 0.125° = 375ms pour mesurer, 12 = 0.0625° = 750ms pour mesurer
    sensors.setResolution(sondeRampe,12);//resolution 9 = 0.5°= 93.75ms pour mesurer;, 10 = 0.25° = 187.5ms pour mesurer , 11 = 0.125° = 375ms pour mesurer, 12 = 0.0625° = 750ms pour mesurer
    sensors.setWaitForConversion(false); // on travaillera en asynchrone, on n'attend pas les lectures
    sensors.requestTemperatures(); // on lance une demande de lecture qui sera prête plus tard
  }
  DDELAY(deuxMille);

  /* Initialisation de la carte SD */
  texteProgmemAuNextion(texte4, texteNextionInitialisationSD, pas2Changement2Couleur); // champ, texte, couleur
  DDELAY(deuxMille);
  if (!SD.begin(SD_CS_PIN)) { // Si carte SD non détéctée
    texteProgmemAuNextion(texte4, texteNextionAucuneReponseSD, rouge); // champ, texte, couleur
  }
  else { // Si carte SD bien initialisée
    texteProgmemAuNextion(texte4, texteNextionInitialisationSDOK, vert); // champ, texte, couleur
    DDELAY(mille);
    lisSurSd(ssidSurSD, identifiantWifi.ssid, maxSsid); // lance la lecture/copie du fichier
    lisSurSd(mdpSurSD, identifiantWifi.mdp, maxMdp); // lance la lecture/copie du fichier
    lisSurSd(numero2TelSurSD, numero2tel, maxnumero2tel); // lance la lecture/copie du fichier
    myFile = SD.open(erreursSurSD, O_WRITE | O_CREAT | O_AT_END);
    myFile.close(); // ferme le fichier
    myFile = SD.open(mesuresEnBinaire, O_WRITE | O_CREAT | O_AT_END);
    myFile.close(); // ferme le fichier
    prepareFichiersLog(finDuFichier, false); // true -> on force la destruction des fichiers
  }

  /* initialise le module GSM */
  gsm.begin(57600); // configure la vitesse de communication avec l'arduino (57600 baud)
  texteProgmemAuNextion(texte5, texteNextionInitialisationGsm, pas2Changement2Couleur); // champ, texte, couleur
  DDELAY(deuxMille);
  if (gsmPrintlnAndWaitATCommand(ATString, OKLongString, mille, true)) {
    if (!gsmPrintlnAndWaitATCommand("AT+CMGF=1", OKLongString, mille, true)) { // on passe les SMS en mode texte
      texteProgmemAuNextion(texte5, texteNextionErreurModeTexte, rouge); // champ, texte, couleur
      gsmOn = false; // Met le GSM en OFF
    }
    else {
      if (!gsmPrintlnAndWaitATCommand("AT+CNMI=1,0,0,0,0", OKLongString, mille, true)) {  // on passe en mode routage des SMS vers le terminal
        texteProgmemAuNextion(texte5, texteNextionErreurModeRoutage, rouge); // champ, texte, couleur
        gsmOn = false; // Met le GSM en OFF
      }
      else {
        texteProgmemAuNextion(texte5, texteNextionInitialisationGsmOK, vert); // champ, texte, couleur
      }
    }
  }
  else {
    texteProgmemAuNextion(texte5, texteNextionAucuneReponseGsm, rouge); // champ, texte, couleur
    gsmOn = false; // Met le GSM en OFF
  }

  /* Initialise le module wifi */
  reboot(hardResetWIFI); // reboot le module wifi avant initialisation
  d1mini.begin(57600); // configure la vitesse de communication du module Wifi avec l'arduino (115200 baud)
  d1mini.setTimeout(500); // temps max de réceptoin d'une structure en ms
  texteProgmemAuNextion(texte6, texteNextionInitialisationWifi, pas2Changement2Couleur); // champ, texte, couleur
  horaire(); // lance la fonction
  executer(RECEVOIRconnectionWifi, true); // demande le statut de connection // pour voir si le module est connecté et repond
  DDELAY(deuxMille);
  if (connectionWifi.presenceModule ) {
    texteProgmemAuNextion(texte6, texteNextionInitialisationWifiOK, vert); // champ, texte, couleur
  }
  else {
    texteProgmemAuNextion(texte6, texteNextionAucuneReponseWifi, rouge); // champ, texte, couleur
  }
  DDELAY(deuxMille);

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Initialisation de l'aquaboun's terminé
  texteProgmemAuNextion(texte1, texteVide, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte2, texteVide, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte3, texteVide, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte4, texteVide, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte5, texteVide, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte6, texteVide, vert); // champ, texte, couleur
  DDELAY(mille);
  texte1.setFont(8); // change de police
  texte2.setFont(8); // change de police
  texte3.setFont(8); // change de police
  texte4.setFont(8); // change de police
  texte5.setFont(8); // change de police
  texteProgmemAuNextion(texte1, texteNextionBIENVENUE, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte2, texteNextionDANS, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte3, texteNextionLAQUABOUNS, vert); // champ, texte, couleur
  texteProgmemAuNextion(texte5, texteVide, vert); // champ, texte, couleur
  uint8_t maxCommandeEtalonnage = 15;
  char commandeEtalonnage[maxCommandeEtalonnage + 1];
  delay(500);
  texteProgmemAuNextion(texte5, texteNextionVersion, vert); // champ, texte, couleur
  strcpy_P(commandeEtalonnage, oec0);
  commandeEtalonnage[maxCommandeEtalonnage] = '\0';
  initialisationEC(commandeEtalonnage);
  delay(500);
  texteProgmemAuNextion(texte5, texteVide, vert); // champ, texte, couleur
  strcpy_P(commandeEtalonnage, osg0);
  commandeEtalonnage[maxCommandeEtalonnage] = '\0';
  initialisationEC(commandeEtalonnage);
  delay(500); // laisse le temps au module de traiter la commande
  texteProgmemAuNextion(texte5, texteNextionVersion, vert); // champ, texte, couleur
  strcpy_P(commandeEtalonnage, otds0);
  commandeEtalonnage[maxCommandeEtalonnage] = '\0';
  initialisationEC(commandeEtalonnage);
  delay(500); // laisse le temps au module de traiter la commande
  texteProgmemAuNextion(texte5, texteVide, vert); // champ, texte, couleur
  strcpy_P(commandeEtalonnage, os1);
  commandeEtalonnage[maxCommandeEtalonnage] = '\0';
  initialisationEC(commandeEtalonnage);
  delay(500); // laisse le temps au module de traiter la commande
  texteProgmemAuNextion(texte5, texteNextionVersion, vert); // champ, texte, couleur
  DDELAY(deuxMille);

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Attache chaque bouton de l'ecran a une fonction
  onoffpomperemonte.attachPush(boutonOnOffRemonte, &onoffpomperemonte);
  onoffalimentation1.attachPush(boutonOnOffAlim1, &onoffalimentation1);
  onoffalimentation2.attachPush(boutonOnOffAlim2, &onoffalimentation2);
  onoffpwmblanc.attachPush(boutonBlanc, &onoffpwmblanc);
  onoffpwmbleu.attachPush(boutonBleu, &onoffpwmbleu);
  onoffpwmBrassage1.attachPush(boutonBrassage1, &onoffpwmBrassage1);
  onoffpwmBrassage2.attachPush(boutonBrassage2, &onoffpwmBrassage2);
  onoffpwmBrassage3.attachPush(boutonBrassage3, &onoffpwmBrassage3);
  boutonversetalonnage.attachPush(versEtalonnage, &boutonversetalonnage);
  onofftempete.attachPush(boutonTempeteManuel, &onofftempete);
  onofftempetealeatoire.attachPush(boutonTempeteAleatoire, &onofftempetealeatoire);
  boutonmenuversconfig.attachPush(versConfig, &boutonmenuversconfig);
  boutonalimentationmanuel.attachPush(boutonNourrissageManuel, &boutonalimentationmanuel);
  boutonconfigverstel.attachPush(versTel, &boutonconfigverstel);
  boutonconfigverswifi.attachPush(versWifi, &boutonconfigverswifi);
  boutonconfigversmenu.attachPush(versMenu, &boutonconfigversmenu);
  boutonconfigversinfo.attachPush(versInfo, &boutonconfigversinfo);
  boutonconfigvershorloge.attachPush(versHorloge, &boutonconfigvershorloge);
  boutonwifiversconfig.attachPush(versConfig, &boutonwifiversconfig);
  boutontelversconfig.attachPush(versConfig, &boutontelversconfig);
  boutoninfoversconfig.attachPush(versConfig, &boutoninfoversconfig);
  boutonBrassageversmenu.attachPush(versMenu, &boutonBrassageversmenu);
  boutonenregistrerBrassageversmenu.attachPush(enregistrerBrassage, &boutonenregistrerBrassageversmenu);
  boutonconfigversBrassage.attachPush(versBrassage, &boutonconfigversBrassage);
  boutonenregistrertelversconfig.attachPop(enregistrerTel, &boutonenregistrertelversconfig);
  boutonenregistrerwifiversconfig.attachPop(enregistrerWifi, &boutonenregistrerwifiversconfig);
  boutonenregistrerconfigversmenu.attachPush(enregistrerConfig, &boutonenregistrerconfigversmenu);
  boutonhorlogeversconfig.attachPush(versConfig, &boutonhorlogeversconfig);
  boutonenregistrerhorlogeversconfig.attachPop(enregistrerHorloge, &boutonenregistrerhorlogeversconfig);
  boutonmoinsminBrassage1.attachPop(boutonminBrassage1, &boutonmoinsminBrassage1);
  boutonplusminBrassage1.attachPop(boutonminBrassage1, &boutonplusminBrassage1);
  boutonmoinsminBrassage2.attachPop(boutonminBrassage2, &boutonmoinsminBrassage2);
  boutonplusminBrassage2.attachPop(boutonminBrassage2, &boutonplusminBrassage2);
  boutonmoinsminBrassage3.attachPop(boutonminBrassage3, &boutonmoinsminBrassage3);
  boutonplusminBrassage3.attachPop(boutonminBrassage3, &boutonplusminBrassage3);
  boutonmoinsoscillo1min.attachPop(boutonoscillo1min, &boutonmoinsoscillo1min);
  boutonplusoscillo1min.attachPop(boutonoscillo1min, &boutonplusoscillo1min);
  boutonmoinsoscillo1max.attachPop(boutonoscillo1max, &boutonmoinsoscillo1max);
  boutonplusoscillo1max.attachPop(boutonoscillo1max, &boutonplusoscillo1max);
  boutonmoinsoscillo2min.attachPop(boutonoscillo2min, &boutonmoinsoscillo2min);
  boutonplusoscillo2min.attachPop(boutonoscillo2min, &boutonplusoscillo2min);
  boutonmoinsoscillo2max.attachPop(boutonoscillo2max, &boutonmoinsoscillo2max);
  boutonplusoscillo2max.attachPop(boutonoscillo2max, &boutonplusoscillo2max);
  boutonmoinsoscillo3min.attachPop(boutonoscillo3min, &boutonmoinsoscillo3min);
  boutonplusoscillo3min.attachPop(boutonoscillo3min, &boutonplusoscillo3min);
  boutonmoinsoscillo3max.attachPop(boutonoscillo3max, &boutonmoinsoscillo3max);
  boutonplusoscillo3max.attachPop(boutonoscillo3max, &boutonplusoscillo3max);
  pagestandby.attachPush(versMenu, &pagestandby);
  boutonversstandby.attachPush(versStandby, &boutonversstandby);
  boutonredemarrage.attachPush(redemarrage, &boutonredemarrage);
  boutonverschoixgraph.attachPush(versChoixGraph, &boutonverschoixgraph);
  boutonchoixgraphversmenu.attachPush(versMenu, &boutonchoixgraphversmenu);
  boutonchoixgraphvers24h.attachPush(versGraph24H, &boutonchoixgraphvers24h);
  boutonchoixgraphvers7j.attachPush(versGraph7J, &boutonchoixgraphvers7j);
  boutongraph24hverschoixgraph.attachPush(versChoixGraph, &boutongraph24hverschoixgraph);
  boutongraph7jverschoixgraph.attachPush(versChoixGraph, &boutongraph7jverschoixgraph);
  boutonorpphversmenu.attachPush(versMenu, &boutonorpphversmenu);//
  boutonoui.attachPush(sondeACalibrer, &boutonoui);//
  boutonconfigverssd.attachPush(versSd, &boutonconfigverssd);
  boutonsdversconfig.attachPush(versConfig, &boutonsdversconfig);
  boutonbas.attachPush(versBasSd, &boutonbas);
  boutonhaut.attachPush(versHautSd, &boutonhaut);
  boutonclear.attachPush(effaceSd, &boutonclear);

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAJ des valeurs avant d'afficher la page menu sur l'ecran
  horaire(); // lance la fonction
  temperature(); // lance la fonction
  eclairage(); // lance la fonction
  variable.pwmBrassage[numeroUn] = sauvegarde.puissanceMaxBrassage[numeroUn];
  variable.pwmBrassage[numeroDeux] = sauvegarde.puissanceMaxBrassage[numeroDeux];
  variable.pwmBrassage[numeroTrois] = sauvegarde.puissanceMaxBrassage[numeroTrois];
  Brassage(); // lance la fonction
  ph(); // lance la fonction
  redox(); // lance la fonction
  salinite(); // lance la fonction
  definiTempeteAleatoire(); // lance la fonction
  if (sauvegarde.bootApresCoupureEDF) { // si l'arduino se rallume apres une coupure edf + batterie
    completerMessageAlerte(texteNextionFinAlerte, smsEdfOk); // envoie un SMS
    completerMessageAlerteTemperature(texteAlerteActuellement); // envoie un SMS
    sauvegarde.bootApresCoupureEDF = false; // inverse le boolean
    EEPROM.put(adresseDeSauvegarde, sauvegarde);  // sauvegarde tout les parametres
  }
  DDELAY(deuxMille);
  attenteMesurePH(); // attend la reception des mesures
  attenteMesureRedox(); // attend la reception des mesures
  attenteMesureSalinite(); // attend la reception des mesures

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Affichage de le page menu
  affichePageMenu();// affiche la page menu

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Ecrit sur la carte sd la date et heure de demarage
  horodatageEtEcritSurSD (texteSurSDDemarrage, ""); // ecrit sur la carte SD le demarage de l'AQUABOUNS

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Active le watchdog de l'arduino
  /* Si plus de remise a zero du compteur "reboot" (fait dans le loop) au bout de 8 secondes = bug de l'arduino = reboot automatique ! */
  wdt_enable(WDTO_8S);
} // fin du setup

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ LOOP $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void loop() {
  lectureBoutons(); /* lis les bontons du nextion >>> !!! IMPORTANT !!! >>> loop minimum 450/seconde pour ne pas avoir de bouton sans reponse <<< !!! IMPORTANT !!! <<< */
  ecouterModuleWifi(); /* ecoute les demande du module wifi */
  horaire(); /* recupere h'aure de l'horloge */
  rebootAlarme(); /* reboot les alarme toutes les heures durant la periode d'alerte determiné */
  tempeteAleatoireAutomatique(); /* declanche la tempete aleatoire si activé */
  nourrissage(); /* declanche le nourissage si activé */
  loopDesFonctions(); // lance des fonctions secondaire a tour de role
  stockLesMesures(); /* pour stocker les mesures temperature et ph sur sd */
  attenteMesurePH(); // attend la reception des mesures
  attenteMesureRedox(); // attend la reception des mesures
  attenteMesureSalinite(); // attend la reception des mesures
  wdt_reset(); // indique que le loop est OK, pas de bug, remise a zero du compteur "reboot" du watchdog
}
