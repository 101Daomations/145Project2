#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "timestuff.h"

int main(void)
{
	DDRA = 0xF; //Set cols as input, rows as output
	PORTA = 0; //Disable col pullups, set rows to LOW
	lcd_init();
	
	struct dateTime defaultTime = {0,0,0,1,1,2022};
	
    while (1) 
    {
		//Update Time
		lcd_clr();
		pTime(&defaultTime);
		pDate(&defaultTime);
		increment_dt(&defaultTime);
		avr_wait(1000);
		
		//Checks if edit button is pressed
		if(pressed(4) == 1){
			waitKeyRelease(4);
			editTimeMode(&defaultTime);
		}
		if(pressed(2) == 1){
			waitKeyRelease(2);
			editDateMode(&defaultTime);
		}
    }
}

