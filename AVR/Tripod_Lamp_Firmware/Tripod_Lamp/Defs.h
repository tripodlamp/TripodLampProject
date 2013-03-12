#ifndef DEF_F_CPU_H_
#define DEF_F_CPU_H_

#define F_CPU			16000000UL		// AVR clock in Hz

// UART Definitions
#define BAUD			38400UL			// Baud rate in Bits/s -> this slow baud-rate because of the ZigBit module (it's his maximum)
#define RX_QUEUE_SIZE	256				// in Bytes (2 Bytes per Command package)


// Timer 1 definitions
#define T1_INITIAL_VALUE		0xFEC7


// Define output ports
#define WHITE_U_ON		D|=(1<<7);
#define WHITE_B_ON		A|=(1<<0);

#define RED_1U_ON		A|=(1<<2);
#define RED_2U_ON		C|=(1<<5);
#define RED_3U_ON		D|=(1<<6);
#define RED_1B_ON		A|=(1<<4);
#define RED_2B_ON		A|=(1<<7);
#define RED_3B_ON		C|=(1<<2);

#define GREEN_1U_ON		A|=(1<<5);
#define GREEN_2U_ON		C|=(1<<4);
#define GREEN_3U_ON		D|=(1<<5);
#define GREEN_1B_ON		A|=(1<<3);
#define GREEN_2B_ON		C|=(1<<7);
#define GREEN_3B_ON		C|=(1<<1);

#define BLUE_1U_ON		A|=(1<<6);
#define BLUE_2U_ON		C|=(1<<3);
#define BLUE_3U_ON		D|=(1<<4);
#define BLUE_1B_ON		A|=(1<<1);
#define BLUE_2B_ON		C|=(1<<6);
#define BLUE_3B_ON		C|=(1<<0);

// Define switch masks
#define MASK_COMMAND	0xE0
#define MASK_LED_NUMS	0x1F
#define MASK_COLOR		0x07

// Define commands
#define CMD_SET_ONE_LED	0x20
#define CMD_SET_COLOR	0x40
#define CMD_SET_FADE	0x80
#define CMD_SET_DEFAULT 0x60

// Define switch values
#define WHITE_U_SW		0x00
#define WHITE_B_SW		0x01

#define RED_1U_SW		0x02
#define RED_2U_SW		0x03
#define RED_3U_SW		0x04
#define RED_1B_SW		0x05
#define RED_2B_SW		0x06
#define RED_3B_SW		0x07

#define GREEN_1U_SW		0x08
#define GREEN_2U_SW		0x09
#define GREEN_3U_SW		0x0A
#define GREEN_1B_SW		0x0B
#define GREEN_2B_SW		0x0C
#define GREEN_3B_SW		0x0D

#define BLUE_1U_SW		0x0E
#define BLUE_2U_SW		0x0F
#define BLUE_3U_SW		0x10
#define BLUE_1B_SW		0x11
#define BLUE_2B_SW		0x12
#define BLUE_3B_SW		0x13

// Define switch values for colors, up- and bottom side
#define SIDE_CONDITION	0x10
#define SIDE_COND_CARE	0x10
#define SIDE_BIT		0x08
#define SIDE_UP			0x00
#define SIDE_BOTTOM		0x08

#define COLOR_RED_SW	0x01
#define COLOR_GREEN_SW	0x02
#define COLOR_BLUE_SW	0x04

#endif /* DEF_F_CPU_H_ */