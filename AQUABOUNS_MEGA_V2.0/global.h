#ifndef global_h_
#define global_h_

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <Servo.h>
#include "DallasTemperature.h"
#include <OneWire.h>
#include "RTClib.h"
#include "SdFat.h"
#include "Nextion.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "eeprom.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* dans .ino */
extern uint8_t roulement1;
extern uint32_t roulementPrecedent1, roulementPrecedent2;
extern const char texteNextionDemarrage[] PROGMEM;
extern const char smsAlerteSecuriteDecante[] PROGMEM;
extern const char smsCoupureEdf[] PROGMEM;
extern const char smsDegree[] PROGMEM;
extern const char smsEdfOk[] PROGMEM;
extern const char smsGodetPlein[] PROGMEM;
extern const char smsOsmolationOk[] PROGMEM;
extern const char smsPh[] PROGMEM;
extern const char smsReserveVide[] PROGMEM;
extern const char smsSecuriteDecanteOk[] PROGMEM;
extern const char smsTemperature[] PROGMEM;
extern const char smsTropOsmolation[] PROGMEM;
extern const char texteNextionAlerte[] PROGMEM;
extern const char texteNextionAnnee[] PROGMEM;
extern const char texteNextionAquaRampe[] PROGMEM;
extern const char texteNextionAucuneReponseGsm[] PROGMEM;
extern const char texteNextionAucuneReponseSD[] PROGMEM;
extern const char texteNextionAucuneReponseWifi[] PROGMEM;
extern const char texteNextionAucuneSonde[] PROGMEM;
extern const char texteNextionBIENVENUE[] PROGMEM;
extern const char texteNextionDANS[] PROGMEM;
extern const char texteNextionTemperatureBac[] PROGMEM;
extern const char texteNextionDeuxSonde[] PROGMEM;
extern const char texteNextionErreurModeRoutage[] PROGMEM;
extern const char texteNextionErreurModeTexte[] PROGMEM;
extern const char texteNextionetalonnage[] PROGMEM;
extern const char texteNextionFinAlerte[] PROGMEM;
extern const char texteAlerteActuellement[] PROGMEM;
extern const char texteNextionGodetHaut[] PROGMEM ;
extern const char texteNextionHorlogeDetectee[] PROGMEM;
extern const char texteNextionHorlogeJamaisInitialise[] PROGMEM;
extern const char texteNextionImportationDe[] PROGMEM;
extern const char texteNextionImportationEepromDefault[] PROGMEM;
extern const char texteNextionImportationEepromOK[] PROGMEM;
extern const char texteNextionInitialisationGsm[] PROGMEM;
extern const char texteNextionInitialisationGsmOK[] PROGMEM;
extern const char texteNextionInitialisationHorloge[] PROGMEM;
extern const char texteNextionInitialisationHorlogeOK[] PROGMEM;
extern const char texteNextionInitialisationSD[] PROGMEM;
extern const char texteNextionInitialisationSDOK[] PROGMEM;
extern const char texteNextionInitialisationSonde[] PROGMEM;
extern const char texteNextionInitialisationWifi[] PROGMEM;
extern const char texteNextionInitialisationWifiOK[] PROGMEM;
extern const char texteNextionInitialisePh[] PROGMEM;
extern const char texteNextionLAQUABOUNS[] PROGMEM;
extern const char texteNextionMesurePh[] PROGMEM;
extern const char texteNextionModuleNonDetecte[] PROGMEM;
extern const char texteNextionNonConnecte[] PROGMEM;
extern const char texteNextionNourissage[] PROGMEM;
extern const char texteNextionOsmolationOff[] PROGMEM;
extern const char texteNextionPasDeFichier[] PROGMEM;
extern const char texteNextionPasDeReponseHorloge[] PROGMEM;
extern const char texteNextionPhBas[] PROGMEM;
extern const char texteNextionPhHaut[] PROGMEM;
extern const char texteNextionRampeAqua[] PROGMEM;
extern const char texteNextionReserveVide[] PROGMEM;
extern const char texteNextionUneSonde[] PROGMEM;
extern const char texteNextionVersion[] PROGMEM;
extern const char texteSurSDBatterieVide[] PROGMEM;
extern const char texteSurSDDemarrage[] PROGMEM;
extern const char texteSurSDErreurEnvoiConnection[] PROGMEM;
extern const char texteSurSDErreurEnvoiIdentifiant[] PROGMEM;
extern const char texteSurSDErreurEnvoiParamS[] PROGMEM;
extern const char texteSurSDErreurEnvoiVariables[] PROGMEM;
extern const char texteSurSDErreurRecepConnection[] PROGMEM;
extern const char texteSurSDErreurRecepIdentifiant[] PROGMEM;
extern const char texteSurSDErreurRecepParamS[] PROGMEM;
extern const char texteSurSDErreurRecepVariable[] PROGMEM;
extern const char texteSurSDOsmolationMAX[] PROGMEM;
extern const char texteSurSDOsmolationPlus1[] PROGMEM;
extern const char texteSurSDRebootGsm[] PROGMEM;
extern const char texteSurSDRebootGsmAT[] PROGMEM;
extern const char texteSurSDRebootGsmModeRoutage[] PROGMEM;
extern const char texteSurSDRebootGsmModeTexte[] PROGMEM;
extern const char texteSurSDRebootGWifi[] PROGMEM;
extern const char texteSurSDRedemarrage[] PROGMEM;
extern const char texteVide[] PROGMEM;
extern const char finDuFichier[] PROGMEM;
extern const char oec0[] PROGMEM ;
extern const char os1[] PROGMEM;

/* dans affichage.cpp */
extern boolean onOffalimentation;
extern char bufferTexte[];
extern const uint8_t dix, cent, maxbufferTexte, zero, un, deux, trois, quatre, pas2Changement2Couleur;
enum pageNextion : uint8_t {menu, parametre, brass, horloge , wifi, tel, info, standby, demarrage, choixgraph, graph24h, graph7j, orph, sd, dernierePage = 255};
extern const uint16_t mille, deuxMille;
extern uint32_t number, numero_page, recupHorraireTemporraire;
extern pageNextion pageActuelNextion;
extern NexPage pageMenu;
extern NexButton onoffpomperemonte;
extern NexButton onoffalimentation1;
extern NexButton onoffalimentation2;
extern NexButton onoffpwmBrassage1;
extern NexButton onoffpwmBrassage2;
extern NexButton onoffpwmBrassage3;
extern NexButton onoffpwmblanc;
extern NexButton onoffpwmbleu;
extern NexButton onofftempete;
extern NexButton onofftempetealeatoire;
extern NexScrolltext messagedefilantalimentationencours;
extern NexText messageanomalie;
extern NexVariable variableetatboutons;
extern NexText affichageheurealimentation1;
extern NexText affichageheurealimentation2;
extern NexButton boutonmenuversconfig;
extern NexButton boutonalimentationmanuel;
extern NexButton boutonconfigverstel;
extern NexButton boutonconfigverswifi;
extern NexButton boutonconfigversmenu;
extern NexButton boutonconfigversinfo;
extern NexButton boutonwifiversconfig;
extern NexButton boutontelversconfig;
extern NexButton boutoninfoversconfig;
extern NexButton boutonconfigverssd;
extern NexButton boutongraph7jverschoixgraph;
extern NexButton boutonenregistrertelversconfig;
extern NexButton boutonenregistrerwifiversconfig;
extern NexButton boutonenregistrerconfigversmenu;
extern NexButton boutonBrassageversmenu;
extern NexButton boutonenregistrerBrassageversmenu;
extern NexButton boutonconfigversBrassage;
extern NexButton boutonconfigvershorloge;
extern NexButton boutonhorlogeversconfig;
extern NexButton boutonenregistrerhorlogeversconfig;
extern NexButton boutonmoinsminBrassage1;
extern NexButton boutonplusminBrassage1;
extern NexButton boutonmoinsminBrassage2;
extern NexButton boutonplusminBrassage2;
extern NexButton boutonmoinsminBrassage3;
extern NexButton boutonplusminBrassage3;
extern NexButton boutonmoinsoscillo1min;
extern NexButton boutonplusoscillo1min;
extern NexButton boutonmoinsoscillo1max;
extern NexButton boutonplusoscillo1max;
extern NexButton boutonmoinsoscillo2min;
extern NexButton boutonplusoscillo2min;
extern NexButton boutonmoinsoscillo2max;
extern NexButton boutonplusoscillo2max;
extern NexButton boutonmoinsoscillo3min;
extern NexButton boutonplusoscillo3min;
extern NexButton boutonmoinsoscillo3max;
extern NexButton boutonplusoscillo3max;
extern NexButton boutonversstandby;
extern NexButton boutonversetalonnage;
extern NexButton boutonredemarrage;
extern NexPage pagestandby;
extern NexButton boutonverschoixgraph;
extern NexButton boutonchoixgraphversmenu;
extern NexButton boutonchoixgraphvers24h;
extern NexButton boutonchoixgraphvers7j;
extern NexButton boutongraph24hverschoixgraph;
extern NexButton boutongraph7jverschoixgraph;
extern NexButton boutonorpphversmenu;//
extern NexText boutonoui;
extern NexButton boutonsdversconfig;
extern NexButton boutonbas;
extern NexButton boutonhaut;
extern NexButton boutonclear;
extern NexText texte1;
extern NexText texte2;
extern NexText texte3;
extern NexText texte4;
extern NexText texte5;
extern NexText texte6;
extern NexText valeursd00;
extern NexText valeursd01;
extern NexText valeursd02;
extern NexText valeursd03;
extern NexText valeursd04;
extern NexText valeursd05;
extern NexText valeursd06;
extern NexText valeursd07;
extern NexText valeursd08;
extern NexText valeursd09;
extern NexText valeursd10;
extern NexText valeursd11;
extern NexText valeursd12;
extern NexText valeursd13;
extern NexText valeursd14;
extern NexText valeursd15;
extern NexText valeursd16;
extern NexText valeursd17;
extern const uint16_t vert, orange, rouge, batterie0;

/* autres.cpp */
extern boolean nourrissage1ON, nourrissage2ON, texteNourrissage, alarmeOnOff;
extern const uint16_t adresseMotClef, adresseDeSauvegarde;
extern const uint32_t motClef;
extern uint32_t dureeNourrissageMillis, heureNourrissage[];
enum {numeroUn, numeroDeux, numeroTrois, dernierNumero = 255}; // utiliser pour Brassage, oscillo, nourrissage ...

/* dans Brassage.cpp */
enum {Arret, Actif, Pwm, Delay, dernierMode = 255}; // utiliser pour Brassage, eclairage, pompe de remonté
extern boolean MajEcranTempeteEnCours, nourissageEnCours, tempeteManuelEnCours, tempeteAleatoireEnCours, progressionPuissanceBrassage;
extern uint8_t pwmBrassage[], puissanceMaxBrassage[], puissanceMinBrassage[], accalmieNocturne, puissanceTempete;
extern uint32_t dureeTempeteMillis, heureTempeteAleatoire, dureeTempeteAleatoire;

/* dans eclairage */
enum {bleu1, bleu2, blanc1, blanc2, derniereCouleur = 255};
extern uint8_t pwmEclairage[], puissanceMaxEclairage[];
extern uint16_t dureelevercoucher;
extern uint32_t leverSoleil, coucherSoleil, debutleverSoleil[], finleverSoleil[], debutcoucherSoleil[], fincoucherSoleil[];

/* dans flotteurs.cpp */
extern boolean smsAlerteOsmolation, smsAlerteGodet, smsAlerteSecurite, smsAlerteReserve;

/* dans gsm.cpp */
extern boolean gsmOn, envoyerSMS(const char * noDeTel, const char * messageAEnvoyer);
extern boolean gsmPrintlnAndWaitATCommand(const char * command, const char * endMarker, uint32_t duration, boolean verbose);
extern char numero2tel[], messageGsm[], buffer[], nomOperateur[];
extern const char * ATString, * OKShortString, * OKLongString;
extern const uint8_t maxnumero2tel, maxMessageSize;
extern const uint8_t maxNomOperateur;
extern uint8_t signalGSM ;

/* dans horloge.cpp */
extern char textime[], minuteEnTexteOut[], minuteEnTexteIn[];
extern const uint8_t minuteEnSeconde, maxminuteEnTexte;
extern uint8_t Heure, minut, jour, mois, jourJ, moisM;
extern uint16_t M, S, annee;
extern uint32_t Time, H, tempsPrecedentNourrissage, tempsPrecedentTempete, tempsPrecedentTempeteAleatoire;

/* dans oscillo.cpp */
extern Servo oscillo[];
extern boolean oscillo1On, oscillo2On, oscillo3On;
extern uint8_t angle1Oscillo[], angle2Oscillo[], positionOscillo[];
extern uint16_t delaisMouvementOscilloMillis[];
extern uint32_t tempsPrecedentOscillo[];

/* dans sd.cpp */
extern SdFat SD;
extern File myFile;
extern const char* ssidSurSD;
extern const char* mdpSurSD;
extern const char* numero2TelSurSD;
extern const char* erreursSurSD;
extern const char* mesuresEnBinaire;
extern const uint8_t nbr2Lignes;
extern uint8_t numero2Ligne;
extern boolean SDPrecedementVersLeBas;
enum pageActuel : uint8_t {PAGE_FIN, PAGE_SUIVANTE, PAGE_PRECEDENTE};

/* dans temperature.cpp */
extern RTC_DS3231 rtc;
extern OneWire oneWire;
extern DallasTemperature sensors;
extern DeviceAddress sondeBac, sondeRampe;
extern boolean alerteTemperature, alertePhBas, alertePhHaut, adresseSondeRampe, adresseSondeBac, tempeteAleatoireOn, etatVentilationBac, etatVentilationRampe, demande2MesureSalinite;
extern const uint8_t cent;
extern uint8_t temperatureRampe, ventilationrampe;
extern float moyennePhBac, moyennePhRac;
extern float temperatureBac, ventilationaquarium, alertetemperaturehaute, alertetemperaturebasse;

/* dans wifi.cpp */
enum typeCommande_t : uint8_t {ENVOYERsauvegarde = 0, ENVOYERvariable, ENVOYERidentifiantWifi, ENVOYERconnectionWifi,
                               RECEVOIRsauvegarde, RECEVOIRvariable, RECEVOIRidentifiantWifi, RECEVOIRconnectionWifi, AUCUNE = 255
                              }; // dans le même ordre que les commandes
extern const uint8_t maxSsid, maxMdp;
extern boolean reponseModuleWifi;

#endif
