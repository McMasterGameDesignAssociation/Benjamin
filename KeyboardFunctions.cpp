/*

This file will contain all of the information needed for the keyboard state machine

*/

#ifndef _KEYBOARD_MACHINE
#define _KEYBOARD_MACHINE


/****

0 - W
1 - S
2 - A
3 - D
4 - Action/E
5 - Inventory/Q
6 - Run/Walk/Shift
7 - MainMenu/ESC

***/
bool key[8];
bool pressed = false;

void keyboard(unsigned char keyStroke, int x, int y)
{
	if(keyStroke == 'w') key[0] = true;
	else if(keyStroke == 's') key[1] = true;
	else if(keyStroke == 'a') key[2] = true;
	else if(keyStroke == 'd') key[3] = true;
	else if(keyStroke == 'e') key[4] = true;
	else if(keyStroke == 'q') key[5] = true;
	pressed = true;
}

void resetKeyBoard(void) {for(int i = 0; i < 8; i++) key[i] = false;}

void keyboardMachine(void)
{
	//W and A
	if(key[0] && key[2] && pressed)
	{
		if(key[6]);
		else;
	}
	//W and D
	else if(key[0] && key[3] && pressed)
	{
		if(key[6]);
		else;
	}
	//S and A
	else if(key[1] && key[2] && pressed)
	{
		if(key[6]);
		else;
	}
	//S and D
	else if(key[1] && key[3] && pressed)
	{
		if(key[6]);
		else;
	}
	//W
	else if(key[0] && pressed)
	{
		if(key[6]);
		else;
	}
	//S
	else if(key[1] && pressed)
	{
		if(key[6]);
		else;
	}
	//A
	else if(key[2] && pressed)
	{
		if(key[6]);
		else;
	}
	//D
	else if(key[3] && pressed)
	{
		if(key[6]);
		else;
	}
	//Action or E key
	else if(key[4] && pressed);
	//Menu or Q key
	else if(key[7] && pressed);
	pressed = false;

}

#endif