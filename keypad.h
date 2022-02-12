#ifndef _KEYPAD_H_
#define _KEYPAD_H_
#include "avr.h"

int get_key();

int is_pressed(int r, int c);

void waitKR(); 

int waitKP(); 

char mapButton(int k); 

int getButtonAsInt(int k); 

#endif