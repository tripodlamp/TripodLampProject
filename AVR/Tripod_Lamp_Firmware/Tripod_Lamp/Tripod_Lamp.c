#include "Tripod_Lamp.h"

int main(void)
{
    uint8_t switchValue = 0x00;
	uint8_t pwmValue, sideCondition, side;
	
	InitAll();
		
	while(1)
    {
		if(uartDataAvail()>=2)	// Data package available (1 data package contains two Bytes)
		{
			switchValue = uartGetByte();
			switch(switchValue & MASK_COMMAND)
			{
				case CMD_SET_ONE_LED:	// set one LED new Value
					pwmValue = uartGetByte();
					switch(switchValue & MASK_LED_NUMS)
					{
						case WHITE_U_SW: whiteU_set = pwmValue; break;
						case WHITE_B_SW: whiteB_set = pwmValue; break;
						
						case RED_1U_SW: red1Uvalue_set = pwmValue; break;
						case RED_2U_SW: red2Uvalue_set = pwmValue; break;
						case RED_3U_SW: red3Uvalue_set = pwmValue; break;
						case RED_1B_SW: red1Bvalue_set = pwmValue; break;
						case RED_2B_SW: red2Bvalue_set = pwmValue; break;
						case RED_3B_SW: red3Bvalue_set = pwmValue; break;
						
						case GREEN_1U_SW: green1Uvalue_set = pwmValue; break;
						case GREEN_2U_SW: green2Uvalue_set = pwmValue; break;
						case GREEN_3U_SW: green3Uvalue_set = pwmValue; break;
						case GREEN_1B_SW: green1Bvalue_set = pwmValue; break;
						case GREEN_2B_SW: green2Bvalue_set = pwmValue; break;
						case GREEN_3B_SW: green3Bvalue_set = pwmValue; break;
						
						case BLUE_1U_SW: blue1Uvalue_set = pwmValue; break;
						case BLUE_2U_SW: blue2Uvalue_set = pwmValue; break;
						case BLUE_3U_SW: blue3Uvalue_set = pwmValue; break;
						case BLUE_1B_SW: blue1Bvalue_set = pwmValue; break;
						case BLUE_2B_SW: blue2Bvalue_set = pwmValue; break;
						case BLUE_3B_SW: blue3Bvalue_set = pwmValue; break;
						
						default: break;
					}
					break;
				case CMD_SET_COLOR:	// set one Color to PWM value
					pwmValue	  = uartGetByte();
					sideCondition = switchValue & SIDE_CONDITION;
					side		  = switchValue & SIDE_BIT;
					switch(switchValue & MASK_COLOR)
					{
						case COLOR_RED_SW:
							if(sideCondition!=SIDE_COND_CARE || side==SIDE_UP) {
								red1Uvalue_set = pwmValue; red2Uvalue_set = pwmValue; red3Uvalue_set = pwmValue;
							}
							if(sideCondition!=SIDE_COND_CARE || side==SIDE_BOTTOM) {
								red1Bvalue_set = pwmValue; red2Bvalue_set = pwmValue; red3Bvalue_set = pwmValue;
							}
							break;
						case COLOR_GREEN_SW:
							if(sideCondition!=SIDE_COND_CARE || side==SIDE_UP) {
								green1Uvalue_set = pwmValue; green2Uvalue_set = pwmValue; green3Uvalue_set = pwmValue;
							}
							if(sideCondition!=SIDE_COND_CARE || side==SIDE_BOTTOM) {
								green1Bvalue_set = pwmValue; green2Bvalue_set = pwmValue; green3Bvalue_set = pwmValue;
							}
							break;
						case COLOR_BLUE_SW:
							if(sideCondition!=SIDE_COND_CARE || side==SIDE_UP) {
								blue1Uvalue_set = pwmValue; blue2Uvalue_set = pwmValue; blue3Uvalue_set = pwmValue;
							}
							if(sideCondition!=SIDE_COND_CARE || side==SIDE_BOTTOM) {
								blue1Bvalue_set = pwmValue; blue2Bvalue_set = pwmValue; blue3Bvalue_set = pwmValue;
							}
							break;
					}
					break;
				case CMD_SET_FADE:
					doFade = uartGetByte();
					break;
				case CMD_SET_DEFAULT:
					uartGetByte();
					eeprom_write_byte(&eeWhiteU , whiteU_now	  ); eeprom_write_byte(&eeWhiteB , whiteB_now	   );
					eeprom_write_byte(&eeRed1U  , red1Uvalue_now  ); eeprom_write_byte(&eeRed2U  , red2Uvalue_now  ); eeprom_write_byte(&eeRed3U  , red3Uvalue_now  );
					eeprom_write_byte(&eeRed1B  , red1Bvalue_now  ); eeprom_write_byte(&eeRed2B  , red2Bvalue_now  ); eeprom_write_byte(&eeRed3B  , red3Bvalue_now  );
					eeprom_write_byte(&eeGreen1U, green1Uvalue_now); eeprom_write_byte(&eeGreen2U, green2Uvalue_now); eeprom_write_byte(&eeGreen3U, green3Uvalue_now);
					eeprom_write_byte(&eeGreen1B, green1Bvalue_now); eeprom_write_byte(&eeGreen2B, green2Bvalue_now); eeprom_write_byte(&eeGreen3B, green3Bvalue_now);
					eeprom_write_byte(&eeBlue1U , blue1Uvalue_now ); eeprom_write_byte(&eeBlue2U , blue2Uvalue_now ); eeprom_write_byte(&eeBlue3U , blue3Uvalue_now );
					eeprom_write_byte(&eeBlue1B , blue1Bvalue_now ); eeprom_write_byte(&eeBlue2B , blue2Bvalue_now ); eeprom_write_byte(&eeBlue3B , blue3Bvalue_now );
					break;
				default:   uartGetByte();
					break;
			}
		}		   
    }
}

void InitAll()
{
	ioPinsInit  ();
	variableInit();
	uartInit    ();
	timer1Init  ();
	sei();
}

void ioPinsInit()
{
	// set Pins of uC to In- or Output direction
	// and set initial value
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xF0;
	
	PORTA = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
}

void variableInit()
{
	doFade = 0x00;
	
	whiteU_now = 0x00; whiteB_now = 0x00; whiteB_set = eeprom_read_byte(&eeWhiteB); whiteU_set = eeprom_read_byte(&eeWhiteU);
	
	red1Bvalue_now = 0x00; red1Uvalue_now = 0x00; red1Bvalue_set = eeprom_read_byte(&eeRed1B); red1Uvalue_set = eeprom_read_byte(&eeRed1U);
	red2Bvalue_now = 0x00; red2Uvalue_now = 0x00; red2Bvalue_set = eeprom_read_byte(&eeRed2B); red2Uvalue_set = eeprom_read_byte(&eeRed2U);
	red3Bvalue_now = 0x00; red3Uvalue_now = 0x00; red3Bvalue_set = eeprom_read_byte(&eeRed3B); red3Uvalue_set = eeprom_read_byte(&eeRed3U);
	
	green1Bvalue_now = 0x00; green1Uvalue_now = 0x00; green1Bvalue_set = eeprom_read_byte(&eeGreen1B); green1Uvalue_set = eeprom_read_byte(&eeGreen1U);
	green2Bvalue_now = 0x00; green2Uvalue_now = 0x00; green2Bvalue_set = eeprom_read_byte(&eeGreen2B); green2Uvalue_set = eeprom_read_byte(&eeGreen2U);
	green3Bvalue_now = 0x00; green3Uvalue_now = 0x00; green3Bvalue_set = eeprom_read_byte(&eeGreen3B); green3Uvalue_set = eeprom_read_byte(&eeGreen3U);
	
	blue1Bvalue_now = 0x00; blue1Uvalue_now = 0x00; blue1Bvalue_set = eeprom_read_byte(&eeBlue1B); blue1Uvalue_set = eeprom_read_byte(&eeBlue1U);
	blue2Bvalue_now = 0x00; blue2Uvalue_now = 0x00; blue2Bvalue_set = eeprom_read_byte(&eeBlue2B); blue2Uvalue_set = eeprom_read_byte(&eeBlue2U);
	blue3Bvalue_now = 0x00; blue3Uvalue_now = 0x00; blue3Bvalue_set = eeprom_read_byte(&eeBlue3B); blue3Uvalue_set = eeprom_read_byte(&eeBlue3U);
}