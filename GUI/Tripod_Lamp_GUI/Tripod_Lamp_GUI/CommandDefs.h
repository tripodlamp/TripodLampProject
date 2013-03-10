#ifndef COMMANDDEFS_H
#define COMMANDDEFS_H

#define MAX_LED_VALUE	0xFF

// Define commands
#define CMD_SET_ONE_LED	0x20
#define CMD_SET_COLOR	0x40
#define CMD_SET_FADE	0x80
#define CMD_SET_DEFAULT	0x60

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
#define SIDE_BOTH		0x04

#define COLOR_RED_SW	0x01
#define COLOR_GREEN_SW	0x02
#define COLOR_BLUE_SW	0x04
#define COLOR_WHITE_SW	0x08


// TCP Server defines
#define SERVER_PORT		5000

#define TCP_COLOR_RED		0
#define TCP_COLOR_GREEN		1
#define TCP_COLOR_BLUE		2
#define TCP_COLOR_WHITE		3
	
#define TCP_BRANCH_ALL		0
#define TCP_BRANCH_1		1
#define TCP_BRANCH_2		2
#define TCP_BRANCH_3		3
	
#define TCP_SIDE_BOTH		0
#define TCP_SIDE_TOP		1
#define TCP_SIDE_BOTTOM		2
	
#define TCP_VALUE_MAX		0
#define TCP_VALUE_P10		1
#define TCP_VALUE_P1		2
#define TCP_VALUE_M1		3
#define TCP_VALUE_M10		4
#define TCP_VALUE_OFF		5
	
#define TCP_COMMAND_END		"#"

//typedef pair<char,char> uartCommand
#define UART_CMD_BUFFER_SIZE	20

#endif // COMMANDDEFS_H