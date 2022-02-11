#include "timestuff.h"

void increment_dt(struct dateTime *dt){
	static int daysForMonths[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	//Clock increments 1 second every cycle
	dt->sec += 1;

	//If the second passes 60, set it to 0 and increment min
	if(dt->sec >= 60){
		dt->sec = 0;
		dt->min ++;
	//If the min passes 60, set it to 0 and increment hour
	} if(dt->min > 60){
		dt->min = 0;
		dt->hour ++;
	//If the hour passes 24, set it to 0 and increment the day
	} if(dt->hour > 24){
		dt->hour = 0;
		dt->day ++;
	//If the month is <= 12 and there arent enough days in the month
	//increment the month
	} if(dt->month <= 12 && dt->day > daysForMonths[dt->month]){
		dt->day = 1;
		dt->month ++;
	//If the month passes 12, increment the year, reset the month and day
	} if(dt->month > 12){
		dt->month = 1;
		dt->day = 1;
		dt->year ++;
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
		
	if(dto->min < 10){sprintf(strMin, "0%d", dto->min);}
	else{sprintf(strMin, "%d", dto->min);}
	
	if(dto->sec < 10){sprintf(strSec, "0%d", dto->sec);}
	else{sprintf(strSec, "%d", dto->sec);}
		
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
	
	if(dto->day < 10){sprintf(strDay, "0%d", dto->day);}
	else{sprintf(strDay, "%d", dto->day);}
	
	if(dto->month < 10){sprintf(strMon, "0%d", dto->month);}
	else{sprintf(strMon, "%d", dto->month);}
	
	if(dto->year < 10){sprintf(strYear, "0%d", dto->year);}
	else{sprintf(strYear, "%d", dto->year);}
	
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
	mydt->hour = 10*mapIntVal(t0) + mapIntVal(t1);
	
	lcd_pos(1,3); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(1,3); lcd_put(mapButton(t0));
	lcd_pos(1,4); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(1,4); lcd_put(mapButton(t1));
	mydt->min = 10*mapIntVal(t0) + mapIntVal(t1);
	
	lcd_pos(1,6); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(1,6); lcd_put(mapButton(t0));
	lcd_pos(1,7); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(1,7); lcd_put(mapButton(t1));
	mydt->sec = 10*mapIntVal(t0) + mapIntVal(t1);
}

void editDateMode(struct dateTime *mydt){
	int t0, t1, t2, t3;
	lcd_pos(0,0); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(0,0); lcd_put(mapButton(t0));
	lcd_pos(0,1); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(0,1); lcd_put(mapButton(t1));
	mydt->month = 10*mapIntVal(t0) + mapIntVal(t1);
	
	lcd_pos(0,3); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(0,3); lcd_put(mapButton(t0));
	lcd_pos(0,4); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(0,4); lcd_put(mapButton(t1));
	mydt->day = 10*mapIntVal(t0) + mapIntVal(t1);
	
	lcd_pos(0,6); lcd_put(cursor);
	t0 = waitPAR(); lcd_pos(0,6); lcd_put(mapButton(t0));
	lcd_pos(0,7); lcd_put(cursor);
	t1 = waitPAR(); lcd_pos(0,7); lcd_put(mapButton(t1));
	lcd_pos(0,8); lcd_put(cursor);
	t2 = waitPAR(); lcd_pos(0,8); lcd_put(mapButton(t2));
	lcd_pos(0,9); lcd_put(cursor);
	t3 = waitPAR(); lcd_pos(0,9); lcd_put(mapButton(t3));
	
	mydt->year = 1000*mapIntVal(t0) + 100*mapIntVal(t1) +
	10*mapIntVal(t2) + mapIntVal(t3);
}