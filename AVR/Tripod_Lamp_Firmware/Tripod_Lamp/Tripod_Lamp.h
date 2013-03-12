#ifndef TRIPOD_LAMP_V2_H_
#define TRIPOD_LAMP_V2_H_


#include "Defs.h"
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>

#define EXTERN
#include "Variables.h"
#include "Functions/UART.h"
#include "Functions/Timer1.h"

void InitAll();
void ioPinsInit();
void variableInit();

uint8_t eeWhiteU EEMEM = 0x7F;
uint8_t eeWhiteB EEMEM = 0x7F;

uint8_t eeRed1U EEMEM = 0x7F; uint8_t eeRed2U EEMEM = 0x7F; uint8_t eeRed3U EEMEM = 0x7F;
uint8_t eeRed1B EEMEM = 0x7F; uint8_t eeRed2B EEMEM = 0x7F; uint8_t eeRed3B EEMEM = 0x7F;

uint8_t eeGreen1U EEMEM = 0x7F; uint8_t eeGreen2U EEMEM = 0x7F; uint8_t eeGreen3U EEMEM = 0x7F;
uint8_t eeGreen1B EEMEM = 0x7F; uint8_t eeGreen2B EEMEM = 0x7F; uint8_t eeGreen3B EEMEM = 0x7F;

uint8_t eeBlue1U EEMEM = 0x00; uint8_t eeBlue2U EEMEM = 0x00; uint8_t eeBlue3U EEMEM = 0x00;
uint8_t eeBlue1B EEMEM = 0x00; uint8_t eeBlue2B EEMEM = 0x00; uint8_t eeBlue3B EEMEM = 0x00;

#endif /* TRIPOD_LAMP_V2_H_ */