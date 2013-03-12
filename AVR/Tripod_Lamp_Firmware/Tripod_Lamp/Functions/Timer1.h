#ifndef TIMER1_H_
#define TIMER1_H_

#include "../Defs.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/twi.h> 
#include <util/delay.h>

#include "../Variables.h"

void timer1Init();

#endif /* TIMER1_H_ */