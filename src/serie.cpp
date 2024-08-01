//
// AntareS
// Fichier : serie.cpp / serie.h
// Version : 0.0.1
// Date : Juillet 2024
//

#include <Arduino.h>
#include "serie.h"

const byte usb_Capacity = 32;   // nombre d'octect maxi.
char usb_Buffer;                // tampon de lecture série.
char usb_Data[usb_Capacity];    // stockage d'une trame.
char usb_StartMarker   = '<';   // marqueur de début de trame.
char usb_EndMarker     = '>';   // marqueur de fin de trame.
char usb_SepP = ';';             // séparateur des paramètres
char usb_SepV = '=';            // séparateur paramètre/valeur.

bool usb_NewData  = false;
bool usb_Receive = false;

int usb_Index = 0;
int usb_IndexSep1 = 0;          // compteur du nombre de séparateur ';'.
int usb_IndexSep2 = 0;          // compteur du nombre de séparateir '='.

int id=0;
int val=0;
  
void USB_Init()
{
  Serial.begin(USB_Speed);
  Serial.println("Initialisation USB ok");
}

void USB_Read(int *tab_Values)
{
  while(Serial.available()>0 && usb_NewData == false)
  {
    usb_Buffer = Serial.read(); // lecture du tampon USB suite à l'arrivé de données sur le port série.

    if(usb_Receive == true)
    {
      if(usb_Buffer != usb_EndMarker)
      {
        usb_Data[usb_Index] = usb_Buffer; // stockage du tampon USB pour constituer la trame tant que l'on ne détecte pas le marqueur de fin de trame.
        usb_Index++;  // incrémentation pour passer au caractère suivant.
        if(usb_Index >= usb_Capacity)
        {
          usb_Index = usb_Capacity -1;
        }
      }
      else
      {
        // Marqueur de fin '>' trouvé dans le tampon USB .
        usb_Data[usb_Index] = '\0';
        usb_Receive = false;
        usb_Index = 0;
        usb_NewData = true;
        USB_Extract(tab_Values); // extraction des données de la trame stockées pour les stocker dans le tableau de valeur. 
      }
    }
    else if(usb_Buffer == usb_StartMarker)
    {
      //Serial.println("Marqueur de début trouvé...");
      usb_Receive = true; // le tampon USB vient de capter une trame suite à la lecture du '<', on va déclencher le stockage...
    }
  }
}
void USB_Extract(int *tab_Values) // on passe l'adresse du tableau de stockage des valeurs.
{
  char *strings[20]; // tableau de pointeur
  char *ptr = NULL;
  byte index = 0;

  ptr = strtok(usb_Data,";"); // on recherche le separateur de paramètres ';'
  while(ptr != NULL)
  {
    strings[index]=ptr;
    sscanf(strings[index],"%d=%d",&id ,&val); // separation index tableau et valeur.
    tab_Values[id]=val;
    index++;
    ptr=strtok(NULL,";");
  }
  usb_NewData=false;  // on a terminé l'extraction de la trame, on est prêt pour une nouvelle lecture.
}
