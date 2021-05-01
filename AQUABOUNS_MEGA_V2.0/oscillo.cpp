
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
#include <Servo.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "oscillo.h"
#include "global.h"
#include "arduino.h"
#include "affichage.h"
#include "eeprom.h"
#include "debug.h"
#include "autres.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
uint8_t positionOscillo[trois];
Servo oscillo[trois];
boolean vaEtVientOscillo[trois];
uint32_t tempsPrecedentOscillo[trois];

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonction $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* effectue le mouvement des oscillateurs */
void oscillateur() {
  enum {aller, retour, fin = 255};
  if (pageActuelNextion != brass) { // pas de mouvement si sur la page Brassage
    for (uint8_t numeroOscillo = numeroUn; numeroOscillo <= numeroTrois; numeroOscillo++) { // effectue la fonction une fois par oscillateurs
      if (sauvegarde.delaisMouvementOscilloMillis[numeroOscillo] != zero) { // si l'oscilo n'est pas en OFF
        if (millis() - tempsPrecedentOscillo[numeroOscillo] >= sauvegarde.delaisMouvementOscilloMillis[numeroOscillo]) { // mouvement des oscillateur  toutes les "sauvegarde.delaisMouvementOscilloMillis"
          tempsPrecedentOscillo[numeroOscillo] = millis(); // MAJ du compteur
          if (positionOscillo[numeroOscillo] == sauvegarde.angle1Oscillo[numeroOscillo]) { // mouvement aller
            positionOscillo[numeroOscillo]++; // incremente la position
            vaEtVientOscillo[numeroOscillo] = aller; // sens oscillation
          }
          else if (positionOscillo[numeroOscillo] == sauvegarde.angle2Oscillo[numeroOscillo]) { // mouvement retour
            positionOscillo[numeroOscillo]-- ; // incremente la position
            vaEtVientOscillo[numeroOscillo] = retour; // sens oscillation
          }
          else if ((vaEtVientOscillo[numeroOscillo] == aller) && (positionOscillo[numeroOscillo] < sauvegarde.angle2Oscillo[numeroOscillo])) { // fait demi tour arriver au max
            positionOscillo[numeroOscillo]++ ; // incremente la position
          }
          else if ((vaEtVientOscillo[numeroOscillo] == retour) && (positionOscillo[numeroOscillo] > sauvegarde.angle1Oscillo[numeroOscillo])) { // fait demi tour arriver au min
            positionOscillo[numeroOscillo]--; // incremente la position
          }
          oscillo[numeroOscillo].write(positionOscillo[numeroOscillo]); // envoie l'angle a l'oscillateur
          //DPRINTF("oscillo "); DPRINT(numeroOscillo); DPRINTF(" position : "); DPRINT(positionOscillo[numeroOscillo]); DPRINTLN();
        }
      }
    }
  }
}
