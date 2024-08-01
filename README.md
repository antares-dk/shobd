# shobd
SimHub OBDII communication

##Objectif :
Réaliser un hud rapidement pour vos jeux de course automobile, en établissant une liaison entre SimHub et un HUD [OBD II](https://en.wikipedia.org/wiki/On-board_diagnostics#OBD-II).

##Pré-requis :

- SimHub
- Arduino Uno
- Bouclier CAN Bus
- Alimentation 12 Vdc.
- <HUD Dashboard ODBII.
   
##Optionnel :

- Prise femelle OBD-II ()

Configuratuin SimHub
Pensez à activer le partage de données entre votre jeu et SimHub.

* Ajouter un périphérique série personalisé
   * Configurer le port com de l'arduino ex : COM4
   * Ajouter des messages selon le format suivant :
         '<index_tableau='+ round(parametre_jeu,0)+';>'
     
Configurer le taux de raffraichissement en général je le place sur 'changes_only', sauf pour les rpm qui sont paramétrés à 60 Hz.

Exemple de message pour l'envoi de la vitesse vers le HUD : '<0='+round([SpeedKmh],0)+';>'


