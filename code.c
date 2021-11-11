#define F_CPU 1000000UL
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTB6
#define EN eS_PORTB7

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


void Adcinit()
{ 
	DDRC= 0b00000000;     // make port c as input
	ADMUX=0b01000100;      // using Avcc with external capacitor at vref and 10bit
	//ADMUX=0b01100000;
	ADCSRA = (1<<ADEN);     
	
}

float AdcRead(int a)
{
	unsigned short x;
	//ADMUX=0b01100000 + a;
	ADMUX=0b01000000 + a;
	ADCSRA = ADCSRA|(1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	//x=ADCH;
	x = ADC;
	return x ;
}

float y_axis,b;
int i;
char *n = "weight(g)";
int main(void)
{
	DDRB=0xFF;
	DDRD=0xFF;
	Adcinit();
	Lcd4_Init();
	 while (1)
	 {
		 b = 0;
		 for (i = 1; i < 1000; ++i)
		 {
			 y_axis=AdcRead(4);
			 y_axis=(y_axis*11 -2939);
			 _delay_ms(1);
			 b = b + y_axis  ;
		 }
		 b = ((b/999)-116);
		 char *y="00000";
		 itoa(b,y,10);
		 Lcd4_Clear();
		 Lcd4_Set_Cursor(1,0);
		 Lcd4_Write_String(n);
		 Lcd4_Set_Cursor(2,0);
		 Lcd4_Write_String(y);
		 _delay_ms(1000);
	 }
		 
		 
		 
}




















