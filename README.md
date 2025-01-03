# Un Dashboard pour le Sim Racing à moins de 35 €
SHOBD (SimHub OBD), mon premier projet à base d'Arduino.

![Project Cars 2](img/pj2.PNG)

_Exemple d'utilisation sur Project Cars 2_
## Objectif :
Je souhaitais me fabriquer un dashboard pour le poser par dessus le boitier du volant Logitech G27, mais par manque de temps et de motivation, sélection des éléments, fabrication d'un boitier, etc... Je suis finalement tombé sur un Hud OBD-II vendu sur un site de commerce en ligne bien connu. [Aliexpress : HUD Display](https://fr.aliexpress.com/w/wholesale-hud-obd2-display.html?spm=a2g0o.home.auto_suggest.1.2eeb7065Oqmlwb).

La solution simple rapide, plutôt facile à développer, le boitier est déjà fait, les pages du dashboard aussi...
C'est de cette manière que j'ai réalisé un hud rapidement pour les jeux de course automobile, en établissant une liaison entre SimHub et un HUD [OBD II](#resources-externes). 

Ce qui me permet déjà de profiter d'un Hud dans mes Simu et de réfléchir un peu plus sur le prochain dashboard. Puis le HUD finira dans la voiture de Madame quand j'aurais mon Dashboard DIY.

Le coût de ce Dashboard ODB-II est aux alentours de 30 €

### Avantages
   - Rapidité de mise en service (même avec l'apprentissage du C++/c et les recherches CAN-Bus, OBD-II), donc pour vous cela devrait être plus rapide...
   - Plusieurs thèmes et pages déjà toutes faites
   - Un boitier bien fini.
   - Reste compatible avec une vraie voiture

### Inconvénients
   - Certaines variables OBD-II n'existe pas dans le jeu, l'animmation du Hud sera donc impossible ou simuler la valeur.
   - Certaones variables du jeux n'existe pas dans le HUD ODBII _(pas d'affichage de la vitesse enclenchée par exemple)_.
   - Impossible de créer de nouvelles pages dashboard.
   - Faut que j'adapte mon code pour d'autre adruino, d'autre interface MCP2515...
     
## Pré-requis :

- SimHub (Gratuit, ou license sur le principe d'un don volontaire).
- [Arduino Uno (3€)](https://fr.aliexpress.com/w/wholesale-arduinos-uno.html?spm=a2g0o.home.auto_suggest.2.2eeb7065GGchxI).
- [Bouclier CAN Bus (3€)](https://fr.aliexpress.com/w/wholesale-bouclier-canbus.html?spm=a2g0o.productlist.search.0).
- Alimentation 12 Vdc. (en stock, le hud consomme moins de 500 mA).
- [HUD Dashboard ODB-II. (25€)](https://fr.aliexpress.com/w/wholesale-hud-obd2-display.html?spm=a2g0o.home.auto_suggest.1.2eeb7065Oqmlwb).
   
## Optionnel :

- [Prise femelle OBD-II (2€)](https://fr.aliexpress.com/w/wholesale-cable-extension-OBD.html?spm=a2g0o.productlist.search.0)

![Prise ODBII](img/ODBII.PNG)

J'ai préféré acheter une prise ODB-2 car d'une part le HUD est facilement déconnectable pour l'installer dans une vraie voiture, d'autre part ce projet pourrait finir par faire un simulateur ODB-II pour tester des outils de diagnostics ou autre équipement ODB-2.
En y ajoutant des sélecteurs, des potentiomètres... Bref les possibilités sont multiples, ce projet peut dérriver à la guise de chacuns.

## Configuratuin SimHub
Pensez à activer le partage de données entre votre jeu et SimHub.

* Ajouter un périphérique série personalisé
   * Configurer le port com de l'arduino ex : COM4
   * Ajouter des messages selon le format suivant :
         '<index_tableau='+ round(parametre_jeu,0)+';>'

>Vous remarquerez un forçage des valeurs en valeur entière, on est pas chez la naza nul besoin d'une precission flottante...
     
Configurer le taux de raffraichissement en général sur 'changes_only', sauf pour les rpm qui sont paramétrés à 60 Hz.

Exemple de message pour l'envoi de la vitesse vers le HUD : '<0='+round([SpeedKmh],0)+';>'

![Messages Sim Hub](img/simhub_messages.PNG)

## Codage
Le code de l'application est divisé en plusieurs parties afin de séparer clairement les fonctionnalités afin de faciliter les mises à jours et le debogage de l'application. Il sera également plus facile d'y ajouter de nouvelles fonctionnalités. Les fichiers se présentent comme suit :

* shobd.ino : Programme principal où sont émis les appels des différentes fonctions.
* serie.cpp (et son fichier d'entête) : Gestion du port série USB et de l'extraction des valeurs renvoyées par Sim Hub
* obd2.cpp (et son fichier d'entête) : Gestion du CAN Bus et envoi des données vers le HUD au format OBD-II.

Comme c'est la première fois que je code, j'attire votre attention sur mon manque d'expérience et fait appel à votre indulgence. Si vous avez des remarques ou suggestion n'hésitez pas à mes les transmettre.

>Le croquis n'utilise que 10294 octets de l'espace de stockage, et les variables globales 527 octets soit respectivement 31% et 25% ce qui laisse de la place pour l'ajout de fonctionnalité comme :
Affichage, Boite à bouton, etc...

### Explication rapide
L'Arduino surveille l'arrivée de nouvelles données sur le port USB, lorsqu'une trame composée de deux chevrons un d'ouverture '<' et l'autre de fermeture '>' la trame est alors analysée afin d'en extraire les valeurs pour les stocker dans une table d'echange. Cette table d'echange est envoyée ensuite sous forme de trame ODB II via le CAN Bus.

exemple d'un message reçu par Sim Hub : <0=55;1=1075;>

dans le fichier "Serie.cpp"
l'index 0 de la table d'échange va donc recevoir la valeur 55.
l'index 1 recevra lui la valeur 1075.

on transforme ensuite la table d'échange dans le fichier "ODB-II"  
on initialise les variables ODB-II avec les valeurs de la table d'échange

``
 int vehicle_Speed = tab_Values[0];
``

``
 int engine_Speed = tab_Values[1];
``

puis on créé le message ODB-II

``
byte vehicle_Speed_Msg[8] = {3, 0x41, 0x0D, (byte)(vehicle_Speed)}; 
``

on envoi ensuite le message via le CAN-Bus

``
OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, vehicle_Speed_Msg);                                     // 0xOD
``
## Câblage
>[!CAUTION]
>Il est nécessaire de relier la masse de votre alimentation 12Vdc avec l'une des masse de l'Arduino.

## Resources externes
- [SimHub](https://www.simhubdash.com/)
- [Wikipédia : OBD II](https://en.wikipedia.org/wiki/On-board_diagnostics#OBD-II)
- [Wikipédia : OBD II Pid](https://en.wikipedia.org/wiki/OBD-II_PIDs)
- [Github : MCP2515](https://github.com/Seeed-Studio/Seeed_Arduino_CAN)
