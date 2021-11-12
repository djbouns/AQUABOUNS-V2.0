# AQUABOUNS-V2.0
Le programme d'automatisation d'aquarium récifal entièrement GRATUIT.
Le Linux du récifaliste ;)

Le projet AQUABOUNS en quelques mots
Le début ... Je suis aquariophile depuis mon enfance et récifaliste depuis 6 ans.

L'aquariophilie marine étant onéreuse, j'ai petit a petit commencé à bricoler pour mon bac, un nano 60L, d'abord une rampe LED en on/off, puis j'ai découvert l'arduino ...

Même si je n'ai aucune formation en informatique, codage et électronique, j'ai cherché à comprendre et apprendre au fur et à mesure ...  tout d'abord avec des choses simples, lever/coucher soleil, prise de température, ventilation ...

Mais quand je suis passé à 500L, je voulais tout automatiser.

Vu les prix pratiqués dans le commerce pour un automate complet, je me suis tourné vers l'ackduino et je me suis vite aperçu que cela ne me convenait pas et il était difficile de modifier un si gros code, donc ...

Ce projet a débuté en Mai 2017 avec l'intention de réaliser un automate pour aquarium récifal complet, fiable et à faible coût pour qu'un maximum de récifalistes puissent en profiter.

Cela représente des milliers d'heures de travail, ~6000 lignes de code. 

Des dépenses importantes pour tester et trouver le matériel le plus adapté.

Il est mis à disposition entièrement gratuitement afin que tout le monde puisse profiter d’un automate à faible coût.

Remerciements: 
Cela a été possible grâce à quelques rares personnes qui m’ont aidé ou guidé quand j’en avais besoin.

Un GRAND merci à JML du forum Arduino pour son aide et tous ses conseils reçus, qui ont permis à ce projet d’être aussi abouti.

Merci à tous le forum Arduino pour son aide.

Merci à Commodore pour sa participation dans le développement de cette V2.0

 *-*-*-*-*
 
 *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-*
 
 *-*-*-*-*
 
> Tout est mis à votre disposition gratuitement et permet d'avoir un automate qui aurais pu vous coûter ~1000€ dans le commerce.
Soutenez le projet pour qu'il continue d’évoluer et d’être mis à disposition gratuitement en faisant un DON PAYPAL ;)

 *-*-*-*-*
 
 https://www.paypal.com/pools/c/88NxY14ZuS
 
 *-*-*-*-*
 
 *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-*
 
 *-*-*-*-*
 
*INFO SUR LES CHANGEMENTS APPORTES DANS LA V2.0

*-*-*-*-* Correction de BUG *-*-*-*-*

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


*-*-*-*-* Amélioration *-*-*-*-*
> optimisation du code.
> 
> envoie de la température avec les alertes EDF.
> 
> Ajout d'un onglet config dans le code permettant avant téléversement, de configurer l'Aquabouns en fonction de votre matériel.
> 
> Ajout de message d'erreur à la compilation en cas de mauvaise sélection de carte et de problème de définition dans l'onglet Config.
> 
> Possibilité d'inverser l'éclairage pour ceux qui utilise des éclairages fonctionnant en sens inverse, PWM 0 = 100% et PWM 255 = 0%. (dans la page Config avant téléversement)
> 
> Possibilité de choisir le nombre de canaux (1 ou 2) par couleur. (dans la page Config avant téléversement)
> 
> possibilité d'activer ou désactiver le buzzer. (dans la page Config avant téléversement)
> 
> décalage d'une minute de la distribution de nouriture pour que l'eau est le temps de se calmer après ralentissement des pompes de brassage.
> 
> Progression par palier de 1% par seconde de la puissance lors du démarrage des tempetes jusque au max tempete.
> 
> ajout de deux pages graphique avec courbe température, Ph, redox et salinité sur 24h ou 7 jours
> 
> ajout d'un bouton redémarrage sur la page paramètre pour rebooter manuellement
> 
> ajout d'un booléen pour être alerté par SMS au redémarrage après une coupure secteur + batterie (seulement si une batterie est installée)
> 
> ajout d'une page pour visualiser les évènements stockés sur la carte SD
> 
> Mesure ORP via module ATLAS
> 
> Mesure EC via module ATLAS
> 
> Mesure PH via module ATLAS
> 
> Ajout d'une page étalonnage des sondes
> 
> Réglage de la puissance de démarrage des pompes de brassage (pour que le 0% corresponde au 0 de chaque pompe)
