// Change me!

#include "main.h"
#include "serviceCAN.h"
#include "serviceBaseDeTemps.h"
#include "interfaceCAN.h"
#include "processusCAN.h"

void processusRX_CAN(void);
void processusTX_CAN(void);

struct SPCAN processusCAN;
unsigned char dataIN[8];

void processusRX_CAN(void) {
  static int counterRX = 0;
  counterRX++;
  if (processusCAN.information == INFO_DISPO)
      return;
  if(counterRX < 2000)
      return;
  counterRX = 0;

  if (CAN_RX() == 1) {
    if (CAN_Read(dataIN, &processusCAN.CallerIDIn) == 1) {
      switch (processusCAN.CallerIDIn) {
        case ADRS_COM:
          BufferCAN.commande.all = dataIN[0];
          break;
        case ADRS_TRI:
          BufferCAN.tri.all = dataIN[0];
          BufferCAN.FE_tri.all = dataIN[1];
          break;
      }
    }
  }
  processusCAN.information = INFO_DISPO;
}

void processusTX_CAN(void) {
  static int counterTX = 0;
  unsigned char a = 0;

  counterTX++;
  if (processusCAN.requete == REQUETE_TRAITE)
      return;
  if(counterTX < 20000)
      return;
  counterTX = 0;
  a = ~a;
  HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, (GPIO_PinState)(a>>7));
  CAN_Send(processusCAN.CallerIDOut, &processusCAN.dataOUT[0], 3);
  processusCAN.requete = REQUETE_TRAITE;
}

void Init_processusCAN(void) {
  processusCAN.information = INFO_TRAITE;
  processusCAN.requete = REQUETE_TRAITE;
  serviceBaseDeTemps_execute[PHASE_RX_CAN] = processusRX_CAN;
  serviceBaseDeTemps_execute[PHASE_TX_CAN] = processusTX_CAN;
}