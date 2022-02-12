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

void increment_dt(struct dateTime *dto);
void pTime(struct dateTime *dto);
void pDate(struct dateTime *dto);
void editTimeMode();
void editDateMode();
#endif