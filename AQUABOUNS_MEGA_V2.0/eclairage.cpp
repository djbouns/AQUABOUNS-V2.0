
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
#include "eclairage.h"
#include "global.h"
#include "debug.h"
#include "wifi.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
uint32_t debutleverSoleil[quatre];
uint32_t finleverSoleil[quatre];
uint32_t debutcoucherSoleil[quatre];
uint32_t fincoucherSoleil[quatre];

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonction $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* defini la puissance de l'eclairage */
void eclairage() {
  const float pourCentEnPwm = 2.55;
  for (uint8_t numeroEclairage = bleu1; numeroEclairage <= blanc2; numeroEclairage++) { // lance la fonction une fois pour chaque canal
    if (sauvegarde.eclairageOnOffPwm [numeroEclairage] == Arret) { // si OFF
      variable.pwmEclairage[numeroEclairage] = zero; // puissance zero
    }
    else if (sauvegarde.eclairageOnOffPwm [numeroEclairage] == Actif) { // si ON
      variable.pwmEclairage[numeroEclairage] = sauvegarde.puissanceMaxEclairage[numeroEclairage]; // puissance max definie
    }
    else if (sauvegarde.eclairageOnOffPwm [numeroEclairage] == Pwm) { // si PWM
      if ((Time >= debutleverSoleil[numeroEclairage]) && (Time < finleverSoleil[numeroEclairage])) { // lever de soleil
        variable.pwmEclairage[numeroEclairage] = map(Time, debutleverSoleil[numeroEclairage], finleverSoleil[numeroEclairage], zero, sauvegarde.puissanceMaxEclairage[numeroEclairage]); // progression
      }
      else if ((Time >= debutcoucherSoleil[numeroEclairage]) && (Time < fincoucherSoleil[numeroEclairage])) { // coucher de soleil
        variable.pwmEclairage[numeroEclairage] = map(Time, debutcoucherSoleil[numeroEclairage], fincoucherSoleil[numeroEclairage], sauvegarde.puissanceMaxEclairage[numeroEclairage], zero); // progression
      }
      else if ((Time >= finleverSoleil[numeroEclairage] ) && (Time < debutcoucherSoleil[numeroEclairage])) { // zenith
        variable.pwmEclairage[numeroEclairage] = sauvegarde.puissanceMaxEclairage[numeroEclairage]; // puissance max definie
      }
      else { // nuit
        variable.pwmEclairage[numeroEclairage] = zero;
      }
    }
#ifdef PWMinvere // Si éclairage invessé (PWM 0 = 100% et PWM 255 = 0%)
    uint8_t pwmEclairageInverse = (variable.pwmEclairage[numeroEclairage] + cent) - (variable.pwmEclairage[numeroEclairage * deux);
                                  analogWrite (pinOutEclairage[numeroEclairage], pwmEclairageInverse * pourCentEnPwm); // envoie sur le pin la puissance calculé
#else // Si éclairage standard
    analogWrite (pinOutEclairage[numeroEclairage], variable.pwmEclairage[numeroEclairage] * pourCentEnPwm); // envoie sur le pin la puissance calculé
#endif
  }
}
