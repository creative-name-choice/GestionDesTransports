// Change me!

#include "../Inc/main.h"
#include <interfaceCAN.h>
#include <processusCAN.h>
#include <serviceBaseDeTemps.h>
#include <serviceCAN.h>

#define INFORMATION_DISPONIBLE              1
#define INFORMATION_TRAITEE                 0
#define REQUETE_ACTIVE                      1
#define REQUETE_TRAITEE                     0
#define MODULE_EN_FONCTION                  1
#define MODULE_PAS_EN_FONCTION              0

#define INFO_TRAITE INFORMATION_TRAITEE
#define REQUETE_TRAITE REQUETE_TRAITEE
#define PHASE_RX_CAN
#define PHASE_TX_CAN

void processusRX_CAN(void);
void processusTX_CAN(void);

struct SPCAN processusCAN;
unsigned char dataIN[8];

void processusRX_CAN(void) {
    static int counterRX = 0;

    counterRX++;
    processusCAN.information == CAN_RX();
    //if (processusCAN.information == INFO_DISPO)
    if (processusCAN.information == 1)
        return;
    if (counterRX < 2000)
        return;
    counterRX = 0;

    if (CAN_RX() == 1) {
        if (CAN_Read(dataIN, &processusCAN.CallerIDIn) == 1) {
            switch (processusCAN.CallerIDIn) {
                case ADDRESS_1:
                    CAN_buffer.byte[0] = dataIN[0];
                    CAN_buffer.byte[1] = dataIN[1];
                    CAN_buffer.byte[2] = dataIN[2];
                    CAN_buffer.byte[3] = dataIN[3];
                    break;
                case ADDRESS_2:
                    CAN_buffer.byte[0] = dataIN[0];
                    CAN_buffer.byte[1] = dataIN[1];
                    CAN_buffer.byte[2] = dataIN[2];
                    CAN_buffer.byte[3] = dataIN[3];
                    break;
            }
        }
    }
    //processusCAN.information = INFO_DISPO;
}

void processusTX_CAN(void) {
    static int counterTX = 0;
    unsigned char a = 0;

    counterTX++;
    if (processusCAN.requete == REQUETE_TRAITE)
        return;
    if (counterTX < 20000)
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
