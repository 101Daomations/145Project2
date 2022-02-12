#include "time.h"

void incrementTime(struct dateTime *currDT){
	static int daysForMonths[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	//Clock increments 1 second every cycle
	currDT->sec += 1;

	//If the second passes 60, set it to 0 and increment min
	if(currDT->sec >= 60){
		currDT->sec = 0;
		currDT->min += 1;
	//If the min passes 60, set it to 0 and increment hour
	} if(currDT->min >= 60){
		currDT->min = 0;
		currDT->hour += 1;
	//If the hour passes 24, set it to 0 and increment the day
	} if(currDT->hour >= 24){
		currDT->hour = 0;
		currDT->day += 1;
	//If the month is <= 12 and there arent enough days in the month
	//increment the month
	} if(currDT->month <= 12 && currDT->day > daysForMonths[currDT->month]){
		currDT->day = 1;
		currDT->month += 1;
	//If the month passes 12, increment the year, reset the month and day
	} if(currDT->month > 12){
		currDT->month = 1;
		currDT->day = 1;
		currDT->year += 1;
	}
}


void updateTime(struct dateTime *currDT){
	char strSec[4];
	char strMin[4];
	char strHr[4];
	
	if (currDT->hour < 10){
		sprintf(strHr, "0%d", currDT->hour);
	} else {
		sprintf(strHr, "%d", currDT->hour);
	}
		
	if(currDT->min < 10){
		sprintf(strMin, "0%d", currDT->min);
	} else{
		sprintf(strMin, "%d", currDT->min);
	}
	
	if(currDT->sec < 10){
		sprintf(strSec, "0%d", currDT->sec);
	}else{
		sprintf(strSec, "%d", currDT->sec);
	}
		
	lcd_pos(1, 0);
	lcd_puts2(strHr);
	lcd_pos(1, 2);
	lcd_put(':');
	lcd_pos(1, 3);
	lcd_puts2(strMin);
	lcd_pos(1, 5);
	lcd_put(':');
	lcd_pos(1,6);
	lcd_puts2(strSec);
	
}

void updateDate(struct dateTime *currDT){
	char strDay[4];
	char strMon[4];
	char strYear[6];
	
	if(currDT->day < 10){
		sprintf(strDay, "0%d", currDT->day);
	}else{
		sprintf(strDay, "%d", currDT->day);
	}
	
	if(currDT->month < 10){
		sprintf(strMon, "0%d", currDT->month);
	}else{
		sprintf(strMon, "%d", currDT->month);
	}
	
	if(currDT->year < 10){
		sprintf(strYear, "0%d", currDT->year);
	}else{
		sprintf(strYear, "%d", currDT->year);
	}
	
	lcd_pos(0, 0);
	lcd_puts2(strMon);
	lcd_pos(0, 2);
	lcd_put('/');
	lcd_pos(0, 3);
	lcd_puts2(strDay);
	lcd_pos(0, 5);
	lcd_put('/');
	lcd_pos(0,6);
	lcd_puts2(strYear);
}

void editTime(struct dateTime *currDT){
	int valA, valB;
	//63 is the ascii for a ? to take the position to show the user where they
	//are currently at in the time to input
	int cursor = 63;

	lcd_pos(1,0); 
	lcd_put(cursor);
	valA = waitKP(); 
	lcd_put(mapButton(valA));

	lcd_pos(1,1); 
	lcd_put(cursor);
	valB = waitKP(); 
	lcd_put(mapButton(valB));

	currDT->hour = 10*getButtonAsInt(valA) + getButtonAsInt(valB);
	
	lcd_pos(1,3); 
	lcd_put(cursor);
	valA = waitKP(); 
	lcd_put(mapButton(valA));

	lcd_pos(1,4); 
	lcd_put(cursor);
	valB = waitKP(); 
	lcd_put(mapButton(valB));

	currDT->min = 10*getButtonAsInt(valA) + getButtonAsInt(valB);
	
	lcd_pos(1,6); 
	lcd_put(cursor);
	valA = waitKP(); 
	lcd_put(mapButton(valA));

	lcd_pos(1,7); 
	lcd_put(cursor);
	valB = waitKP(); 
	lcd_put(mapButton(valB));

	currDT->sec = 10*getButtonAsInt(valA) + getButtonAsInt(valB);
}

void editDate(struct dateTime *currDT){
	int valA, valB, valC, valD;
	//63 is the ascii for a ? to take the position to show the user where they
	//are currently at in the date to input
	int cursor = 63;

	lcd_pos(0,0); 
	lcd_put(cursor);
	valA = waitKP(); 
	lcd_put(mapButton(valA));

	lcd_pos(0,1); 
	lcd_put(cursor);
	valB = waitKP(); 
	lcd_put(mapButton(valB));

	currDT->month = 10*getButtonAsInt(valA) + getButtonAsInt(valB);
	
	lcd_pos(0,3); 
	lcd_put(cursor);
	valA = waitKP(); 
	lcd_put(mapButton(valA));

	lcd_pos(0,4); 
	lcd_put(cursor);
	valB = waitKP(); 
	lcd_put(mapButton(valB));

	currDT->day = 10*getButtonAsInt(valA) + getButtonAsInt(valB);
	
	lcd_pos(0,6); 
	lcd_put(cursor);
	valA = waitKP(); 
	lcd_put(mapButton(valA));

	lcd_pos(0,7); 
	lcd_put(cursor);
	valB = waitKP(); 
	lcd_put(mapButton(valB));

	lcd_pos(0,8); 
	lcd_put(cursor);
	valC = waitKP(); 
	lcd_put(mapButton(valC));

	lcd_pos(0,9); 
	lcd_put(cursor);
	valD = waitKP(); 
	lcd_put(mapButton(valD));
	
	currDT->year = 1000*getButtonAsInt(valA) + 100*getButtonAsInt(valB) + 10*getButtonAsInt(valC) + getButtonAsInt(valD);
}

