/*
 * UltrSonic_Driv.c
 *
 * Created: 3/6/2022 5:15:12 PM
 *  Author: Ahmed ALhalawany
 */ 
#include "UltraSonic_Drive.h"
#include "bit_math.h"
#include <util/delay.h>





void ultrasonic_init_ISR(void)            //write ISR FOR external interrupt TIMER0_CAPT_vect
{
      volatile int *Timerov=&TimerOverflow;     //timer 1 overflow flags
      volatile uint8  *ICcount=&IC_count;      // input caption counts
      timer1_inti(ICU,pre_scal_1);
      timer1_ICU_ES(rising);
	  timer1_ICU_IE();
	  *ICcount=0;
	  *Timerov=0; 
	  set_bit(DDRB,5);
	  set_bit(PORTB,5);
	  _delay_us(10);
	  clear_bit(PORTB,5);

}
void ultrsonic_update()
{
	set_bit(DDRB,5);
	set_bit(PORTB,5);
	_delay_us(10);
	clear_bit(PORTB,5);
}

uint16 ultrasonic_get_value(void)
{
	float *t_on=&Ton;
	float distance=0;
	distance=(17150)*(*t_on)*10;              //distance in mm
	if ((*t_on)>=0.038)
	{
		return 0;
	}else
	return distance;
	
}
ISR(TIMER1_OVF_vect)
{

	*TimerOverflow++;
}

ISR(TIMER1_CAPT_vect)
{ volatile uint8  *ICcount=&IC_count;      // input caption counts
	*IC_count++;
	int echo_freq;
	double pireod;
	float *t_on=&Ton;
	volatile double *t_1=&t1;
	volatile double *t_2=&t2;
	
	if (*ICcount==1)
	{
	  *TimerOverflow=0;
	  TCNT1=0; 
	  timer1_ICU_ES(falling);
	
	}else if(*ICcount==2)
	{
		*t_2=(ICR1+(65536*(*TimerOverflow)));      //calculate timer overflow times 16bit timer value + t2;
		 timer1_ICU_ES(rising);
		*IC_count=0;
		pireod=*t_2;
		echo_freq=F_CPU/(float)pireod;                   //calculate echo back frequancy which is Ton we consider it full pulse with 100% duty
		*t_on=1/(float)echo_freq;                 // calculate time in sec from frequancy
		
	
	}

	
}




 uint16 ultrasonic_read(void) // this function portb,bin5 as pulse trigger & timer1 as icu and return distance if out of range return 0 
{
	 sei();
	 int *Overflow=&TimerOverflow;
	 unsigned int period=0;      
	 double echo_freq=0;
	 float time=0;
	 float distance=0;
	 double count;
    set_bit(DDRB,5);
    set_bit(PORTB,5);
    _delay_us(10);
    clear_bit(PORTB,5);
    TIMSK = (1 << TOIE1);	        //Enable Timer1 overflow interrupts
	timer1_inti(ICU,pre_scal_1);
    timer1_ICU_ES(rising);
    while(!(TIFR&(1<<ICF1)));      //wait for rising edge
	TCNT1=0;
	TIFR|=(1<<ICF1);              //clear input capture flag
	TIFR|=(1<<TOV1);              //clear timer overflow flag
	*Overflow=0;
	timer1_ICU_ES(falling);
	while(!(TIFR&(1<<ICF1)));       //wait for falling edge
	period=ICR1;
	TIFR|=(1<<ICF1);               //clear input capture flag
	TIFR|=(1<<TOV1);              //clear timer overflow flag
	timer1_dis();
	TIMSK = ~(1 << TOIE1);	        //Enable Timer1 overflow interrupts
	cli();
	count=(period+(65536*(*Overflow))); //calculate timer overflow times 16bit timer value + period 
	echo_freq=F_CPU/count;                   //calculate echo back frequancy which is Ton we consider it full pulse with 100% duty
	time=1/(float)echo_freq;                 // calculate time in sec from frequancy 
	distance=(17150)*(time)*10;              //distance in mm
    if (time>=0.038)
	{
		return 0;
	}else 
	return distance;
	
}






/////////////////////////////////////////

