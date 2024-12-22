# Configuration des messages Sim Hub
Voici le code utilisé pour composer les messages Sim Hub, j'ai séparé les messages afin de pouvoir personnaliser le taux de rafraichissement indépendament les uns des autres. 
Notez qu'il est possible d'envoyé une ou plusieurs valeur à la suite dans une trame comme par exemple ceci

``
<0=55;1=1200;3=25>
``
> J'ai eu quelques soucis d'actualisation perte de donnée en utilisant cette méthode avec des taux de rafraichissement trop haut, c'est pour cette raison que j'ai séparé les messages.

Vous avez ci dessous tous les messages ainsi que le taux de rafraichissement, vous pouvez effectuer un copier/coller
 

``'<0='+ round[SpeedKmh],0+';>' (ChangesOnly)``

``'<1='+ round[Rpms],0+';>' (60Hz)``

``'<2='+ round[Rpms],0+';>'``

``'<3='+ round[Rpms],0+';>'``

``'<4='+ round[Rpms],0+';>'``

``'<5='+ round[Rpms],0+';>'``

``'<6='+ round[Rpms],0+';>'``

``'<7='+ round[Rpms],0+';>'``

``'<8='+ round[Rpms],0+';>'``

``'<9='+ round[Rpms],0+';>'``

``'<10='+ round[Rpms],0+';>'``

