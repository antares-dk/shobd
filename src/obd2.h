//
// AntareS
// Fichier : obd2.cpp / obd2.h
// Version : 0.0.1
// Date : Juillet 2024
//

#define SPI_CS_PIN 10
#define OBD_ID 0x7E8

void OBD2_Init();
void OBD2_SendPid();
void OBD2_SendValues(int *);
