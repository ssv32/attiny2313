/*
 * guessTheNumber.cpp
 * Игра угадай число для МК attiny2313
 * Кнопки: 0 1 2 3 4 5 6 7 8
 * Светодиоды: 0 1 2 3 4 5 6 
 * Правила:
 * - загорелись все светодиоды (значит все диоды работают),
 * - число МК (микроконтроллер) загадал от 1 до 5, 
 * - игрок нажимает цифры от 1 до 5 (это кнопки с такими же номерами),
 * - при нажатии на кнопку вначале перед проверкой загорается диод выбранной кнопки, 
 * - если игрок угадал число загаданное МК то загорается светодиоды в одну потом в другую стороны,
 * - если игрок не угадал число, то все диоды загораются 2раза и потом загорается число, загаданное МК.
 * Created: 02.06.2019 21:45:15
 * Author : ssv
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int showTrack( int right ){ // зажечь дорожку 1 в одну сторону, 0 в другую
	int i = 0;
	int j =0;
	
	while(i < 8){
		if (right == 1){
			j = i;
		}else{
			j = 7-i;
		}
		PORTD = 1 << j;
		_delay_ms(200);
		PORTD = 0b00000000;
		i++;	
	}
	return 0;
}

int showDiod(int nDiod){ // зажечь диод цифры (вывести цифру от 1 до 5)
	PORTD =  0b00000000;
	_delay_ms(300);
	PORTD = 1 << nDiod;
	_delay_ms(300);
	PORTD =  0b00000000;
	return 0;
}

int showBadResult(int nDiod){ // отображение когда не угадали число
	PORTD =  0b00000000;
	_delay_ms(300);
	PORTD = 0b11111111;
	_delay_ms(300);
	PORTD =  0b00000000;
	_delay_ms(300);
	PORTD =  0b11111111;
	_delay_ms(300);
	PORTD =  0b00000000;
	_delay_ms(300);
	PORTD =  0b11111111;
	_delay_ms(300);
	
	showDiod(nDiod);
	
	return 0;
}

int a = 1;

int main(void)
{
	DDRD=0xFF; // порты D на вывод // будет 1 горит, 0 - не горит
	
	//PORTB=0b00000000; // притягиваем 8 ножек к 0
	PORTB=0b01111111; // сделать +
	DDRB=0b00000000; // порты B на вход
	
	PORTD=0b11111111;
	showTrack(1);

    while (1) 
    {
			
		if (PINB & 0b00000010){ // выбрана цифра 1
			_delay_ms(50);
			showDiod(1);
			if (a == 1){
				showTrack(1);
				showTrack(0);
			}else{
				showBadResult(a);
			}
		}
		
		if (PINB & 0b00000100){ // выбрана цифра 2
			_delay_ms(50);
			showDiod(2);
			if (a == 2){
				showTrack(1);
				showTrack(0);
			}else{
				showBadResult(a);
			}
		}
		
		if (PINB & 0b00001000){ //выбрана цифра 3 
			_delay_ms(50);
			showDiod(3);
			if (a == 3){
				showTrack(1);
				showTrack(0);
			}else{
				showBadResult(a);
			}
		}
		
		if (PINB & 0b00010000){ //выбрана цифра 4
			_delay_ms(50);
			showDiod(4);
			if (a == 4){
				showTrack(1);
				showTrack(0);
			}else{
				showBadResult(a);
			}
		}
		
		if (PINB & 0b00100000){ //выбрана цифра 5
			_delay_ms(50);
			showDiod(5);
			if (a == 5){
				showTrack(1);
				showTrack(0);
			}else{
				showBadResult(a);
			}
		}
		
		// число перебирается от 1 до 5 до тех пор, пока не нажмётся кнопка, 
		// всё равно что генерировать произвольное число но без подключение доп. библиотек 
		a++; 
		if (a == 6){
			a = 1;
		}
    }
}		

