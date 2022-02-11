#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "timestuff.h"

int cursor = 63; //ASCII val for edit mode cursor

int main(void)
{
	DDRA = 0xF; //Set cols as input, rows as output
	PORTA = 0; //Disable col pullups, set rows to LOW
	lcd_init();
	
	struct dateTime * mydt = {0,0,0,1,1,2020};//Default values
	
    while (1) 
    {
		//Update Time
		lcd_clr();
		pTime(&mydt);
		pDate(&mydt);
		increment_dt(&mydt);
		avr_wait(1000);
		
		//Checks if edit button is pressed
		if(pressed(4) == 1){ //Checks if * pressed
			waitKeyRelease(4);
			editTimeMode(&mydt);
		}
		if(pressed(2) == 1){//Checks if # pressed
			waitKeyRelease(2);
			editDateMode(&mydt);
		}
    }
}

