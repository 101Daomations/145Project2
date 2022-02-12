#include "lcd.h"
#include "avr.h"
#include "keypad.h"


char mapButton(int k){
	static char charmap[17] = {'0',
		'D', '#', '0', '*',
		'C', '9', '8', '7',
		'B', '6', '5', '4',
	    'A', '3', '2', '1'};
	return charmap[k];
}

int getButtonAsInt(int k) {
	if (mapButton(k) != 'A' && mapButton(k) != 'B' && mapButton(k) != 'C' && mapButton(k) != 'D'
	    && mapButton(k) != '#' && mapButton(k) != '*') {
			int num = mapButton(k) - '0';
			return num
		}
	return 0
}

int get_key(){
    int i,j;
    for (i = 0; i < 4; ++i){ 
        for (j = 0; j < 4; ++j){ 
            if (is_pressed(i,j)){
                return i*4+j+1;
            }
        }
    }
    return 0;
}


int is_pressed(int r, int c){ 
    DDRA = 0; 
    PORTA = 0;
    
    SET_BIT(DDRA, r);
    CLR_BIT(PORTA, r);
    
    CLR_BIT(DDRA, c+4); 
    SET_BIT(PORTA, c+4); 
    avr_wait(50);
    
    if (!GET_BIT(PINA, c+4)){ 
        return 1;
    }
    return 0;
}


void waitKR(){
	while(!get_key()){;}
}

int waitKP(){
	int key = get_key();
	waitKR();
	return key;
}