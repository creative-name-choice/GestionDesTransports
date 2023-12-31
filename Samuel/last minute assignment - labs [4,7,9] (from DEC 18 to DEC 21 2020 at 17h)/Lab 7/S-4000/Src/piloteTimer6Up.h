#ifndef PILOTETIMER6UP_H
#define PILOTETIMER6UP_H
#include "main.h"

// MODULE: piloteTimer6Up
// DESCRIPTION: pour permettre des interruptions périodiques par Timer6

// Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define PILOTETIMER6UP_COMPTE_MAX  (\
//  (unsigned int)((FREQUENCE_D_OSCILLATEUR_EN_KHZ \
//  /FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ * 1000.0)-1.0)

void piloteTimer6Up_initialise(void);
void piloteTimer6Up_permetLesInterruptions(void);

extern void (*piloteTimer6Up_execute)(void);

#endif
