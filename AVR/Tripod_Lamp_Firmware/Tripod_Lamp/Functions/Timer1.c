#include "Timer1.h"

uint8_t pwmCycle  = 0x00;

void timer1Init()
{
	TCNT1  = T1_INITIAL_VALUE; 							// Set Timer 1 count value to T1_INITIAL_VALUE (defined in 'Defs.h')
	TIMSK |= (1 << TOIE1);								// Activate overflow interrupt
	TCCR1B|= (0 << CS12 ) | (0 << CS11 ) | (1 << CS10);	// Activate Timer 1 (Prescaler = 1)
}

ISR(TIMER1_OVF_vect)
{
	uint8_t A = 0x00;
	uint8_t C = 0x00;
	uint8_t D = 0x00;
	
	// PWMs here
	if(pwmCycle<whiteU_now) { WHITE_U_ON }
	if(pwmCycle<whiteB_now) { WHITE_B_ON }
	
	if(pwmCycle<red1Uvalue_now) { RED_1U_ON }
	if(pwmCycle<red2Uvalue_now) { RED_2U_ON }
	if(pwmCycle<red3Uvalue_now) { RED_3U_ON }
	if(pwmCycle<red1Bvalue_now) { RED_1B_ON }
	if(pwmCycle<red2Bvalue_now) { RED_2B_ON }
	if(pwmCycle<red3Bvalue_now) { RED_3B_ON }
	
	if(pwmCycle<green1Uvalue_now) { GREEN_1U_ON }
	if(pwmCycle<green2Uvalue_now) { GREEN_2U_ON }
	if(pwmCycle<green3Uvalue_now) { GREEN_3U_ON }
	if(pwmCycle<green1Bvalue_now) { GREEN_1B_ON }
	if(pwmCycle<green2Bvalue_now) { GREEN_2B_ON }
	if(pwmCycle<green3Bvalue_now) { GREEN_3B_ON }
		
	if(pwmCycle<blue1Uvalue_now) { BLUE_1U_ON }
	if(pwmCycle<blue2Uvalue_now) { BLUE_2U_ON }
	if(pwmCycle<blue3Uvalue_now) { BLUE_3U_ON }
	if(pwmCycle<blue1Bvalue_now) { BLUE_1B_ON }
	if(pwmCycle<blue2Bvalue_now) { BLUE_2B_ON }
	if(pwmCycle<blue3Bvalue_now) { BLUE_3B_ON }
		
	if(doFade>0x00)
	{
		// Fades here
		if(pwmCycle==0xFF)
		{
			if(whiteU_now!=whiteU_set) { if(whiteU_now<whiteU_set) { whiteU_now++; } else { whiteU_now--; } }
			if(whiteB_now!=whiteB_set) { if(whiteB_now<whiteB_set) { whiteB_now++; } else { whiteB_now--; } }
	
			if(red1Uvalue_now!=red1Uvalue_set) { if(red1Uvalue_now<red1Uvalue_set) { red1Uvalue_now++; } else { red1Uvalue_now--; } }
			if(red2Uvalue_now!=red2Uvalue_set) { if(red2Uvalue_now<red2Uvalue_set) { red2Uvalue_now++; } else { red2Uvalue_now--; } }
			if(red3Uvalue_now!=red3Uvalue_set) { if(red3Uvalue_now<red3Uvalue_set) { red3Uvalue_now++; } else { red3Uvalue_now--; } }
			if(red1Bvalue_now!=red1Bvalue_set) { if(red1Bvalue_now<red1Bvalue_set) { red1Bvalue_now++; } else { red1Bvalue_now--; } }
			if(red2Bvalue_now!=red2Bvalue_set) { if(red2Bvalue_now<red2Bvalue_set) { red2Bvalue_now++; } else { red2Bvalue_now--; } }
			if(red3Bvalue_now!=red3Bvalue_set) { if(red3Bvalue_now<red3Bvalue_set) { red3Bvalue_now++; } else { red3Bvalue_now--; } }
		
			if(green1Uvalue_now!=green1Uvalue_set) { if(green1Uvalue_now<green1Uvalue_set) { green1Uvalue_now++; } else { green1Uvalue_now--; } }
			if(green2Uvalue_now!=green2Uvalue_set) { if(green2Uvalue_now<green2Uvalue_set) { green2Uvalue_now++; } else { green2Uvalue_now--; } }
			if(green3Uvalue_now!=green3Uvalue_set) { if(green3Uvalue_now<green3Uvalue_set) { green3Uvalue_now++; } else { green3Uvalue_now--; } }
			if(green1Bvalue_now!=green1Bvalue_set) { if(green1Bvalue_now<green1Bvalue_set) { green1Bvalue_now++; } else { green1Bvalue_now--; } }
			if(green2Bvalue_now!=green2Bvalue_set) { if(green2Bvalue_now<green2Bvalue_set) { green2Bvalue_now++; } else { green2Bvalue_now--; } }
			if(green3Bvalue_now!=green3Bvalue_set) { if(green3Bvalue_now<green3Bvalue_set) { green3Bvalue_now++; } else { green3Bvalue_now--; } }
		
			if(blue1Uvalue_now!=blue1Uvalue_set) { if(blue1Uvalue_now<blue1Uvalue_set) { blue1Uvalue_now++; } else { blue1Uvalue_now--; } }
			if(blue2Uvalue_now!=blue2Uvalue_set) { if(blue2Uvalue_now<blue2Uvalue_set) { blue2Uvalue_now++; } else { blue2Uvalue_now--; } }
			if(blue3Uvalue_now!=blue3Uvalue_set) { if(blue3Uvalue_now<blue3Uvalue_set) { blue3Uvalue_now++; } else { blue3Uvalue_now--; } }
			if(blue1Bvalue_now!=blue1Bvalue_set) { if(blue1Bvalue_now<blue1Bvalue_set) { blue1Bvalue_now++; } else { blue1Bvalue_now--; } }
			if(blue2Bvalue_now!=blue2Bvalue_set) { if(blue2Bvalue_now<blue2Bvalue_set) { blue2Bvalue_now++; } else { blue2Bvalue_now--; } }
			if(blue3Bvalue_now!=blue3Bvalue_set) { if(blue3Bvalue_now<blue3Bvalue_set) { blue3Bvalue_now++; } else { blue3Bvalue_now--; } }
		}
	}	
	else
	{
		// Colors jump
		whiteU_now = whiteU_set;
		whiteB_now = whiteB_set;
		
		red1Uvalue_now = red1Uvalue_set; red2Uvalue_now = red2Uvalue_set; red3Uvalue_now = red3Uvalue_set;
		red1Bvalue_now = red1Bvalue_set; red2Bvalue_now = red2Bvalue_set; red3Bvalue_now = red3Bvalue_set;
		
		green1Uvalue_now = green1Uvalue_set; green2Uvalue_now = green2Uvalue_set; green3Uvalue_now = green3Uvalue_set;
		green1Bvalue_now = green1Bvalue_set; green2Bvalue_now = green2Bvalue_set; green3Bvalue_now = green3Bvalue_set; 		
		
		blue1Uvalue_now = blue1Uvalue_set; blue2Uvalue_now = blue2Uvalue_set; blue3Uvalue_now = blue3Uvalue_set; 
		blue1Bvalue_now = blue1Bvalue_set; blue2Bvalue_now = blue2Bvalue_set; blue3Bvalue_now = blue3Bvalue_set;
	}
	
	// Set output ports
	PORTA = A;
	PORTC = C;	
	PORTD = D;
	
	// Reset timer value
	TCNT1 = T1_INITIAL_VALUE;	
	
	// Increase PWM Cycle state (Inc 0xFF will result in 0x00)
	pwmCycle++;
}