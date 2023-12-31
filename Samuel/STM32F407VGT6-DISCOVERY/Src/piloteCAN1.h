#ifndef PILOTECAN1_H
  #define PILOTECAN1_H
  // DESCRIPTION: pour utiliser le CAN1.
  // Copiez et adaptez ce qui suit dans "main.h".
  // #define PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION  0x245
  // #define PILOTECAN1_IDENTIFICATION_EN_RECEPTION  0x247
  // #define PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION  0x244
  
  #define PILOTECAN1_DISPONIBLE  1
  #define PILOTECAN1_PAS_DISPONIBLE 0
  #define PILOTECAN1_TRANSMIS 0
  #define PILOTECAN1_PAS_TRANSMIS 1
  #define PILOTECAN1_ERREUR 1
  #define PILOTECAN1_PAS_D_ERREUR 0
  
  unsigned int piloteCAN1_messageDisponible(void);
  unsigned int piloteCAN1_messageTransmis(void);
  unsigned char piloteCAN1_litUnMessageRecu(unsigned char *);
  unsigned int piloteCAN1_transmetDesDonnes(unsigned int, unsigned char *, unsigned char);
  unsigned int piloteCAN1_initialise(void);
#endif
