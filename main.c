#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "time.h"

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
		incrementTime(&defaultTime);
		updateTime(&defaultTime);
		updateDate(&defaultTime);
		avr_wait(1000);
		
		//Checks if edit button is pressed
		if(is_pressed(13) == 1){
			waitKR();
			editTime(&defaultTime);
		}
		if(is_pressed(15) == 1){
			waitKR();
			editDate(&defaultTime);
		}
    }
}

