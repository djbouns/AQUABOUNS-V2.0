# AQUABOUNS-V2.0
Le programme entierement GRATUIT pour automatiser votre d'aquarium récifal
l'Aquabouns, le Linux du récifaliste ;)

l’AQUABOUNS en questions:  
> l'AQUABOUNS c'est quoi ? ----------------------- l'AQUABOUNS est un programme pour automatiser votre aquarium récifal. 
> 
> Comment ça fonctionne ?------------------------- le programme AQUABOUNS est prévu pour etre instalé sur une cartes arduino Mega. l'arduino communique ensuite avec différents périphériques (ecran, module wifi et module GSM) et interprète l'état des différents capteurs (flotteur, sonde detempérature, horloge) et, en fonction du paramétrage, intervient sur le materiel du bac (pompe remonté, brassage, ventilation, écumeur ...). 
> 
> Comment obtenir le programme ? à quel prix ? --- l'AQUABOUNS est mis a disposition GRATUITEMENT, il a été déposé sous License libre (GPL 3.0) afin que tout le monde puisse en profiter. 
> 
> Comment faire le montage ? --------------------- Tout se trouve dans les notices que vous pouvez télécharger sur www.aquabouns.fr et si le montage n'est pas a votre porté, vous pouvez vous faire aider d'un PCBouns, www.pcbouns.fr. 

 *-*-*-*-*
 
 *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-*
 
 *-*-*-*-*

Remerciements :
Cela a été possible grâce à quelques rares personnes qui m’ont aidé ou guidé quand j’en avais besoin.
Un GRAND merci à JML du forum Arduino pour son aide et tous ses conseils reçus, qui ont permis à ce projet d’être aussi abouti.
Merci à tous le forum Arduino pour son aide.
Merci à Commodore pour sa participation dans le développement de cette V2.0

 *-*-*-*-*
 
 *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-*
 
 *-*-*-*-*
 
> Tout est mis à votre disposition gratuitement, soutenez le projet pour qu'il continue d’évoluer et d’être mis à disposition gratuitement en faisant un DON PAYPAL : 

 [![Donate](https://img.shields.io/badge/paypal-donate-yellow.svg)](https://www.paypal.com/paypalme/ProjetAquabouns)
 
 *-*-*-*-*
 
 *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-*
 
 *-*-*-*-*
 
## INFO SUR LES CHANGEMENTS APPORTES DANS LA V2.0

### Correction de BUG

> Correction du bug "oscillo en mouvement même quand OFF".
> 
> Correction du bug "oscillo démarrage en dehors des angles" >>> démarrage centré entre l'angle 1 et 2.
> 
> Correction du bug "alarme PH a répétition" >>> changement du module PH  par un module ATLAS configurer en I2C.
> 
> Correction de l'inversion blanc / bleu de la page web.
> 
> Correction du problème de non reception des SMS envoyer a la chaine >>> ajout d'un delais apres l'envoie d'un SMS.
> 
> Suppression de la gestion du RAC


### Améliorations
- optimisation du code.
- envoie de la température avec les alertes EDF. 
- Ajout d'un onglet config dans le code permettant, avant téléversement, de configurer l'Aquabouns en fonction de votre matériel.
- Ajout de message d'erreur a la compilation en cas de mauvaise sélection de carte et de problème de définition dans l'onglet Config.
- Possibilité d'inverser l'éclairage pour ceux qui utilise des éclairages fonctionnant en sens inverse, PWM 0 = 100% et PWM 255 = 0%. (dans la page Config avant televersement)
- Possibilité de choisir le nombre de canaux (1 ou 2) par couleur. (dans la page Config avant téléversement)
- possibilité d'activer ou desactiver le buzzer. (dans la page Config avant téléversement)
- décalage d'une minute de la distribution de nouriture pour que l'eau est le temps de se calmer après ralentissement des pompes de brassage.
- Progression par palier de 1% par seconde de la puissance lors du démarrage des tempetes jusque au max tempete.
- ajout de deux pages graphique avec courbe température, Ph, redox et salinité sur 24h ou 7 jours
- ajout d'un bouton redémarrage sur la page paramètre pour rebooter manuellement
- ajout d'un boolean pour être alerté par SMS au redémarrage après une coupure secteur + batterie (seulement si une batterie est installée)
- ajout d'une page pour visualiser les évènements stockés sur la carte SD
- Mesure ORP via module ATLAS
- Mesure EC via module ATLAS
- Mesure PH via module ATLAS
- Ajout d'une page étalonnage des sondes
- Réglage de la puissance de démarrage des pompes de brassage (pour que le 0% corresponde au 0 de chaque pompe)
