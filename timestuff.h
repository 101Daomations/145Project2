#ifndef _DT_H_
#define _DT_H_
#include "lcd.h"
#include "avr.h"
#include "keypad.h"
#include <stdio.h>

struct dateTime{
	int sec;
	int min;
	int hour;
	int day;
	int month;
	int year;
};

extern int cursor;

void increment_dt(struct dateTime *dto); //increments date/time by 1 second
void pTime(struct dateTime *dto); //print time to lcd
void pDate(struct dateTime *dto); //print date to lcd
void editTimeMode(struct dateTime *mydt); //enter mode to edit time
void editDateMode(struct dateTime *mydt); //enter mode to edit date
#endif