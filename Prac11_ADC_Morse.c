/*
    Example code written during the Lab Session given only as reference, 
    Please update the function to your own implementation in order to compile.
*/
#include <avr\io.h>
#include "UART.h"

// ADC1, VRef = Vcc, 10 bits
void ADC_Init()
{
	ADMUX= (1<<REFS0)| (1<<MUX0);// Vcc, ADC1
	ADCSRA = (1<<ADEN)| (7<<ADPS0); // ADC On, PS=128
	ADCSRB = 0;	
}


uint16_t ADC_read()
{
	ADCSRA |= 1<<ADSC; // Start conversion
	while ( ADCSRA&(1<<ADSC) )
		; // Wait for conversion
	return ADC; // Return conversion
}

// ADC Test example
int main(void)
{
	uint16_t value;	
	char str[15];
	
	UART_Ini(0,115200,8,0,1);
	ADC_Init();
	UART_clrscr(0);
	UART_getchar(0);

	while(1)
	{
		value = ADC_read();
		for(uint8_t i=0; i < (value>>4); i++)
		{
			UART_putchar(0,'.');
		}
		itoa(value,str,10);
		UART_puts(0,str);
		UART_puts(0,"\n\r");
	}

	return 1;
}

