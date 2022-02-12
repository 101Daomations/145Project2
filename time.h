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

void incrementTime(struct dateTime *currDT);
void updateTime(struct dateTime *currDT);
void updateDate(struct dateTime *currDT);
void editTime(struct dateTime *currDT);
void editDate(struct dateTime *currDT);

#endif