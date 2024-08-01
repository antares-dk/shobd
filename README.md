# shobd
SimHub OBDII communication

Objectif :
Etablir une liaison entre SimHub et un HUD OBDII

Pré-requis :

- SimHub
- Arduino Uno
- Bouclier CAN Bus
- Alimentation 12 Vdc.
- HUD Dashboard ODBII.
   
Optionnel :

- Prise femelle OBD-II ()

Configuratuin SimHub
* Ajouter un périphérique série personalisé
   * Configurer le port com de l'arduino ex : COM4
   * Ajouter des messages selon le format suivant :
         '<index_tableau='+ round(parametre_jeu,0)+';>'
     Configurer le taux de raffraichissement en général je le place sur 'changes_only'
     sauf pour les rpm qui sont paramétrés à 60 Hz.
