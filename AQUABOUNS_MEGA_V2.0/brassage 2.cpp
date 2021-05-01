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

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "config.h"
#include "brassage.h"
#include "global.h"
#include "debug.h"
#include "affichage.h"
#include "wifi.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
boolean tempeteManuelEnCours = false;
boolean tempeteAleatoireOn = false;
boolean tempeteAleatoireEnCours = false;
boolean MajEcranTempeteEnCours = false;
boolean MajEcranNourrissageEnCours = false;
boolean nourissageEnCours = false;
boolean definiTempeteDuLendemain = true;
boolean progressionPuissanceBrassage = true;
uint8_t puissanceMinBrassage[trois];
uint32_t heureTempeteAleatoire;
uint32_t dureeTempeteAleatoire;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonctions $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* defini la puissance du Brassage */
void Brassage() {
  const uint8_t pwmMax = 255;
  if (pageActuelNextion != brass) { // si pas sur la page Brassage
    for (uint8_t numeroBrassage = numeroUn; numeroBrassage <= numeroTrois ; numeroBrassage++) { // lance la fonction pour chaque pompe de Brassage
      /* si nourissage en cours */
      if (nourissageEnCours ) {
        if (millis() - tempsPrecedentNourrissage <= sauvegarde.dureeNourrissageMillis) { // si duree du nourisssage non ateinte
          if (sauvegarde.BrassageOnOffPwm[numeroBrassage] != Arret) { // si pas en OFF baisse du Brassage au MIN
            variable.pwmBrassage[numeroBrassage] = puissanceMinBrassage[numeroBrassage];
            // DPRINTF("Brassage minimum car Nourrissage"); DPRINTLN();
          }
          else { // si en OFF
            variable.pwmBrassage[numeroBrassage] = zero;
            // DPRINTF("Nourrissage mais en OFF"); DPRINTLN();
          }
          if (MajEcranTempeteEnCours ) { // si tempette en cours, tempette OFF
            MajEcranTempeteEnCours = false;
            statutTempete(); // met a jour l'icone sur l'ecran
          }
          if (tempeteAleatoireEnCours ) { // si la tempette etait ON
            tempeteAleatoireEnCours = false; // met tempete en OFF
          }
        }
        else { // nourissage fini
          nourissageEnCours = false;
          onOffalimentation = true; // met le bouton en true
        }
      }
      /* si tempete manuel en cours */
      else if (tempeteManuelEnCours ) { // tempete manuel ON
        if (millis() - tempsPrecedentTempete <= sauvegarde.dureeTempeteMillis) { // si tempete manuel
          if (sauvegarde.BrassageOnOffPwm[numeroBrassage] == Actif) { // si en ON
            variable.pwmBrassage[numeroBrassage] = sauvegarde.puissanceTempete; // puissance maximal definie pour la tempete
          }
          else if (sauvegarde.BrassageOnOffPwm[numeroBrassage] == Pwm) { // si en PWM
            if (variable.pwmBrassage[numeroBrassage] < sauvegarde.puissanceTempete) { // si puissance inferienre a sauvegarde.puissanceTempete
              variable.pwmBrassage[numeroBrassage]++; // ajoute 1%
              progressionPuissanceBrassage = true; // progression en cours
            }
            else {
              variable.pwmBrassage[numeroBrassage] = sauvegarde.puissanceTempete; // puissance maximal definie pour la tempete
            }
          }
          else { // si en OFF
            variable.pwmBrassage[numeroBrassage] = zero; // puissance zero
          }
          if (MajEcranTempeteEnCours == false) { // boolean pour ne pas mettre a jour les info a l'ecran en boucle
            MajEcranTempeteEnCours = true;
            statutTempete(); // MAJ l'icone sur l'ecran
          }
          if (MajEcranNourrissageEnCours ) { // boolean pour ne pas mettre a jour les info a l'ecran en boucle
            MajEcranNourrissageEnCours = false;
          }
          if (tempeteAleatoireEnCours ) {// boolean pour ne pas mettre a jour les info a l'ecran en boucle
            tempeteAleatoireEnCours = false;
          }
        }
        else { // fin de la tempette manuel
          tempeteManuelEnCours = false; // boolean pour mettre a jour les info a l'ecran
        }
      }

      /* si tempete aleatoir en cours */
      else if (tempeteAleatoireEnCours ) { // tempete aleatoir activé
        if (millis() - tempsPrecedentTempeteAleatoire <= dureeTempeteAleatoire) { // dans le delais de la tempte
          if (sauvegarde.BrassageOnOffPwm[numeroBrassage] == Actif) { // si en ON
            variable.pwmBrassage[numeroBrassage] = sauvegarde.puissanceTempete; // puissance maximal definie pour la tempete
          }
          else if (sauvegarde.BrassageOnOffPwm[numeroBrassage] == Pwm) { // si en PWM
            if (variable.pwmBrassage[numeroBrassage] < sauvegarde.puissanceTempete) { // si puissance inferienre a sauvegarde.puissanceTempete
              variable.pwmBrassage[numeroBrassage]++; // ajoute 1%
              progressionPuissanceBrassage = true; // progression en cours
            }
            else {
              variable.pwmBrassage[numeroBrassage] = sauvegarde.puissanceTempete; // puissance maximal definie pour la tempete
            }
          }
          else { // si en OFF
            variable.pwmBrassage[numeroBrassage] = zero; // puissance zero
          }
          if (MajEcranTempeteEnCours == false) { // boolean pour ne pas mettre a jour les info a l'ecran en boucle
            MajEcranTempeteEnCours = true;
            statutTempete(); // MAJ l'icone sur l'ecran
          }
          if (MajEcranNourrissageEnCours ) {
            MajEcranNourrissageEnCours = false;
          }
        }
        else { // si tempete aleatoir fini
          tempeteAleatoireEnCours = false;
        }
      }
      /* sinon Brassage "normal" selon horraire */
      else {
        if (sauvegarde.BrassageOnOffPwm[numeroBrassage] == Arret) { // si Brassage OFF
          variable.pwmBrassage[numeroBrassage] = zero; // puissance zero
          //DPRINTF("Brassage OFF");DPRINT(numeroBrassage); DPRINTLN(); //debug
        }
        else if (sauvegarde.BrassageOnOffPwm[numeroBrassage] == Actif) { // si Brassage ON
          variable.pwmBrassage[numeroBrassage] = sauvegarde.puissanceMaxBrassage[numeroBrassage]; // puissance MAX defini
          //DPRINTF("Brassage nominal");DPRINT(numeroBrassage); DPRINTLN(); //debug
        }
        else if (sauvegarde.BrassageOnOffPwm[numeroBrassage] == Pwm) { // si Brassage PWM acalmie la nuit, lever/coucher associer au soleil
          if ((Time >= debutleverSoleil[bleu1]) && (Time < finleverSoleil[blanc2])) { // augmentation pendent lever soleil
            variable.pwmBrassage[numeroBrassage] = map(Time, debutleverSoleil[bleu1], finleverSoleil[blanc2], puissanceMinBrassage[numeroBrassage], sauvegarde.puissanceMaxBrassage[numeroBrassage]);
          }
          else if ((Time >= finleverSoleil[blanc2]) && (Time < debutcoucherSoleil[blanc1])) { // puissance MAX defini pendent le zenith
            if (variable.pwmBrassage[numeroBrassage] < sauvegarde.puissanceMaxBrassage[numeroBrassage]) {
              variable.pwmBrassage[numeroBrassage]++; // ajoute 1%
              progressionPuissanceBrassage = true; // progression en cours
            }
            else {
              variable.pwmBrassage[numeroBrassage] = sauvegarde.puissanceMaxBrassage[numeroBrassage];
              progressionPuissanceBrassage = false; // progression en cours
            }
          }
          else if ((Time >= debutcoucherSoleil[blanc1]) && (Time < fincoucherSoleil[bleu2])) { // dimminition pendent coucher soleil
            variable.pwmBrassage[numeroBrassage] = map(Time, debutcoucherSoleil[blanc1], fincoucherSoleil[bleu2], sauvegarde.puissanceMaxBrassage[numeroBrassage], puissanceMinBrassage[numeroBrassage]);
          }
          else {
            variable.pwmBrassage[numeroBrassage] = puissanceMinBrassage[numeroBrassage]; // puissance MAX minoré de la baisse accalmie/nourissage
          }
        }
        if (MajEcranTempeteEnCours ) { // boolean pour ne pas avoir de mise a jour de l'ecran a repetition
          MajEcranTempeteEnCours = false;
          statutTempete();
        }
        if (MajEcranNourrissageEnCours ) { // boolean pour ne pas avoir de mise a jour de l'ecran a repetition
          MajEcranNourrissageEnCours = false;
        }
        if (tempeteAleatoireEnCours ) { // boolean pour ne pas avoir de mise a jour de l'ecran a repetition
          tempeteAleatoireEnCours = false;
        }
      }
      if (variable.pwmBrassage[numeroBrassage] == zero) {
        analogWrite(pinOutBrassage[numeroBrassage], zero);
        DPRINTF("PWM : 0"); DPRINTLN();
      }
      else {
        uint8_t pwmPompe = map(variable.pwmBrassage[numeroBrassage], zero, cent, sauvegarde.puissanceDemarageBrassage[numeroBrassage], pwmMax );
        analogWrite(pinOutBrassage[numeroBrassage], pwmPompe);
        DPRINTF("PWM : "); DPRINT(pwmPompe); DPRINTLN();
      }
    }
  }
}

/* defini l'heure et la duree de la tempete aleatoire */
void definiTempeteAleatoire() {
  heureTempeteAleatoire = random(finleverSoleil[blanc2], debutcoucherSoleil[blanc1]); // defini aléatoirement l'heure de la tempête (forcement pendant le zenith)
  dureeTempeteAleatoire = random((sauvegarde.dureeTempeteMillis / dix), (sauvegarde.dureeTempeteMillis )); // defini aléatoire la duree de la tempête (minimum : MAX/10 maximun: MAX defini)
  tempsPrecedentTempeteAleatoire = zero;
  DPRINTF("heure tempete aleatoire :"); DPRINT(heureTempeteAleatoire);  DPRINTLN(); // debug //debug
  DPRINTF("duree tempete aleatoire :"); DPRINT((dureeTempeteAleatoire / mille) / minuteEnSeconde);  DPRINTLN(); // debug //debug
}

/* declanche la tempete aleatoir si l'heure defini est ateint */
void tempeteAleatoireAutomatique() {
  if (sauvegarde.tempeteAleatoireOn ) { // si mode tempête aléatoire ON
    if (tempeteAleatoireEnCours == false) {
      if (Time == heureTempeteAleatoire ) { // declanchement de la tempête selon heure aléatoire
        tempsPrecedentTempeteAleatoire = millis(); // met le compteur a zero
        tempeteAleatoireEnCours = true; // temepete aleatoir ON
        definiTempeteDuLendemain = true; // pour definir la tempetre du lendemain
        progressionPuissanceBrassage = true;
        DPRINTF("declenchement automatique de la tempete Aleatoire");  DPRINTLN(); // debug //debug
        DPRINTF("time :"); DPRINT(Time); DPRINTF(" / heure tempete :"); DPRINT(heureTempeteAleatoire);  DPRINTLN(); // debug //debug
        DPRINT(millis()); DPRINTF(" / duree :"); DPRINT(dureeTempeteAleatoire);  DPRINTLN(); // debug //debug
      }
    }
  }
  if (sauvegarde.tempeteAleatoireOn ) { // si mode tempête aléatoire ON
    if (definiTempeteDuLendemain ) {
      if (Time == sauvegarde.coucherSoleil) { // prevoi la tempette du lendemain une fois le soleil couché
        definiTempeteAleatoire(); // lance la fonction
        definiTempeteDuLendemain = false; // pour ne pas definir la tempete aleatoir en boucle
        if (pageActuelNextion == menu) { // si sur page menu
          tempeteNextion(); // MAJ l'heure et duree de la tempete aleatoir a l'ecran
        }
      }
    }
  }
}
