#ifndef VARIABLES_H_
#define VARIABLES_H_

// =================================================================
// Define global variables
#ifndef EXTERN
#define EXTERN extern
#endif

// Operation defining variables
EXTERN uint8_t doFade;

// For LEDs on upper side ...#(U)...
EXTERN uint8_t whiteU_set, whiteU_now;

EXTERN uint8_t red1Uvalue_set, red1Uvalue_now;
EXTERN uint8_t red2Uvalue_set, red2Uvalue_now;
EXTERN uint8_t red3Uvalue_set, red3Uvalue_now;

EXTERN uint8_t green1Uvalue_set, green1Uvalue_now;
EXTERN uint8_t green2Uvalue_set, green2Uvalue_now;
EXTERN uint8_t green3Uvalue_set, green3Uvalue_now;

EXTERN uint8_t blue1Uvalue_set, blue1Uvalue_now;
EXTERN uint8_t blue2Uvalue_set, blue2Uvalue_now;
EXTERN uint8_t blue3Uvalue_set, blue3Uvalue_now;

// For LEDs on bottom side ...#(B)...
EXTERN uint8_t whiteB_set, whiteB_now;

EXTERN uint8_t red1Bvalue_set, red1Bvalue_now;
EXTERN uint8_t red2Bvalue_set, red2Bvalue_now;
EXTERN uint8_t red3Bvalue_set, red3Bvalue_now;

EXTERN uint8_t green1Bvalue_set, green1Bvalue_now;
EXTERN uint8_t green2Bvalue_set, green2Bvalue_now;
EXTERN uint8_t green3Bvalue_set, green3Bvalue_now;

EXTERN uint8_t blue1Bvalue_set, blue1Bvalue_now;
EXTERN uint8_t blue2Bvalue_set, blue2Bvalue_now;
EXTERN uint8_t blue3Bvalue_set, blue3Bvalue_now;
// =================================================================

#endif /* VARIABLES_H_ */