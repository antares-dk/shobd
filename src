//
// AntareS
// Fichier : obd2.cpp / obd2.h
// Version : 0.0.1
// Date : Juillet 2024
//

#include <Arduino.h>
#include "obd2.h"
#include <mcp2515_can.h>

mcp2515_can OBD2_CAN(SPI_CS_PIN);
//bool test_Mode = false;

void OBD2_Init()
{
  if(CAN_OK == OBD2_CAN.begin(CAN_500KBPS))
  {
    Serial.println("Initialisation CAN Bus ok !!!");
  }
}

void OBD2_SendPid()
{
  // Message OBD2 PID supportés
  byte mode1Supported0x00PID[8] = {0x06, 0x41, 0x00, 0x88, 0x1F, 0x00, 0x00, 0x00};
  byte mode1Supported0x20PID[8] = {0x06, 0x41, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00};
  byte mode1Supported0x40PID[8] = {0x06, 0x41, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00};
  byte mode1Supported0x60PID[8] = {0x06, 0x41, 0x60, 0x02, 0x00, 0x00, 0x00, 0x00};
  byte mode1Supported0x80PID[8] = {0x06, 0x41, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00};

  OBD2_CAN.sendMsgBuf(0x7E8, 0, 8, mode1Supported0x00PID);             // Plage des PID supportés
  OBD2_CAN.sendMsgBuf(0x7E8, 0, 8, mode1Supported0x20PID);             // Plage des PID supportés
  OBD2_CAN.sendMsgBuf(0x7E8, 0, 8, mode1Supported0x40PID);             // Plage des PID supportés 
}

void OBD2_SendValues(int *tab_Values)
{
  // Passer la variable test_Mode à true, puis assignez une adresse et une valeur à tester.
  
  //int test_Address = 0x0B;
  //int test_Value = 255;
  

  int vehicle_Speed = tab_Values[0];                // 0x0D < AC, ETS2
  int engine_Speed = tab_Values[1];                 // 0x0C < AC, ETS2
  int fuel_Level = tab_Values[2];                   // 0x2F < AC, ETS2, ...
  int engine_CalculatedLoad= tab_Values[3];         // 0x04
  int air_Temperature = tab_Values[4];              // 0x46 < AC
  int engine_CoolantTemp = tab_Values[5];           // 0x05 < ETS2, ...
  int intake_Air_Temp1 = tab_Values[6];              // 0x0F
  int intake_Air_Temp2=tab_Values[7];                // 0x68
  int mass_AirFlow = tab_Values[8];                  // 0x10
  int throttle1 = tab_Values[10];                    // 0x..
  int throttle2 = tab_Values[11];                    // 0x49 <
  int oil_Temperature = tab_Values[12];              // 0x5C < 
  int oil_Pressure = tab_Values[13];                 // Non supporté par l'OBD II

  // Calcul pour les RPM à mettre sur 2 bytes
  float rpm_Val = engine_Speed * 4;
  unsigned int rpm_A = (long)rpm_Val / 256;
  unsigned int rpm_B = (long)rpm_Val % 256;

  // Mass Air Flow (simulée avec la pédale d'accelérateur, puisque cette valeur est non gérée par les jeux)
  float maf_Val = throttle1*6.55*100;
  unsigned int maf_A = (long)maf_Val / 256;
  unsigned int maf_B = (long)maf_Val % 256;
  // Wikipédia OBDII > https://en.wikipedia.org/wiki/OBD-II_PIDs

  // Messages OBDII avec variables
  //                    Nombre d'octet après celui-ci (longueur)
  //                   |      Requête en mode 1 040 + 1 > 0x41 (65 en décimal).
  //                   |     |    Adresse Pid
  //                   |     |    |      Valeur Pid
  //                   |     |    |       |
  //                   v     v    v       v
  //byte message[8] = {3, 0x41, 0x0D, (byte)(value)};  
  
  byte vehicle_Speed_Msg[8] = {3, 0x41, 0x0D, (byte)(vehicle_Speed)};                       //0x0D 1 byte <0-255> (Km/h)
  byte engine_Speed_Msg[8] = {4, 0x41, 0x0C, (byte)rpm_A, (byte)rpm_B};                     //0x0C 2 bytes <0-1638>(rpm)
  byte engine_CalculatedLoad_Msg[8] = {3, 65,0x04,(byte)(engine_CalculatedLoad*2.55)};      //0x04
  byte engine_CoolantTemp_Msg[8] = {3, 0x41,0x05,(byte)(engine_CoolantTemp+40)};            //0x05
  byte fuel_Level_Msg[8] = {3, 0x41, 0x2F, (byte)(fuel_Level*(2.55))};                      //0x2F
  byte air_Temperature_Msg[8] = {3, 0x41, 0x46, (byte)(air_Temperature+40)};                //0x46  
  byte engine_MAF_Rate_Msg[8] = {4, 0x41, 0x10, (byte)maf_A, (byte)maf_B};                  //0x10
  byte throttle2_Msg[8] = {3, 0x41, 0x47, (byte)(throttle2*2.55)};                          //0x47
  byte oil_Temperature_Msg[8] = {3, 0x41, 0x5C, (byte)oil_Temperature};                     //0x5C
  byte intake_AirTemp1_Msg[8] = {3, 0x41, 0x0F, (byte)(intake_Air_Temp1+40)};               //0x0F  
  byte intake_AirTemp2_Msg[8] = {3, 0x41, 0x68, (byte)(intake_Air_Temp2+40)};               //0x68
  
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, vehicle_Speed_Msg);                                     // 0xOD
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, engine_Speed_Msg);                                      // 0xOC
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, engine_CalculatedLoad_Msg);                             // 0x04 
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, engine_CoolantTemp_Msg);                                // 0x05
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, engine_MAF_Rate_Msg);                                   // 0x10
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, fuel_Level_Msg);                                        // 0x2F  
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, air_Temperature_Msg);                                   // 0x46  
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, throttle2_Msg);                                         // 0x47
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, oil_Temperature_Msg);                                   // 0x5C
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, intake_AirTemp1_Msg);                                   // 0x0F
  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, intake_AirTemp2_Msg);                                   // 0x0F
  
  // Pour tester un Pid
  //if(test_Mode==true)
  //{
  //   byte test_Value_Msg[8] = {4, 65, test_Address, (byte)(test_Value)};
  //  OBD2_CAN.sendMsgBuf(OBD_ID, 0, 8, test_Value_Msg);
  //}
}
