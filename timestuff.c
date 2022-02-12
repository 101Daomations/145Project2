#include "timestuff.h"

void increment_dt(struct dateTime *dto){
	static int daysForMonths[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	//Clock increments 1 second every cycle
	dto->sec += 1;

	//If the second passes 60, set it to 0 and increment min
	if(dto->sec >= 60){
		dto->sec = 0;
		dto->min += 1;
	//If the min passes 60, set it to 0 and increment hour
	} if(dto->min >= 60){
		dto->min = 0;
		dto->hour += 1;
	//If the hour passes 24, set it to 0 and increment the day
	} if(dto->hour >= 24){
		dto->hour = 0;
		dto->day += 1;
	//If the month is <= 12 and there arent enough days in the month
	//increment the month
	} if(dto->month <= 12 && dto->day > daysForMonths[dto->month]){
		dto->day = 1;
		dto->month += 1;
	//If the month passes 12, increment the year, reset the month and day
	} if(dto->month > 12){
		dto->month = 1;
		dto->day = 1;
		dto->year += 1;
	}
}


void pTime(struct dateTime *dto){
	char strSec[5];
	char strMin[5];
	char strHr[5];
	
	if (dto->hour < 10){
		sprintf(strHr, "0%d", dto->hour);
	} else {
		sprintf(strHr, "%d", dto->hour);
	}
		
	if(dto->min < 10){
		sprintf(strMin, "0%d", dto->min);
	} else{
		sprintf(strMin, "%d", dto->min);
	}
	
	if(dto->sec < 10){
		sprintf(strSec, "0%d", dto->sec);
	}else{
		sprintf(strSec, "%d", dto->sec);
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

void pDate(struct dateTime *dto){
	char strDay[5];
	char strMon[5];
	char strYear[7];
	
	if(dto->day < 10){
		sprintf(strDay, "0%d", dto->day);
	}else{
		sprintf(strDay, "%d", dto->day);
	}
	
	if(dto->month < 10){
		sprintf(strMon, "0%d", dto->month);
	}else{
		sprintf(strMon, "%d", dto->month);
	}
	
	if(dto->year < 10){
		sprintf(strYear, "0%d", dto->year);
	}else{
		sprintf(strYear, "%d", dto->year);
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

void editTimeMode(struct dateTime *mydt){
	int t0, t1;
	//63 is the ascii for a ? to take the position to show the user where they
	//are currently at in the time to input
	int cursor = 63;

	lcd_pos(1,0); 
	lcd_put(cursor);
	t0 = waitPAR(); 
	lcd_pos(1,0); 
	lcd_put(mapButton(t0));

	lcd_pos(1,1); 
	lcd_put(cursor);
	t1 = waitPAR(); 
	lcd_pos(1,1); 
	lcd_put(mapButton(t1));

	mydt->hour = 10*getButtonAsInt(t0) + getButtonAsInt(t1);
	
	lcd_pos(1,3); 
	lcd_put(cursor);
	t0 = waitPAR(); 
	lcd_pos(1,3); 
	lcd_put(mapButton(t0));

	lcd_pos(1,4); 
	lcd_put(cursor);
	t1 = waitPAR(); 
	lcd_pos(1,4); 
	lcd_put(mapButton(t1));
	
	mydt->min = 10*getButtonAsInt(t0) + getButtonAsInt(t1);
	
	lcd_pos(1,6); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(1,6); lcd_put(mapButton(t0));
	lcd_pos(1,7); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(1,7); lcd_put(mapButton(t1));
	mydt->sec = 10*getButtonAsInt(t0) + getButtonAsInt(t1);
}

void editDateMode(struct dateTime *mydt){
	int t0, t1, t2, t3;
	//63 is the ascii for a ? to take the position to show the user where they
	//are currently at in the date to input
	int cursor = 63;

	lcd_pos(0,0); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(0,0); lcd_put(mapButton(t0));
	lcd_pos(0,1); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(0,1); lcd_put(mapButton(t1));
	mydt->month = 10*getButtonAsInt(t0) + getButtonAsInt(t1);
	
	lcd_pos(0,3); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(0,3); lcd_put(mapButton(t0));
	lcd_pos(0,4); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(0,4); lcd_put(mapButton(t1));
	mydt->day = 10*getButtonAsInt(t0) + getButtonAsInt(t1);
	
	lcd_pos(0,6); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(0,6); lcd_put(mapButton(t0));
	lcd_pos(0,7); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(0,7); lcd_put(mapButton(t1));
	lcd_pos(0,8); lcd_put(cursor);
	t2 = waitPAR(); lcd_pos(0,8); lcd_put(mapButton(t2));
	lcd_pos(0,9); lcd_put(cursor);
	t3 = waitPAR(); lcd_pos(0,9); lcd_put(mapButton(t3));
	
	mydt->year = 1000*getButtonAsInt(t0) + 100*getButtonAsInt(t1) +
	10*getButtonAsInt(t2) + getButtonAsInt(t3);
}