#ifndef  _gsm_h_
#define _gsm_h_

#define gsmPrintATCommand(...)    gsm.print(__VA_ARGS__)
#define gsmPrintlnATCommand(...)  gsm.println(__VA_ARGS__)
#define gsmWriteATCommand(...)    gsm.write(__VA_ARGS__)

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <avr/wdt.h>
#include <arduino.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Declarations des fonctions dans le .cpp $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
boolean getGSMLine();
void ecouterGSM();
boolean envoyerSMS(const char * noDeTel, const char * messageAEnvoyer);
void completerMessageAlerte(const char debutMessage[] PROGMEM, const char milieuMessage[] PROGMEM);
void completerMessageAlerteTemperature(const char debutMessage[] PROGMEM);
void completerMessageAlertePh(const char debutMessage[] PROGMEM);
void effaceMessageGsm();
void etatGSM();
boolean nomOperateurRecu();
boolean signalGSMRecu() ;
#endif

/* tableau equivalence puissance du signal en reponse a AT+CSQ
Valeur  dBm   Qualité
2       -109  Marginal
3       -107  Marginal
4       -105  Marginal
5       -103  Marginal
6       -101  Marginal
7       -99   Marginal
8       -97   Marginal
9       -95   Marginal
10      -93   D'accord
11      -91   D'accord
12      -89   D'accord
13      -87   D'accord
14      -85   D'accord
15      -83   Bien
16      -81   Bien
17      -79   Bien
18      -77   Bien
19      -75   Bien
20      -73   Excellent
21      -71   Excellent
22      -69   Excellent
23      -67   Excellent
24      -65   Excellent
25      -63   Excellent
26      -61   Excellent
27      -59   Excellent
28      -57   Excellent
29      -55   Excellent
30      -53   Excelent
*/
