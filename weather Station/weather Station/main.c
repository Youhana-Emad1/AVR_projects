#ifndef F_CPU
#define F_CPU 1600000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/lcd.h"

void adc_init() {
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch) {
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xF8)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}

void pwm_init() {
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01) | (1 << CS00);
	DDRB |= (1 << PB3);
}

void set_motor_speed(uint8_t duty_cycle) {
	OCR0 = (duty_cycle * 255) / 100;
}

int main() {
	DDRB = 0xFF;
	uint16_t adc_result0;
	int temp;
	char buffer[10];
	uint8_t duty_cycle = 0;

	adc_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	pwm_init();

	lcd_clrscr();
	lcd_gotoxy(0, 0);

	_delay_ms(50);

	while (1) {
		adc_result0 = adc_read(0);
		temp = adc_result0 / 2.01;

		lcd_clrscr();
		lcd_gotoxy(0, 0);
		itoa(temp, buffer, 10);
		lcd_puts("Temp=");
		lcd_puts(buffer);
		lcd_gotoxy(7, 0);
		lcd_puts("C");

		if (temp >= 20 && temp < 25) {
			duty_cycle = 50;
			lcd_gotoxy(0, 1);
			lcd_puts("Fan ON 50%");
			} else if (temp >= 25 && temp < 30) {
			duty_cycle = 70;
			lcd_gotoxy(0, 1);
			lcd_puts("Fan ON 70%");
			} else if (temp >= 30 && temp < 35) {
			duty_cycle = 90;
			lcd_gotoxy(0, 1);
			lcd_puts("Fan ON 90%");
			} else if (temp >= 35 && temp <= 40) {
			duty_cycle = 100;
			lcd_gotoxy(0, 1);
			lcd_puts("Fan ON 100%");
			} else {
			duty_cycle = 0;
			lcd_gotoxy(0, 1);
			lcd_puts("Fan OFF 0%");
		}

		set_motor_speed(duty_cycle);

		_delay_ms(1000);
	}
}
