#ifndef  _carteSD_h_
#define _carteSD_h_

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <arduino.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Declarations des fonctions dans le .cpp $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void ecritSurSd(const char * nomDuFichierTxt, char * donneeAEcrireSurSD);
boolean lisSurSd(const char * nomDuFichierTxt, char *donneeLueSurSD, size_t NbMaxCaracteres);
void horodatageEtEcritSurSD (const char Erreur1AAjouter[] PROGMEM, const char* Erreur2AAjouter);
void stockMesuresEnBinaire();
void lisMesuresEnBinaire24h();
void lisMesuresEnBinaire7J();
void lisLesEvenementsSurLaCarteSd();
void stockLesMesures();
void videFichierErreur();
bool logMessage(const char* unMessage);
bool indexPage(uint32_t& page, uint32_t& teteDeLecture);
const char* lireLigne(File& f);
bool lirePage(pageActuel commande);
bool prepareFichiersLog(const char enTete[] PROGMEM, bool forceDestruction = false);

struct __attribute__ ((packed)) stockDansSD_t {// force l'ordre des champs
  uint32_t clef;
  uint32_t horodatage;
  uint16_t mesuresT;
  uint16_t mesuresPh;
  uint16_t mesuresRedox;
  float mesuresSalinite;
};
extern stockDansSD_t stockMesuresDansSD;

#endif
