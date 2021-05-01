

// INFO SUR LES CHANGEMENTS APPORTES DANS LA V2.0

// *-*-*-*-* Correction de BUG *-*-*-*
/* > Correction du bug "oscillo en mouvement meme quand OFF"
   > Correction du bug "oscillo demarage en dehors des angles" >>> demarrage centré entre l'angle 1 et 2
   > Correction du bug "alarme PH a repetition" >>> changement du module PH  par un modul ATLAS configurer en I2C
   > Correction de l'inversion blanc / bleu de la page web
   > Correction du probleme de non reception des sms envoyer a la chaine >>> ajout d'un delais apres l'envoie d'un SMS
   > suppresion de la gestion du RAC
*/

// *-*-*-*-* Amelioration *-*-*-*-*
/* > optimisation du code.
   > envoie de la temperature avec les alertes EDF.
   > Ajout d'un onglet config dans le code permetant, avant televersement, de configurer l'aquabouns en fonction de votre materiel.
   > Ajout de message d'erreur a la compilation en cas de mauvaise selection de carte et de probleme de definition dans l'onglet Config.
   > Possibilité d'inverser l'eclairage pour ceux qui utilise des eclairage fonctionnant en sens inverse, PWM 0 = 100% et PWM 255 = 0%. (dans la page Config avant televersement)
   > Possibilité de choisir le nombre de canaux (1 ou 2) par couleur. (dans la page Config avant televersement)
   > possibilité d'activer ou desactiver le buzzer. (dans la page Config avant televersement)
   > decalage d'une minute de la distribution de nouriture pour que l'eau est le temps de se calmer apres ralentissement des pompes de Brassage.
   > Progression par palier de 1% par seconde de la puissance lors du demarrage des tempetes jusque au max tempete.
   > ajout de deux pages graphique avec courbe temperature, Ph, redox et salinité sur 24h ou 7 jours
   > ajout d'un bouton redemarrage sur la page parametre pour rebooté manuelement
   > ajout d'un boolean pour etre alerté par sms au redemarrage apres une coupure edf + batterie (seulement si une batterie est installée)
   > ajout d'une page pour visualiser les evenements stockés sur la carte SD
   > Mesure ORP via module ATLAS
   > Mesure EC via module ATLAS
   > Mesure Ph via module ATLAS
   > Ajout d'une page etalonnage des sondes
   > Reglage de la puissance de demarage des pompe de Brassage (pour que le 0% corresponde au 0 de chaque pompe)
*/

// * *-*-*-*-* AMELIORATIONS ENVISAGEES DANS LES PROCHAINES VERSION : *-*-*-*-*
/* > creation d'une page web pour le parametrage ( toujours en attente d'aide pour le HTML !!! )
   > changement de la biblioteque nextion pour gagner en fiabilité, vitesse et ressource
*/
