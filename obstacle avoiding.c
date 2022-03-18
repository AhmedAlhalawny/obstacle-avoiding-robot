/*
 * obstacle_avoiding.c
 *
 * Created: 3/13/2022 11:43:22 PM
 *  Author: Ahmed ALhalawany
 */ 


#include <avr/io.h>
#include "obstacle_avoiding.h"
#include <util/delay.h>
#define F_CPU 16000000UL
#include "bit_math.h"


float distanc;
int angle=0;





int main(void)
{
	int x[16];
	lcd_init(LCD_DISP_ON);
  
servo_init();
ultrasonic_init_ISR();
sei();
    while(1)
    {
		
			
			servo_mov(3);
			ultrsonic_update();
			distanc=ultrasonic_get_value();
			_delay_ms(50);
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("DIST:");
			lcd_gotoxy(5,0);
			lcd_puts(itoa((uint16)distanc,x,10));
			lcd_puts("mm");
			
			if (distanc==0)
			{
				lcd_gotoxy(5,0);
				lcd_puts("out of range");
			}
			_delay_ms(500);
			servo_mov(9.375);
			ultrsonic_update();
			distanc=ultrasonic_get_value();
			_delay_ms(50);
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("DIST:");
			lcd_gotoxy(5,0);
			lcd_puts(itoa((uint16)distanc,x,10));
			lcd_puts("mm");
			
			if (distanc==0)
			{
				lcd_gotoxy(5,0);
				lcd_puts("out of range");
			}
			_delay_ms(500);
			servo_mov(15);
			ultrsonic_update();
			distanc=ultrasonic_get_value();
			_delay_ms(50);
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("DIST:");
			lcd_gotoxy(5,0);
			lcd_puts(itoa((uint16)distanc,x,10));
			lcd_puts("mm");
			
			if (distanc==0)
			{
				lcd_gotoxy(5,0);
				lcd_puts("out of range");
			}
			_delay_ms(500);
			
			
			

			



/*
for (angle;angle<=180;angle++)
{
	servo_mov(angle);
	_delay_ms(20);
}
for (angle;angle>0;angle--)
{
	servo_mov(angle);
	_delay_ms(20);
}*/

	
    }
}