# shobd
Sim Hub OBDII communication

## Objectif :
Réaliser un hud rapidement pour vos jeux de course automobile, en établissant une liaison entre SimHub et un HUD [OBD II](https://en.wikipedia.org/wiki/On-board_diagnostics#OBD-II).

## Pré-requis :

- SimHub
- Arduino Uno
- Bouclier CAN Bus
- Alimentation 12 Vdc.
- <HUD Dashboard ODBII.
   
## Optionnel :

- Prise femelle OBD-II ()

## Configuratuin SimHub
Pensez à activer le partage de données entre votre jeu et SimHub.

* Ajouter un périphérique série personalisé
   * Configurer le port com de l'arduino ex : COM4
   * Ajouter des messages selon le format suivant :
         '<index_tableau='+ round(parametre_jeu,0)+';>'
     
Configurer le taux de raffraichissement en général je le place sur 'changes_only', sauf pour les rpm qui sont paramétrés à 60 Hz.

Exemple de message pour l'envoi de la vitesse vers le HUD : '<0='+round([SpeedKmh],0)+';>'

## Codage
Le code de l'application est divisé en plusieurs parties afin de séparer clairement les fonctionnalités afin de faciliter les mises à jours et le debogage de l'application. Il sera également plus facile d'y ajouter de nouvelles fonctionnalités. Les fichiers se présentent comme suit :

* shobd.ino : Programme principal où sont émis les appels des différentes fonctions.
* serie.cpp (et son fichier d'entête) : Gestion du port série USB et de l'extraction des valeurs renvoyées par Sim Hub
* obd2.cpp (et son fichier d'entête) : Gestion du CAN Bus et envoi des données vers le HUD au format OBD-II.

## Câblage
>[!CAUTION]
>Il est nécessaire de relier la masse de votre alimentation 12Vdc avec l'une des masse de l'Arduino.

## Resources externes
- [SimHub](https://www.simhubdash.com/)
- [Wikipédia : OBD II](https://en.wikipedia.org/wiki/On-board_diagnostics#OBD-II)
- [Wikipédia : OBD II Pid](https://en.wikipedia.org/wiki/OBD-II_PIDs)
