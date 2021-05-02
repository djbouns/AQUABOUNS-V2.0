# AQUABOUNS-V2.0
Automate pour aquarium recifal GRATUIT

Le projet AQUABOUNS en quelques mots
Le début ... Je suis aquariophile depuis mon enfance et récifaliste depuis 6 ans.

L'aquariophilie marine étant onéreuse, j'ai petit a petit commencé à bricoler pour mon bac, un nano 60L, d'abord une rampe LED en on/off, puis j'ai découvert l'arduino ...

Même si je n'ai aucune formation en informatique, codage et électronique, j'ai cherché à comprendre et apprendre au fur et à mesure ...  tout d'abord avec des choses simple, lever/coucher soleil, prise de température, ventilation ...

Mais quand je suis passé à 500L, je voulait tout automatiser.

Vu les prix pratiqués dans le commerce pour un automate complet, je me suis tourné vers l'ackduino et je me suis vite aperçu que cela ne me convenait pas et il était difficile de modifier un si gros code, donc ...

Ce projet a débuté en Mai 2017 dans l'intention de réaliser un automate pour aquarium récifal complet, fiable et à faible coût pour qu'un maximum de récifalistes puissent en profiter.

Cela représente des milliers d'heures de travail, ~6000 lignes de code. 

Des dépenses importantes pour tester et trouver le matériel le plus adapté.

Il est mis à disposition entièrement gratuitement afin que tout le monde puisse profiter d’un automate à faible coût.

Remerciements 
Cela a été possible grâce à quelques rares personnes qui m’ont aidé ou guidé quand j’en avais besoin.

Un GRAND merci à JML du forum Arduino pour son aide et tous ses conseils reçus, qui ont permis à ce projet d’être aussi abouti.

Merci à tous le forum Arduino pour son aide.

Merci à Commodore pour sa participation dans le développement de cette V2.0
 *-*-*-*-*
 *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-*
 *-*-*-*-*
> Tout est mis a votre disposition gratuitement et permet d'avoir un automate qui aurais pu vous coûter ~1000€ dans le commerce.
Soutenez le projet pour qu'il continue d’évoluer et d’être mis à disposition gratuitement en faisant un DON PAYPAL ;)

 *-*-*-*-*
 
 https://www.paypal.com/pools/c/88NxY14ZuS
 
 *-*-*-*-*
 
 *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-* *-*-*-*-*
 *-*-*-*-*

*INFO SUR LES CHANGEMENTS APPORTES DANS LA V2.0

*-*-*-*-* Correction de BUG *-*-*-*-*

> Correction du bug "oscillo en mouvement meme quand OFF".
> 
> Correction du bug "oscillo demarage en dehors des angles" >>> demarrage centré entre l'angle 1 et 2.
> 
> Correction du bug "alarme PH a repetition" >>> changement du module PH  par un modul ATLAS configurer en I2C.
> 
> Correction de l'inversion blanc / bleu de la page web.
> 
> Correction du probleme de non reception des sms envoyer a la chaine >>> ajout d'un delais apres l'envoie d'un SMS.
> 
> Suppresion de la gestion du RAC


*-*-*-*-* Amelioration *-*-*-*-*
> optimisation du code.
> 
> envoie de la temperature avec les alertes EDF.
> 
> Ajout d'un onglet config dans le code permetant, avant televersement, de configurer l'aquabouns en fonction de votre materiel.
> 
> Ajout de message d'erreur a la compilation en cas de mauvaise selection de carte et de probleme de definition dans l'onglet Config.
> 
> Possibilité d'inverser l'eclairage pour ceux qui utilise des eclairage fonctionnant en sens inverse, PWM 0 = 100% et PWM 255 = 0%. (dans la page Config avant televersement)
> 
> Possibilité de choisir le nombre de canaux (1 ou 2) par couleur. (dans la page Config avant televersement)
> 
> possibilité d'activer ou desactiver le buzzer. (dans la page Config avant televersement)
> 
> decalage d'une minute de la distribution de nouriture pour que l'eau est le temps de se calmer apres ralentissement des pompes de Brassage.
> 
> Progression par palier de 1% par seconde de la puissance lors du demarrage des tempetes jusque au max tempete.
> 
> ajout de deux pages graphique avec courbe temperature, Ph, redox et salinité sur 24h ou 7 jours
> 
> ajout d'un bouton redemarrage sur la page parametre pour rebooté manuelement
> 
> ajout d'un boolean pour etre alerté par sms au redemarrage apres une coupure edf + batterie (seulement si une batterie est installée)
> 
> ajout d'une page pour visualiser les evenements stockés sur la carte SD
> 
> Mesure ORP via module ATLAS
> 
> Mesure EC via module ATLAS
> 
> Mesure Ph via module ATLAS
> 
> Ajout d'une page etalonnage des sondes
> 
> Reglage de la puissance de demarage des pompe de Brassage (pour que le 0% corresponde au 0 de chaque pompe)
