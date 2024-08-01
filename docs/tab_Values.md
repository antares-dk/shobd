# La table d'échange
Voici la correspondance entre les valeurs du jeu envoyées via les messages configurés sur SimHub l'index de la table d'échange et le PID OBD-II sur lesquels les valeurs sont renvoyées.

>Message SimHub > Table d'echange > Variables OBD II > Message OBD II

  0. Vitesse du véhicule (SpeedKmh)                 => Pid **0x0D**
  1. Régime moteur (Rpms).                          => Pid **0x0C**
  2. Niveau de carburant (FuelPercent)              => Pid **0x2F**
  3. Utilisation du CPU (CPULoadPercent)            => Pid **0x04**
  4. Température de l'air ambiant (AirTemperature)  => Pid **0x**
  5. Température du liquide de refroidissement      => Pid **0x**
  6. Température de l'air d'admission IAT (AirTemperature) => Pid **0x0F**      
  7. Température de l'air d'admission
  8. Volume d'air messuré par le débimètre MAF (Throttle) = PID **0x**
  9. Position pédale d'accélérateur (Throttle)  =>  PID **0x**
  10. Température de l'huile moteur
  11. Pression d'Huile = Pas de PID OBDII pour cette valeur, réservation utilisation future.
